#pragma once
#include "engine-core/ActionEvent.h"

enum class MoveDirection {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class MoveEvent : public ActionEvent {
public:
	MoveDirection direction;

	MoveEvent( unsigned int playerGuid, size_t index, MoveDirection direction );
	~MoveEvent();
};

