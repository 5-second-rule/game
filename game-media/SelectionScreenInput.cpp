#include "SelectionScreenInput.h"

SelectionScreenInput::SelectionScreenInput() {
	this->renderingEngine = nullptr;
	this->alreadySent = false;
}

SelectionScreenInput::SelectionScreenInput(RenderingEngine *renderingEngine) {
	this->renderingEngine = renderingEngine;
}

SelectionScreenInput::~SelectionScreenInput() {}

std::vector<Event *> SelectionScreenInput::inputTranslator(InputAdapter *inputAdapter) {
	Transmission::Input::KeyState up = Transmission::Input::KeyState::STATE_UP;
	Transmission::Input::KeyState down = Transmission::Input::KeyState::STATE_DOWN;

	std::vector<Event *> inputEventVector;
	SelectionEvent::SelectionType selection;

	selection.guid = this->renderingEngine->getLocalPlayerGuid(0);

	if (inputAdapter->isControllerConnected()) {
		std::pair<Common::Vector4, float> leftStickInfo;
		float leftStickMagnitude, stickDirection;

		leftStickInfo = inputAdapter->getAnalogStickPosition(Transmission::Input::Key::GAMEPAD_LEFT_STICK);
		leftStickMagnitude = leftStickInfo.second;

		stickDirection = leftStickMagnitude*leftStickInfo.first.x();

		if (stickDirection > 0) {
			selection.action = SelectionEvent::Next;
			inputEventVector.push_back(new SelectionEvent(this->renderingEngine->getLocalPlayerGuid(0), selection));
		}

		if (stickDirection < 0) {
			selection.action = SelectionEvent::Prev;
			inputEventVector.push_back(new SelectionEvent(this->renderingEngine->getLocalPlayerGuid(0), selection));

		}

		if (inputAdapter->getKeyState(Transmission::Input::Key::GAMEPAD_A) == down) {
			selection.action = SelectionEvent::Select;
			inputEventVector.push_back(new SelectionEvent(this->renderingEngine->getLocalPlayerGuid(0), selection));
		}


		if (inputAdapter->getKeyState(Transmission::Input::Key::GAMEPAD_B) == down) {
			selection.action = SelectionEvent::Deselect;
			inputEventVector.push_back(new SelectionEvent(this->renderingEngine->getLocalPlayerGuid(0), selection));
		}

	} else {
		if (inputAdapter->getKeyState(Transmission::Input::Key::LEFT_ARROW) == down ||
			inputAdapter->getKeyState(Transmission::Input::Key::A) == down) {
			selection.action = SelectionEvent::Prev;
			inputEventVector.push_back(new SelectionEvent(this->renderingEngine->getLocalPlayerGuid(0), selection));
		}

		if (inputAdapter->getKeyState(Transmission::Input::Key::RIGHT_ARROW) == down ||
			inputAdapter->getKeyState(Transmission::Input::Key::D) == down) {
			selection.action = SelectionEvent::Next;
			inputEventVector.push_back(new SelectionEvent(this->renderingEngine->getLocalPlayerGuid(0), selection));
		}

		if (inputAdapter->getKeyState(Transmission::Input::Key::SPACE) == down ||
			inputAdapter->getKeyState(Transmission::Input::Key::ENTER) == down) {
			selection.action = SelectionEvent::Toggle;
			inputEventVector.push_back(new SelectionEvent(this->renderingEngine->getLocalPlayerGuid(0), selection));
		}

		if (inputAdapter->getKeyState(Transmission::Input::Key::G) == down) {
			selection.action = SelectionEvent::Go;
			inputEventVector.push_back(new SelectionEvent(this->renderingEngine->getLocalPlayerGuid(0), selection));
		}
	}

	// if an event has already been sent
	if (alreadySent) {

		// if no events were generated, all the keys have come up;
		// we're safe to send new ones next time
		if (inputEventVector.empty()) {
			alreadySent = false;
		} else {

			// otherwise, we have to throw away all the invalid events
			while (!inputEventVector.empty()) {
				delete inputEventVector.back();
				inputEventVector.pop_back();
			}
		}
	
	} else {
		if (!inputEventVector.empty()) alreadySent = true;
	}
	return inputEventVector;

}