#include "ServerGame.h"
#include "ObjectTypes.h"
#include "Sounds.h"
#include "MovingObject.h"

#include "engine-core/ServerEngine.h"

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

ServerGame::ServerGame(float frameTime) {
	this->frameTime = frameTime;
}

Engine * ServerGame::makeEngineInstance( ConstructorTable<BaseObject> *objectCtors, ConstructorTable<ActionEvent>* eventCtors ) {

	Engine* eng  = new ServerEngine(
		new World(),
		objectCtors,
		eventCtors,
		this->frameTime);

	return eng;
}

void ServerGame::stop() {
	dynamic_cast<ServerEngine *>(this->getEngineInstance())->stop();
}

void ServerGame::init() {
	Game::init();
	this->gameState = new GameState();
	this->getEngineInstance()->getWorld()->allocateHandle(this->gameState, HandleType::GLOBAL);
	this->getEngineInstance()->getWorld()->insert(this->gameState);
	this->getEngineInstance()->setPlayerRegistration(this->gameState);

	this->gameState->setState(GameState::Selection);
}