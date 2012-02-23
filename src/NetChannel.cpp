#include "NetChannel.hpp"


NetChannel::NetChannel(NetConnection *nc, channel_id_t channel_id, enum ObjectType ObjectType)
 :nc(nc),
  ObjectType(ObjectType),
  channel_id(channel_id)
   
{
    pending_delete = false;

    if (nc->is_server) {
        channel_acked = false;
    } 
}

NetChannel::~NetChannel()
{

}

void NetChannel::Loop()
{

}

int NetChannel::ServerAckChannel()
{
    channel_acked = true;
    return 0;
}

int NetChannel::ClientSendAck()
{
   char buffer[MAX_PACKET_SIZE];
   size_t bufsize = PrepareAckPacket(buffer); 
    
   return nc->SendPacket(buffer, bufsize);
}

NetChannel * NetChannel::ClientCreateChannel(NetConnection *nc, channel_id_t channel_id, enum ObjectType ObjectType)
{
    if (ObjectType == GAREA) {
        GArea *ga = nc->game->GetGArea();
        return new NetChannel_GArea(nc, channel_id, ga);
    } else {
        return NULL;
    }
}

size_t NetChannel::PrepareOpenPacket(char *buffer)
{
    if (buffer) {
        (*(int16_t *) buffer) = htons(channel_id);
        (*(int8_t *) (buffer + 2)) = (uint8_t) CHANNEL_OPEN;
        (*(uint16_t *) (buffer + 3)) = htons(ObjectType);
    }

    return 2 + 1 + 2;
}

size_t NetChannel::PrepareAckPacket(char *buffer)
{
    if (buffer) {
        (*(int16_t *) buffer) = htons(channel_id);  
        (*(int8_t *) (buffer + 2)) = CHANNEL_ACK;
    }

    return 2 + 1;

}

size_t NetChannel::PrepareDataPacket(char *buffer)
{
    if (buffer) {
        (*(int16_t *) buffer) = htons(channel_id);
        (*(int8_t *) (buffer + 2)) = CHANNEL_DATA;
    }

    return 2 + 1;
}
size_t NetChannel::PrepareClosePacket(char *buffer)
{
    if (buffer) {
        (*(int16_t *) buffer) = htons(channel_id);
        (*(int8_t *) (buffer + 2)) = CHANNEL_CLOSE;
    }

    return 2 + 1;
}

/*
 *
 * CLASS SPECIFIC CHANNELS BELOW 
 *
 */

/*
 * GArea
 */
NetChannel_GArea::NetChannel_GArea(NetConnection *nc, channel_id_t channel_id, GArea *ga)
 :NetChannel::NetChannel(nc, channel_id, GAREA),
  ga(ga)
{
    
}
int NetChannel_GArea::ServerHandleData(const char *, size_t)
{
    return 0;
}

int NetChannel_GArea::ClientHandleData(const char *buffer, size_t size)
{
    size_t bufsize = 0;
    if ((int) size - bufsize < 2 + 2) return -1;
    
    int max_x = ntohs(*(int16_t*)(buffer + bufsize));
    bufsize += 2;
    int max_y = ntohs(*(int16_t*)(buffer + bufsize));
    bufsize += 2;

    if ((size - bufsize) != max_x * max_y * 1) return -1;

    // XXX width and height should be set here,
    // but they're currently private
    
    for (int x = 0; x < max_x; x++) {
        for (int y = 0; y < max_y; y++) {
            ga->SetTileCoord(x, y, buffer[bufsize++]);       
        }
    }
    return 0;
}

size_t NetChannel_GArea::DumpData(char *buffer)
{
    size_t bufsize = 0;

    int max_x = ga->GetWidth(); 
    int max_y = ga->GetHeight();

    *(int16_t*)(buffer + bufsize) = htons(max_x);
    bufsize += 2;
    *(int16_t*)(buffer + bufsize) = htons(max_y);
    bufsize += 2;
    
    for (int x = 0; x < max_x; x++) {
        for (int y = 0; y < max_y; y++) {
            buffer[bufsize++] = (uint8_t) ga->GetTileCoord(x, y);       
        }
    }
    
    return bufsize;
}

int NetChannel_GArea::ServerSendInitialPacket()
{
    char buffer[MAX_PACKET_SIZE];
    size_t bufsize = PrepareOpenPacket(buffer);
    
    bufsize += DumpData(buffer + bufsize);

    return nc->SendPacket(buffer, bufsize);
}

int NetChannel_GArea::ServerSendUpdate()
{
    char buffer[MAX_PACKET_SIZE];
    size_t bufsize = PrepareDataPacket(buffer);
    
    bufsize += DumpData(buffer + bufsize);

    return nc->SendPacket(buffer, bufsize);
}

void NetChannel_GArea::Loop(void)
{
    NetChannel::Loop();

    if (ga->bNetDirty) {
        ServerSendUpdate(); 
        // XXX it should be set at the end of the tick
        // there can be other clients, you know
        ga->bNetDirty = false;
    }
}
