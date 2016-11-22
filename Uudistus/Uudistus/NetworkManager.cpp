#include "NetworkManager.h"
#include <stdio.h>
#include "World.h"

#include <climits>

//template <typename T>
//T swap_endian(T u)
//{
//    static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");
//
//    union
//    {
//        T u;
//        unsigned char u8[sizeof(T)];
//    } source, dest;
//
//    source.u = u;
//
//    for (size_t k = 0; k < sizeof(T); k++)
//        dest.u8[k] = source.u8[sizeof(T) - k - 1];
//
//    return dest.u;
//}

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
            int* messageType = (int*)event.packet->data;


            printf_s("recieved: \n");
            for (int i = 0; i < event.packet->dataLength; i++)
            {
                printf_s("%02x ", event.packet->data[i]);
            }
            printf_s("\n");

            switch (*messageType)
            {
            case 0:
                printf_s("Game starts!");
                break;
            case 1:
            {
                int* message = (int*)event.packet->data;

                printf_s("Creating a star...\n");

                for (int i = 0; i < 6; i++)
                {
                    printf_s("%u ", *(message + i));
                }

                m_world->createStar(*(message + 1), *(message + 2), *(message + 3), *(message + 4));
                break;
            }
            case 2:
            {
                int* message = (int*)event.packet->data;

                printf_s("Sending a ship...\n");

                for (int i = 0; i < 3; i++)
                {
                    printf_s("%u ", *(message + i));
                }

                m_world->sendShip(*(message + 1), *(message + 2));
                break;
            }
            default:
                break;
            }
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
    const int size = 6 * sizeof(unsigned int);
    unsigned buf2[6] = { 1, x, y, energy, owner, level };

    char* buf = (char*)buf2;

    printf_s("sending:\n");
    for (int i = 0; i < 6; i++)
    {
        printf_s("%08x ", buf2[i]);
    }
    printf_s("\n");

    if (peer->data != 0)
    {
        ENetPacket * packet = enet_packet_create(buf2, size, ENET_PACKET_FLAG_RELIABLE);
        enet_packet_resize(packet, size);
        enet_peer_send(peer, 0, packet);
    }
}

void NetworkManager::sendShip(int sender, int target)
{
    const int size = 3 * sizeof(int);
    unsigned buf2[3] = { 2, sender, target };

    char* buf = (char*)buf2;

    printf_s("sending:\n");
    for (int i = 0; i < 3; i++)
    {
        printf_s("%08x ", buf2[i]);
    }
    printf_s("\n");

    if (peer->data != 0)
    {
        ENetPacket * packet = enet_packet_create(buf2, size, ENET_PACKET_FLAG_RELIABLE);
        enet_packet_resize(packet, size);
        enet_peer_send(peer, 0, packet);
    }
}