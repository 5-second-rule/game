#include "SignallingGameState.h"


SignallingGameState::SignallingGameState(INotifyReady<GameState> *notifier)
	: BaseObject(ObjectTypes::State) {
	this->notifier = notifier;
}

SignallingGameState::~SignallingGameState() {}


bool SignallingGameState::handleEvent(Event* evt) {
	return false;
}

void SignallingGameState::update(float dt){
	BaseObject::update(dt);
}

void SignallingGameState::reserveSize(IReserve& buffer) const {
	BaseObject::reserveSize(buffer);
	buffer.reserve(sizeof(notifier));
}

void SignallingGameState::fillBuffer(IFill& buffer) const {
	BaseObject::fillBuffer(buffer);
	INotifyReady<GameState> *notifier = reinterpret_cast<INotifyReady<GameState> *>(buffer.getPointer());
	buffer.filled();
}

void SignallingGameState::deserialize(BufferReader& reader) {
	BaseObject::deserialize(reader);
	const INotifyReady<GameState> *notifier = reinterpret_cast<const INotifyReady<GameState> *>(reader.getPointer());
	reader.finished(sizeof(MovingObjectData));
}