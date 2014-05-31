#include "ServerGame.h"
#include "ObjectTypes.h"

#include "engine-core/ServerEngine.h"

ServerGame::ServerGame(float frameTime) {
	this->frameTime = frameTime;
}

ServerGame::~ServerGame() {
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
	IHasHandle *AIManager = this->invoke(ObjectTypes::AIManager);
	this->getEngineInstance()->getWorld()->allocateHandle(AIManager, HandleType::LOCAL);
	this->getEngineInstance()->getWorld()->insert(AIManager);
}