#include "RenderableGame.h"
#include "game-core/MoveEvent.h"
#include "game-core/ShootEvent.h"
#include "RenderableGameObjectCtorTable.h"
#include "engine-renderer/RenderableWorld.h"
#include "TrackingCameraHandler.h"
#include "SoundCtorTable.h"
#include "RenderableMovingObject.h"

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

RenderableGame::RenderableGame(void *appHandle)
{
	this->appHandle = appHandle;
}

void RenderableGame::init() {
	Game::init();
	static_cast<SoundCtorTable*>(this->getRenderingEngineInstance()->soundCtors)->initCtors();
	this->getRenderingEngineInstance()->waitForServer();
	this->getEngineInstance()->registerPlayer(true);
	this->gameManager = new RenderingGameManager(this->getRenderingEngineInstance());
	this->getRenderingEngineInstance()->frameDelegate = this;
}

Engine * RenderableGame::makeEngineInstance( ConstructorTable<BaseObject> *objectCtors, ConstructorTable<ActionEvent>* eventCtors ) {

	RenderingEngine* eng = new RenderingEngine(
		new RenderableWorld(), 
		objectCtors,
		eventCtors,
		new SoundCtorTable(),
		this->appHandle,
		new TrackingCameraHandler(),
		"resources\\defaultVertex.cso",
		"resources\\defaultPixel.cso",
		L"Vein: Rivers of Blood");

	return eng;
}

RenderableGame * RenderableGame::getGlobalInstance() {
	RenderableGame *renderableInstance =
		dynamic_cast<RenderableGame *>(Game::getGlobalInstance());

	if (renderableInstance == nullptr) {
		throw std::runtime_error("Game instance isn't a rendering version.");
	}

	return renderableInstance;
}

RenderingEngine * RenderableGame::getRenderingEngineInstance() {
	return dynamic_cast<RenderingEngine *>(this->getEngineInstance());
}

GameObjectCtorTable * RenderableGame::makeCtorTable() {
	return new RenderableGameObjectCtorTable();
}

RenderingGameManager *RenderableGame::getGameManager() {
	return this->gameManager;
}


void RenderableGame::beforeDraw() {

	if (this->getGameManager()->getGameState()->getState() == GameState::Game) {
		std::vector<Player*> players = this->gameManager->getPlayers();

		Common::Vector4 *positions = new Common::Vector4[players.size()];
		Common::Vector4 *colors = new Common::Vector4[players.size()];

		for (size_t i = 0; i < players.size(); ++i) {
			IHasHandle* obj = theWorld.get(players[i]->getMovingObject());
			RenderableMovingObject* mo = dynamic_cast<RenderableMovingObject*>(obj);
			if (mo != nullptr) positions[i] = mo->getPosition();
			colors[i] = Common::Vector4(0.9f, 0.9f, 0.9f, 100.0f);
		}

		this->getRenderingEngineInstance()->setLightBuffers(positions, colors, players.size());
	}
}