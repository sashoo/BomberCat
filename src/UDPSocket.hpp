#ifndef UDPSocket_H
#define UDPSocket_H

#include <map>

extern "C" {
#ifdef _WIN32
#include <winsock2.h>
#include <WS2tcpip.h>

#define EWOULDBLOCK WSAEWOULDBLOCK
#define EAGAIN WSAEWOULDBLOCK
#define ECONNREFUSED WSAECONNREFUSED

#else
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#endif
}

class UDPSocket;

#include "StateGame.hpp"
#include "NetConnection.hpp"

std::ostream& operator << (std::ostream &o, const sockaddr_storage &x);

class UDPSocket {
public:

#ifdef _WIN32
    SOCKET fd;
#else
    int fd;
#endif

    StateGame * const game;
    MirageApp * const app;
    bool is_listening;

    typedef std::map<struct sockaddr_storage, NetConnection> connections_t;
    connections_t connections;
    
    int Init(const struct addrinfo *);

    UDPSocket(StateGame *, MirageApp *);
    ~UDPSocket();

    int Listen(const char *host, const char *port);
    int Connect(const char *host, const char *port);

    int HandlePacket(char *buffer, size_t size, struct sockaddr_storage *address, socklen_t address_len);
    int SendPacket(const char *buffer, size_t size, const struct sockaddr_storage *address, socklen_t address_len);
    void CloseSocket();

    bool IsClosed();

    void Loop(void);

    void FillHints(struct addrinfo *);

};

#endif
