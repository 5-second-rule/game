#include "RenderableSelectionScreen.h"

using namespace Transmission;

RenderableSelectionScreen::RenderableSelectionScreen(SelectionScreenData::Objects *objectData)
: StaticObject(ObjectTypes::SelectionScreen) {
	this->objectData = objectData;
	this->engine = RenderableGame::getGlobalInstance()->getEngineInstance();
	this->players = RenderableGame::getGlobalInstance()->getGameManager()->getPlayers();
}

RenderableSelectionScreen::~RenderableSelectionScreen() {}

void RenderableSelectionScreen::render() {
	this->objectData->backgroundObject->render();
	this->objectData->titleObject->render();
	unsigned int myGuid = RenderableGame::getGlobalInstance()->getEngineInstance()->getLocalPlayerGuid(0);

	//for (int i = 0; i < 4; ++i) {
	//	if (this->players[i]->getGuid() == myGuid) {
	//		this->objectData->myPlayerBackgroundObjects[i]->render();
	//		this->objectData->myPlayerNameObjects[i]->render();
	//	} else {
	//		this->objectData->otherPlayerBackgroundObjects[i]->render();
	//		this->objectData->otherPlayerNameObjects[i]->render();
	//	}
	//}

	for (int i = 0; i < this->players.size(); ++i) {
		Common::Vector4 pos = Common::Vector4(this->objectData->playerCenters[i], 0, 0, 1);
		int selection = this->players[i]->getTempSelection();
		this->objectData->playerObjects[selection]->setPosition(pos);
		this->objectData->playerObjects[selection]->render();
	}

};
