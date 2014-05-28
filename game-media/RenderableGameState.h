#pragma once

#include "game-core/GameState.h"
#include "game-core/SelectionEvent.h"
#include "engine-renderer/RenderableObject.h"
#include "engine-renderer/RenderingEngine.h"
#include "RenderableGame.h"

class RenderableGameState 
	: public GameState, 
	public RenderableObject, 
	public IRenderingEngineDelegate {
public:
	RenderableGameState();
	~RenderableGameState();
	
	virtual std::vector<Event *> inputTranslator(InputAdapter *inputAdapter);
	virtual void render();
};
