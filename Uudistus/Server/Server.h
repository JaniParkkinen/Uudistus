#ifndef SERVER_H
#define SERVER_H

#include <enet\enet.h>
#include <stdio.h>
//#include <thread>
#include <vector>
#include <World.h>

#include <string.h>

class Server
{
public:
    Server();
    ~Server();

private:
    void serverLoop();
    void initNetwork();

    std::vector<ENetPeer*> m_connections;
    //std::thread m_serverThread;

    ENetEvent event;
    ENetHost * host = 0;
    ENetPeer * peer = 0;
    ENetAddress address;

    int m_tick;

    bool m_stop;

    World m_world;
};

#endif