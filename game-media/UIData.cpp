#include "UIData.h"
#include "RenderableGame.h"
#include "game-core/ObjectTypes.h"
#include "renderer/Model.h"
#include <vector>

UIData::UIData() {
	this->engine = RenderableGame::getGlobalInstance()->getRenderingEngineInstance();

	const int MAX_PLAYERS = 4;
	const int BOOST_BARS = 4;
	this->margin = 0.02f;
	float scale = (2.0f - 5 * this->margin) / 8;
	Transmission::Index rectangleIndices[6] = { 0, 1, 2, 3, 0, 2 };
	char *playerTextures[4] = {
		"resources/ui-ecoli2D.dds",
		"resources/ui-chickenpox2D.dds",
		"resources/ui-syphilis2D.dds",
		"resources/ui-malaria2D.dds"
	};

	char *glowPlayerTextures[4] = {
		"resources/ui-ecoliglow.dds",
		"resources/ui-chickenpoxglow.dds",
		"resources/ui-syphilisglow.dds",
		"resources/ui-malariaglow.dds"
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

	char *countdownTextures[4] = {
		"resources/countdown-go.dds",
		"resources/countdown-1.dds",
		"resources/countdown-2.dds",
		"resources/countdown-3.dds"
	};

	char *boostTexture = "resources/boost.dds";

	char *boostColorTextures[2] = {
		"resources/blueBoost.dds",
		"resources/whiteBoost.dds"
	};

	char *winnerTextures[4] = {
		"resources/ui-ecoliwinner.dds",
		"resources/ui-chickenpoxwinner.dds",
		"resources/ui-syphiliswinner.dds",
		"resources/ui-malariawinner.dds"
	};

	float lastEdge;

	// regular toon images
	lastEdge = this->calculatePlayerVertices(this->vertices);
	for (int i = 0; i < MAX_PLAYERS; ++i) {
		this->playerModels[i] = engine->create2DModelFromScratch(vertices, 4, rectangleIndices, 6, playerTextures[i], textures, true);
		this->objectData.playerObjects[i] = new RenderableStaticObject(ObjectTypes::UI, playerModels[i]);
	}

	// glow toon images
	for (int i = 0; i < MAX_PLAYERS; ++i) {
		this->glowPlayerModels[i] = engine->create2DModelFromScratch(vertices, 4, rectangleIndices, 6, glowPlayerTextures[i], textures, true);
		this->objectData.glowPlayerObjects[i] = new RenderableStaticObject(ObjectTypes::UI, glowPlayerModels[i]);
	}

	// x image
	lastEdge = this->calculateXVertices(this->vertices, lastEdge);
	this->xModel = engine->create2DModelFromScratch(vertices, 4, rectangleIndices, 6, "resources/ui-x.dds", textures, true);
	this->objectData.xObject = new RenderableStaticObject(ObjectTypes::UI, xModel);

	// number images
	lastEdge = this->calculateNumberVertices(this->vertices, lastEdge);
	for (int i = 0; i < 10; ++i) {
		this->numberModels[i] = engine->create2DModelFromScratch(vertices, 4, rectangleIndices, 6, numberTextures[i], textures, true);
		this->objectData.numberObjects[i] = new RenderableStaticObject(ObjectTypes::UI, numberModels[i]);
	}

	// dead image
	this->calculateDeadVertices(this->vertices, lastEdge);
	this->deadModel = engine->create2DModelFromScratch(vertices, 4, rectangleIndices, 6, "resources/ui-dead.dds", textures, true);
	this->objectData.deadObject = new RenderableStaticObject(ObjectTypes::UI, deadModel);

	// boost text
	lastEdge = this->calculateBoostVertices(this->vertices);
	this->boostModel = engine->create2DModelFromScratch(vertices, 4, rectangleIndices, 6, "resources/boost.dds", textures, true);
	this->objectData.boostObject = new RenderableStaticObject(ObjectTypes::UI, boostModel);

	// boost bars
	this->calculateBoostTileVertices(this->vertices, lastEdge);
	this->boostMeterFullModel = engine->create2DModelFromScratch(vertices, 4, rectangleIndices, 6, boostColorTextures[0], textures, true);
	this->objectData.boostMeterFullObject = new RenderableStaticObject(ObjectTypes::UI, boostMeterFullModel);
	
	this->boostMeterEmptyModel = engine->create2DModelFromScratch(vertices, 4, rectangleIndices, 6, boostColorTextures[1], textures, true);
	this->objectData.boostMeterEmptyObject = new RenderableStaticObject(ObjectTypes::UI, boostMeterEmptyModel);

	// adrenaline image
	this->calculateAdrenalineVertices(this->vertices, this->leftEdge);
	this->adrenalineModel = engine->create2DModelFromScratch(vertices, 4, rectangleIndices, 6, "resources/ui-adrenaline.dds", textures, true);
	this->objectData.adrenalineObject = new RenderableStaticObject(ObjectTypes::UI, adrenalineModel);

	// Countdown images
	for (int i = 0; i < 4; ++i) {
		if (i == 0) {
			this->calculateCountdownVertices(this->vertices, true);
		}
		else {
			this->calculateCountdownVertices(this->vertices, false);
		}
		this->countdownModels[i] = engine->create2DModelFromScratch(vertices, 4, rectangleIndices, 6, countdownTextures[i], textures, true);
		this->objectData.countdownObjects[i] = new RenderableStaticObject(ObjectTypes::UI, countdownModels[i]);
	}

	// winner images
	this->calculateWinnerVertices(this->vertices);
	for (int i = 0; i < 4; ++i) {
		this->winnerModels[i] = engine->create2DModelFromScratch(vertices, 4, rectangleIndices, 6, winnerTextures[i], textures, true);
		this->objectData.winnerObjects[i] = new RenderableStaticObject(ObjectTypes::UI, winnerModels[i]);
	}
}

UIData::~UIData() {}

UIData::Objects *UIData::getData() {
	return &(this->objectData);
}

float UIData::calculatePlayerVertices(Transmission::Vertex *vertices) {
	float imgWidth, imgHeight, h_w_ratio, winRatio;
	if (this->engine->getWindowWidth() == 0 || this->engine->getWindowHeight() == 0) {
		winRatio = 800.0f / 600.0f;
	} else {
		winRatio = 1.0f * this->engine->getWindowWidth() / this->engine->getWindowHeight();
	}
	
	imgWidth = 400;
	imgHeight = 540;
	h_w_ratio = imgHeight / imgWidth;
	
	float width = 0.075f;
	float height = width * h_w_ratio * winRatio;

	float edgeT = 1.0f - this->margin;
	float edgeB = edgeT - height;
	
	float edgeL = -1.0f + this->margin;
	float edgeR = edgeL + width;

	vertices[0] = { { edgeL, edgeT, 0.0f }, { 0, 0 }, { 0, 0, -1 }, {} };
	vertices[1] = { { edgeR, edgeT, 0.0f }, { 1, 0 }, { 0, 0, -1 }, {} };
	vertices[2] = { { edgeR, edgeB, 0.0f }, { 1, 1 }, { 0, 0, -1 }, {} };
	vertices[3] = { { edgeL, edgeB, 0.0f }, { 0, 1 }, { 0, 0, -1 }, {} };

	this->playerHeight = height;
	this->leftEdge = edgeL;
	return edgeR;
}

float UIData::calculateXVertices(Transmission::Vertex *vertices, float lastEdge) {
	float imgWidth, imgHeight, h_w_ratio, winRatio;
	if (this->engine->getWindowWidth() == 0 || this->engine->getWindowHeight() == 0) {
		winRatio = 800.0f / 600.0f;
	} else {
		winRatio = 1.0f * this->engine->getWindowWidth() / this->engine->getWindowHeight();
	}

	imgWidth = 111;
	imgHeight = 129;
	h_w_ratio = imgHeight / imgWidth;

	float width = 0.024f;
	float height = width * h_w_ratio * winRatio;

	float edgeT = (1.0f - this->margin) - (this->playerHeight - height) / 2.0f;
	float edgeB = edgeT - height;

	float edgeL = lastEdge + 0.01f;
	float edgeR = edgeL + width;

	vertices[0] = { { edgeL, edgeT, 0.0f }, { 0, 0 }, { 0, 0, -1 }, {} };
	vertices[1] = { { edgeR, edgeT, 0.0f }, { 1, 0 }, { 0, 0, -1 }, {} };
	vertices[2] = { { edgeR, edgeB, 0.0f }, { 1, 1 }, { 0, 0, -1 }, {} };
	vertices[3] = { { edgeL, edgeB, 0.0f }, { 0, 1 }, { 0, 0, -1 }, {} };

	return edgeR;
}

float UIData::calculateNumberVertices(Transmission::Vertex *vertices, float lastEdge) {
	float imgWidth, imgHeight, h_w_ratio, winRatio;
	if (this->engine->getWindowWidth() == 0 || this->engine->getWindowHeight() == 0) {
		winRatio = 800.0f / 600.0f;
	} else {
		winRatio = 1.0f * this->engine->getWindowWidth() / this->engine->getWindowHeight();
	}

	imgWidth = 186;
	imgHeight = 234;
	h_w_ratio = imgHeight / imgWidth;

	float width = 0.04f;
	float height = width * h_w_ratio * winRatio;

	float edgeT = (1.0f - this->margin) - (this->playerHeight - height) / 2.0f;
	float edgeB = edgeT - height;

	float edgeL = lastEdge + 0.01f;
	float edgeR = edgeL + width;

	vertices[0] = { { edgeL, edgeT, 0.0f }, { 0, 0 }, { 0, 0, -1 }, {} };
	vertices[1] = { { edgeR, edgeT, 0.0f }, { 1, 0 }, { 0, 0, -1 }, {} };
	vertices[2] = { { edgeR, edgeB, 0.0f }, { 1, 1 }, { 0, 0, -1 }, {} };
	vertices[3] = { { edgeL, edgeB, 0.0f }, { 0, 1 }, { 0, 0, -1 }, {} };

	return edgeR;
}

void UIData::calculateDeadVertices(Transmission::Vertex *vertices, float lastEdge) {
	float imgWidth, imgHeight, h_w_ratio, winRatio;
	if (this->engine->getWindowWidth() == 0 || this->engine->getWindowHeight() == 0) {
		winRatio = 800.0f / 600.0f;
	}
	else {
		winRatio = 1.0f * this->engine->getWindowWidth() / this->engine->getWindowHeight();
	}

	imgWidth = 925;
	imgHeight = 311;
	h_w_ratio = imgHeight / imgWidth;

	float edgeL = this->leftEdge;
	float edgeR = lastEdge;

	float width = abs(edgeR - edgeL);
	float height = width * h_w_ratio * winRatio;

	float edgeT = (1.0f - this->margin) - (this->playerHeight - height) / 2.0f;
	float edgeB = edgeT - height;
	
	vertices[0] = { { edgeL, edgeT, 0.0f }, { 0, 0 }, { 0, 0, -1 }, {} };
	vertices[1] = { { edgeR, edgeT, 0.0f }, { 1, 0 }, { 0, 0, -1 }, {} };
	vertices[2] = { { edgeR, edgeB, 0.0f }, { 1, 1 }, { 0, 0, -1 }, {} };
	vertices[3] = { { edgeL, edgeB, 0.0f }, { 0, 1 }, { 0, 0, -1 }, {} };

	this->playerHeight = height;
}

float UIData::calculateBoostVertices(Transmission::Vertex *vertices) {
	float imgWidth, imgHeight, h_w_ratio, winRatio;
	if (this->engine->getWindowWidth() == 0 || this->engine->getWindowHeight() == 0) {
		winRatio = 800.0f / 600.0f;
	}
	else {
		winRatio = 1.0f * this->engine->getWindowWidth() / this->engine->getWindowHeight();
	}

	imgWidth = 770;
	imgHeight = 231;
	h_w_ratio = imgHeight / imgWidth;

	float width = 0.2f;
	float height = width * h_w_ratio * winRatio;

	float edgeT = 1.0f - this->margin;
	float edgeB = edgeT - height;

	float edgeR = 1.0f - this->margin;
	float edgeL = edgeR - width;

	vertices[0] = { { edgeL, edgeT, 0.0f }, { 0, 0 }, { 0, 0, -1 }, {} };
	vertices[1] = { { edgeR, edgeT, 0.0f }, { 1, 0 }, { 0, 0, -1 }, {} };
	vertices[2] = { { edgeR, edgeB, 0.0f }, { 1, 1 }, { 0, 0, -1 }, {} };
	vertices[3] = { { edgeL, edgeB, 0.0f }, { 0, 1 }, { 0, 0, -1 }, {} };

	this->boostHeight = height;
	this->rightEdge = edgeR;
	this->leftEdge = edgeL;
	return edgeB;
}

void UIData::calculateBoostTileVertices(Transmission::Vertex *vertices, float lastEdge) {
	float imgWidth, imgHeight, h_w_ratio, winRatio;
	if (this->engine->getWindowWidth() == 0 || this->engine->getWindowHeight() == 0) {
		winRatio = 800.0f / 600.0f;
	}
	else {
		winRatio = 1.0f * this->engine->getWindowWidth() / this->engine->getWindowHeight();
	}

	imgWidth = 213;
	imgHeight = 207;
	h_w_ratio = imgHeight / imgWidth;

	float width = 0.05f;// 0.024f;
	float height = width * h_w_ratio * winRatio;

	float edgeT = (lastEdge - this->margin);
	float edgeB = edgeT - height;

	float edgeR = this->rightEdge;
	float edgeL = edgeR - width;

	vertices[0] = { { edgeL, edgeT, 0.0f }, { 0, 0 }, { 0, 0, -1 }, {} };
	vertices[1] = { { edgeR, edgeT, 0.0f }, { 1, 0 }, { 0, 0, -1 }, {} };
	vertices[2] = { { edgeR, edgeB, 0.0f }, { 1, 1 }, { 0, 0, -1 }, {} };
	vertices[3] = { { edgeL, edgeB, 0.0f }, { 0, 1 }, { 0, 0, -1 }, {} };

	return;
}

void UIData::calculateAdrenalineVertices(Transmission::Vertex *vertices, float lastEdge) {
	float imgWidth, imgHeight, h_w_ratio, winRatio;
	if (this->engine->getWindowWidth() == 0 || this->engine->getWindowHeight() == 0) {
		winRatio = 800.0f / 600.0f;
	} else {
		winRatio = 1.0f * this->engine->getWindowWidth() / this->engine->getWindowHeight();
	}

	imgWidth = 2354;
	imgHeight = 1586;
	h_w_ratio = imgHeight / imgWidth;

	float width = 0.15f;
	float height = width * h_w_ratio * winRatio;

	float edgeR = lastEdge - this->margin;
	float edgeL = edgeR - width;

	float edgeT = 1.0f - this->margin;
	float edgeB = edgeT - height;

	vertices[0] = { { edgeL, edgeT, 0.0f }, { 0, 0 }, { 0, 0, -1 }, {} };
	vertices[1] = { { edgeR, edgeT, 0.0f }, { 1, 0 }, { 0, 0, -1 }, {} };
	vertices[2] = { { edgeR, edgeB, 0.0f }, { 1, 1 }, { 0, 0, -1 }, {} };
	vertices[3] = { { edgeL, edgeB, 0.0f }, { 0, 1 }, { 0, 0, -1 }, {} };

	this->playerHeight = height;
}

void UIData::calculateCountdownVertices(Transmission::Vertex *vertices, bool isGo) {
	float imgWidth, imgHeight, width, winRatio;
	if (this->engine->getWindowWidth() == 0 || this->engine->getWindowHeight() == 0) {
		winRatio = 800.0f / 600.0f;
	}
	else {
		winRatio = 1.0f * this->engine->getWindowWidth() / this->engine->getWindowHeight();
	}

	if (isGo) {
		imgWidth = 625;
		imgHeight = 321;
		width = 0.4f;
	}
	else {
		imgWidth = 200;
		imgHeight = 300;
		width = 0.2f;
	}

	float h_w_ratio = imgHeight / imgWidth;
	float height = width * h_w_ratio * winRatio;

	float edgeT = 0.8f;
	float edgeB = edgeT - height;

	float edgeL = -width / 2.0f;
	float edgeR = width / 2.0f;

	vertices[0] = { { edgeL, edgeT, 0.0f }, { 0, 0 }, { 0, 0, -1 }, {} };
	vertices[1] = { { edgeR, edgeT, 0.0f }, { 1, 0 }, { 0, 0, -1 }, {} };
	vertices[2] = { { edgeR, edgeB, 0.0f }, { 1, 1 }, { 0, 0, -1 }, {} };
	vertices[3] = { { edgeL, edgeB, 0.0f }, { 0, 1 }, { 0, 0, -1 }, {} };
}

void UIData::calculateWinnerVertices(Transmission::Vertex *vertices) {
	vertices[0] = { { -1.0f, 1.0f, 0.0f }, { 0, 0 }, { 0, 0, -1 }, {} };
	vertices[1] = { { 1.0f, 1.0f, 0.0f }, { 1, 0 }, { 0, 0, -1 }, {} };
	vertices[2] = { { 1.0f, -1.0f, 0.0f }, { 1, 1 }, { 0, 0, -1 }, {} };
	vertices[3] = { { -1.0f, -1.0f, 0.0f }, { 0, 1 }, { 0, 0, -1 }, {} };
}