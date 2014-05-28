#include "RenderableSelectionScreen.h"

using namespace Transmission;

RenderableSelectionScreen::RenderableSelectionScreen(RenderableMovingObject *(&playerObjects)[4])
: StaticObject(ObjectTypes::SelectionScreen) {

	RenderingEngine *engine =
		RenderableGame::getGlobalInstance()->getRenderingEngineInstance();

	const int MAX_PLAYERS = 4;
	const float MARGIN = 0.05;
	float scale = (2.0 - 5 * MARGIN) / 8;

	char *names[4] = {
		"resources/select-name-ecoli.dds",
		"resources/select-name-chickenpox.dds",
		"resources/select-name-syphilis.dds",
		"resources/select-name-malaria.dds"
	};

	this->backgroundVertices[0] = { { -1.0f, 1.0f, 0.0f }, { 0, 0 }, { 0, 0, -1 }, {} };
	this->backgroundVertices[1] = { { 1.0f, 1.0f, 0.0f }, { 1, 0 }, { 0, 0, -1 }, {} };
	this->backgroundVertices[2] = { { 1.0f, -1.0f, 0.0f }, { 1, 1 }, { 0, 0, -1 }, {} };
	this->backgroundVertices[3] = { { -1.0f, -1.0f, 0.0f }, { 0, 1 }, { 0, 0, -1 }, {} };

	this->calculateTitleVertices(titleVertices, 800, 600);

	Transmission::Index rectangleIndices[6] = { 0, 1, 2, 3, 0, 2 };

	for (int i = 0; i < MAX_PLAYERS; ++i) {
		this->playerCenters[i] = this->calculatePlayerBackgroundVertices(playerVertices, i, MARGIN) * 5.5;
		playerbackgroundModels[i] = engine->create2DModelFromScratch(playerVertices, 4, rectangleIndices, 6, "resources/select-rectangle.dds", textures, false);
		playerbackgroundObjects[i] = new RenderableStaticObject(ObjectTypes::SelectionScreen, playerbackgroundModels[i]);
		calculatePlayerNameVertices(playerVertices, i, MARGIN);
		this->playerNameModels[i] = engine->create2DModelFromScratch(playerVertices, 4, rectangleIndices, 6, names[i], textures, true);
		this->playerNameObjects[i] = new RenderableStaticObject(i, playerNameModels[i]);
		this->playerObjects[i] = playerObjects[i];
	}

	this->playerObjects[ObjectTypes::Ecoli]->getMoveable()->setScale(scale);
	this->playerObjects[ObjectTypes::ChickenPox]->getMoveable()->setScale(scale);
	this->playerObjects[ObjectTypes::Malaria]->getMoveable()->setScale(scale*0.9);
	this->playerObjects[ObjectTypes::Syphillis]->getMoveable()->setScale(scale*3.0);

	backgroundModel = engine->create2DModelFromScratch(backgroundVertices, 4, rectangleIndices, 6, "resources/select-background.dds", textures, false);
	titleModel = engine->create2DModelFromScratch(titleVertices, 4, rectangleIndices, 6, "resources/select-title.dds", textures, true);

	backgroundObject = new RenderableStaticObject(ObjectTypes::SelectionScreen, backgroundModel);
	titleObject = new RenderableStaticObject(ObjectTypes::SelectionScreen, titleModel);
}

RenderableSelectionScreen::~RenderableSelectionScreen() {
	delete backgroundObject;
	delete titleObject;
	backgroundObject = nullptr;
	titleObject = nullptr;

	for (int i = 0; i < 4; ++i) {
		delete playerbackgroundObjects[i];
		delete playerNameObjects[i];
		delete playerObjects[i];
		playerbackgroundObjects[i] = nullptr;
		playerNameObjects[i] = nullptr;
		playerObjects[i] = nullptr;

	}
}

void RenderableSelectionScreen::calculateTitleVertices(Transmission::Vertex *vertices, float winHeight, float winWidth) {
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

void RenderableSelectionScreen::calculatePlayerNameVertices(Transmission::Vertex *vertices, int playerIndex, float margin) {
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

float RenderableSelectionScreen::calculatePlayerBackgroundVertices(Transmission::Vertex *vertices, int playerIndex, float margin) {
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

void RenderableSelectionScreen::render() {
	this->backgroundObject->render();
	this->titleObject->render();

	for (int i = 0; i < 4; ++i) {
		this->playerbackgroundObjects[i]->render();
		this->playerNameObjects[i]->render();
	}

	for (int i = 0; i < 4; ++i) {
		//this->get
		//Common::Vector4 pos = Common::Vector4(this->playerCenters[i], 0, 0, 1);
		//this->playerObjects[i]->setPosition(pos);
		//this->playerObjects[i]->render();
	}

};
