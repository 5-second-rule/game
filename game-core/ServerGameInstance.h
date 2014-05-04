#pragma once

#include "game-core.h"
#include "GameInstance.h"

class GAMECOREDLL ServerGameInstance : public GameInstance
{
private:
	float frameTime;

protected:
	virtual Engine * makeEngineInstance(GameObjectCtorTable *ctors);

public:
	ServerGameInstance(float frameTime);
	~ServerGameInstance();

	void stop();

	virtual ActionEvent* MakeActionEvent( int actionType, unsigned int playerGuid, const char* data );
};

