#include "ServerGame.h"
#include "ObjectTypes.h"
#include "Sounds.h"
#include "MovingObject.h"

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

	this->populateRedBloodCells();


	// HACK --	this only works if the clients are up first, but in the future this will
	//					only be sent when the game starts after character selection
	// this->getEngineInstance()->sendEvent( new SoundEvent( static_cast<int>(Sounds::SOUNDTRACK), true, false ));
}

void ServerGame::populateRedBloodCells() {
	for (size_t i = 0; i < this->getTrackPath()->nodes.size(); i += 5) {
		float x = ((float) (rand()) / (float) (INT_MAX));
		float y = ((float) (rand()) / (float) (INT_MAX));
		float z = ((float) (rand()) / (float) (INT_MAX));

		Common::Vector4 random(x, y, z);
		random.normalize();
		random *= 100.0f; //TODO: radius;

		PathNode n = this->getTrackPath()->nodes[i];

		

		MovingObject* rbc = new MovingObject(ObjectTypes::RedBlood, this, true, false);
		rbc->setPosition(n.point + random);

		this->getEngineInstance()->getWorld()->allocateHandle(rbc, HandleType::GLOBAL);
		this->getEngineInstance()->getWorld()->insert(rbc);
		// todo pick an arbitrary position
	}
}