#include "NetChannel.hpp"
#include "NetSerialize.hpp"

#define UPDATE_INTERVAL 100

enum {
    SERVER_MOVE,
    SERVER_PLACE_BOMB
};

static inline uint8_t EncodeMovement(bool up, bool down, bool left, bool right)
{
    return (
        up |
        down << 1 |
        left << 2 |
        right << 3
    );
}

static inline void DecodeMovement(uint8_t x, bool &up, bool &down, bool &left, bool &right) 
{
    up = x & 1;
    down = x & 2;
    left = x & 4;
    right = x & 8;
}

NetChannel_GBomber::NetChannel_GBomber(NetConnection *nc, channel_id_t channel_id, GBomber *gb)
 :NetChannel(nc, channel_id, GBOMBER),
  gb(gb),
  lastUpdate(0),
  lastMoveBits(0)
{ 
    if (gb->netConnection == nc) {
        gb->netChannel = this;
    }
}

int NetChannel_GBomber::ServerHandleData(const char *buffer, size_t size)
{
    if (gb->netChannel != this) {
        nc->app->Log << "attempted to control not owned Bomber\n";
        return -1;
    }

    uint8_t type = NetSerialize::unpack<uint8_t>(&buffer);

    switch (type) {
    case SERVER_MOVE:
    {
        uint8_t direction = NetSerialize::unpack<uint8_t>(&buffer);
        DecodeMovement(direction, gb->MoveUp, gb->MoveDown, gb->MoveLeft, gb->MoveRight);
        break;
    }
    case SERVER_PLACE_BOMB:
    {
        gb->PlaceBomb();
        break;
    }
    default:
        break;
    }

    return 0;
}

int NetChannel_GBomber::ClientHandleData(const char *buffer, size_t size, bool is_initial)
{
    uint32_t lastUpdate = NetSerialize::unpack<uint32_t>(&buffer);
    if (this->lastUpdate > lastUpdate) {
        // packet is out of order
        return 0;
    }
    
    if (is_initial) {
        bool owned = NetSerialize::unpack<uint8_t>(&buffer) != 0;
        if (owned && gb->netConnection == NULL) {
            gb->netConnection = nc;
            gb->netChannel = this;
            // possess it (bind controls)
            auto iter = nc->app->BomberMap.begin();
            if (iter == nc->app->BomberMap.end()) {
                nc->app->Log << "Warning! No controls available\n"; 
            } else {
                nc->app->dev(iter->input)->Connect(gb);  
                nc->app->devs.push_back(nc->app->dev(iter->input));
            }
        }
        gb->ColorID = NetSerialize::unpack<int32_t>(&buffer);
    }

    gb->X = NetSerialize::unpack<float>(&buffer);
    gb->Y = NetSerialize::unpack<float>(&buffer);
    
    int8_t direction = NetSerialize::unpack<uint8_t>(&buffer);
    DecodeMovement(direction, gb->MoveUp, gb->MoveDown, gb->MoveLeft, gb->MoveRight);

    return 0;
}

size_t NetChannel_GBomber::DumpData(char *buffer, bool is_initial)
{
    const char * const buffer_start = buffer;
    
    NetSerialize::pack<uint32_t>(&buffer, lastUpdate);
    if (is_initial) {
        NetSerialize::pack<uint8_t>(&buffer, nc == gb->netConnection);
        NetSerialize::pack<int32_t>(&buffer, gb->ColorID);
    }
    NetSerialize::pack<float>(&buffer, gb->X);
    NetSerialize::pack<float>(&buffer, gb->Y);
    int8_t direction = EncodeMovement(gb->MoveUp, gb->MoveDown, gb->MoveLeft, gb->MoveRight);
    NetSerialize::pack<uint8_t>(&buffer, direction);
    
    return buffer - buffer_start;
}

int NetChannel_GBomber::ServerSendInitialPacket()
{
    char buffer[MAX_PACKET_SIZE];
    size_t bufsize = PrepareOpenPacket(buffer);
    lastUpdate = nc->app->GetTimeReal();
    
    bufsize += DumpData(buffer + bufsize, true);

    return nc->SendPacket(buffer, bufsize);
}

int NetChannel_GBomber::ServerSendUpdate()
{
    char buffer[MAX_PACKET_SIZE];
    size_t bufsize = PrepareDataPacket(buffer);
    lastUpdate = nc->app->GetTimeReal();
    
    bufsize += DumpData(buffer + bufsize, false);

    return nc->SendPacket(buffer, bufsize);
}

void NetChannel_GBomber::Loop()
{
    NetChannel::Loop();

    if (nc->is_server && channel_acked) {
        if (nc->app->GetTimeReal() - lastUpdate > UPDATE_INTERVAL) {
            ServerSendUpdate();
        }
    }
}

void NetChannel_GBomber::ServerMove(bool up, bool down, bool left, bool right)
{
    uint8_t direction = EncodeMovement(up, down, left, right);
    if (direction != lastMoveBits) {
        char buffer[MAX_PACKET_SIZE];
        size_t bufsize = PrepareDataPacket(buffer);
        char *data_buffer = buffer + bufsize;
        
        NetSerialize::pack<uint8_t>(&data_buffer, SERVER_MOVE);
        NetSerialize::pack<uint8_t>(&data_buffer, direction);

        nc->SendPacket(buffer, data_buffer - buffer);

        lastMoveBits = direction;
    }
}

void NetChannel_GBomber::ServerPlaceBomb()
{
    char buffer[MAX_PACKET_SIZE];
    size_t bufsize = PrepareDataPacket(buffer);
    char *data_buffer = buffer + bufsize;

    NetSerialize::pack<uint8_t>(&data_buffer, SERVER_PLACE_BOMB);
        
    nc->SendPacket(buffer, data_buffer - buffer);
}
