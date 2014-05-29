#pragma once
#include <vector>
#include "RenderableGame.h"
#include "RenderableMovingObject.h"
#include "RenderableStaticObject.h"
#include "renderer/Model.h"
#include "game-core/ObjectTypes.h"

class SelectionScreenData {
public:
	struct Objects {
		float playerCenters[4];
		RenderableStaticObject *backgroundObject;
		RenderableStaticObject *titleObject;
		RenderableStaticObject *otherPlayerBackgroundObjects[4];
		RenderableStaticObject *myPlayerBackgroundObjects[4];
		RenderableStaticObject *otherPlayerNameObjects[4];
		RenderableStaticObject *myPlayerNameObjects[4];
		RenderableMovingObject *playerObjects[4];
	};
private:
	Objects objectData;

	Transmission::Model *backgroundModel;
	Transmission::Model *titleModel;
	Transmission::Model *otherPlayerBackgroundModels[4];
	Transmission::Model *myPlayerBackgroundModels[4];
	Transmission::Model *otherPlayerNameModels[4];
	Transmission::Model *myPlayerNameModels[4];
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

public:
	SelectionScreenData(RenderableMovingObject *(&playerObjects)[4]);
	~SelectionScreenData();
	Objects *getData();
};

