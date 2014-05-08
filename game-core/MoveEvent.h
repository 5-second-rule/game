#pragma once
#include "game-core.h"
#include "engine-core/ActionEvent.h"

class GAMECOREDLL MoveEvent : public ActionEvent {
public:
	struct MoveDirection {
		float x;
		float y;
		float z;
	};
	MoveDirection direction;

	MoveEvent( unsigned int playerGuid, MoveDirection direction );
	~MoveEvent();

	virtual void reserveSize( IReserve& buffer );
	virtual void fillBuffer( IFill& buffer );
	virtual void deserialize( BufferReader& buffer );
};