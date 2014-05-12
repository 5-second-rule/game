#include "RenderableGameObjectCtorTable.h"
#include "game-core/ObjectTypes.h"
#include "engine-renderer/RenderableObject.h"

#include "RenderableMovingObject.h"

#include "RenderableGame.h"

RenderableGameObjectCtorTable::RenderableGameObjectCtorTable() {}

RenderableGameObjectCtorTable::~RenderableGameObjectCtorTable() {}

static IHasHandle * makeRenderableEcoli( ConstructorTable<IHasHandle> *thisObj, Args* arg ) {
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

static IHasHandle * makeRenderableChickenPox( ConstructorTable<IHasHandle> *thisObj, Args* arg ) {
	RenderableGameObjectCtorTable *table = (RenderableGameObjectCtorTable *)thisObj;

	return new RenderableMovingObject(
		ObjectTypes::ChickenPox,
		RenderableGame::getGlobalInstance()
		->getRenderingEngineInstance()
		->createModelFromIndex(
		table->modelIndexes[ObjectTypes::ChickenPox],
		table->textureIndexes[ObjectTypes::ChickenPox]
		)
		);
}

static IHasHandle * makeRenderableSyphillis( ConstructorTable<IHasHandle> *thisObj, Args* arg ) {
	RenderableGameObjectCtorTable *table = (RenderableGameObjectCtorTable *)thisObj;

	return new RenderableMovingObject(
		ObjectTypes::Syphillis,
		RenderableGame::getGlobalInstance()
		->getRenderingEngineInstance()
		->createModelFromIndex(
		table->modelIndexes[ObjectTypes::Syphillis],
		table->textureIndexes[ObjectTypes::Syphillis]
		)
		);
}

static IHasHandle * makeRenderableWhiteBlood( ConstructorTable<IHasHandle> *thisObj, Args* arg ) {
	RenderableGameObjectCtorTable *table = (RenderableGameObjectCtorTable *)thisObj;

	return new RenderableMovingObject(
		ObjectTypes::WhiteBlood,
		RenderableGame::getGlobalInstance()
		->getRenderingEngineInstance()
		->createModelFromIndex(
		table->modelIndexes[ObjectTypes::WhiteBlood],
		table->textureIndexes[ObjectTypes::WhiteBlood]
		)
		);
}

static IHasHandle * makeRenderableRedBlood( ConstructorTable<IHasHandle> *thisObj, Args* arg ) {
	RenderableGameObjectCtorTable *table = (RenderableGameObjectCtorTable *)thisObj;

	return new RenderableMovingObject(
		ObjectTypes::RedBlood,
		RenderableGame::getGlobalInstance()
		->getRenderingEngineInstance()
		->createModelFromIndex(
		table->modelIndexes[ObjectTypes::RedBlood],
		table->textureIndexes[ObjectTypes::RedBlood]
		)
		);
}

void RenderableGameObjectCtorTable::initCtors() {
	RenderingEngine *engine = 
		RenderableGame::getGlobalInstance()->getRenderingEngineInstance();

	this->modelIndexes[ObjectTypes::Ecoli] = engine->loadModel("resources/ecoli6_nomedia.fbx");
	this->textureIndexes[ObjectTypes::Ecoli] = engine->loadTexture("resources/Wood.dds");
	this->modelIndexes[ObjectTypes::ChickenPox] = engine->loadModel( "resources/ecoli6_nomedia.fbx" );
	this->textureIndexes[ObjectTypes::ChickenPox] = engine->loadTexture( "resources/Wood.dds" );
	this->modelIndexes[ObjectTypes::Syphillis] = engine->loadModel( "resources/ecoli6_nomedia.fbx" );
	this->textureIndexes[ObjectTypes::Syphillis] = engine->loadTexture( "resources/Wood.dds" );
	this->modelIndexes[ObjectTypes::WhiteBlood] = engine->loadModel( "resources/ecoli6_nomedia.fbx" );
	this->textureIndexes[ObjectTypes::WhiteBlood] = engine->loadTexture( "resources/Wood.dds" );
	this->modelIndexes[ObjectTypes::RedBlood] = engine->loadModel( "resources/ecoli6_nomedia.fbx" );
	this->textureIndexes[ObjectTypes::RedBlood] = engine->loadTexture( "resources/Wood.dds" );
	

	this->setConstructor(ObjectTypes::Ecoli, makeRenderableEcoli);
	this->setConstructor( ObjectTypes::ChickenPox, makeRenderableChickenPox );
	this->setConstructor( ObjectTypes::Syphillis, makeRenderableSyphillis );
	this->setConstructor( ObjectTypes::WhiteBlood, makeRenderableWhiteBlood );
	this->setConstructor( ObjectTypes::RedBlood, makeRenderableRedBlood );
}