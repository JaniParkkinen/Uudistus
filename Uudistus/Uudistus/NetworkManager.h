#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <enet\enet.h>
#include <string>
#include <thread>
#include "SceneManager.h"

class World;

class NetworkManager
{
public:
	static NetworkManager* instance() {
		return (!nm) ?
			nm = new NetworkManager() :
			nm;
	}


	void setWorld(World* world);
	void setSceneManager(SceneManager* sm);
	void initNetwork(std::string ip);
    void createStar(int x, int y, int energy, int owner, int level);
    void sendShip(int id1, int id2);
    void connect(int id1, int id2);
	void setReady(bool isReady);

    const int getTick()const;
private:
	NetworkManager(); //connect
    ~NetworkManager();
	static NetworkManager* nm;

    //char* createStation(int x, int y, int energy, int owner, int type);;
    //char* upgrade(int id);
    //end serialization

    int m_tick;

    World* m_world;
	SceneManager* m_sceneM;
	sf::RenderWindow* m_rw;

    void clientLoop();

    std::thread m_clientThread;

    ENetEvent event;
    ENetHost * host = 0;
    ENetPeer * peer = 0;
    ENetAddress address;
};
#endif