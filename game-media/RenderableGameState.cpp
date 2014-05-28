#include "RenderableGameState.h"


RenderableGameState::RenderableGameState()
: RenderableObject(nullptr) {
	if (this->engine != nullptr) {
		RenderableGame::getGlobalInstance()->getRenderingEngineInstance()->selectionRenderingDelegate = this;
	}
}

RenderableGameState::~RenderableGameState() {}

std::vector<Event *> RenderableGameState::inputTranslator(InputAdapter *inputAdapter) {
	Transmission::Input::KeyState down = Transmission::Input::KeyState::STATE_DOWN;
	std::vector<Event *> inputEventVector;

	float selectionDirection = 0;
	bool selectChar = false;
	bool unSelectChar = false;
	bool toggleSelect = false;

	if (inputAdapter->isControllerConnected()) {
		// Analog Stick Examples -- normalized vector and magnitude
		std::pair<Common::Vector4, float> leftStickInfo;
		float leftStickMagnitude;

		leftStickInfo = inputAdapter->getAnalogStickPosition(Transmission::Input::Key::GAMEPAD_LEFT_STICK);
		leftStickMagnitude = leftStickInfo.second;

		selectionDirection = leftStickMagnitude*leftStickInfo.first.x();

		if (inputAdapter->getKeyState(Transmission::Input::Key::GAMEPAD_A) == down) {
			selectChar = true;
		}

		if (inputAdapter->getKeyState(Transmission::Input::Key::GAMEPAD_B) == down) {
			unSelectChar = true;
		}
	} else {
		if (inputAdapter->getKeyState(Transmission::Input::Key::LEFT_ARROW) == down) {
			selectionDirection = -1;
		}

		if (inputAdapter->getKeyState(Transmission::Input::Key::RIGHT_ARROW) == down) {

			selectionDirection = 1;
		}

		if (inputAdapter->getKeyState(Transmission::Input::Key::A) == down) {
			selectionDirection = -1;
		}

		if (inputAdapter->getKeyState(Transmission::Input::Key::D) == down) {
			selectionDirection = 1;
		}

		if (inputAdapter->getKeyState(Transmission::Input::Key::SPACE) == down) {
			toggleSelect = true;
		}

		if (inputAdapter->getKeyState(Transmission::Input::Key::ENTER) == down) {
			toggleSelect = true;
		}
	}

	return inputEventVector;
}

void RenderableGameState::render() {}