#include "GameObjectCtorTable.h"

#include "MovingObject.h"
#include "ObjectTypes.h"

GameObjectCtorTable::GameObjectCtorTable() : ConstructorTable<IHasHandle>( OBJECT_TYPE_COUNT ) {}

GameObjectCtorTable::~GameObjectCtorTable() {}

static IHasHandle * makeEcoli( ConstructorTable<IHasHandle> *thisObj, Args* arg ) {
	return new MovingObject(ObjectTypes::Ecoli);
}

static IHasHandle * makeChickenPox( ConstructorTable<IHasHandle> *thisObj, Args* arg ) {
	return new MovingObject( ObjectTypes::ChickenPox );;
}

static IHasHandle * makeSyphillis( ConstructorTable<IHasHandle> *thisObj, Args* arg ) {
	return new MovingObject( ObjectTypes::Syphillis );;
}

static IHasHandle * makeMalaria( ConstructorTable<IHasHandle> *thisObj, Args* arg ) {
	return new MovingObject( ObjectTypes::Malaria );;
}

static IHasHandle * makeWhiteBlood( ConstructorTable<IHasHandle> *thisObj, Args* arg ) {
	return new MovingObject( ObjectTypes::WhiteBlood );;
}

static IHasHandle * makeRedBlood( ConstructorTable<IHasHandle> *thisObj, Args* arg ) {
	return new MovingObject( ObjectTypes::RedBlood );;
}

void GameObjectCtorTable::initCtors() {
	this->setConstructor( ObjectTypes::Ecoli, makeEcoli );
	this->setConstructor( ObjectTypes::ChickenPox, makeChickenPox );
	this->setConstructor( ObjectTypes::Syphillis, makeSyphillis );
	this->setConstructor( ObjectTypes::Malaria, makeMalaria );
	this->setConstructor( ObjectTypes::WhiteBlood, makeWhiteBlood );
	this->setConstructor( ObjectTypes::RedBlood, makeRedBlood );
}