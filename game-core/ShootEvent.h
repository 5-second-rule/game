#pragma once
#include "game-core.h"
#include "engine-core/ActionEvent.h"
#include "ActionType.h"

class GAMECOREDLL ShootEvent : public ActionEvent {
public:
	static const ActionType ACTIONTYPE = ActionType::SHOOT;

	ShootEvent( unsigned int playerGuid );
	~ShootEvent();

	virtual void reserveSize( IReserve& buffer ) const;
	virtual void fillBuffer( IFill& buffer ) const;
	virtual void deserialize( BufferReader& buffer );
};
