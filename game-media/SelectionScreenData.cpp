#include "SelectionScreenData.h"

SelectionScreenData::SelectionScreenData(RenderableMovingObject *(&playerObjects)[4]) {
	RenderingEngine *engine =
		RenderableGame::getGlobalInstance()->getRenderingEngineInstance();

	const int MAX_PLAYERS = 4;
	const float MARGIN = 0.05f;
	float scale = (2.0f - 5 * MARGIN) / 8;
	Transmission::Index rectangleIndices[6] = { 0, 1, 2, 3, 0, 2 };
	char *otherModelNames[4] = {
		"resources/select-name-ecoli-noarrows.dds",
		"resources/select-name-chickenpox-noarrows.dds",
		"resources/select-name-syphilis-noarrows.dds",
		"resources/select-name-malaria-noarrows.dds"
	};
	char *myModelNames[4] = {
		"resources/select-name-ecoli.dds",
		"resources/select-name-chickenpox.dds",
		"resources/select-name-syphilis.dds",
		"resources/select-name-malaria.dds"
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
		this->objectData.playerCenters[i] = this->calculatePlayerBackgroundVertices(playerbackgroundVertices, i, MARGIN) * 5.5f;
		this->otherPlayerBackgroundModels[i] = engine->create2DModelFromScratch(playerbackgroundVertices, 4, rectangleIndices, 6, "resources/select-rectangle.dds", textures, false);
		this->objectData.otherPlayerBackgroundObjects[i] = new RenderableStaticObject(ObjectTypes::SelectionScreen, otherPlayerBackgroundModels[i]);
		this->myPlayerBackgroundModels[i] = engine->create2DModelFromScratch(playerbackgroundVertices, 4, rectangleIndices, 6, "resources/select-rectangle.dds", textures, false);
		this->objectData.myPlayerBackgroundObjects[i] = new RenderableStaticObject(ObjectTypes::SelectionScreen, myPlayerBackgroundModels[i]);

		// Create the name for each model
		for (int j = 0; j < 4; ++j) {
			int index = i * 4 + j;
			this->calculatePlayerNameVertices(playerNameVertices, i, MARGIN);
			this->otherPlayerNameModels[index] = engine->create2DModelFromScratch(playerNameVertices, 4, rectangleIndices, 6, otherModelNames[j], textures, true);
			this->objectData.otherPlayerNameObjects[index] = new RenderableStaticObject(j, otherPlayerNameModels[index]);
			this->myPlayerNameModels[index] = engine->create2DModelFromScratch(playerNameVertices, 4, rectangleIndices, 6, myModelNames[j], textures, true);
			this->objectData.myPlayerNameObjects[index] = new RenderableStaticObject(j, myPlayerNameModels[index]);
		}

	//	// Store the model
		this->objectData.playerObjects[i] = playerObjects[i];
	}
	//s all approximately the same size
	this->objectData.playerObjects[ObjectTypes::Ecoli]->getMoveable()->setScale(scale);
	this->objectData.playerObjects[ObjectTypes::ChickenPox]->getMoveable()->setScale(scale);
	this->objectData.playerObjects[ObjectTypes::Malaria]->getMoveable()->setScale(scale*0.9f);
	this->objectData.playerObjects[ObjectTypes::Syphillis]->getMoveable()->setScale(scale*3.0f);
}

SelectionScreenData::~SelectionScreenData() {
	delete this->objectData.backgroundObject;
	delete this->objectData.titleObject;
	this->objectData.backgroundObject = nullptr;
	this->objectData.titleObject = nullptr;
	
	for (int i = 0; i < 4; ++i) {
		delete this->objectData.otherPlayerBackgroundObjects[i];
		delete this->objectData.myPlayerBackgroundObjects[i];
		this->objectData.otherPlayerBackgroundObjects[i] = nullptr;
		this->objectData.myPlayerBackgroundObjects[i] = nullptr;
	}
	
	for (int i = 0; i < 16; ++i) {
		delete this->objectData.otherPlayerNameObjects[i];
		delete this->objectData.myPlayerNameObjects[i];
		this->objectData.otherPlayerNameObjects[i] = nullptr;
		this->objectData.myPlayerNameObjects[i] = nullptr;
	}
}

void SelectionScreenData::calculateTitleVertices(Transmission::Vertex *vertices, float winHeight, float winWidth) {
	float scale;
	if (winHeight < winWidth)
		scale = winHeight / winWidth / 2;
	else
		scale = winWidth / winHeight / 2;

	float l = -2.0f * scale,
		r = 2.0f * scale,
		t = 1.0f,
		b = 1.0f - scale;

	vertices[0] = { { l, t, 0.0f }, { 0, 0 }, { 0, 0, -1 }, {} };
	vertices[1] = { { r, t, 0.0f }, { 1, 0 }, { 0, 0, -1 }, {} };
	vertices[2] = { { r, b, 0.0f }, { 1, 1 }, { 0, 0, -1 }, {} };
	vertices[3] = { { l, b, 0.0f }, { 0, 1 }, { 0, 0, -1 }, {} };

	// don't think these calculations are right but I can't think
}

void SelectionScreenData::calculatePlayerNameVertices(Transmission::Vertex *vertices, int playerIndex, float margin) {
	float numMargins[] = { -1.5, -0.5, 0.5, 1.5 };
	float pos[] = { -2, -1, 0, 1 };
	float width = (2.0f - 5 * margin) / 4;
	float height = width * 0.80f * 0.237f;

	float edgeB = -0.7f + width * 0.1f;
	float edgeT = edgeB + height;

	float edgeL = pos[playerIndex] * width + numMargins[playerIndex] * margin + width * 0.1f;
	float edgeR = edgeL + width * 0.80f;

	vertices[0] = { { edgeL, edgeT, 0.0f }, { 0, 0 }, { 0, 0, -1 }, {} };
	vertices[1] = { { edgeR, edgeT, 0.0f }, { 1, 0 }, { 0, 0, -1 }, {} };
	vertices[2] = { { edgeR, edgeB, 0.0f }, { 1, 1 }, { 0, 0, -1 }, {} };
	vertices[3] = { { edgeL, edgeB, 0.0f }, { 0, 1 }, { 0, 0, -1 }, {} };
}

float SelectionScreenData::calculatePlayerBackgroundVertices(Transmission::Vertex *vertices, int playerIndex, float margin) {
	float numMargins[] = { -1.5f, -0.5f, 0.5f, 1.5f };
	float pos[] = { -2, -1, 0, 1 };

	float edgeT = 0.5f;
	float edgeB = -0.7f;

	float width = (2.0f - 5.0f * margin) / 4.0f;

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