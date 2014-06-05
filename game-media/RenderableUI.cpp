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
	this->leaderboard = game->getGameManager()->getGameState()->getLeaderboard();
	this->playerGuid = game->getRenderingEngineInstance()->getLocalPlayerGuid(0);
}

RenderableUI::~RenderableUI() {}

void RenderableUI::render() {
	float winRatio = 1.0f * this->engine->getWindowWidth() / this->engine->getWindowHeight();
	float origRatio = 800.0f / 600.0f;
	float xScalar = winRatio / origRatio * 5.5f;
	std::vector<LeaderboardEntry>::iterator it;
	std::vector<LeaderboardEntry>::iterator end = this->leaderboard.end();
	int i;
	bool itsMe = false;
	
	RenderableMovingObject *playerObject, *xObject, *onesObject, *tensObject;

	for (it = this->leaderboard.begin(), i = 0; it != end; ++it, ++i) {
		float x = 0, y = 0;
		y -= 0.22f * i;
		Common::Vector4 pos = Common::Vector4(x, y, 0, 1);

		int selection = this->players[it->playerIndex]->getSelection();
		int numDeaths = this->players[it->playerIndex]->getDeathCount();

		if (this->players[it->playerIndex]->getGuid() == this->playerGuid) {
			itsMe = true;
			playerObject = this->objectData->jumboPlayerObjects[selection];
			onesObject = this->objectData->jumboNumberObjects[numDeaths / 10];
			if (numDeaths < 10) {
				tensObject = nullptr;
				onesObject = this->objectData->jumboNumberObjects[numDeaths];
			} else {
				tensObject = this->objectData->jumboNumberObjects[numDeaths / 10];
				onesObject = this->objectData->jumboNumberObjects[numDeaths % 10];
			}
			xObject = this->objectData->jumbboXObject;
		} else {
			playerObject = this->objectData->playerObjects[selection];
			onesObject = this->objectData->numberObjects[selection];
			tensObject = this->objectData->numberObjects[selection];
			xObject = this->objectData->xObject;
		}

		playerObject->setPosition(pos);
		playerObject->render();
		xObject->setPosition(pos);
		xObject->render();

		if (numDeaths < 10) {	
			onesObject->setPosition(pos);
			onesObject->render();
		} else {
			tensObject->setPosition(pos);
			tensObject->render();

			x += 0.04f;
			if (itsMe) {
				x += 0.02f;
			}
			pos = Common::Vector4(x, y, 0, 1);
			onesObject->setPosition(pos);
			onesObject->render();
		}
		
	}

};
