#pragma once
#include "game-core\Powerup.h"
#include "engine-renderer\RenderableObject.h"

class RenderablePowerup : 
	public Powerup, public RenderableObject
{
public:
	RenderablePowerup(int type, Transmission::Model* m);
	~RenderablePowerup();

	virtual void render();
};

