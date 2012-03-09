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

// technically signed and unsigned types are incompatible
// but I'll assume every machine uses two's complement
// under this assumption, since hton/ntoh just swaps bytes
// unsigned and signed types are the same

#define FORCE_TYPE(F, T, FUNCTION_TYPE) \
    inline T F(T x) { return (T) F((FUNCTION_TYPE) x); }

FORCE_TYPE(htonl, int32_t, uint32_t)
FORCE_TYPE(ntohl, int32_t, uint32_t)
FORCE_TYPE(htons, int16_t, uint16_t)
FORCE_TYPE(ntohs, int16_t, uint16_t)

template<typename T, T (*hton)(T)>
void pack_template(char **buffer, T x)
{
    *(T *)(*buffer) = hton(x);
    *buffer += sizeof(T);
}

template<typename T, T (*ntoh)(T)>
T unpack_template(const char **buffer)
{
    T x;
    x = ntoh(*(T *)(*buffer));
    *buffer += sizeof(T);
    return x;
}

template<typename T>
inline T identity(T x) { return x; }

#define GENERATE_FUNCTIONS(T, HTON, NTOH) \
    template<> \
    void NetSerialize::pack<T>(char **buffer, T x) \
    { \
        pack_template<T, (HTON)>(buffer, x); \
    } \
    template<> \
    T NetSerialize::unpack<T>(const char **buffer) \
    { \
        return unpack_template<T, (NTOH)>(buffer); \
    }

GENERATE_FUNCTIONS(uint32_t, htonl, ntohl)
GENERATE_FUNCTIONS(int32_t, htonl, ntohl)
GENERATE_FUNCTIONS(uint16_t, htons, ntohs)
GENERATE_FUNCTIONS(int16_t, htons, ntohs)
GENERATE_FUNCTIONS(uint8_t, identity, identity)
