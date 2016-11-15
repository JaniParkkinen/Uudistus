#include <SFML\Graphics.hpp>
#include <World.h>

#include <enet\enet.h>

#include "GameScene.h"

void initNetwork();
void clientLoop();

ENetEvent event;
ENetHost * host = 0;
ENetPeer * peer = 0;
ENetAddress address;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Galactic Uudistus");

    window.setFramerateLimit(60);

    sf::CircleShape shape(256.f);
    shape.setFillColor(sf::Color(0, 25, 10));

    Scene* current = new GameScene(&window);

    //ENET
    initNetwork();
    while (true)
    {
        clientLoop();
    }

    //ENET END

    printf_s("Starting game loop\n");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        current->update(0.1f);

        window.clear();

        current->render(&window);
        //window.draw(shape);
        window.display();
    }
    return 0;
}

void clientLoop() {

    // processing incoming events:
    while (enet_host_service(host, &event, 1000) > 0) {
        switch (event.type) {
        case ENET_EVENT_TYPE_CONNECT: {
            printf("  A new connected has been established to %u:%u\n",
                event.peer->address.host, event.peer->address.port);
            fflush(stdout);

            char buf[64];
            sprintf_s(buf, "%u:%u", event.peer->address.host, event.peer->address.port);
            int buflen = strlen(buf);
            event.peer->data = malloc(buflen + 1);
            //strncpy((char*)event.peer->data, buf, buflen);
            peer = event.peer;
            break;
        }
        case ENET_EVENT_TYPE_RECEIVE:

            printf("%s says %s on channel %u\n",
                (char*)event.peer->data, event.packet->data, event.channelID);
            fflush(stdout);

            enet_packet_destroy(event.packet); // clean up the packet now that we're done using it
            break;

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

    /* Create a reliable packet of size 7 containing "packet\0" */
    ENetPacket * packet = enet_packet_create("packet",
        strlen("packet") + 1,
        ENET_PACKET_FLAG_RELIABLE);
    /* Extend the packet so and append the string "foo", so it now */
    /* contains "packetfoo\0"                                      */
    //enet_packet_resize(packet, strlen("packetfoo") + 1);
    //strcpy(&packet->data[strlen("packet")], "foo");
    /* Send the packet to the peer over channel id 0. */
    /* One could also broadcast the packet by         */
    /* enet_host_broadcast (host, 0, packet);         */
    enet_peer_send(peer, 0, packet);
}

void initNetwork() {

    if (enet_initialize() != 0)
    {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
    }
    atexit(enet_deinitialize);

    printf("Initialized.\n");

    address.port = 1234;

    printf("I am client...\n");
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
    enet_address_set_host(&address, "");
    peer = enet_host_connect(host, &address, 2, 0);
    peer->data = 0; // use this as mark that connection is not yet acknowledged
    if (!peer) {
        fprintf(stderr, "No available peers for initiating an ENet connection.\n");
        exit(EXIT_FAILURE);
    }

}