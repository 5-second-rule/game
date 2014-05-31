#pragma once
#include "game-media.h"
#include "engine-renderer/RenderingEngine.h"
#include "game-core/SelectionEvent.h"

class GAMEMEDIADLL SelectionScreenInput : public IRenderingEngineDelegate {
private:
	RenderingEngine *renderingEngine;
	bool alreadySent;
public:
	SelectionScreenInput();
	SelectionScreenInput(RenderingEngine *renderingEngine);
	~SelectionScreenInput();
	virtual std::vector<Event *> inputTranslator(InputAdapter *inputAdapter);
};
