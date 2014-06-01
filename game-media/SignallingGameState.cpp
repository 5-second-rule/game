#include "SignallingGameState.h"

#include "RenderableGame.h"

SignallingGameState::SignallingGameState(INotifyReady<GameState> *notifier)
: GameState() {
	this->notifier = notifier;
}

SignallingGameState::~SignallingGameState() {}


void SignallingGameState::deserialize(BufferReader& buffer) {
	GameState::deserialize(buffer);
	this->notifier->ready(this);
}

void SignallingGameState::setState(State state) {
	GameState::setState(state);
	RenderableGame::getGlobalInstance()->getGameManager()->inputTranslator();
}
