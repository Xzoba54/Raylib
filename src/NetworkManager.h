#pragma once

#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <functional>

enum class NetworkMode {
    Server,
    Client
};

enum class PacketType : uint8_t{
    AssignID,
    PlayerMove,
    TileMapGround
};

struct AssignIDPacket{
    PacketType type;
    uint8_t playerID;
};

struct PlayerMovePacket{
    PacketType type;
    uint8_t playerID;
    float x;
    float y;
};

struct TileMapGroundPacketHeader{
    PacketType type;
    int width;
    int height;
    //raw ground data
};

struct PlayerPosition{
    float x;
    float y;
};

class NetworkManager{
public:
    NetworkManager();
    ~NetworkManager();

    std::function<void(uint8_t newClientID)> onClientConnected;
    std::function<void(uint8_t clientID, int width, int height, std::vector<uint8_t> data)> onTileMapGroundReceived;

    void InitServer();
    void InitClient();

    void Update();

    void SendPlayerPosition(float x, float y);
    void SendTileMapGround(uint8_t clientID, int width, int height, std::vector<uint8_t>& data);

    NetworkMode GetMode();
    uint8_t GetLocalPlayerID();

    const std::unordered_map<uint8_t, PlayerPosition>& GetRemotePlayerPositions() const;

private:
    struct Impl;
    Impl* impl;

    unsigned int port = 1234;
    int maxClients = 2;
    const char* serverIP = "127.0.0.1";

    NetworkMode mode;

    uint8_t nextID = 1;

    std::unordered_map<uint8_t, PlayerPosition> remotePlayerPositions;
};