#include "RenderableGameState.h"


RenderableGameState::RenderableGameState()
{
}


RenderableGameState::~RenderableGameState()
{
}

void RenderableGameState::render() {
	if (this->getState() == State::Selection) {

	} else if (this->getState() == State::Game) {

	}
}