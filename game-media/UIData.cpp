#include "UIData.h"
#include "RenderableGame.h"
#include "game-core/ObjectTypes.h"
#include "renderer/Model.h"
#include <vector>

UIData::UIData() {
	this->engine = RenderableGame::getGlobalInstance()->getRenderingEngineInstance();

	const int MAX_PLAYERS = 4;
	const float MARGIN = 0.02f;
	float scale = (2.0f - 5 * MARGIN) / 8;
	Transmission::Index rectangleIndices[6] = { 0, 1, 2, 3, 0, 2 };
	char *modelNames[4] = {
		"resources/ui-ecoli2D.dds",
		"resources/ui-chickenpox2D.dds",
		"resources/ui-syphilis2D.dds",
		"resources/ui-malaria2D.dds"
	};

	for (int i = 0; i < MAX_PLAYERS; ++i) {
		this->calculatePlayerVertices(this->vertices, i, MARGIN);
		this->player1Models[i] = engine->create2DModelFromScratch(vertices, 4, rectangleIndices, 6, modelNames[i], textures, true);
		this->objectData.player1Objects[i] = new RenderableMovingObject(ObjectTypes::UI, player1Models[i]);
	}
}

UIData::~UIData() {}

void UIData::calculateNumberVertices(Transmission::Vertex *vertices, int playerIndex, float margin) {
	float imgWidth, imgHeight, h_w_ratio;
	imgWidth = 1100;
	imgHeight = 221;
	h_w_ratio = imgHeight / imgWidth;

	float l = -1.0f + margin,
		r = 1.0f - margin,
		t = 1.0f - margin,
		b = t - h_w_ratio * 2;

	vertices[0] = { { l, t, 0.0f }, { 0, 0 }, { 0, 0, -1 }, {} };
	vertices[1] = { { r, t, 0.0f }, { 1, 0 }, { 0, 0, -1 }, {} };
	vertices[2] = { { r, b, 0.0f }, { 1, 1 }, { 0, 0, -1 }, {} };
	vertices[3] = { { l, b, 0.0f }, { 0, 1 }, { 0, 0, -1 }, {} };

	// don't think these calculations are right but I can't think
}

void UIData::calculatePlayerVertices(Transmission::Vertex *vertices, int playerIndex, float margin) {
	float imgWidth, imgHeight, h_w_ratio, h_offset, winRatio;
	if (this->engine->getWindowWidth() == 0 || this->engine->getWindowHeight() == 0) {
		winRatio = 800.0f / 600.0f;
	} else {
		winRatio = 1.0f * this->engine->getWindowWidth() / this->engine->getWindowHeight();
	}
	
	imgWidth = 350;
	imgHeight = 500;
	h_w_ratio = imgHeight / imgWidth;
	h_offset = 0;

	float width = 0.075f;
	float height = (width * h_w_ratio * winRatio);

	float edgeT = 1.0f - margin;
	float edgeB = edgeT - height;
	
	float edgeL = -1.0f + margin;
	float edgeR = edgeL + width;

	vertices[0] = { { edgeL, edgeT, 0.0f }, { 0, 0 }, { 0, 0, -1 }, {} };
	vertices[1] = { { edgeR, edgeT, 0.0f }, { 1, 0 }, { 0, 0, -1 }, {} };
	vertices[2] = { { edgeR, edgeB, 0.0f }, { 1, 1 }, { 0, 0, -1 }, {} };
	vertices[3] = { { edgeL, edgeB, 0.0f }, { 0, 1 }, { 0, 0, -1 }, {} };
}

UIData::Objects *UIData::getData() {
	return &(this->objectData);
}