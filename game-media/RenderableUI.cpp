#include "RenderableUI.h"
//#include "RenderableGame.h"
//#include "RenderingGameManager.h"

using namespace Transmission;

RenderableUI::RenderableUI(UIData::Objects *objectData)
: StaticObject(ObjectTypes::UI) {
	this->objectData = objectData;
	this->engine = RenderableGame::getGlobalInstance()->getRenderingEngineInstance();
	this->players = RenderableGame::getGlobalInstance()->getGameManager()->getPlayers();
}

RenderableUI::~RenderableUI() {}

void RenderableUI::render() {
	float winRatio = 1.0f * this->engine->getWindowWidth() / this->engine->getWindowHeight();
	float origRatio = 800.0f / 600.0f;
	float xScalar = winRatio / origRatio * 5.5f;

	for (size_t i = 0; i < this->players.size(); ++i) {
		float x = 0, y = 0;
		y -= 0.15f * i;
		Common::Vector4 pos = Common::Vector4( x, y, 0, 1);
		int selection = this->players[i]->getSelection();
		this->objectData->player1Objects[selection]->setPosition(pos);
		this->objectData->player1Objects[selection]->render();
	}

};
