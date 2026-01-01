// #include <enet/enet.h>
// #include <iostream>

// void InitServer(){
//     ENetAddress address;
//     address.host = ENET_HOST_ANY;
//     address.port = 1234;
    
//     ENetHost* host = enet_host_create(&address, 2, 2, 0, 0);
//     int hostID = 0;

//     while(true){
//         ENetEvent event;
//         while(enet_host_service(host, &event, 100) > 0){
//             switch(event.type){
//                 case ENET_EVENT_TYPE_CONNECT:
//                     std::cout << "[SERVER] Client connected\n";

//                     int id = 2;
//                     ENetPacket* packet = enet_packet_create(&id, sizeof(id), ENET_PACKET_FLAG_RELIABLE);
//                     enet_peer_send(event.peer, 0, packet);

//                     break;
//             }
//         }
//     }
// }
// void InitClient(){
//     ENetHost* host = enet_host_create(nullptr, 1, 2, 0, 0);

//     ENetAddress address;
//     enet_address_set_host(&address, "127.0.0.1");
//     address.port = 1234;

    
//     ENetPeer* peer = enet_host_connect(host, &address, 2, 0);

//     int myID = -1;
//     std::cout << "[CLIENT] Connecting...\n";

//     while(true){
//         ENetEvent event;
//         while(enet_host_service(host, &event, 100) > 0){
//             switch(event.type){
//                 case ENET_EVENT_TYPE_CONNECT:
//                     std::cout << "[CLIENT] Connected to server\n";
//                     break;
//                 case ENET_EVENT_TYPE_RECEIVE:
//                     std::cout << "received: " << *(int*)event.packet->data << "\n";
//                     enet_packet_destroy(event.packet);
//                     break;
//             }
//         }
//     }
// }

// int main(){
//     if(enet_initialize() != 0){
//         std::cout << "failed to initialize ENet\n";
//     }
    
//     std::cout << "Server(s) or Client(c): ";
//     char mode;
//     std::cin >> mode;

//     if(mode == 's') InitServer();
//     if(mode == 'c') InitClient();

//     return 0;
// }





#include "Game.h"

int main(){
    Game game;
    game.Run();

    return 0;
}