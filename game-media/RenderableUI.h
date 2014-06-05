#pragma once

#include "engine-renderer/IRenderable.h"
#include "UIData.h"

class GAMEMEDIADLL RenderableUI : public StaticObject, public IRenderable {
private:
	RenderingEngine *engine;
	std::vector<Player*> players;
	UIData::Objects *objectData;

public:
	RenderableUI(UIData::Objects *objectData);
	virtual ~RenderableUI();

	virtual void render();
};