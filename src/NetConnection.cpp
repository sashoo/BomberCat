#include "NetConnection.hpp"
    
const char NetConnection::magic_header[] = {0x30, 0xd5, 0x30, 0xe9, 0x30, 0xf3, 0x30, 0xc9, 0x30, 0xfc, 0x30, 0xeb, 0x30, 0xfb, 0x30, 0xb9, 0x30, 0xab, 0x30, 0xfc, 0x30, 0xec, 0x30, 0xc3, 0, 0};
    
bool NetConnection::StartsWithMagicHeader(const char *buffer, size_t size)
{
    if (size < sizeof(magic_header)) return false;

    return memcmp(buffer, magic_header, sizeof(magic_header)) == 0;
}

bool NetConnection::ShouldAcceptSyn(const char *buffer, size_t size)
{
    return NetConnection::StartsWithMagicHeader(buffer, size);
}

NetConnection::NetConnection(UDPSocket *socket, const struct sockaddr_storage *sa, socklen_t sa_len)
    : app(socket->app),
      socket(socket),
      game(socket->game),
      addr(*sa),
      addr_len(sa_len),
      is_server(socket->is_listening)
{
    if (socket->is_listening) {
        conn_status = AWAITING_SYN; 
    } else {
        SendSyn();
    }

    for (int i = 0; i < MAX_CHANNELS; i++) {
        channels[i] = NULL;
    }
}   

NetConnection::~NetConnection()
{
    for (int i = 0; i < MAX_CHANNELS; i++) {
        if (channels[i]) delete channels[i];
    }   
}

int NetConnection::HandlePacket(const char *buffer, size_t size)
{
    app->Log << "handling packet from " << addr << " status " << conn_status << std::endl;

    switch (conn_status) {
    case AWAITING_SYN:
        return HandleSyn(buffer, size);
    case SYN_SENT:
        return HandleSynAck(buffer, size); 
    case SYNACK_SENT:

        if (StartsWithMagicHeader(buffer, size)) {
            return HandleAck(buffer, size);
        } else {
            // since we ACK'ed client SYN, we're willing to receive data
            return HandleData(buffer, size);
        }
        break;
    case OPEN:
        return HandleData(buffer, size);
        break;
    case CLOSED:
    default:
        return -1;
        break;
    }

    return 0;
}

int NetConnection::SendPacket(const char *buffer, size_t size)
{
    return this->socket->SendPacket(buffer, size, &addr, addr_len);
}

int NetConnection::SendSyn(void)
{
    this->rnd = rand();
    uint32_t rnd = htonl(this->rnd);
    char buffer[sizeof(magic_header) + sizeof(rnd)];

    memcpy(buffer, magic_header, sizeof(magic_header));
    memcpy(buffer + sizeof(magic_header), &rnd, sizeof(rnd));

    app->Log << "sending SYN with number " << this->rnd << std::endl;

    conn_status = SYN_SENT;
    return SendPacket(buffer, sizeof(buffer)); 
}

int NetConnection::SendSynAck(void)
{
    this->rnd++;
    uint32_t rnd = htonl(this->rnd);
    char buffer[sizeof(magic_header) + sizeof(rnd)];

    memcpy(buffer, magic_header, sizeof(magic_header));
    memcpy(buffer + sizeof(magic_header), &rnd, sizeof(rnd));
    
    conn_status = SYNACK_SENT;
    return SendPacket(buffer, sizeof(buffer)); 
}

int NetConnection::SendAck(void)
{
    this->rnd++;
    uint32_t rnd = htonl(this->rnd);
    char buffer[sizeof(magic_header) + sizeof(rnd)];

    memcpy(buffer, magic_header, sizeof(magic_header));
    memcpy(buffer + sizeof(magic_header), &rnd, sizeof(rnd));
    
    conn_status = OPEN;
    app->Log << "connection to " << addr << " is now open" << std::endl;
    return SendPacket(buffer, sizeof(buffer)); 
}

// on server's side
int NetConnection::HandleSyn(const char *buffer, size_t size)
{ 
    if (!StartsWithMagicHeader(buffer, size)) return -1;

    buffer += sizeof(magic_header);
    size -= sizeof(magic_header);

    if (size < sizeof(uint32_t)) return -1;

    rnd = ntohl(*(uint32_t *) buffer);

    return SendSynAck();
}

// on client's side
int NetConnection::HandleSynAck(const char *buffer, size_t size)
{ 
    if (!StartsWithMagicHeader(buffer, size)) return -1;

    buffer += sizeof(magic_header);
    size -= sizeof(magic_header);

    if (size < sizeof(uint32_t)) return -1;

    rnd++;
    if (rnd != ntohl(*(uint32_t *) buffer)) {
        return -1;
    }

    return SendAck();
}

// on server's side again
int NetConnection::HandleAck(const char *buffer, size_t size)
{
    if (!StartsWithMagicHeader(buffer, size)) return -1;

    buffer += sizeof(magic_header);
    size -= sizeof(magic_header);

    if (size < sizeof(uint32_t)) return -1;

    rnd++;
    if (rnd != ntohl(*(uint32_t *) buffer)) {
        return -1;
    }

    conn_status = OPEN;
    app->Log << "connection to " << addr << " is now open" << std::endl;

    OpenChannels();

    return 0;
}

int NetConnection::HandleData(const char *buffer, size_t size)
{
    int16_t channel_id;
    int8_t channel_action;

    size_t index = 0;

    if (size < sizeof(channel_id) + sizeof(channel_action)) {
        return -1;
    }

    channel_id = ntohs(*(int16_t *) (buffer + index));
    index += sizeof(channel_id);

    // there is no byte order for a single byte
    channel_action = *(int8_t *) (buffer + index);
    index += sizeof(channel_action);

    if (channel_id >= MAX_CHANNELS || channel_id < 0) return -1;

    NetChannel *ch = channels[channel_id];
    if (ch == NULL) {
        // no such channel (yet)
        if (channel_action == CHANNEL_OPEN && !is_server) {
            // for now channels can be created only by server
            enum ObjectType object_type = (enum ObjectType)ntohs(*(uint16_t*) (buffer + index)); 
            index += sizeof(uint16_t);

            ch = NetChannel::ClientCreateChannel(this, channel_id, object_type);
            if (ch != NULL) {
                AddChannel(ch); 
                if (size > index) {
                    ch->ClientHandleData(buffer + index, size - index);
                }
                ch->ClientSendAck();
            } else {
                app->Log << "packet with invalid ObjectType (" << object_type << ") has been received" << std::endl;
            }
        } else {
            return -1;
        }
    } else {
        if (is_server) {
            switch (channel_action) {
            case CHANNEL_OPEN:
                // client-initiated open is not supported
                return -1; 
            case CHANNEL_ACK:
                return ch->ServerAckChannel();
            case CHANNEL_DATA:
                return ch->ServerHandleData(buffer + index, size - index);
            case CHANNEL_CLOSE:
                // client-iniated close is not supported
                return -1;
            }
        } else {
            switch (channel_action) {
            case CHANNEL_OPEN:
                // already open, ignore
                return 0; 
            case CHANNEL_ACK:
                // ACK isn't meant to be sent by server
                return -1;
            case CHANNEL_DATA:
                return ch->ClientHandleData(buffer + index, size - index);
            case CHANNEL_CLOSE:
                // TODO implement channel close
                return -1;
            }
        }
    }

    return 0;
}

void NetConnection::OpenChannels(void)
{
    if (!is_server) return;
    int i;

    // 1. GArea
    i = GetFreeChannelIdx();
    if (i >= 0) {
        GArea *ga = game->GetGArea();
        AddChannel(new NetChannel_GArea(this, i, ga));
    }
    
    for (active_channels_t::iterator it = active_channels.begin(); it != active_channels.end(); it++) {
        (*it)->ServerSendInitialPacket();
    }
}

int NetConnection::GetFreeChannelIdx(void)
{
    for (int i = 0; i < MAX_CHANNELS; i++) {
        if (channels[i] == NULL) return i;
    }
    return -1;
}

NetChannel * NetConnection::AddChannel(NetChannel *channel)
{
    int i = channel->channel_id;
    if (i < 0) {
        delete channel;
        return NULL;
    }
    
    channels[i] = channel;
    active_channels.push_back(channel);

    return channel;
}

void NetConnection::Loop(void)
{
    active_channels_t::iterator it;

    for (it = active_channels.begin(); it != active_channels.end(); it++) {
        (*it)->Loop();
    }
}
