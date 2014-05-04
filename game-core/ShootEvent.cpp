#include "ShootEvent.h"
#include "GameInstance.h"

ShootEvent::ShootEvent( unsigned int playerGuid ) : ActionEvent( playerGuid ) {
	this->actionType = static_cast<int>(ActionType::SHOOT);
}

ShootEvent::~ShootEvent() {}

void ShootEvent::reserveSize( BufferBuilder *buffer ) {
	ActionEvent::reserveSize( buffer );
}

void ShootEvent::fillBuffer( BufferBuilder *buffer ) {
	ActionEvent::fillBuffer( buffer );
}

void ShootEvent::deserialize( BufferReader& buffer ) {
	ActionEvent::deserialize( buffer );
}