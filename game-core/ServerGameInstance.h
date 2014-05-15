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

	void run();
	void stop();

	virtual ActionEvent* MakeActionEvent(int actionType, unsigned int playerGuid, const char* data);
	Handle createObject(int p_object_type);
	void setPosition(float, float, float, Handle*);
	void setPosition(Vector4 &pos, Handle* objH);
	void createAI(Handle* objH);
	void handleTerminal();
	void printCommand(stringstream&);
};

