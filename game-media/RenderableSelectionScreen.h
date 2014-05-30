#pragma once

#include "engine-renderer/IRenderable.h"
#include "SelectionScreenData.h"
#include "RenderableMovingObject.h"
#include "RenderableStaticObject.h"
#include "RenderableGame.h"
#include "RenderingGameManager.h"

class GAMEMEDIADLL RenderableSelectionScreen : public StaticObject, public IRenderable
{
private:
	Engine *engine;
	std::vector<Player*> players;
	SelectionScreenData::Objects *objectData;

public:
	RenderableSelectionScreen(SelectionScreenData::Objects *objectData);
	virtual ~RenderableSelectionScreen();

	virtual void render();
};
