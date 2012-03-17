#include "NetChannel.hpp"
#include "NetSerialize.hpp"

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
        NetSerialize::pack<uint16_t>(&buffer, channel_id);
        NetSerialize::pack<uint8_t>(&buffer, CHANNEL_OPEN);
        NetSerialize::pack<uint16_t>(&buffer, ObjectType);
    }

    return 2 + 1 + 2;
}

size_t NetChannel::PrepareAckPacket(char *buffer)
{
    if (buffer) {
        NetSerialize::pack<uint16_t>(&buffer, channel_id);
        NetSerialize::pack<uint8_t>(&buffer, CHANNEL_ACK);
    }

    return 2 + 1;

}

size_t NetChannel::PrepareDataPacket(char *buffer)
{
    if (buffer) {
        NetSerialize::pack<uint16_t>(&buffer, channel_id);
        NetSerialize::pack<uint8_t>(&buffer, CHANNEL_DATA);
    }

    return 2 + 1;
}
size_t NetChannel::PrepareClosePacket(char *buffer)
{
    if (buffer) {
        NetSerialize::pack<uint16_t>(&buffer, channel_id);
        NetSerialize::pack<uint8_t>(&buffer, CHANNEL_CLOSE);
    }

    return 2 + 1;
}


