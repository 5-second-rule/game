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
	IHasHandle *track = this->objectCtors->invoke(ObjectTypes::Track);
	this->getEngineInstance()->getWorld()->allocateHandle(track, HandleType::GLOBAL);
	this->getEngineInstance()->getWorld()->insert(track);

	// TODO make the client get this too (in the wallOfDeath variable)?
	this->wallOfDeath = dynamic_cast<WallOfDeath *>(this->objectCtors->invoke(ObjectTypes::Wwod));
	if (this->wallOfDeath == nullptr) {
		throw std::runtime_error("Error creating wall of death.");
	}

	this->getEngineInstance()->getWorld()->allocateHandle(this->wallOfDeath, HandleType::GLOBAL);
	this->getEngineInstance()->getWorld()->insert(this->wallOfDeath);

	this->wallOfDeath->reset();
}