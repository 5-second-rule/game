#include "RenderableUI.h"
#include "game-core/Leaderboard.h"
//#include "RenderableGame.h"
//#include "RenderingGameManager.h"

using namespace Transmission;

RenderableUI::RenderableUI(UIData::Objects *objectData)
: StaticObject(ObjectTypes::UI) {
	this->objectData = objectData;

	RenderableGame *game = RenderableGame::getGlobalInstance();
	this->engine = game->getRenderingEngineInstance();
	this->players = game->getGameManager()->getPlayers();
	this->deathboard = game->getGameManager()->getGameState()->getDeathboard();
	this->playerGuid = game->getRenderingEngineInstance()->getLocalPlayerGuid(0);
}

RenderableUI::~RenderableUI() {}

void RenderableUI::render() {
	float winRatio = 1.0f * this->engine->getWindowWidth() / this->engine->getWindowHeight();
	float origRatio = 800.0f / 600.0f;
	float xScalar = winRatio / origRatio * 5.5f;
	std::vector<DeathboardEntry>::iterator it;
	std::vector<DeathboardEntry>::iterator end = this->deathboard.end();
	RenderableStaticObject *playerObject;
	bool itsMe = false;
	int i;

	
	for (it = this->deathboard.begin(), i = 0; it != end; ++it, ++i) {
		float x = 0, y = 0;
		int selection = this->players[it->playerIndex]->getSelection();
		int numLives = MAX_LIVES - it->numDeaths;

		if (it->winner) {
			this->objectData->winnerObjects[selection]->render();
			break;
		}
		
		y -= i*0.22f;
		if (this->players[it->playerIndex]->getGuid() == this->playerGuid) {
			itsMe = true;
			playerObject = this->objectData->glowPlayerObjects[selection];
			if (this->players[it->playerIndex]->hasAdrenaline()) {
				this->objectData->adrenalineObject->render();
			}
		} else {
			itsMe = false;
			playerObject = this->objectData->playerObjects[selection];
		}

		Common::Vector4 pos = Common::Vector4(x, y, 0, 1);
		playerObject->getMoveable()->setPosition(pos);
		playerObject->render();

		if (numLives > 0) {	
			this->objectData->xObject->getMoveable()->setPosition(pos);
			this->objectData->xObject->render();
			this->objectData->numberObjects[numLives]->getMoveable()->setPosition(pos);
			this->objectData->numberObjects[numLives]->render();
		}
		else {
			this->objectData->deadObject->getMoveable()->setPosition(pos);
			this->objectData->deadObject->render();
		}
	}

};
