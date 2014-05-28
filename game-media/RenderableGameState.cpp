#include "RenderableGameState.h"


RenderableGameState::RenderableGameState()
: RenderableObject(nullptr) {
	if (this->engine != nullptr) {
		this->renderingEngine = RenderableGame::getGlobalInstance()->getRenderingEngineInstance();
		this->renderingEngine->selectionRenderingDelegate = this;
	}
}

RenderableGameState::~RenderableGameState() {}

std::vector<Event *> RenderableGameState::inputTranslator(InputAdapter *inputAdapter) {
	Transmission::Input::KeyState down = Transmission::Input::KeyState::STATE_DOWN;
	std::vector<Event *> inputEventVector;
	SelectionEvent::SelectionType selection;

	if (inputAdapter->isControllerConnected()) {
		std::pair<Common::Vector4, float> leftStickInfo;
		float leftStickMagnitude, stickDirection;

		leftStickInfo = inputAdapter->getAnalogStickPosition(Transmission::Input::Key::GAMEPAD_LEFT_STICK);
		leftStickMagnitude = leftStickInfo.second;

		stickDirection = leftStickMagnitude*leftStickInfo.first.x();
		if (stickDirection != 0) {
			selection.selectionDirection = stickDirection;
			inputEventVector.emplace_back(new SelectionEvent(this->renderingEngine->getLocalPlayerGuid(0), selection));
		}

		if (inputAdapter->getKeyState(Transmission::Input::Key::GAMEPAD_A) == down) {
			selection.selectChar = true;
			inputEventVector.emplace_back(new SelectionEvent(this->renderingEngine->getLocalPlayerGuid(0), selection));
		}

		if (inputAdapter->getKeyState(Transmission::Input::Key::GAMEPAD_B) == down) {
			selection.unselectChar = true;
			inputEventVector.emplace_back(new SelectionEvent(this->renderingEngine->getLocalPlayerGuid(0), selection));
		}
	} else {
		if (inputAdapter->getKeyState(Transmission::Input::Key::LEFT_ARROW) == down ||
			inputAdapter->getKeyState(Transmission::Input::Key::A) == down) {
			selection.selectionDirection = -1;
			inputEventVector.emplace_back(new SelectionEvent(this->renderingEngine->getLocalPlayerGuid(0), selection));
		}

		if (inputAdapter->getKeyState(Transmission::Input::Key::RIGHT_ARROW) == down ||
			inputAdapter->getKeyState(Transmission::Input::Key::D) == down) {
			selection.selectionDirection = 1;
			inputEventVector.emplace_back(new SelectionEvent(this->renderingEngine->getLocalPlayerGuid(0), selection));
		}

		if (inputAdapter->getKeyState(Transmission::Input::Key::SPACE) == down ||
			inputAdapter->getKeyState(Transmission::Input::Key::ENTER) == down) {
			selection.toggleSelect = true;
			inputEventVector.emplace_back(new SelectionEvent(this->renderingEngine->getLocalPlayerGuid(0), selection));
		}
	}

	return inputEventVector;
}

void RenderableGameState::render() {}