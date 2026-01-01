#include "NetworkManager.h"
#include <enet/enet.h>      

struct NetworkManager::Impl{
    ENetHost* host = nullptr;
    ENetPeer* serverPeer = nullptr;
    uint8_t localPlayerID = 0;

    std::unordered_map<uint8_t, ENetPeer*> clients;
};

NetworkManager::NetworkManager() : impl(new Impl) {
    if(enet_initialize() != 0){
        std::cout << "failed to initialize enet";
    }
}

NetworkManager::~NetworkManager(){
    if(impl->host){
        enet_host_destroy(impl->host);
    }
}

void NetworkManager::InitServer(){
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = port;

    impl->localPlayerID = 0;
    
    impl->host = enet_host_create(&address, maxClients, 2, 0, 0);
    if(!impl->host){
        std::cout << "Failed to create server\n";
    }

    mode = NetworkMode::Server;
}

void NetworkManager::InitClient(){
    impl->host = enet_host_create(nullptr, 1, 2, 0, 0);
    if(!impl->host) {
        std::cout << "Failed to create client\n";
    }

    ENetAddress address;
    enet_address_set_host(&address, serverIP);
    address.port = port;
    impl->serverPeer = enet_host_connect(impl->host, &address, 2, 0);
    if(!impl->serverPeer){
        std::cout << "Failed to connect to the server\n";
    }

    mode = NetworkMode::Client;
}

void NetworkManager::Update(){
    ENetEvent event;

    while(enet_host_service(impl->host, &event, 0) > 0){
        switch (event.type){
            case ENET_EVENT_TYPE_CONNECT: {
                event.peer->data = reinterpret_cast<void*>(static_cast<uintptr_t>(nextID));
                std::cout << "Client connected! id: " << static_cast<int>(nextID) << "\n";

                impl->clients[nextID] = event.peer;

                onClientConnected(nextID);

                AssignIDPacket pkt;
                pkt.type = PacketType::AssignID;
                pkt.playerID = nextID;

                ENetPacket* packet = enet_packet_create(&pkt, sizeof(pkt), ENET_PACKET_FLAG_RELIABLE);
                enet_peer_send(event.peer, 0, packet);

                nextID++;
                break;
            }
            case ENET_EVENT_TYPE_DISCONNECT: {
                std::cout << "Client disconnected\n";
                break;
            }
            case ENET_EVENT_TYPE_RECEIVE: {
                PacketType type = static_cast<PacketType>(event.packet->data[0]);

                if(mode == NetworkMode::Client && type == PacketType::AssignID){
                    AssignIDPacket* packet = reinterpret_cast<AssignIDPacket*>(event.packet->data);
                    impl->localPlayerID = packet->playerID;
                }

                if(mode == NetworkMode::Server && type == PacketType::PlayerMove){
                    PlayerMovePacket* packet = reinterpret_cast<PlayerMovePacket*>(event.packet->data);

                    remotePlayerPositions[packet->playerID] = {packet->x, packet->y};

                    ENetPacket* copy = enet_packet_create(event.packet->data, event.packet->dataLength, ENET_PACKET_FLAG_UNSEQUENCED);
                    enet_host_broadcast(impl->host, 0, copy);
                }

                if(mode == NetworkMode::Client && type == PacketType::PlayerMove){
                    PlayerMovePacket* packet = reinterpret_cast<PlayerMovePacket*>(event.packet->data);

                    remotePlayerPositions[packet->playerID] = {packet->x, packet->y};
                }

                if(mode == NetworkMode::Client && type == PacketType::TileMapGround){
                    std::cout << "enter\n";
                    TileMapGroundPacketHeader* packet = reinterpret_cast<TileMapGroundPacketHeader*>(event.packet->data);

                    uint8_t* rawDataStart = event.packet->data + sizeof(TileMapGroundPacketHeader);
                    size_t rawDataSize = event.packet->dataLength - sizeof(TileMapGroundPacketHeader);

                    std::vector<uint8_t> data(rawDataStart, rawDataStart + rawDataSize);

                    onTileMapGroundReceived(impl->localPlayerID, packet->width, packet->height, data);
                }

                enet_packet_destroy(event.packet);
                break;
            }
        }
    }
}

void NetworkManager::SendPlayerPosition(float x, float y){
    PlayerMovePacket packet;
    packet.type = PacketType::PlayerMove;
    packet.playerID = impl->localPlayerID;
    packet.x = x;
    packet.y = y;

    if(mode == NetworkMode::Client && impl->serverPeer){
        ENetPacket* pkt = enet_packet_create(&packet, sizeof(packet), ENET_PACKET_FLAG_UNSEQUENCED);
        enet_peer_send(impl->serverPeer, 0, pkt);
    }
    else if(mode == NetworkMode::Server && impl->host){
        ENetPacket* pkt = enet_packet_create(&packet, sizeof(packet), ENET_PACKET_FLAG_UNSEQUENCED);
        remotePlayerPositions[impl->localPlayerID] = {x, y};

        enet_host_broadcast(impl->host, 0, pkt);
    }
}

void NetworkManager::SendTileMapGround(uint8_t clientID, int width, int height, std::vector<uint8_t> &data){
    auto it = impl->clients.find(clientID);
    if(it == impl->clients.end()) return;

    TileMapGroundPacketHeader header;
    header.type = PacketType::TileMapGround;
    header.width = width;
    header.height = height;

    std::vector<uint8_t> packetData;
    packetData.insert(packetData.end(),
        reinterpret_cast<uint8_t*>(&header),
        reinterpret_cast<uint8_t*>(&header) + sizeof(header)
    );

    packetData.insert(packetData.end(), data.begin(), data.end());

    ENetPacket* pkt = enet_packet_create(packetData.data(), packetData.size(), ENET_PACKET_FLAG_RELIABLE);
    std::cout << "presend\n";
    enet_peer_send(it->second, 0, pkt);
    std::cout << "sent\n";
}

NetworkMode NetworkManager::GetMode(){
    return mode;
}

uint8_t NetworkManager::GetLocalPlayerID(){
    return impl->localPlayerID;
}

const std::unordered_map<uint8_t, PlayerPosition>& NetworkManager::GetRemotePlayerPositions() const{
    return remotePlayerPositions;
}
