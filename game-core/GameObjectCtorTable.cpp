#include "GameObjectCtorTable.h"

#include "engine-core\IHasHandle.h"
#include "ObjectTypes.h"
#include "GameInstance.h"

GameObjectCtorTable::GameObjectCtorTable() : ObjectCtorTable( OBJECT_TYPE_COUNT ) {
	this->initCtors();
}

GameObjectCtorTable::~GameObjectCtorTable() {}

static IHasHandle * makeEcoli( void *thisObj ) {
	return nullptr;
}

static IHasHandle * makeChickenPox( void *thisObj ) {
	return nullptr;
}

static IHasHandle * makeSyphillis( void *thisObj ) {
	return nullptr;
}
static IHasHandle * makeWhiteBlood( void *thisObj ) {
	return nullptr;
}

static IHasHandle * makeRedBlood( void *thisObj ) {
	return nullptr;
}

void GameObjectCtorTable::initCtors() {
	this->setCtor( ObjectTypes::Ecoli, makeEcoli );
	this->setCtor( ObjectTypes::ChickenPox, makeChickenPox );
	this->setCtor( ObjectTypes::Syphillis, makeSyphillis );
	this->setCtor( ObjectTypes::WhiteBlood, makeWhiteBlood );
	this->setCtor( ObjectTypes::RedBlood, makeRedBlood );
}