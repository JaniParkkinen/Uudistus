#include "Server.h"

Server::Server()
{
    m_stop = false;
    initNetwork();
    serverLoop();
    //m_serverThread = std::thread(&Server::serverLoop, this);
}

Server::~Server()
{
    m_stop = true;
}

void Server::serverLoop() {

    // processing incoming events:
    while (enet_host_service(host, &event, 1000) > 0 || !m_stop) {
        //printf("Checking Incoming");
        switch (event.type) {
        case ENET_EVENT_TYPE_CONNECT: {
            printf("  A new connected has been established to %u:%u\n",
                event.peer->address.host, event.peer->address.port);
            fflush(stdout);

            //char buf[64];
            //sprintf_s(buf, "%u:%u", event.peer->address.host, event.peer->address.port);
            //int buflen = strlen(buf);
            //event.peer->data = malloc(buflen + 1);
            ////strncpy((char*)event.peer->data, buf, buflen);
            peer = event.peer;

            break;
        }
        case ENET_EVENT_TYPE_RECEIVE:
        {
            printf("%s says %s on channel %u\n",
                (char*)event.peer->data, event.packet->data, event.channelID);
            fflush(stdout);

            for (int i = 0; i < event.packet->dataLength; i++)
            {
                printf_s("%02x ", event.packet->data[i]);
            }
            printf_s("\n");

            //echo back
            ENetPacket * packet = enet_packet_create(event.packet->data,
                event.packet->dataLength,
                ENET_PACKET_FLAG_RELIABLE);

            enet_host_broadcast(host, 0, packet);
            //enet_peer_send(peer, 0, packet);
            enet_host_flush(host);
            //SendPacket(0, (char*)event.packet->data);

            enet_packet_destroy(event.packet); // clean up the packet now that we're done using it

            break;
        }
        case ENET_EVENT_TYPE_DISCONNECT:
        {
            printf("  host disconnected.\n");
            fflush(stdout);
            free(event.peer->data);
            event.peer->data = 0; // reset the peer's client information.
            peer = 0;
        }
        default:
            break;
        }
        event.type = ENET_EVENT_TYPE_NONE;
    }
}

void Server::initNetwork() {
    if (enet_initialize() != 0)
    {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
    }
    atexit(enet_deinitialize);

    printf("Initialized.\n");


    /* Bind the server to the default localhost.     */
    /* A specific host address can be specified by   */
    /* enet_address_set_host (& address, "x.x.x.x"); */

    address.port = 1234;

    printf("I am server...\n");
    fflush(stdout);

    address.host = ENET_HOST_ANY;
    host = enet_host_create(&address, // the address to bind the server host to 
        32,   // allow only 1 client and/or outgoing connections
        2,
        0,   // assume any amount of incoming bandwidth
        0);  // assume any amount of outgoing bandwidth
    if (!host) {
        fprintf(stderr, "An error occurred while trying to create an ENet server host.\n");
        exit(EXIT_FAILURE);
    }
    printf("Host Created at %s.\n", address.host);
}