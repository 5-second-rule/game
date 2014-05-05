#pragma once
#include "game-core.h"
#include "engine-core/ActionEvent.h"

class GAMECOREDLL ShootEvent : public ActionEvent {
public:

	ShootEvent( unsigned int playerGuid );
	~ShootEvent();

	virtual void reserveSize( IReserve& buffer );
	virtual void fillBuffer( IFill& buffer );
	virtual void deserialize( BufferReader& buffer );
};
