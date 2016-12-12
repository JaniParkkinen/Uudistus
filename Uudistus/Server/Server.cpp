#include "Server.h"

Server::Server()
{
    m_stop = false;
    m_tick = 0;
    m_ok = 0;
    m_nPlayers = 0;

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
    while (enet_host_service(host, &event, 100) > 0 || !m_stop) {
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
            m_nPlayers++;
			
			unsigned buf[3] = { 8, m_ready, m_nPlayers };

			ENetPacket* packet3 = enet_packet_create(buf, 3 * sizeof(int), ENET_PACKET_FLAG_RELIABLE);
			broadcast(packet3);


            break;
        }
        case ENET_EVENT_TYPE_RECEIVE:
        {
            printf_s("event recieved.\n");
            fflush(stdout);
            int* intData = (int*)event.packet->data;
			if (intData[0] == 0)
			{
				//TODO: ready check
				m_ready++;
				unsigned buf[3] = { 8, m_ready, m_nPlayers };

				ENetPacket* packet3 = enet_packet_create(buf, 3 * sizeof(int), ENET_PACKET_FLAG_RELIABLE);
				broadcast(packet3);

				printf_s("Ready\n");

				if (m_ready == m_nPlayers)
				{
                    Sleep(500);
                    m_world.generateMap(m_nPlayers);
					unsigned buf2[2] = { 10, 0 };
					ENetPacket* packet2 = enet_packet_create(buf2, 2 * sizeof(int), ENET_PACKET_FLAG_RELIABLE);
					broadcast(packet2);
				}
				//unsigned buf[3] = { 10, m_ready, m_nPlayers};

				//ENetPacket * packet2 = enet_packet_create(buf, 3 * sizeof(int), ENET_PACKET_FLAG_RELIABLE);
				//broadcast(packet2);
			}
            else if (intData[0] > 10) //command
            {
                printf_s("test command\n");
                m_packets.push_back(std::make_pair(event.packet, intData[1]));
            }
            else if (intData[0] == 10) //ok
            {
                printf_s("test ok\n");
                m_ok++;
            }
            else
                printf_s("asd %u \n", intData[0]);
            enet_host_flush(host);
            break;
        }
        case ENET_EVENT_TYPE_DISCONNECT:
        {
            printf("  host disconnected.\n");
            fflush(stdout);
            free(event.peer->data);
            event.peer->data = 0; // reset the peer's client information.
            peer = 0;
            m_nPlayers--;
        }
        default:
            break;
        }
        event.type = ENET_EVENT_TYPE_NONE;

        if (m_ok == m_nPlayers && m_nPlayers > 0)
        {
            Sleep(100);
            eventLoop();
            m_ok = 0;
            m_tick++;
        }
    }
}


void Server::eventLoop()
{
    for (unsigned i = 0; i < m_packets.size(); i++)
    {
        if (m_packets[i].second == m_tick)
        {
            ENetPacket* packet = m_packets[i].first;
            processPacket(packet);
            enet_packet_destroy(packet);
            //  remove packet from vector
        }
        else
            continue;

    }

    unsigned buf[2] = { 10, m_tick };

    ENetPacket * packet2 = enet_packet_create(buf, 2 * sizeof(int), ENET_PACKET_FLAG_RELIABLE);
    broadcast(packet2);
}

void Server::broadcast(ENetPacket* packet)
{
    ENetPacket * packet2 = enet_packet_create(packet->data,
        packet->dataLength,
        ENET_PACKET_FLAG_RELIABLE);

    enet_host_broadcast(host, 0, packet2);
}

void Server::processPacket(ENetPacket* packet)
{
    int* message = (int*)packet->data;

    printf_s("Processing...\n");
    switch (message[0])
    {
    case 11:
    {
        printf_s("Creating a star...\n");

        m_world.createStar(*(message + 2), *(message + 3), *(message + 4), *(message + 5));
        break;
    }
    case 12:
    {

        printf_s("Sending a ship...\n");

        m_world.sendShip(*(message + 2), *(message + 3));
        break;
    }
    case 13:
    {
        printf_s("Connecting stars...\n");

        m_world.connectStars(*(message + 2), *(message + 3));
        break;
    }
    default:
        break;
    }
    broadcast(packet); 
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