#include "RenderableUI.h"
#include "game-core/Leaderboard.h"
//#include "RenderableGame.h"
//#include "RenderingGameManager.h"

using namespace Transmission;

RenderableUI::RenderableUI(UIData::Objects *objectData)
: StaticObject(ObjectTypes::UI) {
	this->objectData = objectData;

	RenderableGame *game = RenderableGame::getGlobalInstance();
	this->gamestate = game->getGameManager()->getGameState();
	this->engine = game->getRenderingEngineInstance();

	this->playerGuid = this->engine->getLocalPlayerGuid(0);
	this->players = this->gamestate->getPlayers();
	this->deathboard = this->gamestate->getDeathboard();

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
			if (this->players[it->playerIndex]->hasAdrenaline()) {
				playerObject = this->objectData->adrenalineObject;
				//playerObject->getMoveable()->setPosition(-0.2, 0, 0);
				playerObject->render();
			}
			playerObject = this->objectData->glowPlayerObjects[selection];
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

	int flag = this->gamestate->getCountdownFlag();
	if (flag >= 0) {
		this->objectData->countdownObjects[flag]->render();
	}


	Common::Vector4 boostPos = Common::Vector4(0, 0, 0, 1);
	playerObject = this->objectData->boostObject;
	playerObject->getMoveable()->setPosition(boostPos);
	playerObject->render();

	std::vector<Player*> playerVec;
	playerVec = RenderableGame::getGlobalInstance()->getGameManager()->getPlayers();

	const float shiftAmt = -0.05f;

	int boostVal = 0;
	//loop over that vector until you find one that matchines local guid 0
	for (int i = 0; i < playerVec.size(); i++)
	{
		if (this->engine->getLocalPlayerGuid(0) == playerVec[i]->getGuid())
		{
			PlayerMovingObject* playObj = dynamic_cast<PlayerMovingObject*> (theWorld.get(playerVec[i]->getMovingObject()));
			if( playObj != nullptr )
			{
				boostVal = playObj->getBoostCount();
			}
		}
	}

	if (boostVal < 25)
	{
		playerObject = this->objectData->boostMeterEmptyObject;
		for (int i = 0; i < 4; i++)
		{
			boostPos.set(shiftAmt*i, 0, 0);
			playerObject->getMoveable()->setPosition(boostPos);
			playerObject->render();
		}
	}
	else if ((boostVal >= 25) && (boostVal < 50))
	{
		playerObject = this->objectData->boostMeterEmptyObject;
		for (int i = 0; i < 3; i++)
		{
			boostPos.set(shiftAmt*i, 0, 0);
			playerObject->getMoveable()->setPosition(boostPos);
			playerObject->render();
		}

		playerObject = this->objectData->boostMeterFullObject;
		boostPos.set(shiftAmt * 3, 0, 0);
		playerObject->getMoveable()->setPosition(boostPos);
		playerObject->render();
	}
	else if ((boostVal >= 50) && (boostVal < 75))
	{
		playerObject = this->objectData->boostMeterEmptyObject;
		for (int i = 0; i < 2; i++)
		{
			boostPos.set(shiftAmt*i, 0, 0);
			playerObject->getMoveable()->setPosition(boostPos);
			playerObject->render();
		}

		playerObject = this->objectData->boostMeterFullObject;

		for (int i = 0; i < 2; i++)
		{
			boostPos.set(shiftAmt*(i + 2), 0, 0);
			playerObject->getMoveable()->setPosition(boostPos);
			playerObject->render();
		}
	}
	else if ((boostVal >= 75) && (boostVal < 100))
	{
		playerObject = this->objectData->boostMeterEmptyObject;
		for (int i = 0; i < 1; i++)
		{
			boostPos.set(shiftAmt*i, 0, 0);
			playerObject->getMoveable()->setPosition(boostPos);
			playerObject->render();
		}

		playerObject = this->objectData->boostMeterFullObject;

		for (int i = 0; i < 3; i++)
		{
			boostPos.set(shiftAmt*(i + 1), 0, 0);
			playerObject->getMoveable()->setPosition(boostPos);
			playerObject->render();
		}
	}
	else
	{
		playerObject = this->objectData->boostMeterFullObject;

		for (int i = 0; i < 4; i++)
		{
			boostPos.set(shiftAmt*(i), 0, 0);
			playerObject->getMoveable()->setPosition(boostPos);
			playerObject->render();
		}
	}

};
