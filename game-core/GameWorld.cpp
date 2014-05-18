#include "GameWorld.h"


GameWorld::GameWorld(ServerGame *server)
{
	this->server = server;
}


GameWorld::~GameWorld()
{
}

void GameWorld::update(float dt){
	server->update();
	World::update(dt);
}