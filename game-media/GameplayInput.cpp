#include "GameplayInput.h"
#include "RenderableGame.h"

GameplayInput::GameplayInput() {
	this->renderingEngine = nullptr;
}

GameplayInput::GameplayInput(RenderingEngine *renderingEngine) {
	this->renderingEngine = renderingEngine;
}

GameplayInput::~GameplayInput() {}


std::vector<Event *>  GameplayInput::inputTranslator(InputAdapter *inputAdapter) {
	Transmission::Input::KeyState down = Transmission::Input::KeyState::STATE_DOWN;
	MoveEvent::MoveDirection dir = { 0.0, 0.0, 0.0, 0.0 };
	std::vector<Event *> inputEventVector;


	if( inputAdapter->isControllerConnected() ) {

		// Analog Stick Examples -- normalized vector and magnitude
		std::pair<Common::Vector4, float> leftStickInfo, rightStickInfo;
		float leftStickMagnitude, rightStickMagnitude;
		const float stickScale = 6.0;

		leftStickInfo = inputAdapter->getAnalogStickPosition( Transmission::Input::Key::GAMEPAD_LEFT_STICK );
		leftStickMagnitude = leftStickInfo.second * stickScale;

		rightStickInfo = inputAdapter->getAnalogStickPosition( Transmission::Input::Key::GAMEPAD_RIGHT_STICK );
		rightStickMagnitude = rightStickInfo.second;

		dir.x = leftStickMagnitude*leftStickInfo.first.x();
		dir.y = leftStickMagnitude*leftStickInfo.first.y();

		// Trigger Examples -- values [0.0, 1.0]
		//dir.z -= inputAdapter->getAnalogTriggerValue(Transmission::Input::Key::GAMEPAD_LEFT_TRIGGER);
		//dir.z += inputAdapter->getAnalogTriggerValue(Transmission::Input::Key::GAMEPAD_RIGHT_TRIGGER);

		// Button Examples -- KeyState::STATE_UP or KeyState::STATE_DOWN
		if( inputAdapter->getKeyState( Transmission::Input::Key::GAMEPAD_A ) == down ) {
			dir.z += 1;
		}

		if( inputAdapter->getKeyState( Transmission::Input::Key::GAMEPAD_B ) == down ) {
			dir.z -= 1;
		}

		if( inputAdapter->getKeyState( Transmission::Input::Key::GAMEPAD_RIGHT_SHOULDER ) == down ) {
			dir.w += 1;
		}

		if( inputAdapter->getKeyState( Transmission::Input::Key::GAMEPAD_LEFT_SHOULDER ) == down ) {
			dir.w -= 1;
		}

		if( inputAdapter->getKeyState( Transmission::Input::Key::GAMEPAD_X ) == down ) {
			inputEventVector.emplace_back( new ShootEvent( this->renderingEngine->getLocalPlayerGuid( 0 ) ) );
		}

	} else {
		const float keyScale = 6.0;

		if( inputAdapter->getKeyState( Transmission::Input::Key::A ) == down ) {
			dir.x -= 1 * keyScale;
		}

		if( inputAdapter->getKeyState( Transmission::Input::Key::D ) == down ) {

			dir.x += 1 * keyScale;
		}

		if( inputAdapter->getKeyState( Transmission::Input::Key::I ) == down ) {
			dir.z += 1;
		}

		if( inputAdapter->getKeyState( Transmission::Input::Key::O ) == down ) {
			dir.z -= 1;
		}

		if( inputAdapter->getKeyState( Transmission::Input::Key::S ) == down ) {
			dir.y -= 1 * keyScale;
		}

		if( inputAdapter->getKeyState( Transmission::Input::Key::W ) == down ) {
			dir.y += 1 * keyScale;
		}

		if( inputAdapter->getKeyState( Transmission::Input::Key::Q ) == down ) {
			dir.w -= 1;
		}

		if( inputAdapter->getKeyState( Transmission::Input::Key::E ) == down ) {
			dir.w += 1;
		}

		if( inputAdapter->getKeyState( Transmission::Input::Key::SPACE ) == down ) {
			inputEventVector.push_back( new ShootEvent( this->renderingEngine->getLocalPlayerGuid( 0 ) ) );
		}
	}

	if (inputAdapter->getKeyState(Transmission::Input::Key::H) == down) {
		RenderableGame::getGlobalInstance()->getRenderingEngineInstance()->changeSaturation(-0.005f);
	}

	if (inputAdapter->getKeyState(Transmission::Input::Key::J) == down) {
		RenderableGame::getGlobalInstance()->getRenderingEngineInstance()->changeSaturation(0.005f);
	}

	if (inputAdapter->getKeyState(Transmission::Input::Key::K) == down) {
		RenderableGame::getGlobalInstance()->getRenderingEngineInstance()->changeLightness(-0.005f);
	}

	if (inputAdapter->getKeyState(Transmission::Input::Key::L) == down) {
		RenderableGame::getGlobalInstance()->getRenderingEngineInstance()->changeLightness(0.005f);
	}

	//if (dir.x != 0 || dir.y != 0 || dir.z != 0 || dir.w != 0) {
	inputEventVector.emplace_back( new MoveEvent( this->renderingEngine->getLocalPlayerGuid( 0 ), dir ) );
	//}
	return inputEventVector;
}