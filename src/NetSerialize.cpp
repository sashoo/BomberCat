#include "NetSerialize.hpp"

#ifdef _WIN32
#include <Winsock2.h>

// КОСТЫЛИ BEGIN
// Windows htonl/ntohl accepts u_long (unsigned long) argument
// Other systems - uint32_t (unsigned int)
// despite being almost identical types, they're incompatible
// hence КОСТЫЛИ
inline uint32_t htonl(uint32_t x) { return htonl((u_long) x); }
inline uint32_t ntohl(uint32_t x) { return ntohl((u_long) x); }
// КОСТЫЛИ END

#else
#include <arpa/inet.h>
#endif
template<typename T>
inline T identity(T x) { return x; }

// T - argument type
// CAST_TYPE - unsigned integer type that T can be safely casted to and from
// HTON - host to network byte order conversion function
// NTOH - network to host conversion function
#define GENERATE_FUNCTIONS(T, CAST_TYPE, HTON, NTOH) \
    template<> \
    void NetSerialize::pack<T>(char **buffer, T x) \
    { \
        *(CAST_TYPE *)(*buffer) = HTON((CAST_TYPE) x);\
        *buffer += sizeof(CAST_TYPE); \
    } \
    template<> \
    T NetSerialize::unpack<T>(const char **buffer) \
    { \
        T x; \
        x = (T) NTOH(*(CAST_TYPE *)(*buffer)); \
        *buffer += sizeof(CAST_TYPE); \
        return x; \
    }

GENERATE_FUNCTIONS(uint32_t, uint32_t, htonl, ntohl)
GENERATE_FUNCTIONS(int32_t , uint32_t, htonl, ntohl)

GENERATE_FUNCTIONS(uint16_t, uint16_t, htons, ntohs)
GENERATE_FUNCTIONS(int16_t , uint16_t, htons, ntohs)

GENERATE_FUNCTIONS(uint8_t, uint8_t, identity, identity)
GENERATE_FUNCTIONS(int8_t, uint8_t, identity, identity)

template<>
void NetSerialize::pack<float>(char **buffer, float x)
{
    static_assert(sizeof(float) == sizeof(uint32_t), "unsupported float size");
    NetSerialize::pack<uint32_t>(buffer, *(uint32_t *)&x);
}

template<>
float NetSerialize::unpack<float>(const char **buffer)
{
    static_assert(sizeof(float) == sizeof(uint32_t), "unsupported float size");
    uint32_t y = NetSerialize::unpack<uint32_t>(buffer);
    return *(float *)&y;
}
