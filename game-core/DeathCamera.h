#pragma once
#include "game-core.h"

#include "engine-core\BaseObject.h"
#include "common\Vector4.h"
#include "GameState.h"

using namespace Common;

struct DeathCameraData {
	float target[3];
	float position[3];
};

class GAMECOREDLL DeathCamera :
	public BaseObject
{
public:
	DeathCamera(Handle gameState);
	~DeathCamera();

	Vector4 getPosition();
	Vector4 getTarget();

	void update(float dt);

	bool handleEvent(Event *evt) { return false; }

	// ISerializable Methods
	void reserveSize(IReserve& buffer) const;
	void fillBuffer(IFill& buffer) const;
	void deserialize(BufferReader& buffer);

private:
	Handle gameState;
	GameState* getGameState();

	Vector4 target;
	Vector4 position;
};

