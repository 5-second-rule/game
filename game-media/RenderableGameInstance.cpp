#include "RenderableGameInstance.h"
#include "game-core/MoveEvent.h"
#include "game-core/ShootEvent.h"
#include "RenderableGameObjectCtorTable.h"
#include "engine-renderer/RenderableWorld.h"

RenderableGameInstance::RenderableGameInstance(void *appHandle)
{
	this->appHandle = appHandle;
}

RenderableGameInstance::~RenderableGameInstance()
{
}

void RenderableGameInstance::init() {
	GameInstance::init();
	//this->getEngineInstance()->waitForConnection();
	this->getRenderingEngineInstance()->waitForServer();
	this->getEngineInstance()->registerPlayer(true);
}

std::vector<Event *>  RenderableGameInstance::inputTranslator(InputAdapter *inputAdapter) {
	Transmission::Input::KeyState down = Transmission::Input::KeyState::STATE_DOWN;
	MoveEvent::MoveDirection dir = { 0.0, 0.0, 0.0 };
	bool moveKeyPressed = false;
	std::vector<Event *> inputEventVector;
 
	if (inputAdapter->getKeyState(Transmission::Input::Key::SPACE) == down) {
		inputEventVector.emplace_back(new ShootEvent(this->getEngineInstance()->getLocalPlayerGuid(0)));
	}
		
	if (inputAdapter->getKeyState(Transmission::Input::Key::A) == down) {
		dir.x -= 1;
		moveKeyPressed = true;
	}

	if (inputAdapter->getKeyState(Transmission::Input::Key::D) == down) {
		dir.x += 1;
		moveKeyPressed = true;
	}

	if (inputAdapter->getKeyState(Transmission::Input::Key::I) == down) {
		dir.z += 1;
		moveKeyPressed = true;
	}

	if (inputAdapter->getKeyState(Transmission::Input::Key::O) == down) {
		dir.z -= 1;
		moveKeyPressed = true;
	}

	if (inputAdapter->getKeyState(Transmission::Input::Key::S) == down) {
		dir.y -= 1;
		moveKeyPressed = true;
	}

	if (inputAdapter->getKeyState(Transmission::Input::Key::W) == down) {
		dir.y += 1;
		moveKeyPressed = true;
	}
	
	if (moveKeyPressed) {
		inputEventVector.emplace_back(new MoveEvent(this->getEngineInstance()->getLocalPlayerGuid(0), dir));
	}
	return inputEventVector;
}

Engine * RenderableGameInstance::makeEngineInstance(GameObjectCtorTable *ctors) {
	
	RenderingEngine* eng = new RenderingEngine(
		new RenderableWorld(), 
		ctors,
		this->appHandle);
	eng->renderingDelegate = this;
	return eng;
}

GameObjectCtorTable * RenderableGameInstance::makeCtorTable() {
	return new RenderableGameObjectCtorTable();
}

RenderableGameInstance * RenderableGameInstance::getGlobalInstance() {
	RenderableGameInstance *renderableInstance =
		dynamic_cast<RenderableGameInstance *>(GameInstance::getGlobalInstance());

	if (renderableInstance == nullptr) {
		throw std::runtime_error("Game instance isn't a rendering version.");
	}

	return renderableInstance;
}

RenderingEngine * RenderableGameInstance::getRenderingEngineInstance() {
	return dynamic_cast<RenderingEngine *>(this->getEngineInstance());
}

