#include "NetConnection.hpp"
    
const char NetConnection::magic_header[] = {0x30, 0xd5, 0x30, 0xe9, 0x30, 0xf3, 0x30, 0xc9, 0x30, 0xfc, 0x30, 0xeb, 0x30, 0xfb, 0x30, 0xb9, 0x30, 0xab, 0x30, 0xfc, 0x30, 0xec, 0x30, 0xc3, 0, 0};
    
bool NetConnection::StartsWithMagicHeader(const char *buffer, size_t size)
{
    if (size < sizeof(magic_header)) return false;

    return memcmp(buffer, magic_header, sizeof(magic_header)) == 0;
}

NetConnection::NetConnection(MirageApp *app, UDPSocket *socket, StateGame *game, const struct sockaddr_storage *sa, socklen_t sa_len)
    : app(app),
      socket(socket),
      game(game),
      addr(*sa),
      addr_len(sa_len)

{
    if (socket->is_listening) {
        conn_status = AWAITING_SYN; 
    } else {
        SendSyn();
        conn_status = SYN_SENT;
    }
}   

int NetConnection::HandlePacket(const char *buffer, size_t size)
{
    app->Log << conn_status << std::endl;

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
    rnd = htonl(rand());
    char buffer[sizeof(magic_header) + sizeof(rnd)];

    memcpy(buffer, magic_header, sizeof(magic_header));
    memcpy(buffer + sizeof(magic_header), &rnd, sizeof(rnd));

    return SendPacket(buffer, sizeof(buffer)); 
}

int NetConnection::SendSynAck(void)
{
    rnd++;
    char buffer[sizeof(magic_header) + sizeof(rnd)];

    memcpy(buffer, magic_header, sizeof(magic_header));
    memcpy(buffer + sizeof(magic_header), &rnd, sizeof(rnd));

    return SendPacket(buffer, sizeof(buffer)); 
}

int NetConnection::SendAck(void)
{
    rnd++;
    char buffer[sizeof(magic_header) + sizeof(rnd)];

    memcpy(buffer, magic_header, sizeof(magic_header));
    memcpy(buffer + sizeof(magic_header), &rnd, sizeof(rnd));

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

    if (rnd + 1 != ntohl(*(uint32_t *) buffer)) {
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

    if (rnd + 1 != ntohl(*(uint32_t *) buffer)) {
        return -1;
    }

    return SendAck();
}

int NetConnection::HandleData(const char *buffer, size_t size)
{
    return 0;
}

void NetConnection::OnLoop(void)
{

}
