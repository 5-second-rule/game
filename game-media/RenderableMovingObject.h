#pragma once

#include "game-core/MovingObject.h"
#include "engine-renderer/RenderableObject.h"

class RenderableMovingObject : public MovingObject, public RenderableObject
{
public:
	RenderableMovingObject(int type, Transmission::Model* model);
	~RenderableMovingObject();

	virtual void render();
};

