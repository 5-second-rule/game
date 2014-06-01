#pragma once
#include "game-media.h"
#include "engine-renderer/RenderingEngine.h"
#include "game-core/ShootEvent.h"
#include "game-core/MoveEvent.h"

class GAMEMEDIADLL GameplayInput : public IRenderingEngineDelegate {
private:
	RenderingEngine *renderingEngine;
public:
	GameplayInput();
	GameplayInput(RenderingEngine *renderingEngine);
	~GameplayInput();
	virtual std::vector<Event *> inputTranslator(InputAdapter *inputAdapter);
};
