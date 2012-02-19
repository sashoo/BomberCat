#ifndef NETCHANNEL_HPP
#define NETCHANNEL_HPP

enum ObjectType {
   GAREA
};

class NetChannel {
protected:
    NetChannel();
    ~NetChannel();

    virtual int HandlePacketServer(const char *, size_t);
public:
    static NetChannel * GetNetChannel(enum ObjectType);
};

class NetChannel_GArea : NetChannel {
     
};

#endif
