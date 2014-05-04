#include "MoveEvent.h"
#include "GameInstance.h"

MoveEvent::MoveEvent( unsigned int playerGuid, size_t index, MoveDirection direction ) : ActionEvent(playerGuid, index) {
	this->direction = direction;
	this->actionType = static_cast<int>(ActionType::MOVE);
}


MoveEvent::~MoveEvent() {}


void MoveEvent::reserveSize( BufferBuilder *buffer ) {
	ActionEvent::reserveSize( buffer );
	buffer->reserve( sizeof( this->direction ) );
}

void MoveEvent::fillBuffer( BufferBuilder *buffer ) {
	ActionEvent::fillBuffer( buffer );
	*reinterpret_cast<MoveDirection*>(buffer->getPointer()) = this->direction;
	buffer->pop();
}


void MoveEvent::deserialize( BufferReader& buffer ) {
	const struct EventHeader *hdr = reinterpret_cast<const struct EventHeader *>(buffer.getPointer());
	buffer.finished( sizeof( struct EventHeader ) );
}