#pragma once
#include "game-core.h"
#include "engine-core/ActionEvent.h"

enum class MoveDirection {
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3,
	FORWARD = 4 ,
	BACK = 5
};

class GAMECOREDLL MoveEvent : public ActionEvent {
public:
	MoveDirection direction;

	MoveEvent( unsigned int playerGuid, MoveDirection direction );
	~MoveEvent();

	virtual void reserveSize( IReserve& buffer );
	virtual void fillBuffer( IFill& buffer );
	virtual void deserialize( BufferReader& buffer );
};