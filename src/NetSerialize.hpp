#ifndef NETSERIALIZE_HPP
#define NETSERIALIZE_HPP

#include <stdint.h>

class NetSerialize {
public:
    template <typename T> 
    static void pack(char **buffer, T x);
    template <typename T> 
    static T unpack(const char **buffer);
    
protected:
    NetSerialize() {}

    NetSerialize(const NetSerialize &); // don't implement
    void operator=(const NetSerialize &); // don't implement

};

#endif
