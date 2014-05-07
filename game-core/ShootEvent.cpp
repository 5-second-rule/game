#include "ShootEvent.h"
#include "ActionType.h"
#include "Game.h"

ShootEvent::ShootEvent(unsigned int playerGuid)
	: ActionEvent(playerGuid, static_cast<int>(ShootEvent::ACTIONTYPE) )
{}

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