#pragma once
#include "game-media.h"
#include "INotifyReady.h"
#include "game-core/GameState.h"
#include "game-core/ObjectTypes.h"

class GAMEMEDIADLL SignallingGameState : public BaseObject {
private:
	INotifyReady<GameState> *notifier;

public:
	SignallingGameState(INotifyReady<GameState> *notifier);
	~SignallingGameState();
	virtual bool handleEvent(Event *evt);
	virtual void reserveSize(IReserve& buffer) const;
	virtual void fillBuffer(IFill& buffer) const;
	virtual void deserialize(BufferReader& buffer);
	virtual void update(float dt);
};

