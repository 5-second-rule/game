#include "RenderableSelectionScreen.h"

using namespace Transmission;

RenderableSelectionScreen::RenderableSelectionScreen(SelectionScreenData::Objects *objectData)
: StaticObject(ObjectTypes::SelectionScreen) {
	this->objectData = objectData;
	this->engine = RenderableGame::getGlobalInstance()->getRenderingEngineInstance();
	this->players = RenderableGame::getGlobalInstance()->getGameManager()->getPlayers();

	for (int i = 0; i < 4; ++i) {
		this->objectData->playerObjects[i]->setHeading(Vector(0.0f, 0.0f, -1.0f));
	}
}

RenderableSelectionScreen::~RenderableSelectionScreen() {}

void RenderableSelectionScreen::render() {
	if (RenderableGame::getGlobalInstance()->getGameManager()->getGameState()->getState() == GameState::State::Selection) {


		this->objectData->backgroundObject->render();
		this->objectData->titleObject->render();
		unsigned int myGuid = this->engine->getLocalPlayerGuid(0);
		size_t i;
		for (i = 0; i < 4; ++i) {
			if (i < this->players.size() && this->players[i]->getGuid() == myGuid) {
				this->objectData->myPlayerBackgroundObjects[i]->render();
			}
			else {
				this->objectData->otherPlayerBackgroundObjects[i]->render();
			}
		}


		float winRatio = 1.0f * this->engine->getWindowWidth() / this->engine->getWindowHeight();
		float origRatio = 800.0f / 600.0f;
		float xScalar = winRatio / origRatio * 5.5f;

		for (size_t i = 0; i < this->players.size(); ++i) {
			Common::Vector4 pos = Common::Vector4(this->objectData->playerCenters[i] * xScalar, 0, 0, 1);
			int selection = this->players[i]->getSelection();

			if (this->players[i]->isSelected()) {
				this->objectData->checkMarkObjects[i]->render();
			}

			int nameIndex = i * 4 + selection;
			if (this->players[i]->getGuid() == myGuid) {
				this->objectData->myPlayerNameObjects[nameIndex]->render();
			}
			else {
				this->objectData->otherPlayerNameObjects[nameIndex]->render();
			}

			this->objectData->playerObjects[selection]->setPosition(pos);
			this->objectData->playerObjects[selection]->render();
		}
	}
};
