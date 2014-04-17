#include "GameObjectCtorTable.h"

#include "engine-core\IHasHandle.h"
#include "ObjectTypes.h"

GameObjectCtorTable::GameObjectCtorTable() : ObjectCtorTable(10) {
	this->initCtors();
}


GameObjectCtorTable::~GameObjectCtorTable() {
}

// Sample method
static IHasHandle * makeCommonCold() {
	return nullptr;
}

void GameObjectCtorTable::initCtors() {
	this->setCtor(ObjectTypes::CommonCold, makeCommonCold);
}