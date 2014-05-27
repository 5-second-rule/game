#include "RenderableSelectionScreen.h"

using namespace Transmission;

RenderableSelectionScreen::RenderableSelectionScreen()
{
	RenderingEngine *engine =
		RenderableGame::getGlobalInstance()->getRenderingEngineInstance();

	const int MAX_PLAYERS = 4;
	const float MARGIN = 0.05;

	Transmission::Model *backgroundModel;
	Transmission::Model *titleModel;
	Transmission::Model *playerbackgroundModels[4];
	Transmission::Model *playerModels[4];

	Transmission::Vertex titleVertices[4];
	Transmission::Vertex playerbackgroundVertices[4];
	Transmission::Vertex playerVertices[4];

	Transmission::Vertex backgroundVertices[4] =
		{ {{ -1.0f,  1.0f, 0.0f }, { 0, 0 }, { 0, 0, -1 }, {} },
		  {{  1.0f,  1.0f, 0.0f }, { 1, 0 }, { 0, 0, -1 }, {} },
		  {{  1.0f, -1.0f, 0.0f }, { 1, 1 }, { 0, 0, -1 }, {} },
		  {{ -1.0f, -1.0f, 0.0f }, { 0, 1 }, { 0, 0, -1 }, {} } };

	this->calculateTitleVertices(titleVertices, 800, 600);

	float centers[MAX_PLAYERS];
	for (int i = 0; i < MAX_PLAYERS; ++i) {
		centers[i] = this->calculatePlayerBackgroundVertices(playerVertices, i, MARGIN);
	}

	Transmission::Index rectangleIndices[6]	= { 0, 1, 2, 3, 0, 2 };

	backgroundModel = engine->create2DModelFromVertices(backgroundVertices, 4, rectangleIndices, 6, windowBgTex);
	titleModel = engine->create2DModelFromVertices(titleVertices, 4, rectangleIndices, 6, titleTex);
	

	
}


RenderableSelectionScreen::~RenderableSelectionScreen()
{
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
	this->backgroundModel->draw();
	this->titleModel->draw();
	
	for (int i = 0; i < 4; ++i) {
		this->playerbackgroundModels[i]->draw();
		this->playerModels[i]->draw();
	}
	
};
