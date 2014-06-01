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

	// HACK, wait to load when game screen up?
	IHasHandle *track = this->invoke(ObjectTypes::Track);
	this->getEngineInstance()->getWorld()->allocateHandle(track, HandleType::GLOBAL);
	this->getEngineInstance()->getWorld()->insert(track);

	// HACK --	this only works if the clients are up first, but in the future this will
	//					only be sent when the game starts after character selection
	// this->getEngineInstance()->sendEvent( new SoundEvent( static_cast<int>(Sounds::SOUNDTRACK), true, false ));
	IHasHandle *AIManager = this->invoke(ObjectTypes::AIManager);
	
	theWorld.allocateHandle(AIManager, HandleType::LOCAL);
	theWorld.insert(AIManager);
}