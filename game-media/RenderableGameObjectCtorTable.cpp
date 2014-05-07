#include "RenderableGameObjectCtorTable.h"
#include "game-core/ObjectTypes.h"
#include "engine-renderer/RenderableObject.h"

#include "RenderableMovingObject.h"

#include "RenderableGame.h"

RenderableGameObjectCtorTable::RenderableGameObjectCtorTable() {
}

RenderableGameObjectCtorTable::~RenderableGameObjectCtorTable() {
}

static IHasHandle * makeRenderableEcoli(ObjectCtorTable *thisObj) {
	RenderableGameObjectCtorTable *table = (RenderableGameObjectCtorTable *)thisObj;

	return new RenderableMovingObject(
		ObjectTypes::Ecoli,
		RenderableGame::getGlobalInstance()
			->getRenderingEngineInstance()
			->createModelFromIndex(
				table->modelIndexes[ObjectTypes::Ecoli],
				table->textureIndexes[ObjectTypes::Ecoli]
			)
		);
}

void RenderableGameObjectCtorTable::initCtors() {
	RenderingEngine *engine = 
		RenderableGame::getGlobalInstance()
			->getRenderingEngineInstance();

	this->modelIndexes[ObjectTypes::Ecoli] = engine->loadModel("resources/ecoli6_nomedia.fbx");
	this->textureIndexes[ObjectTypes::Ecoli] = engine->loadTexture("resources/Wood.dds");

	this->setCtor(ObjectTypes::Ecoli, makeRenderableEcoli);
}