#include "RenderableGameInstance.h"
#include "RenderableGameObjectCtorTable.h"
#include "engine-renderer/RenderableWorld.h"

RenderableGameInstance::RenderableGameInstance(void *appHandle)
{
	this->appHandle = appHandle;
}

RenderableGameInstance::~RenderableGameInstance()
{
}

Event* RenderableGameInstance::inputTranslator(Transmission::Input::Key key, Transmission::Input::KeyState state) {
	switch (key) {
	case (Transmission::Input::Key::MOUSE_LMB): 
		if (state == Transmission::Input::KeyState::STATE_DOWN) {
			//e.g., return new MoveEvent(Direction::Forward)
			//e.g., return new AttackEvent(cursorLocation)
		}
		break;
	case (Transmission::Input::Key::MOUSE_RMB): break;
	case (Transmission::Input::Key::CANCEL): break;
	case (Transmission::Input::Key::MOUSE_MMB): break;
	case (Transmission::Input::Key::MOUSE_XB1): break;
	case (Transmission::Input::Key::MOUSE_XB2): break;
	case (Transmission::Input::Key::BACKSPACE): break;
	case (Transmission::Input::Key::TAB): break;
	case (Transmission::Input::Key::CLEAR): break;
	case (Transmission::Input::Key::ENTER): break;
	case (Transmission::Input::Key::SHIFT): break;
	case (Transmission::Input::Key::CONTROL): break;
	case (Transmission::Input::Key::ALT): break;
	case (Transmission::Input::Key::PAUSE): break;
	case (Transmission::Input::Key::CAPSLOCK): break;
	case (Transmission::Input::Key::ESC): break;
	case (Transmission::Input::Key::SPACE): break;
	case (Transmission::Input::Key::PAGE_UP): break;
	case (Transmission::Input::Key::PAGE_DOWN): break;
	case (Transmission::Input::Key::END): break;
	case (Transmission::Input::Key::HOME): break;
	case (Transmission::Input::Key::LEFT_ARROW): break;
	case (Transmission::Input::Key::UP_ARROW): break;
	case (Transmission::Input::Key::RIGHT_ARROW): break;
	case (Transmission::Input::Key::DOWN_ARROW): break;
	case (Transmission::Input::Key::PRINTSCREEN): break;
	case (Transmission::Input::Key::INSERT): break;
	case (Transmission::Input::Key::DEL): break;
	case (Transmission::Input::Key::KEY_0): break;
	case (Transmission::Input::Key::KEY_1): break;
	case (Transmission::Input::Key::KEY_2): break;
	case (Transmission::Input::Key::KEY_3): break;
	case (Transmission::Input::Key::KEY_4): break;
	case (Transmission::Input::Key::KEY_5): break;
	case (Transmission::Input::Key::KEY_6): break;
	case (Transmission::Input::Key::KEY_7): break;
	case (Transmission::Input::Key::KEY_8): break;
	case (Transmission::Input::Key::KEY_9): break;
	case (Transmission::Input::Key::A): break;
	case (Transmission::Input::Key::B): break;
	case (Transmission::Input::Key::C): break;
	case (Transmission::Input::Key::D): break;
	case (Transmission::Input::Key::E): break;
	case (Transmission::Input::Key::F): break;
	case (Transmission::Input::Key::G): break;
	case (Transmission::Input::Key::H): break;
	case (Transmission::Input::Key::I): break;
	case (Transmission::Input::Key::J): break;
	case (Transmission::Input::Key::K): break;
	case (Transmission::Input::Key::L): break;
	case (Transmission::Input::Key::M): break;
	case (Transmission::Input::Key::N): break;
	case (Transmission::Input::Key::O): break;
	case (Transmission::Input::Key::P): break;
	case (Transmission::Input::Key::Q): break;
	case (Transmission::Input::Key::R): break;
	case (Transmission::Input::Key::S): break;
	case (Transmission::Input::Key::T): break;
	case (Transmission::Input::Key::U): break;
	case (Transmission::Input::Key::V): break;
	case (Transmission::Input::Key::W): break;
	case (Transmission::Input::Key::X): break;
	case (Transmission::Input::Key::Y): break;
	case (Transmission::Input::Key::Z): break;
	case (Transmission::Input::Key::SUPER): break;
	case (Transmission::Input::Key::MENU): break;
	case (Transmission::Input::Key::NUM_0): break;
	case (Transmission::Input::Key::NUM_1): break;
	case (Transmission::Input::Key::NUM_2): break;
	case (Transmission::Input::Key::NUM_3): break;
	case (Transmission::Input::Key::NUM_4): break;
	case (Transmission::Input::Key::NUM_5): break;
	case (Transmission::Input::Key::NUM_6): break;
	case (Transmission::Input::Key::NUM_7): break;
	case (Transmission::Input::Key::NUM_8): break;
	case (Transmission::Input::Key::NUM_9): break;
	case (Transmission::Input::Key::NUM_MULT): break;
	case (Transmission::Input::Key::NUM_ADD): break;
	case (Transmission::Input::Key::NUM_SUB): break;
	case (Transmission::Input::Key::NUM_DEC): break;
	case (Transmission::Input::Key::NUM_DIV): break;
	case (Transmission::Input::Key::F1): break;
	case (Transmission::Input::Key::F2): break;
	case (Transmission::Input::Key::F3): break;
	case (Transmission::Input::Key::F4): break;
	case (Transmission::Input::Key::F5): break;
	case (Transmission::Input::Key::F6): break;
	case (Transmission::Input::Key::F7): break;
	case (Transmission::Input::Key::F8): break;
	case (Transmission::Input::Key::F9): break;
	case (Transmission::Input::Key::F10): break;
	case (Transmission::Input::Key::F11): break;
	case (Transmission::Input::Key::F12): break;
	case (Transmission::Input::Key::NUM_LOCK): break;
	case (Transmission::Input::Key::SCROLL_LOCK): break;
	default:
		return nullptr;
	}

	return nullptr;
}

Engine * RenderableGameInstance::makeEngineInstance(GameObjectCtorTable *ctors) {
	return new RenderingEngine(
		new RenderableWorld(), 
		ctors,
		this->appHandle);
}

GameObjectCtorTable * RenderableGameInstance::makeCtorTable() {
	return new RenderableGameObjectCtorTable();
}

RenderableGameInstance * RenderableGameInstance::getGlobalInstance() {
	RenderableGameInstance *renderableInstance =
		dynamic_cast<RenderableGameInstance *>(GameInstance::getGlobalInstance());

	if (renderableInstance == nullptr) {
		throw std::runtime_error("Game instance isn't a rendering version.");
	}

	return renderableInstance;
}

RenderingEngine * RenderableGameInstance::getRenderingEngineInstance() {
	return dynamic_cast<RenderingEngine *>(this->getEngineInstance());
}

