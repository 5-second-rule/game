#pragma once
#include "game-media.h"
#include "INotifyReady.h"
#include "game-core/GameState.h"
#include "engine-renderer/RenderingEngine.h"
#include "SelectionScreenInput.h"
#include "GameplayInput.h"

class GAMEMEDIADLL RenderingGameManager: public INotifyReady<GameState> {
private:
	RenderingEngine *engine;
	GameState *gameState;
	SelectionScreenInput selectionInput;
	GameplayInput gameplayInput;

public:
	RenderingGameManager(RenderingEngine *engine);
	~RenderingGameManager();
	void ready(GameState *gameState);
	void inputTranslator();
	GameState *getGameState();
	std::vector<Player*> getPlayers();
};

