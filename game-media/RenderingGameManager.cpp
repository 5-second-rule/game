#include "RenderingGameManager.h"
RenderingGameManager::RenderingGameManager() {}

RenderingGameManager::RenderingGameManager(RenderingEngine *engine) {
	this->engine = engine;
	this->selectionInput = SelectionScreenInput(this->engine);
	this->gameplayInput = GameplayInput(this->engine);
}

RenderingGameManager::~RenderingGameManager() {}

void RenderingGameManager::ready(GameState *gameState) {
	this->gameState = gameState;
}

void RenderingGameManager::inputTranslator() {
	if (gameState == nullptr)
		return;

	switch (gameState->getState()) {
	case (GameState::State::Selection):
		this->engine->renderingDelegate = &(this->selectionInput);
		break;
	case (GameState::State::Game):
		this->engine->renderingDelegate = &(this->gameplayInput);
		break;
	default: 
		break;
	}
}

GameState *RenderingGameManager::getGameState() {
	return this->gameState;
}

std::vector<Player*> RenderingGameManager::getPlayers() {
	return this->gameState->getPlayers();
}