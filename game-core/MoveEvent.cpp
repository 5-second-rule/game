#include "MoveEvent.h"
#include "GameInstance.h"
#include "ActionType.h"

MoveEvent::MoveEvent( unsigned int playerGuid, MoveDirection direction ) : ActionEvent(playerGuid) {
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
	ActionEvent::deserialize( buffer );
	this->direction = *reinterpret_cast<const MoveDirection*>(buffer.getPointer());
	buffer.finished( sizeof( this->direction ) );
}