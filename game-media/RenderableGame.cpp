#include "RenderableGame.h"
#include "game-core/MoveEvent.h"
#include "game-core/ShootEvent.h"
#include "RenderableGameObjectCtorTable.h"
#include "engine-renderer/RenderableWorld.h"
#include "TrackingCameraHandler.h"
#include "SoundCtorTable.h"

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
