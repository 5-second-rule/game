#include "GameObjectCtorTable.h"

#include "engine-core\IHasHandle.h"
#include "RedBloodCell.h"
#include "ObjectTypes.h"
#include "GameInstance.h"

GameObjectCtorTable::GameObjectCtorTable() : ObjectCtorTable( OBJECT_TYPE_COUNT ) {
	this->initCtors();
}

GameObjectCtorTable::~GameObjectCtorTable() {}

static IHasHandle * makeEcoli(ObjectCtorTable *thisObj) {
	return new MovingObject(ObjectTypes::Ecoli);
}

static IHasHandle * makeChickenPox(ObjectCtorTable *thisObj) {
	return nullptr;
}

static IHasHandle * makeSyphillis(ObjectCtorTable *thisObj) {
	return nullptr;
}

static IHasHandle * makeWhiteBlood(ObjectCtorTable *thisObj) {
	return nullptr;
}

static IHasHandle * makeRedBlood(ObjectCtorTable *thisObj) {
	return nullptr;
}

void GameObjectCtorTable::initCtors() {
	this->setCtor( ObjectTypes::Ecoli, makeEcoli );
	this->setCtor( ObjectTypes::ChickenPox, makeChickenPox );
	this->setCtor( ObjectTypes::Syphillis, makeSyphillis );
	this->setCtor( ObjectTypes::WhiteBlood, makeWhiteBlood );
	this->setCtor( ObjectTypes::RedBlood, makeRedBlood );
}