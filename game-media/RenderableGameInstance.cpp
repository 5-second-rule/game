#include "RenderableGameInstance.h"
#include "RenderableGameObjectCtorTable.h"
#include "engine-renderer/RenderableWorld.h"

RenderableGameInstance::RenderableGameInstance()
{
}


RenderableGameInstance::~RenderableGameInstance()
{
}

World * RenderableGameInstance::makeWorld() {
	return new World();
}

ObjectCtorTable * RenderableGameInstance::makeCtorTable() {
	return new RenderableGameObjectCtorTable();
}
