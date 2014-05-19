#include "RenderableGameObjectCtorTable.h"
#include "game-core/ObjectTypes.h"

#include "RenderableMovingObject.h"
#include "RenderableStaticObject.h"

#include "RenderableGame.h"

RenderableGameObjectCtorTable::RenderableGameObjectCtorTable() {}

RenderableGameObjectCtorTable::~RenderableGameObjectCtorTable() {}

static BaseObject * makeRenderableEcoli(ConstructorTable<BaseObject> *thisObj) {
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

static BaseObject * makeRenderableChickenPox(ConstructorTable<BaseObject> *thisObj) {
	RenderableGameObjectCtorTable *table = (RenderableGameObjectCtorTable *)thisObj;

	return new RenderableMovingObject(
		ObjectTypes::ChickenPox,
		RenderableGame::getGlobalInstance()
		->getRenderingEngineInstance()
		->createModelFromIndex(
		table->modelIndexes[ObjectTypes::ChickenPox],
		table->textureIndexes[ObjectTypes::ChickenPox],
		table->vertexShaderIndexes[ObjectTypes::ChickenPox],
		table->pixelShaderIndexes[ObjectTypes::ChickenPox])
		);
}

static BaseObject * makeRenderableSyphillis(ConstructorTable<BaseObject> *thisObj) {
	RenderableGameObjectCtorTable *table = (RenderableGameObjectCtorTable *)thisObj;

	return new RenderableMovingObject(
		ObjectTypes::Syphillis,
		RenderableGame::getGlobalInstance()
		->getRenderingEngineInstance()
		->createModelFromIndex(
		table->modelIndexes[ObjectTypes::Syphillis],
		table->textureIndexes[ObjectTypes::Syphillis],
		table->vertexShaderIndexes[ObjectTypes::Syphillis],
		table->pixelShaderIndexes[ObjectTypes::Syphillis] )
		);
}

static BaseObject * makeRenderableMalaria(ConstructorTable<BaseObject> *thisObj) {
	RenderableGameObjectCtorTable *table = (RenderableGameObjectCtorTable *)thisObj;

	return new RenderableMovingObject(
		ObjectTypes::Malaria,
		RenderableGame::getGlobalInstance()
		->getRenderingEngineInstance()
		->createModelFromIndex(
		table->modelIndexes[ObjectTypes::Malaria],
		table->textureIndexes[ObjectTypes::Malaria],
		table->vertexShaderIndexes[ObjectTypes::Malaria],
		table->pixelShaderIndexes[ObjectTypes::Malaria] )
		);
}

static BaseObject * makeRenderableWhiteBlood(ConstructorTable<BaseObject> *thisObj) {
	RenderableGameObjectCtorTable *table = (RenderableGameObjectCtorTable *)thisObj;

	return new RenderableMovingObject(
		ObjectTypes::WhiteBlood,
		RenderableGame::getGlobalInstance()
		->getRenderingEngineInstance()
		->createModelFromIndex(
		table->modelIndexes[ObjectTypes::WhiteBlood],
		table->textureIndexes[ObjectTypes::WhiteBlood] )
		);
}

static BaseObject * makeRenderableRedBlood(ConstructorTable<BaseObject> *thisObj) {
	RenderableGameObjectCtorTable *table = (RenderableGameObjectCtorTable *)thisObj;

	return new RenderableMovingObject(
		ObjectTypes::RedBlood,
		RenderableGame::getGlobalInstance()
		->getRenderingEngineInstance()
		->createModelFromIndex(
		table->modelIndexes[ObjectTypes::RedBlood],
		table->textureIndexes[ObjectTypes::RedBlood] )
		);
}

static BaseObject * makeRenderableTrack(ConstructorTable<BaseObject> *thisObj) {
	RenderableGameObjectCtorTable *table = (RenderableGameObjectCtorTable *)thisObj;

	return new RenderableStaticObject(
		ObjectTypes::Track,
		RenderableGame::getGlobalInstance()
		->getRenderingEngineInstance()
		->createModelFromIndex(
		table->modelIndexes[ObjectTypes::Track],
		table->textureIndexes[ObjectTypes::Track],
		table->bumpIndexes[ObjectTypes::Track],
		table->vertexShaderIndexes[ObjectTypes::Track],
		table->pixelShaderIndexes[ObjectTypes::Track])
		);
}

void RenderableGameObjectCtorTable::initCtors() {
	GameObjectCtorTable::initCtors();
	RenderingEngine *engine = 
		RenderableGame::getGlobalInstance()->getRenderingEngineInstance();

	this->modelIndexes[ObjectTypes::Ecoli] = engine->loadModel("resources/ecoli6_nomedia.fbx");
	this->textureIndexes[ObjectTypes::Ecoli] = engine->loadTexture("resources/Wood.dds");

	this->modelIndexes[ObjectTypes::ChickenPox] = engine->loadModel( "resources/herpes2.fbx" );
	this->textureIndexes[ObjectTypes::ChickenPox] = engine->loadTexture( "resources/herpes_3_TXTR.dds" );
	this->vertexShaderIndexes[ObjectTypes::ChickenPox] = engine->loadVertexShader( "resources/vertexRipple.cso" );
	this->pixelShaderIndexes[ObjectTypes::ChickenPox] = engine->loadPixelShader( "resources/pixel.cso" );

	this->modelIndexes[ObjectTypes::Syphillis] = engine->loadModel( "resources/pox.fbx" );
	this->textureIndexes[ObjectTypes::Syphillis] = engine->loadTexture( "resources/pox_TXTR.dds" );
	this->vertexShaderIndexes[ObjectTypes::Syphillis] = engine->loadVertexShader( "resources/vertexSpring.cso" );
	this->pixelShaderIndexes[ObjectTypes::Syphillis] = engine->loadPixelShader( "resources/pixel.cso" );

	this->modelIndexes[ObjectTypes::Malaria] = engine->loadModel( "resources/malaria.fbx" );
	this->textureIndexes[ObjectTypes::Malaria] = engine->loadTexture( "resources/malaria_TXTR.dds" );
	this->vertexShaderIndexes[ObjectTypes::Malaria] = engine->loadVertexShader( "resources/vertexWiggle.cso" );
	this->pixelShaderIndexes[ObjectTypes::Malaria] = engine->loadPixelShader( "resources/pixel.cso" );

	this->modelIndexes[ObjectTypes::WhiteBlood] = engine->loadModel( "resources/ecoli6_nomedia.fbx" );
	this->textureIndexes[ObjectTypes::WhiteBlood] = engine->loadTexture( "resources/Wood.dds" );

	this->modelIndexes[ObjectTypes::RedBlood] = engine->loadModel( "resources/ecoli6_nomedia.fbx" );
	this->textureIndexes[ObjectTypes::RedBlood] = engine->loadTexture( "resources/Wood.dds" );

	this->modelIndexes[ObjectTypes::Track] = engine->loadModel("resources/track.trk", false);
	this->textureIndexes[ObjectTypes::Track] = engine->loadTexture("resources/bloodCell_TXTR.dds");
	this->bumpIndexes[ObjectTypes::Track] = engine->loadBumpMap("resources/bloodCellBump.dds");
	this->vertexShaderIndexes[ObjectTypes::Track] = engine->loadVertexShader("resources/vertexTrack.cso");
	this->pixelShaderIndexes[ObjectTypes::Track] = engine->loadPixelShader("resources/pixelBump.cso");

	this->setConstructor(ObjectTypes::Ecoli, makeRenderableEcoli);
	this->setConstructor( ObjectTypes::ChickenPox, makeRenderableChickenPox );
	this->setConstructor( ObjectTypes::Syphillis, makeRenderableSyphillis );
	this->setConstructor( ObjectTypes::Malaria, makeRenderableMalaria );
	this->setConstructor( ObjectTypes::WhiteBlood, makeRenderableWhiteBlood );
	this->setConstructor( ObjectTypes::RedBlood, makeRenderableRedBlood );
	this->setConstructor(ObjectTypes::Track, makeRenderableTrack);
}