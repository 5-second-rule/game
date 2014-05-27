#include "RenderableSelectionScreen.h"

using namespace Transmission;

RenderableSelectionScreen::RenderableSelectionScreen(RenderableStaticObject *(&playerObjects)[4]) : StaticObject(ObjectTypes::SelectionScreen) {
	RenderingEngine *engine =
		RenderableGame::getGlobalInstance()->getRenderingEngineInstance();

	const int MAX_PLAYERS = 4;
	const float MARGIN = 0.05;

	char *names[4] = {
		"resources/select-name-ecoli.dds",
		"resources/select-name-chickenpox.dds",
		"resources/select-name-syphilis.dds",
		"resources/select-name-malaria.dds"
	};

	this->backgroundVertices[0] = {{ -1.0f,  1.0f, 0.0f }, { 0, 0 }, { 0, 0, -1 }, {} };
	this->backgroundVertices[1] = {{  1.0f,  1.0f, 0.0f }, { 1, 0 }, { 0, 0, -1 }, {} };
	this->backgroundVertices[2] = {{  1.0f, -1.0f, 0.0f }, { 1, 1 }, { 0, 0, -1 }, {} };
	this->backgroundVertices[3] = {{ -1.0f, -1.0f, 0.0f }, { 0, 1 }, { 0, 0, -1 }, {} };

	this->calculateTitleVertices(titleVertices, 800, 600);

	Transmission::Index rectangleIndices[6] = { 0, 1, 2, 3, 0, 2 };

	
	for (int i = 0; i < MAX_PLAYERS; ++i) {
		this->playerCenters[i] = this->calculatePlayerBackgroundVertices(playerVertices, i, MARGIN);
		if (i == 0) {
			backgroundModel = engine->create2DModelFromScratch(backgroundVertices, 4, rectangleIndices, 6, "resources/select-background.dds", textures);
		}
		calculatePlayerNameVertices(playerVertices, i, MARGIN);
		this->playerNameModels[i] = engine->create2DModelFromScratch(playerVertices, 4, rectangleIndices, 6, names[i], textures);
		this->playerNameObjects[i] = new RenderableStaticObject(i, playerNameModels[i]);
		this->playerObjects[i] = playerObjects[i];
	}

	titleModel = engine->create2DModelFromScratch(titleVertices, 4, rectangleIndices, 6, "resources/select-title.dds", textures);
	playerbackgroundModel = engine->create2DModelFromScratch(playerVertices, 4, rectangleIndices, 6, "resources/select-rectangle.dds", textures);

	backgroundObject = new RenderableStaticObject(ObjectTypes::SelectionScreen, backgroundModel);
	titleObject = new RenderableStaticObject(ObjectTypes::SelectionScreen, titleModel);
	playerbackgroundObject = new RenderableStaticObject(ObjectTypes::SelectionScreen, playerbackgroundModel);
}


RenderableSelectionScreen::~RenderableSelectionScreen()
{
	delete backgroundObject;
	delete titleObject;
	delete playerbackgroundObject;

	backgroundObject = NULL;
	titleObject = NULL;
	playerbackgroundObject = NULL;

	for (int i = 0; i < 4; ++i) {
		delete playerNameObjects[i];
		delete playerObjects[i];
		playerNameObjects[i] = NULL;
		playerObjects[i] = NULL;
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

	float edgeT = 0.5;
	float edgeB = -0.7;

	float width = (2.0 - 5 * margin) / 4;

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
		float pos[3] = { this->playerCenters[i], 0.0, 0.0 };
		this->playerbackgroundObject->setPosition(pos);
		this->playerbackgroundObject->render();
		this->playerNameObjects[i]->setPosition(pos);
		this->playerNameObjects[i]->render();
		this->playerObjects[i]->setPosition(pos);
		this->playerObjects[i]->render();
	}
};
