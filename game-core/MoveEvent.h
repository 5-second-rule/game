#pragma once
#include "game-core.h"
#include "engine-core/ActionEvent.h"
#include "ActionType.h"

class GAMECOREDLL MoveEvent : public ActionEvent {
public:
	struct MoveDirection {
		float x;
		float y;

		float z;
	};
	static const ActionType ACTIONTYPE = ActionType::MOVE;

	MoveDirection direction;

	MoveEvent( unsigned int playerGuid, MoveDirection direction );
	MoveEvent(unsigned int playerGuid, const char* data);
	~MoveEvent();

	virtual void reserveSize( IReserve& buffer ) const;
	virtual void fillBuffer( IFill& buffer ) const;
	virtual void deserialize( BufferReader& buffer );
};
