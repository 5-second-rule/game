#pragma once

#include "game-core/GameState.h"
#include "engine-renderer/RenderableObject.h"

class RenderableGameState : public GameState, public RenderableObject {
public:
	RenderableGameState();
	~RenderableGameState();
	virtual void render();
};

