#include "NetChannel.hpp"
#include "NetSerialize.hpp"

NetChannel_GArea::NetChannel_GArea(NetConnection *nc, channel_id_t channel_id, GArea *ga)
 :NetChannel(nc, channel_id, GAREA),
  ga(ga),
  lastUpdate(0)
{ 

}

int NetChannel_GArea::ServerHandleData(const char *, size_t)
{
    return 0;
}

int NetChannel_GArea::ClientHandleData(const char *buffer, size_t size)
{
    const char * const buffer_start = buffer;
    if (size < 4 + 2 + 2) return -1;
    
    uint32_t lastUpdate = NetSerialize::unpack<uint32_t>(&buffer);
    if (this->lastUpdate > lastUpdate) {
        // packet is out of order
        return 0;
    }
    int max_x = NetSerialize::unpack<int16_t>(&buffer);
    int max_y = NetSerialize::unpack<int16_t>(&buffer);

    if ((size - (buffer - buffer_start)) != max_x * max_y * 1) return -1;

    // XXX width and height should be set here,
    // but they're currently private
    
    for (int x = 0; x < max_x; x++) {
        for (int y = 0; y < max_y; y++) {
            ga->SetTileCoord(x, y, NetSerialize::unpack<uint8_t>(&buffer));       
        }
    }

    this->lastUpdate = lastUpdate;
    // XXX insert ACK here

    return 0;
}

size_t NetChannel_GArea::DumpData(char *buffer)
{
    const char * const buffer_start = buffer;

    NetSerialize::pack<uint32_t>(&buffer, nc->app->GetTimeReal());

    int max_x = ga->GetWidth(); 
    int max_y = ga->GetHeight();

    NetSerialize::pack<int16_t>(&buffer, max_x);
    NetSerialize::pack<int16_t>(&buffer, max_y);
    
    for (int x = 0; x < max_x; x++) {
        for (int y = 0; y < max_y; y++) {
            NetSerialize::pack<uint8_t>(&buffer, ga->GetTileCoord(x, y));
        }
    }
    
    return buffer - buffer_start;
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
