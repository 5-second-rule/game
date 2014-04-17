#include "RenderableGameObjectCtorTable.h"
#include "game-core/ObjectTypes.h"

RenderableGameObjectCtorTable::RenderableGameObjectCtorTable() {
}


RenderableGameObjectCtorTable::~RenderableGameObjectCtorTable() {
}

// Sample method
static IHasHandle * makeRenderableCommonCold() {
	return nullptr;
}

void RenderableGameObjectCtorTable::initCtors() {
	this->setCtor(ObjectTypes::CommonCold, makeRenderableCommonCold);
}