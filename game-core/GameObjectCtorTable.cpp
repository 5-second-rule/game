#include "GameObjectCtorTable.h"

#include "engine-core\IHasWorldObject.h"
#include "ObjectTypes.h"

GameObjectCtorTable::GameObjectCtorTable() : ObjectCtorTable(10) {
	this->initCtors();
}


GameObjectCtorTable::~GameObjectCtorTable() {
}

// Sample method
static IHasWorldObject * makeCommonCold() {
	return nullptr;
}

void GameObjectCtorTable::initCtors() {
	this->setCtor(ObjectTypes::CommonCold, makeCommonCold);
}