#include "MoveEvent.h"


MoveEvent::MoveEvent( unsigned int playerGuid, size_t index, MoveDirection direction ) : ActionEvent(playerGuid, index) {
	this->direction = direction;
}


MoveEvent::~MoveEvent() {}
