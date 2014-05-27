#pragma once

#include "engine-renderer/IRenderable.h"
#include "RenderableGameObjectCtorTable.h"
#include "RenderableMovingObject.h"
#include "RenderableStaticObject.h"
#include "renderer/Model.h"
#include "game-core/ObjectTypes.h"

class RenderableSelectionScreen : public StaticObject, public IRenderable
{
private:
	float playerCenters[4];

	Transmission::Model *backgroundModel;
	Transmission::Model *titleModel;
	Transmission::Model *playerbackgroundModels[4];
	Transmission::Model *playerNameModels[4];
	Transmission::Model *playerModels[4];

	Transmission::Vertex titleVertices[4];
	Transmission::Vertex playerbackgroundVertices[4];
	Transmission::Vertex playerNameVertices[4];
	Transmission::Vertex playerVertices[4];
	Transmission::Vertex backgroundVertices[4];

	std::vector<Transmission::Texture *>textures;
	void calculateTitleVertices(Transmission::Vertex *vertices, float winHeight, float winWidth);
	void calculatePlayerNameVertices(Transmission::Vertex *vertices, int playerIndex, float margin);
	// returns center x screen coord of background
	float calculatePlayerBackgroundVertices(Transmission::Vertex *vertices, int playerIndex, float margin);

protected:
	RenderableStaticObject *backgroundObject;
	RenderableStaticObject *titleObject;
	RenderableStaticObject *playerbackgroundObjects[4];
	RenderableStaticObject *playerNameObjects[4];
	RenderableStaticObject *playerObjects[4];

public:
	RenderableSelectionScreen(RenderableStaticObject *(&playerObjects)[4]);
	virtual ~RenderableSelectionScreen();

	virtual void render();
};
