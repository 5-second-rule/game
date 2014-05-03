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

	virtual void ServerGameInstance::HandleAction( ActionEvent* evt );
	virtual ActionEvent* MakeActionEvent( int actionType, unsigned int playerGuid, size_t index, const char* data );
};

