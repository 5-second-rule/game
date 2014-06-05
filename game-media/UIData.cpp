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
	char *playerTextures[4] = {
		"resources/ui-ecoli2D.dds",
		"resources/ui-chickenpox2D.dds",
		"resources/ui-syphilis2D.dds",
		"resources/ui-malaria2D.dds"
	};

	char *numberTextures[10] = {
		"resources/ui-number-0.dds",
		"resources/ui-number-1.dds",
		"resources/ui-number-2.dds",
		"resources/ui-number-3.dds",
		"resources/ui-number-4.dds",
		"resources/ui-number-5.dds",
		"resources/ui-number-6.dds",
		"resources/ui-number-7.dds",
		"resources/ui-number-8.dds",
		"resources/ui-number-9.dds"
	};

	float lastEdge;
	lastEdge = this->calculatePlayerVertices(this->vertices, MARGIN, false);

	for (int i = 0; i < MAX_PLAYERS; ++i) {
		this->playerModels[i] = engine->create2DModelFromScratch(vertices, 4, rectangleIndices, 6, playerTextures[i], textures, true);
		this->objectData.playerObjects[i] = new RenderableMovingObject(ObjectTypes::UI, playerModels[i]);
	}

	lastEdge=this->calculateXVertices(this->vertices, MARGIN, lastEdge, false);
	this->xModel = engine->create2DModelFromScratch(vertices, 4, rectangleIndices, 6, "resources/ui-x.dds", textures, true);
	this->objectData.xObject = new RenderableMovingObject(ObjectTypes::UI, xModel);

	this->calculateNumberVertices(this->vertices, MARGIN, lastEdge, false);
	for (int i = 0; i < 10; ++i) {
		this->numberModels[i] = engine->create2DModelFromScratch(vertices, 4, rectangleIndices, 6, numberTextures[i], textures, true);
		this->objectData.numberObjects[i] = new RenderableMovingObject(ObjectTypes::UI, numberModels[i]);
	}

	lastEdge = this->calculatePlayerVertices(this->vertices, MARGIN, true);
	for (int i = 0; i < MAX_PLAYERS; ++i) {
		this->jumboPlayerModels[i] = engine->create2DModelFromScratch(vertices, 4, rectangleIndices, 6, playerTextures[i], textures, true);
		this->objectData.jumboPlayerObjects[i] = new RenderableMovingObject(ObjectTypes::UI, jumboPlayerModels[i]);
	}

	lastEdge = this->calculateXVertices(this->vertices, MARGIN, lastEdge, true);
	this->jumboXModel = engine->create2DModelFromScratch(vertices, 4, rectangleIndices, 6, "resources/ui-x.dds", textures, true);
	this->objectData.jumbboXObject = new RenderableMovingObject(ObjectTypes::UI, jumboXModel);

	this->calculateNumberVertices(this->vertices, MARGIN, lastEdge, true);
	for (int i = 0; i < 10; ++i) {
		this->jumboNumberModels[i] = engine->create2DModelFromScratch(vertices, 4, rectangleIndices, 6, numberTextures[i], textures, true);
		this->objectData.jumboNumberObjects[i] = new RenderableMovingObject(ObjectTypes::UI, jumboNumberModels[i]);
	}
}

UIData::~UIData() {}

float UIData::calculatePlayerVertices(Transmission::Vertex *vertices, float margin, bool isJumbo) {
	float imgWidth, imgHeight, h_w_ratio, winRatio;
	if (this->engine->getWindowWidth() == 0 || this->engine->getWindowHeight() == 0) {
		winRatio = 800.0f / 600.0f;
	} else {
		winRatio = 1.0f * this->engine->getWindowWidth() / this->engine->getWindowHeight();
	}
	
	imgWidth = 350;
	imgHeight = 500;
	h_w_ratio = imgHeight / imgWidth;

	float width = isJumbo ? 0.075f * 1.5f: 0.075f;
	float height = (width * h_w_ratio * winRatio);

	float edgeT = 1.0f - margin;
	float edgeB = edgeT - height;
	
	float edgeL = -1.0f + margin;
	float edgeR = edgeL + width;

	vertices[0] = { { edgeL, edgeT, 0.0f }, { 0, 0 }, { 0, 0, -1 }, {} };
	vertices[1] = { { edgeR, edgeT, 0.0f }, { 1, 0 }, { 0, 0, -1 }, {} };
	vertices[2] = { { edgeR, edgeB, 0.0f }, { 1, 1 }, { 0, 0, -1 }, {} };
	vertices[3] = { { edgeL, edgeB, 0.0f }, { 0, 1 }, { 0, 0, -1 }, {} };

	this->playerHeight = height;
	return edgeR;
}

float UIData::calculateXVertices(Transmission::Vertex *vertices, float margin, float lastEdge, bool isJumbo) {
	float imgWidth, imgHeight, h_w_ratio, winRatio;
	if (this->engine->getWindowWidth() == 0 || this->engine->getWindowHeight() == 0) {
		winRatio = 800.0f / 600.0f;
	} else {
		winRatio = 1.0f * this->engine->getWindowWidth() / this->engine->getWindowHeight();
	}

	imgWidth = 111;
	imgHeight = 129;
	h_w_ratio = imgHeight / imgWidth;

	float width = isJumbo ? 0.024f * 1.5f : 0.024f;
	float height = (width * h_w_ratio * winRatio);

	float edgeT = (1.0f - margin) - (this->playerHeight - height) / 2.0f;
	float edgeB = edgeT - height;

	float edgeL = lastEdge + 0.01f;
	float edgeR = edgeL + width;

	vertices[0] = { { edgeL, edgeT, 0.0f }, { 0, 0 }, { 0, 0, -1 }, {} };
	vertices[1] = { { edgeR, edgeT, 0.0f }, { 1, 0 }, { 0, 0, -1 }, {} };
	vertices[2] = { { edgeR, edgeB, 0.0f }, { 1, 1 }, { 0, 0, -1 }, {} };
	vertices[3] = { { edgeL, edgeB, 0.0f }, { 0, 1 }, { 0, 0, -1 }, {} };

	return edgeR;
}

void UIData::calculateNumberVertices(Transmission::Vertex *vertices, float margin, float lastEdge, bool isJumbo) {
	float imgWidth, imgHeight, h_w_ratio, winRatio;
	if (this->engine->getWindowWidth() == 0 || this->engine->getWindowHeight() == 0) {
		winRatio = 800.0f / 600.0f;
	} else {
		winRatio = 1.0f * this->engine->getWindowWidth() / this->engine->getWindowHeight();
	}

	imgWidth = 186;
	imgHeight = 234;
	h_w_ratio = imgHeight / imgWidth;

	float width = isJumbo ? 0.04f * 1.5f : 0.04f;
	float height = (width * h_w_ratio * winRatio);

	float edgeT = (1.0f - margin) - (this->playerHeight - height) / 2.0f;
	float edgeB = edgeT - height;

	float edgeL = lastEdge + 0.01f;
	float edgeR = edgeL + width;

	vertices[0] = { { edgeL, edgeT, 0.0f }, { 0, 0 }, { 0, 0, -1 }, {} };
	vertices[1] = { { edgeR, edgeT, 0.0f }, { 1, 0 }, { 0, 0, -1 }, {} };
	vertices[2] = { { edgeR, edgeB, 0.0f }, { 1, 1 }, { 0, 0, -1 }, {} };
	vertices[3] = { { edgeL, edgeB, 0.0f }, { 0, 1 }, { 0, 0, -1 }, {} };
}

UIData::Objects *UIData::getData() {
	return &(this->objectData);
}