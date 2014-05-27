#pragma once

#include "game-media.h"
#include "engine-core\ConstructorTable.h"
#include "engine-renderer\SoundObject.h"
#include "game-core\Sounds.h"

class GAMEMEDIADLL SoundCtorTable :
	public ConstructorTable < SoundObject > {
public:
	int soundIndices[static_cast<int>(Sounds::COUNT)];
	
	SoundCtorTable();
	~SoundCtorTable();

	virtual void initCtors();
};

