#pragma once

#include "game-core.h"
#include "GameInstance.h"

class GAMECOREDLL ServerGameInstance : public GameInstance
{
private:
	float frameTime;

protected:
	virtual EngineInstance * makeEngineInstance(GameObjectCtorTable *ctors);

public:
	ServerGameInstance(float frameTime);
	~ServerGameInstance();

	void stop();
};

