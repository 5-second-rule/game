#include "ShootEvent.h"
#include "GameInstance.h"

ShootEvent::ShootEvent( unsigned int playerGuid ) : ActionEvent( playerGuid ) {
	this->actionType = static_cast<int>(ActionType::SHOOT);
}

ShootEvent::~ShootEvent() {}

void ShootEvent::reserveSize( IReserve& buffer ) {
	ActionEvent::reserveSize( buffer );
}

void ShootEvent::fillBuffer( IFill& buffer ) {
	ActionEvent::fillBuffer( buffer );
}

void ShootEvent::deserialize( BufferReader& buffer ) {
	ActionEvent::deserialize( buffer );
}