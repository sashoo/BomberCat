#ifndef NetConnection_HPP
#define NetConnection_HPP

class NetConnection;

#include <cstdlib>

#include "UDPSocket.hpp"
#include "NetChannel.hpp"
#include "Srand.hpp"

class NetConnection {
public:
    MirageApp * const app;
    UDPSocket * const socket;
    StateGame * const game;
    const sockaddr_storage addr;
    const socklen_t addr_len;

    // true if server -> client connection
    const bool is_server;

    static const int MAX_CHANNELS = 1024;
    NetChannel *channels[MAX_CHANNELS];

    enum { // parody on TCP
        AWAITING_SYN, // default state on server
        SYN_SENT, 
        SYNACK_SENT, 
        OPEN,
        CLOSED
    } conn_status;
    uint32_t rnd; // random value for handshake
    
    NetConnection(UDPSocket *, const struct sockaddr_storage *, socklen_t);

    int HandlePacket(const char *buffer, size_t size);
    int SendPacket(const char *buffer, size_t size);

    int SendSyn(void);
    int SendSynAck(void);
    int SendAck(void);

    int HandleSyn(const char *buffer, size_t size);
    int HandleSynAck(const char *buffer, size_t size);
    int HandleAck(const char *buffer, size_t size);

    int HandleData(const char *buffer, size_t size);

    void OnLoop(void);

    const static char magic_header[];
    static bool StartsWithMagicHeader(const char *buffer, size_t size);
    static bool ShouldAcceptSyn(const char *buffer, size_t size);
};

#endif
