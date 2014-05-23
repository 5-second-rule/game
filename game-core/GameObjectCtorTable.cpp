#include "GameObjectCtorTable.h"

#include "MovingObject.h"
#include "ObjectTypes.h"
#include "StaticObject.h"
#include "Tube.h"

GameObjectCtorTable::GameObjectCtorTable() : ConstructorTable<BaseObject>( OBJECT_TYPE_COUNT ) {}

GameObjectCtorTable::~GameObjectCtorTable() {}

static BaseObject * makeEcoli(ConstructorTable<BaseObject> *thisObj) {
	return new MovingObject(ObjectTypes::Ecoli);
}

static BaseObject * makeChickenPox(ConstructorTable<BaseObject> *thisObj) {
	return new MovingObject( ObjectTypes::ChickenPox );
}

static BaseObject * makeSyphillis(ConstructorTable<BaseObject> *thisObj) {
	return new MovingObject( ObjectTypes::Syphillis );
}

static BaseObject * makeMalaria(ConstructorTable<BaseObject> *thisObj) {
	return new MovingObject( ObjectTypes::Malaria );
}

static BaseObject * makeWhiteBlood(ConstructorTable<BaseObject> *thisObj) {
	return new MovingObject( ObjectTypes::WhiteBlood );
}

static BaseObject * makeRedBlood(ConstructorTable<BaseObject> *thisObj) {
	return new MovingObject( ObjectTypes::RedBlood );
}

static BaseObject * makeTrack(ConstructorTable<BaseObject> *thisObj) {
	return new Tube();
}

void GameObjectCtorTable::initCtors() {
	this->setConstructor( ObjectTypes::Ecoli, makeEcoli );
	this->setConstructor( ObjectTypes::ChickenPox, makeChickenPox );
	this->setConstructor( ObjectTypes::Syphillis, makeSyphillis );
	this->setConstructor( ObjectTypes::Malaria, makeMalaria );
	this->setConstructor( ObjectTypes::WhiteBlood, makeWhiteBlood );
	this->setConstructor( ObjectTypes::RedBlood, makeRedBlood );
	this->setConstructor( ObjectTypes::Track, makeTrack );
}