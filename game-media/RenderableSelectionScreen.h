#pragma once

#include "engine-renderer/IRenderable.h"
#include "RenderableStaticObject.h"
#include "renderer/Model.h"

class RenderableSelectionScreen : public IRenderable
{
private:
	RenderableStaticObject *backgroundModel;
	RenderableStaticObject *titleModel;
	RenderableStaticObject *playerbackgroundModels[4];
	RenderableStaticObject *playerModels[4];

	void calculateTitleVertices(Transmission::Vertex *vertices, float winHeight, float winWidth);

	// returns center x screen coord of background
	float calculatePlayerBackgroundVertices(Transmission::Vertex *vertices, int playerIndex, float margin);

public:
	RenderableSelectionScreen();
	virtual ~RenderableSelectionScreen();

	virtual void render();
};
