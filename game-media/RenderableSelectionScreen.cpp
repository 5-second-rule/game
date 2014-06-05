#include "RenderableSelectionScreen.h"
#include "RenderableGame.h"
#include "RenderingGameManager.h"

using namespace Transmission;

RenderableSelectionScreen::RenderableSelectionScreen(SelectionScreenData::Objects *objectData)
: StaticObject(ObjectTypes::SelectionScreen) {
	this->objectData = objectData;
	this->engine = RenderableGame::getGlobalInstance()->getRenderingEngineInstance();
	this->players = RenderableGame::getGlobalInstance()->getGameManager()->getPlayers();
}

RenderableSelectionScreen::~RenderableSelectionScreen() {}

void RenderableSelectionScreen::destroy() {
	delete this->objectData->backgroundObject;
	delete this->objectData->titleObject;
	this->objectData->backgroundObject = nullptr;
	this->objectData->titleObject = nullptr;
	for (int i = 0; i < 4; ++i) {
		delete this->objectData->otherPlayerBackgroundObjects[i];
		delete this->objectData->myPlayerBackgroundObjects[i];
		delete this->objectData->checkMarkObjects[i];
		delete this->objectData->playerObjects[i];
		this->objectData->otherPlayerBackgroundObjects[i] = nullptr;
		this->objectData->myPlayerBackgroundObjects[i] = nullptr;
		this->objectData->checkMarkObjects[i] = nullptr;
		this->objectData->playerObjects[i] = nullptr;
	}
	for (int i = 0; i < 16; ++i) {
		delete this->objectData->otherPlayerNameObjects[i];
		delete this->objectData->myPlayerNameObjects[i];
		this->objectData->otherPlayerNameObjects[i] = nullptr;
		this->objectData->myPlayerNameObjects[i] = nullptr;
	}
}

void RenderableSelectionScreen::render() {
	this->objectData->backgroundObject->render();
	this->objectData->titleObject->render();
	unsigned int myGuid = this->engine->getLocalPlayerGuid(0);
	size_t i;
	for (i = 0; i < 4; ++i) {
		if (i < this->players.size() && this->players[i]->getGuid() == myGuid) {
			this->objectData->myPlayerBackgroundObjects[i]->render();
		} else {
			this->objectData->otherPlayerBackgroundObjects[i]->render();
		}
	}

	float winRatio = 1.0f * this->engine->getWindowWidth() / this->engine->getWindowHeight();
	float origRatio = 800.0f / 600.0f;
	float xScalar =  winRatio / origRatio * 5.5f;

	for (size_t i = 0; i < this->players.size(); ++i) {	
		Common::Vector4 pos = Common::Vector4(this->objectData->playerCenters[i] * xScalar, 0, 0, 1);
		int selection = this->players[i]->getSelection();

		if (this->players[i]->isSelected()) {
			this->objectData->checkMarkObjects[i]->render();
		}

		int nameIndex = i * 4 + selection;
		if (this->players[i]->getGuid() == myGuid) {
			this->objectData->myPlayerNameObjects[nameIndex]->render();
		} else {
			this->objectData->otherPlayerNameObjects[nameIndex]->render();
		}

		this->objectData->playerObjects[selection]->setPosition(pos);
		this->objectData->playerObjects[selection]->render();
	}

};
