#include "SoundCtorTable.h"

#include "RenderableGame.h"

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

SoundCtorTable::SoundCtorTable() : ConstructorTable<SoundObject>( 10 ) {}


SoundCtorTable::~SoundCtorTable() {}


static SoundObject * makeSoundtrack( ConstructorTable<SoundObject> *thisObj ) {
	SoundCtorTable *table = (SoundCtorTable *)thisObj;

	return new SoundObject( RenderableGame::getGlobalInstance()->getRenderingEngineInstance()->createSoundFromIndex(
		table->soundIndices[ static_cast<int>(Sounds::SOUNDTRACK) ] )
		);
}


static SoundObject * makeShootSound( ConstructorTable<SoundObject> *thisObj ) {
	SoundCtorTable *table = (SoundCtorTable *)thisObj;

	return new SoundObject( RenderableGame::getGlobalInstance()->getRenderingEngineInstance()->createSoundFromIndex(
		table->soundIndices[static_cast<int>(Sounds::SHOOT)])
		);
}


static SoundObject * makeCollideSound( ConstructorTable<SoundObject> *thisObj ) {
	SoundCtorTable *table = (SoundCtorTable *)thisObj;

	return new SoundObject(RenderableGame::getGlobalInstance()->getRenderingEngineInstance()->createSoundFromIndex(
		table->soundIndices[static_cast<int>(Sounds::COLLIDE)])
		);
}

void SoundCtorTable::initCtors() {
	RenderingEngine *engine =
		RenderableGame::getGlobalInstance()->getRenderingEngineInstance();


	this->soundIndices[static_cast<int>(Sounds::SOUNDTRACK)] = engine->loadSound( "resources/soundtrack.wav" );
	//this->soundIndices[static_cast<int>(Sounds::ACCEL)] = engine->loadSound( "resources/accelerate.wav" );
	//this->soundIndices[static_cast<int>(Sounds::DEACCEL)] = engine->loadSound( "resources/deaccelerate.wav" );
	this->soundIndices[static_cast<int>(Sounds::SHOOT)] = engine->loadSound( "resources/shoot.wav" );
	this->soundIndices[static_cast<int>(Sounds::COLLIDE)] = engine->loadSound( "resources/collide.wav" );

	this->setConstructor( static_cast<int>(Sounds::SOUNDTRACK), makeSoundtrack );
	this->setConstructor( static_cast<int>(Sounds::SHOOT), makeShootSound );
	this->setConstructor( static_cast<int>(Sounds::COLLIDE), makeCollideSound );
}