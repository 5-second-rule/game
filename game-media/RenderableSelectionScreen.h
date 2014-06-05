#pragma once

#include "engine-renderer/IRenderable.h"
#include "SelectionScreenData.h"

class GAMEMEDIADLL RenderableSelectionScreen : public StaticObject, public IRenderable
{
private:
	RenderingEngine *engine;
	std::vector<Player*> players;
	SelectionScreenData::Objects *objectData;

public:
	RenderableSelectionScreen(SelectionScreenData::Objects *objectData);
	virtual ~RenderableSelectionScreen();

	virtual void render();
};
