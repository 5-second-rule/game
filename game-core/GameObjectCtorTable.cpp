#include "GameObjectCtorTable.h"

#include "MovingObject.h"
#include "ObjectTypes.h"
#include "StaticObject.h"
#include "Tube.h"

GameObjectCtorTable::GameObjectCtorTable() : ConstructorTable<BaseObject>( OBJECT_TYPE_COUNT ) {}

GameObjectCtorTable::~GameObjectCtorTable() {}

static BaseObject * makeEcoli(ConstructorTable<BaseObject> *thisObj) {
	return new MovingObject(ObjectTypes::Ecoli, Game::getGlobalInstance());
}

static BaseObject * makeChickenPox(ConstructorTable<BaseObject> *thisObj) {
	return new MovingObject( ObjectTypes::ChickenPox, Game::getGlobalInstance() );
}

static BaseObject * makeSyphillis(ConstructorTable<BaseObject> *thisObj) {
	return new MovingObject( ObjectTypes::Syphillis, Game::getGlobalInstance() );
}

static BaseObject * makeMalaria(ConstructorTable<BaseObject> *thisObj) {
	return new MovingObject( ObjectTypes::Malaria, Game::getGlobalInstance() );
}

static BaseObject * makeWhiteBlood(ConstructorTable<BaseObject> *thisObj) {
	return new MovingObject( ObjectTypes::WhiteBlood, Game::getGlobalInstance() );
}

static BaseObject * makeRedBlood(ConstructorTable<BaseObject> *thisObj) {
	return new MovingObject( ObjectTypes::RedBlood, Game::getGlobalInstance() );
}

static BaseObject * makeTrack(ConstructorTable<BaseObject> *thisObj) {
	return new Tube();
}

static BaseObject * makeSelectionScreen(ConstructorTable<BaseObject> *thisObj) {
	return new StaticObject(ObjectTypes::SelectionScreen);
}

void GameObjectCtorTable::initCtors() {
	this->setConstructor( ObjectTypes::Ecoli, makeEcoli );
	this->setConstructor( ObjectTypes::ChickenPox, makeChickenPox );
	this->setConstructor( ObjectTypes::Syphillis, makeSyphillis );
	this->setConstructor( ObjectTypes::Malaria, makeMalaria );
	this->setConstructor( ObjectTypes::WhiteBlood, makeWhiteBlood );
	this->setConstructor( ObjectTypes::RedBlood, makeRedBlood );
	this->setConstructor( ObjectTypes::Track, makeTrack );
	this->setConstructor( ObjectTypes::SelectionScreen, makeSelectionScreen );
}