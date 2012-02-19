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
    return 0;
}

int NetConnection::HandleData(const char *buffer, size_t size)
{
    int16_t channel_id;
    int8_t channel_action;

    if (size < sizeof(channel_id) + sizeof(channel_action)) {
        return -1;
    }

    channel_id = ntohs(*(int16_t *) buffer);
    buffer += sizeof(channel_id);

    // there is no byte order for a single byte
    channel_action = *(int8_t *) buffer;
    buffer += sizeof(channel_action);

    return 0;
}

void NetConnection::OnLoop(void)
{
    /*if (!is_server) {
        static uint32_t time = 0; 
        uint32_t new_time = app->GetTimeReal(); 

        if (new_time - time > 5000) {
            const char *s = "hello there!\n";
            time = new_time;
            SendPacket(s, strlen(s));
        }
    }*/
}
