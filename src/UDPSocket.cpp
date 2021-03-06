#include "UDPSocket.hpp"

#ifdef _WIN32
#ifdef errno
#undef errno
#endif
#define errno (WSAGetLastError())
#endif

bool operator < (const struct sockaddr_storage &a, const struct sockaddr_storage &b) {
    if (a.ss_family != b.ss_family) {
        // unlikely enough, though
        return a.ss_family < b.ss_family;
    } else {
        size_t n;

        switch (a.ss_family) {
        case AF_INET:
            n = sizeof(struct sockaddr_in);
            break;
        case AF_INET6:
            n = sizeof(struct sockaddr_in6);
            break;
        default:
            n = sizeof(struct sockaddr_storage);
            break;
        }
        return memcmp(&a, &b, n) < 0;
    }
}



std::ostream& operator << (std::ostream &o, const sockaddr_storage &x)
{
    // we're losing const here
    // thank you, Windows
    if (x.ss_family == AF_INET) {
        char buffer[INET_ADDRSTRLEN];
        struct sockaddr_in *s = (struct sockaddr_in *)&x;

        if (inet_ntop(x.ss_family, &s->sin_addr, buffer, sizeof(buffer)) != NULL) {
            return o << buffer << ":" << ntohs(s->sin_port);
        }
    } else if (x.ss_family == AF_INET6) {
        char buffer[INET6_ADDRSTRLEN];
        struct sockaddr_in6 *s = (struct sockaddr_in6 *)&x;

        if (inet_ntop(x.ss_family, &s->sin6_addr, buffer, sizeof(buffer)) != NULL) {
            return o << "[" << buffer << "]:" << ntohs(s->sin6_port);
        }         
    }

    return o << "(unprintable address)";
}

UDPSocket::UDPSocket(StateGame *game, MirageApp *app)
    : game(game),
      app(app)
{
#ifdef _WIN32
    fd = INVALID_SOCKET;
    InitWinsock();
#else
    fd = -1;
#endif 
}

UDPSocket::~UDPSocket()
{
    CloseSocket();
}

int UDPSocket::Init(const struct addrinfo *ai)
{
    CloseSocket();

    // 1. Create a socket 
    fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
#ifdef _WIN32
    if (fd == INVALID_SOCKET)
#else 
    if (fd < 0)
#endif
    {   
        app->Log << "socket() failed: " << errno << std::endl;
        return -1; 
    }   
    
    // 2. Put it into non-blocking mode
#ifdef _WIN32
    {
        u_long arg = 1;
        ioctlsocket(fd, FIONBIO, &arg);
    }
#else
    {
        int opts;
        opts = fcntl(fd, F_GETFL, 0);
        opts |= O_NONBLOCK;
        fcntl(fd, F_SETFL, opts);
    }
#endif

    return 0;
}

int UDPSocket::Listen(const char *host, const char *port)
{
    struct addrinfo *result;
    struct addrinfo hints;
    int error;

    FillHints(&hints);

    error = getaddrinfo(host, port, &hints, &result);

    if (error != 0 || result == NULL) {
        app->Log << "getaddrinfo() failed: " << error << std::endl;
        return -1;
    }
    
    error = Init(result);
    if (error < 0) {
        return error;
    }
    app->Log << "binding to " << *(struct sockaddr_storage *) result->ai_addr << "..." << std::endl;
    error = bind(fd, result->ai_addr, result->ai_addrlen);

    int bind_errno = errno;

    freeaddrinfo(result);

#ifdef _WIN32
    if (error == SOCKET_ERROR)
#else
    if (error < 0)
#endif
    {
        app->Log << "bind() error: " << bind_errno << std::endl;
        return -1;
    }

    app->Log << "Bound!" << std::endl;

    is_listening = true;
    return 0;
}

int UDPSocket::Connect(const char *host, const char *port)
{
    struct addrinfo *result;
    struct addrinfo hints;
    struct sockaddr_storage sockaddr;
    int error;

    FillHints(&hints);

    error = getaddrinfo(host, port, &hints, &result);

    if (error != 0 || result == NULL) {
        app->Log << "getaddrinfo() error : " << error << std::endl;
        return -1;
    }
    
    error = Init(result);
    if (error < 0) {
        return error;
    }
    app->Log << "connecting to " << *(struct sockaddr_storage *) result->ai_addr << std::endl;
    error = connect(fd, result->ai_addr, result->ai_addrlen);
    int connect_errno = errno;
    
    memset(&sockaddr, 0, sizeof(sockaddr));
    memcpy(&sockaddr, result->ai_addr, result->ai_addrlen);

    freeaddrinfo(result);
#ifdef _WIN32
    if (error == SOCKET_ERROR)
#else
    if (error < 0)
#endif
    {
        app->Log << "connect() failed: " << connect_errno << std::endl;
        return -1;
    }

    is_listening = false;

    connections.insert(std::make_pair(sockaddr, NetConnection(this, &sockaddr, (socklen_t) 0)));

    return 0;
}

void UDPSocket::Loop(void)
{
    char buffer[1024];
    int received;
    struct sockaddr_storage address;
    socklen_t address_len;
    address_len = sizeof(address);

    if (IsClosed()) return;
    
    while (true) {
        if (is_listening) {
            received = recvfrom(fd, buffer, sizeof(buffer), 0, (struct sockaddr *) &address, &address_len);
        } else {
            received = recv(fd, buffer, sizeof(buffer), 0);
        }

#ifdef _WIN32
        if (received == SOCKET_ERROR) 
#else 
        if (received < 0) 
#endif
        {

#ifdef _WIN32
            if (errno == WSAEWOULDBLOCK) 
#else
            if (errno == EWOULDBLOCK || errno == EAGAIN)
#endif
            {
                // nothing to read yet
                break;
            }
            app->Log << "recv() failed: " << errno << std::endl;

            if (errno == ECONNREFUSED && !is_listening) {
                app->Log << "Connection refused." << std::endl;
            } else {
                // TODO more errors
            }
            CloseSocket();
            return;
        }


        if (HandlePacket(buffer, received, &address, address_len) < 0) {
            app->Log << "invalid packet received from " << address << std::endl;
            if (!is_listening) {
                CloseSocket();
            }
            return;
        }
    }

    connections_t::iterator it;
    for (it = connections.begin(); it != connections.end(); it++) {
        it->second.Loop();
    }
}

int UDPSocket::HandlePacket(char *buffer, size_t size, struct sockaddr_storage *address, socklen_t address_len)
{
    //connections_t::iterator it;
    NetConnection *p;
    connections_t::iterator it;

    if (is_listening) {
        it = connections.find(*address);
        if (it == connections.end()) {
            if (NetConnection::ShouldAcceptSyn(buffer, size)) {
                it = connections.insert(std::make_pair(*address, NetConnection(this, address, address_len))).first;
            } else {
                return -1;
            }
        } 
    } else {
        // as of clients, there's only one connection in the map
        // under arbitrary key
        it = connections.begin();
    }
    p = &it->second;

    int ret = p->HandlePacket(buffer, size);
    if (is_listening && ret) {
        app->Log << "an error has occured during handling packets from " << *address << "\n";
        connections.erase(it); 
        return 0;
    } else {
        return ret;
    }
}

int UDPSocket::SendPacket(const char *buffer, size_t size, const struct sockaddr_storage *address, socklen_t address_len)
{   
    int error;

    if (is_listening) {
        error = sendto(fd, buffer, size, 0, (const struct sockaddr *) address, address_len);
    } else {
        error = send(fd, buffer, size, 0);
    }

#ifdef _WIN32
    if (error == SOCKET_ERROR)
#else
    if (error < 0)
#endif
    {
        return -1;
    }

    return 0;
}

void UDPSocket::CloseSocket(void)
{
    if (!IsClosed()) {
        connections.clear();

#ifdef _WIN32
        if (fd != INVALID_SOCKET) {
            closesocket(fd);
            fd = INVALID_SOCKET;
        }
#else
        if (fd >= 0) {
            close(fd);
            fd = -1;
        }
#endif
    }
}

bool UDPSocket::IsClosed(void)
{
#ifdef _WIN32
    return (fd == INVALID_SOCKET);
#else
    return (fd < 0);
#endif
}   

void UDPSocket::FillHints(struct addrinfo *ai)
{
    memset(ai, 0, sizeof(*ai));
    ai->ai_family = AF_UNSPEC;
    ai->ai_socktype = SOCK_DGRAM;
    ai->ai_protocol = 0;
    if (is_listening) {
        ai->ai_flags |= AI_PASSIVE;
    }
}

#ifdef _WIN32
int UDPSocket::InitWinsock(void)
{
    static bool already_initialized = false;

    if (!already_initialized) {
        WORD wVersionRequested = MAKEWORD(2, 2);
        WSADATA wsaData;
        
        int error = WSAStartup(wVersionRequested, &wsaData);
        
        if (error) {
            app->Log << "WSAStartup failed: " << error << std::endl;
            return -1;
        } else {
            already_initialized = true;
            return 0;
        }
    }
    return 0;
}
#endif
