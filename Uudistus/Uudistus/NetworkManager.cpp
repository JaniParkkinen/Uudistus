#include "NetworkManager.h"
#include <stdio.h>
#include "World.h"

NetworkManager::NetworkManager(World* world, std::string ip)
{
    m_world = world;
    printf("Constructing Network..\n");
    m_clientThread = std::thread(&NetworkManager::clientLoop, this);
    //while (true)
    //{
    //    clientLoop();
    //}
}

NetworkManager::~NetworkManager()
{
    //TODO
}

void NetworkManager::clientLoop() {
    printf("Client thread started\n");

    initNetwork("127.0.0.1");
    // processing incoming events:
    while(true)
    while (enet_host_service(host, &event, 50) > 0) {
        switch (event.type) {
        case ENET_EVENT_TYPE_CONNECT: {
            printf("  A new connected has been established to %u:%u\n",
                event.peer->address.host, event.peer->address.port);
            fflush(stdout);

            char buf[64];
            sprintf_s(buf, "%u:%u\n", event.peer->address.host, event.peer->address.port);
            int buflen = strlen(buf);
            event.peer->data = malloc(buflen + 1);
            //strncpy_s((char*)event.peer->data, sizeof(event.peer->data), buf);
            memcpy_s(event.peer->data, buflen + 1, buf, buflen + 1);
            peer = event.peer;

            break;
        }
        case ENET_EVENT_TYPE_RECEIVE:
        {

            std::string lol = "lol-\0";
            if (strcmp((char*)event.packet->data, lol.c_str()) == 0)
            {
                if (m_world)
                    m_world->createShip(0, 0, 5, 100, m_world->getObjects()[0], 10);
            }

            printf("%s says %s on channel %u\n",
                (char*)event.peer->data, event.packet->data, event.channelID);
            fflush(stdout);

            enet_packet_destroy(event.packet); // clean up the packet now that we're done using it
            break;
        }
        case ENET_EVENT_TYPE_DISCONNECT:
            printf("  host disconnected.\n");
            fflush(stdout);
            free(event.peer->data);
            event.peer->data = 0; // reset the peer's client information.
            peer = 0;
        default:
            break;
        }
    }
}

void NetworkManager::initNetwork(std::string ip) {

    if (enet_initialize() != 0)
    {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
    }
    atexit(enet_deinitialize);

    printf("Initialized.\n");

    address.port = 1234;

    printf("I am client.\n");
    printf("Connecting...\n");
    fflush(stdout);

    host = enet_host_create(0, // create a client host
        1, // allow only 1 outgoing connection
        2, // 2 channels
        0, // use 57600 / 8 for 56K modem with 56 Kbps downstream bandwidth
        0);// use 14400 / 8 for 56K modem with 14 Kbps upstream bandwidth

    if (!host) {
        fprintf(stderr, "An error occurred while trying to create an ENet client host.\n");
        exit(EXIT_FAILURE);
    }

    // connect to server:
    enet_address_set_host(&address, ip.c_str());
    peer = enet_host_connect(host, &address, 2, 0);
    peer->data = 0; // use this as mark that connection is not yet acknowledged
    if (!peer) {
        fprintf(stderr, "No available peers for initiating an ENet connection.\n");
        exit(EXIT_FAILURE);
    }

}

void NetworkManager::createStar(int x, int y, int energy, int owner, int level)
{
    //char** buf = serializeCreateStar(x, y, energy, owner, level);
    char** buf = nullptr;
    sendBuffer(buf, 0);
}

char** NetworkManager::serializeCreateStar(int x, int y, int energy, int owner, int level)
{
    char* buf = new char[5*sizeof(int)];
    memcpy(buf + sizeof(int) * 0, &x, sizeof(int));
    memcpy(buf + sizeof(int) * 1, &y, sizeof(int));
    memcpy(buf + sizeof(int) * 2, &energy, sizeof(int));
    memcpy(buf + sizeof(int) * 3, &owner, sizeof(int));
    memcpy(buf + sizeof(int) * 4, &level, sizeof(int));

    return &buf;
}

void NetworkManager::sendBuffer(char** buffer, int bufLength)
{
    if (peer->data != 0)
    {
        //ENetPacket * packet = enet_packet_create(buffer, bufLength, ENET_PACKET_FLAG_RELIABLE);
        ENetPacket * packet = enet_packet_create("lol-\0", 5, ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(peer, 0, packet);

        //delete[] *buffer;
    }
}