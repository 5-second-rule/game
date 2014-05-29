#include "SelectionScreenData.h"

SelectionScreenData::SelectionScreenData(RenderableMovingObject *(&playerObjects)[4]) {
	RenderingEngine *engine =
		RenderableGame::getGlobalInstance()->getRenderingEngineInstance();

	const int MAX_PLAYERS = 4;
	const float MARGIN = 0.05;
	float scale = (2.0 - 5 * MARGIN) / 8;
	Transmission::Index rectangleIndices[6] = { 0, 1, 2, 3, 0, 2 };
	char *otherModelNames[4] = {
		"resources/select-name-ecoli.dds",
		"resources/select-name-chickenpox.dds",
		"resources/select-name-syphilis.dds",
		"resources/select-name-malaria.dds"
	};
	char *myModelNames[4] = {
		"resources/select-my-ecoli.dds",
		"resources/select-my-chickenpox.dds",
		"resources/select-my-syphilis.dds",
		"resources/select-my-malaria.dds"
	};

	// Create background for this screen
	this->backgroundVertices[0] = { { -1.0f, 1.0f, 0.0f }, { 0, 0 }, { 0, 0, -1 }, {} };
	this->backgroundVertices[1] = { { 1.0f, 1.0f, 0.0f }, { 1, 0 }, { 0, 0, -1 }, {} };
	this->backgroundVertices[2] = { { 1.0f, -1.0f, 0.0f }, { 1, 1 }, { 0, 0, -1 }, {} };
	this->backgroundVertices[3] = { { -1.0f, -1.0f, 0.0f }, { 0, 1 }, { 0, 0, -1 }, {} };
	this->backgroundModel = engine->create2DModelFromScratch(backgroundVertices, 4, rectangleIndices, 6, "resources/select-background.dds", textures, false);
	this->objectData.backgroundObject = new RenderableStaticObject(ObjectTypes::SelectionScreen, backgroundModel);

	// Create object for screen title, e.g., "Choose Player"
	this->calculateTitleVertices(titleVertices, 800, 600);
	this->titleModel = engine->create2DModelFromScratch(titleVertices, 4, rectangleIndices, 6, "resources/select-title.dds", textures, true);
	this->objectData.titleObject = new RenderableStaticObject(ObjectTypes::SelectionScreen, titleModel);

	for (int i = 0; i < MAX_PLAYERS; ++i) {
		// Create backgound for each player model and find its center
		this->objectData.playerCenters[i] = this->calculatePlayerBackgroundVertices(playerVertices, i, MARGIN) * 5.5;
		this->otherPlayerBackgroundModels[i] = engine->create2DModelFromScratch(playerVertices, 4, rectangleIndices, 6, "resources/select-rectangle.dds", textures, false);
		this->objectData.otherPlayerBackgroundObjects[i] = new RenderableStaticObject(ObjectTypes::SelectionScreen, otherPlayerBackgroundModels[i]);
		this->myPlayerBackgroundModels[i] = engine->create2DModelFromScratch(playerVertices, 4, rectangleIndices, 6, "resources/select-my-rectangle.dds", textures, false);
		this->objectData.myPlayerBackgroundObjects[i] = new RenderableStaticObject(ObjectTypes::SelectionScreen, myPlayerBackgroundModels[i]);
		
		// Create the name for each model
		this->calculatePlayerNameVertices(playerVertices, i, MARGIN);
		this->otherPlayerNameModels[i] = engine->create2DModelFromScratch(playerVertices, 4, rectangleIndices, 6, otherModelNames[i], textures, true);
		this->objectData.otherPlayerNameObjects[i] = new RenderableStaticObject(i, otherPlayerNameModels[i]);
		this->myPlayerNameModels[i] = engine->create2DModelFromScratch(playerVertices, 4, rectangleIndices, 6, myModelNames[i], textures, true);
		this->objectData.otherPlayerNameObjects[i] = new RenderableStaticObject(i, myPlayerNameModels[i]);

		// Store the model
		this->objectData.playerObjects[i] = playerObjects[i];
	}

	// Make models all approximately the same size
	this->objectData.playerObjects[ObjectTypes::Ecoli]->getMoveable()->setScale(scale);
	this->objectData.playerObjects[ObjectTypes::ChickenPox]->getMoveable()->setScale(scale);
	this->objectData.playerObjects[ObjectTypes::Malaria]->getMoveable()->setScale(scale*0.9);
	this->objectData.playerObjects[ObjectTypes::Syphillis]->getMoveable()->setScale(scale*3.0);
}

SelectionScreenData::~SelectionScreenData() {}

void SelectionScreenData::calculateTitleVertices(Transmission::Vertex *vertices, float winHeight, float winWidth) {
	float scale;
	if (winHeight < winWidth)
		scale = winHeight / winWidth / 2;
	else
		scale = winWidth / winHeight / 2;

	float l = -2.0 * scale,
		r = 2.0 * scale,
		t = 1.0,
		b = 1.0 - scale;

	vertices[0] = { { l, t, 0.0f }, { 0, 0 }, { 0, 0, -1 }, {} };
	vertices[1] = { { r, t, 0.0f }, { 1, 0 }, { 0, 0, -1 }, {} };
	vertices[2] = { { r, b, 0.0f }, { 1, 1 }, { 0, 0, -1 }, {} };
	vertices[3] = { { l, b, 0.0f }, { 0, 1 }, { 0, 0, -1 }, {} };

	// don't think these calculations are right but I can't think
}

void SelectionScreenData::calculatePlayerNameVertices(Transmission::Vertex *vertices, int playerIndex, float margin) {
	float numMargins[] = { -1.5, -0.5, 0.5, 1.5 };
	float pos[] = { -2, -1, 0, 1 };
	float width = (2.0 - 5 * margin) / 4;
	float height = width * 0.80 * 0.237;

	float edgeB = -0.7 + width * 0.1;
	float edgeT = edgeB + height;

	float edgeL = pos[playerIndex] * width + numMargins[playerIndex] * margin + width * 0.1;
	float edgeR = edgeL + width * 0.80;

	vertices[0] = { { edgeL, edgeT, 0.0f }, { 0, 0 }, { 0, 0, -1 }, {} };
	vertices[1] = { { edgeR, edgeT, 0.0f }, { 1, 0 }, { 0, 0, -1 }, {} };
	vertices[2] = { { edgeR, edgeB, 0.0f }, { 1, 1 }, { 0, 0, -1 }, {} };
	vertices[3] = { { edgeL, edgeB, 0.0f }, { 0, 1 }, { 0, 0, -1 }, {} };
}

float SelectionScreenData::calculatePlayerBackgroundVertices(Transmission::Vertex *vertices, int playerIndex, float margin) {
	float numMargins[] = { -1.5, -0.5, 0.5, 1.5 };
	float pos[] = { -2, -1, 0, 1 };

	float edgeT = 0.5;
	float edgeB = -0.7;

	float width = (2.0 - 5 * margin) / 4;

	float edgeL = pos[playerIndex] * width + numMargins[playerIndex] * margin;
	float edgeR = edgeL + width;

	vertices[0] = { { edgeL, edgeT, 0.0f }, { 0, 0 }, { 0, 0, -1 }, {} };
	vertices[1] = { { edgeR, edgeT, 0.0f }, { 1, 0 }, { 0, 0, -1 }, {} };
	vertices[2] = { { edgeR, edgeB, 0.0f }, { 1, 1 }, { 0, 0, -1 }, {} };
	vertices[3] = { { edgeL, edgeB, 0.0f }, { 0, 1 }, { 0, 0, -1 }, {} };

	return edgeL + width / 2;
}

SelectionScreenData::Objects *SelectionScreenData::getData() {
	return &(this->objectData);
}
