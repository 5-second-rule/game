#pragma once
#include "game-core.h"
#include "engine-core/ActionEvent.h"

class GAMECOREDLL ShootEvent : public ActionEvent {
public:

	ShootEvent( unsigned int playerGuid );
	~ShootEvent();

	virtual void reserveSize( BufferBuilder *buffer );
	virtual void fillBuffer( BufferBuilder *buffer );
	virtual void deserialize( BufferReader& buffer );
};
