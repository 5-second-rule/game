#pragma once

#include "game-core.h"
#include "GameInstance.h"

class GAMECOREDLL ServerGameInstance : public GameInstance
{
private:
	int minimumFrameTime;

protected:
	virtual EngineInstance * makeEngineInstance(GameObjectCtorTable *ctors);

public:
	ServerGameInstance(int minimumFrameTime);
	~ServerGameInstance();

	void stop();
};

