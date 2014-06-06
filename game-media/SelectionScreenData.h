#pragma once
#include "RenderableMovingObject.h"
#include "RenderablePlayerMovingObject.h"
#include "RenderableStaticObject.h"
#include "renderer/Model.h"

class SelectionScreenData {
public:
	struct Objects {
		unsigned int width;
		unsigned int height;
		float playerCenters[4];
		RenderableStaticObject *backgroundObject;
		RenderableStaticObject *titleObject;
		RenderableStaticObject *otherPlayerBackgroundObjects[4];
		RenderableStaticObject *myPlayerBackgroundObjects[4];
		RenderableStaticObject *otherPlayerNameObjects[16];
		RenderableStaticObject *myPlayerNameObjects[16];
		RenderableStaticObject *checkMarkObjects[4];
		RenderablePlayerMovingObject *playerObjects[4];
	};
private:
	Objects objectData;
	RenderingEngine *engine;

	Transmission::Model *backgroundModel;
	Transmission::Model *titleModel;
	Transmission::Model *otherPlayerBackgroundModels[4];
	Transmission::Model *myPlayerBackgroundModels[4];
	Transmission::Model *otherPlayerNameModels[16];
	Transmission::Model *myPlayerNameModels[16];
	Transmission::Model *checkMarkModels[4];
	Transmission::Model *playerModels[4];

	Transmission::Vertex titleVertices[4];
	Transmission::Vertex playerbackgroundVertices[4];
	Transmission::Vertex playerNameVertices[4];
	Transmission::Vertex playerVertices[4];
	Transmission::Vertex backgroundVertices[4];

	std::vector<Transmission::Texture *>textures;
	void calculateTitleVertices(Transmission::Vertex *vertices, float margin);
	void calculatePlayerNameVertices(Transmission::Vertex *vertices, int playerIndex, float margin, bool isCheck);

	// returns center x screen coord of background
	float calculatePlayerBackgroundVertices(Transmission::Vertex *vertices, int playerIndex, float margin);

public:
	SelectionScreenData(RenderablePlayerMovingObject *(&playerObjects)[4]);
	~SelectionScreenData();
	Objects *getData();
};

