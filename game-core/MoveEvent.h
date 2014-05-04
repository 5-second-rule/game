#pragma once
#include "game-core.h"
#include "engine-core/ActionEvent.h"

enum class MoveDirection {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class GAMECOREDLL MoveEvent : public ActionEvent {
public:
	MoveDirection direction;

	MoveEvent( unsigned int playerGuid, size_t index, MoveDirection direction );
	~MoveEvent();

	virtual void reserveSize( BufferBuilder *buffer );
	virtual void fillBuffer( BufferBuilder *buffer );
	virtual void deserialize( BufferReader& buffer );
};

