#include "GameObjectCtorTable.h"

#include "engine-core\IHasHandle.h"
#include "ObjectTypes.h"
#include "GameInstance.h"

GameObjectCtorTable::GameObjectCtorTable() : ObjectCtorTable(OBJECT_TYPE_COUNT) {
	this->initCtors();
}

GameObjectCtorTable::~GameObjectCtorTable() {
}

static IHasHandle * makeEcoli(void *thisObj) {
	return nullptr;
}

void GameObjectCtorTable::initCtors() {
	this->setCtor(ObjectTypes::Ecoli, makeEcoli);
}