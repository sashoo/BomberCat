#ifndef NETCHANNEL_HPP
#define NETCHANNEL_HPP

class NetChannel;

#include "NetConnection.hpp"

#include "GArea.hpp"

/* Packet structure outline
 *  
 * channel_id (2 bytes) - uniquely identifies channel object
 * channel_action (1 byte) - see enum ChannelAction
 * channel_type (2 bytes) - OPEN packets only
 * channel_data (X bytes) - behaviour defined by channel itself
 */

enum { 
    HEADER_SIZE = 2 + 1,
    ACK_HEADER_SIZE = HEADER_SIZE + 2
};
enum { MAX_PACKET_SIZE = 512 };;

enum ObjectType {
    CONTROL = 0, // control channel
    GAREA = 1, // GArea

    UNKNOWN = 0xFFFF,
};

enum ChannelAction {
    CHANNEL_OPEN = 0,
    CHANNEL_ACK = 1,
    CHANNEL_DATA = 2,
    CHANNEL_CLOSE = 3,
};

typedef int16_t channel_id_t;

// functions prefixed with "Server" will be executed on server only
// (and vice versa for the ones prefixed with "Client")

class NetChannel {
protected:
    NetConnection * const nc;

    // used on server only, if true, can be used to send data
    bool channel_acked; 

    bool pending_delete; 

public:
    NetChannel(NetConnection *, channel_id_t, enum ObjectType);
    virtual ~NetChannel();
    
    virtual void Loop(void);

    static NetChannel * ClientCreateChannel(NetConnection *nc, channel_id_t channel_id, enum ObjectType);

    virtual int ServerHandleData(const char *, size_t) = 0;
    virtual int ClientHandleData(const char *, size_t) = 0;

    int ServerAckChannel(void);
    virtual int ServerSendInitialPacket() = 0; 
    int ClientSendAck();

    size_t PrepareOpenPacket(char *);
    size_t PrepareAckPacket(char *);
    size_t PrepareDataPacket(char *);
    size_t PrepareClosePacket(char *);

    const enum ObjectType ObjectType;
    const channel_id_t channel_id;
};

class NetChannel_GArea : public NetChannel {
protected:
    GArea * const ga;
    uint32_t lastUpdate;
public:
    NetChannel_GArea(NetConnection *, channel_id_t, GArea *); 

    virtual int ServerHandleData(const char *, size_t);
    virtual int ClientHandleData(const char *, size_t);
    
    virtual int ServerSendInitialPacket();

    int ServerSendUpdate(void);
    size_t DumpData(char *buffer);

    virtual void Loop(void);
};

#endif
