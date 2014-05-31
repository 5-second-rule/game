#pragma once
#include "game-media.h"
#include "INotifyReady.h"
#include "game-core/GameState.h"
#include "game-core/ObjectTypes.h"

class GAMEMEDIADLL SignallingGameState : public GameState {
private:
	INotifyReady<GameState> *notifier;

public:
	SignallingGameState(INotifyReady<GameState> *notifier);
	~SignallingGameState();
	virtual void setState(State state);
	virtual void deserialize(BufferReader& buffer);
};
