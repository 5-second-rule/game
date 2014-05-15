#include "MoveEvent.h"
#include "Game.h"

MoveEvent::MoveEvent( unsigned int playerGuid, MoveDirection direction )
	: ActionEvent(playerGuid, static_cast<int>(MoveEvent::ACTIONTYPE))
{
	this->direction = direction;
}

MoveEvent::MoveEvent(unsigned int playerGuid, const char* data)
	: ActionEvent(playerGuid, static_cast<int>(MoveEvent::ACTIONTYPE))
{
	if(data != nullptr )
		this->direction = *reinterpret_cast<const MoveDirection*>(data);
}


MoveEvent::~MoveEvent() {}


void MoveEvent::reserveSize( IReserve& buffer ) const {
	ActionEvent::reserveSize( buffer );
	buffer.reserve( sizeof( this->direction ) );
}

void MoveEvent::fillBuffer( IFill& buffer ) const {
	ActionEvent::fillBuffer( buffer );
	*reinterpret_cast<MoveDirection*>(buffer.getPointer()) = this->direction;
	buffer.filled();
}


void MoveEvent::deserialize( BufferReader& buffer ) {
	ActionEvent::deserialize( buffer );
	this->direction = *reinterpret_cast<const MoveDirection*>(buffer.getPointer());
	buffer.finished( sizeof( this->direction ) );
}