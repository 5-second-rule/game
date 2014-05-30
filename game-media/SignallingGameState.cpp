#include "SignallingGameState.h"


SignallingGameState::SignallingGameState(INotifyReady<GameState> *notifier)
: GameState() {
	this->notifier = notifier;
}

SignallingGameState::~SignallingGameState() {}

bool SignallingGameState::handleEvent(Event *evt) {
	return false;
}

void SignallingGameState::deserialize(BufferReader& buffer) {
	GameState::deserialize(buffer);
	this->notifier->ready(this);
}
