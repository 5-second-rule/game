#pragma once
#include "game-core/PlayerMovingObject.h"
#include "engine-renderer/RenderableObject.h"

class RenderablePlayerMovingObject : public PlayerMovingObject, public RenderableObject
{
public:
	RenderablePlayerMovingObject(int type, Transmission::Model* model);
	virtual ~RenderablePlayerMovingObject();

	virtual void render();
};

