#ifndef SERVER_H
#define SERVER_H

#include <enet\enet.h>
#include <stdio.h>
//#include <thread>
#include <vector>
#include <World.h>
//#include <chrono>

#include <string.h>

class Server
{
public:
    Server();
    ~Server();

private:
    void initNetwork();
    void serverLoop();
    void eventLoop();
    void processPacket(ENetPacket* packet);
    void broadcast(ENetPacket* packet);

    std::vector<ENetPeer*> m_connections;
    //std::thread m_serverThread;

    ENetEvent event;
    ENetHost * host = 0;
    ENetPeer * peer = 0;
    ENetAddress address;

    int m_tick;
    int m_ok;
    int m_nPlayers;
	int m_ready;
    //float m_tickTimer;
    std::vector<std::pair<ENetPacket*, int>> m_packets; //packet, tick

    bool m_stop;

    World m_world;
};

#endif