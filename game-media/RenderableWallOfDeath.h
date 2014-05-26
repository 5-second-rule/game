#pragma once

#include "game-core/WallOfDeath.h"
#include "engine-renderer/RenderableObject.h"

class RenderableWallOfDeath : public WallOfDeath, public RenderableObject
{
public:
	RenderableWallOfDeath(Transmission::Model* model);
	~RenderableWallOfDeath();

	virtual void render();
};

