#include "RenderableGameObjectCtorTable.h"
#include "game-core/ObjectTypes.h"

#include "RenderableMovingObject.h"
#include "RenderableStaticObject.h"
#include "RenderableWallOfDeath.h"
#include "RenderablePowerup.h"

#include "RenderableSelectionScreen.h"
#include "RenderableGame.h"

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

static SelectionScreenData *selectionScreenData;

RenderableGameObjectCtorTable::RenderableGameObjectCtorTable() {}

RenderableGameObjectCtorTable::~RenderableGameObjectCtorTable() {}

static BaseObject * makeRenderableEcoli( ConstructorTable<BaseObject> *thisObj ) {
	RenderableGameObjectCtorTable *table = (RenderableGameObjectCtorTable *)thisObj;

	return new RenderableMovingObject(
		ObjectTypes::Ecoli,
		RenderableGame::getGlobalInstance()
		->getRenderingEngineInstance()
		->createModelFromIndex(
		table->modelIndexes[ObjectTypes::Ecoli],
		table->textureIndexes[ObjectTypes::Ecoli],
		table->vertexShaderIndexes[ObjectTypes::Ecoli],
		table->pixelShaderIndexes[ObjectTypes::Ecoli] )
		);
}

static BaseObject * makeRenderableChickenPox( ConstructorTable<BaseObject> *thisObj ) {
	RenderableGameObjectCtorTable *table = (RenderableGameObjectCtorTable *)thisObj;

	return new RenderableMovingObject(
		ObjectTypes::ChickenPox,
		RenderableGame::getGlobalInstance()
		->getRenderingEngineInstance()
		->createModelFromIndex(
		table->modelIndexes[ObjectTypes::ChickenPox],
		table->textureIndexes[ObjectTypes::ChickenPox],
		table->vertexShaderIndexes[ObjectTypes::ChickenPox],
		table->pixelShaderIndexes[ObjectTypes::ChickenPox] )
		);
}

static BaseObject * makeRenderableSyphillis( ConstructorTable<BaseObject> *thisObj ) {
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

static BaseObject * makeRenderableMalaria( ConstructorTable<BaseObject> *thisObj ) {
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

static BaseObject * makeRenderableWhiteBlood( ConstructorTable<BaseObject> *thisObj ) {
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

static BaseObject * makeRenderableRedBlood( ConstructorTable<BaseObject> *thisObj ) {
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

static BaseObject * makeRenderableTrack( ConstructorTable<BaseObject> *thisObj ) {
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
		table->pixelShaderIndexes[ObjectTypes::Track] )
		);
}

static BaseObject * makeRenderableAdrenaline(ConstructorTable<BaseObject> *thisObj) {
	RenderableGameObjectCtorTable *table = (RenderableGameObjectCtorTable *)thisObj;

	return new RenderablePowerup(
		ObjectTypes::Adrenaline,
		RenderableGame::getGlobalInstance()
		->getRenderingEngineInstance()
		->createModelFromIndex(
		table->modelIndexes[ObjectTypes::Adrenaline],
		table->textureIndexes[ObjectTypes::Adrenaline])
		);
}

static BaseObject * makeRenderableSelectionScreen(ConstructorTable<BaseObject> *thisObj) {
	RenderableGameObjectCtorTable *table = (RenderableGameObjectCtorTable *)thisObj;
	return new RenderableSelectionScreen(selectionScreenData->getData());
}

void RenderableGameObjectCtorTable::prepSelectionScreenData() {
	RenderableMovingObject *playerObjects[4] = {
		new RenderableMovingObject(
		ObjectTypes::Ecoli,
		RenderableGame::getGlobalInstance()
		->getRenderingEngineInstance()
		->createModelFromIndex(
		this->modelIndexes[ObjectTypes::Ecoli],
		this->textureIndexes[ObjectTypes::Ecoli],
		this->vertexShaderIndexes[ObjectTypes::Ecoli],
		this->pixelShaderIndexes[ObjectTypes::Ecoli])
		),
		new RenderableMovingObject(
		ObjectTypes::ChickenPox,
		RenderableGame::getGlobalInstance()
		->getRenderingEngineInstance()
		->createModelFromIndex(
		this->modelIndexes[ObjectTypes::ChickenPox],
		this->textureIndexes[ObjectTypes::ChickenPox],
		this->vertexShaderIndexes[ObjectTypes::ChickenPox],
		this->pixelShaderIndexes[ObjectTypes::ChickenPox])
		),
		new RenderableMovingObject(
		ObjectTypes::Syphillis,
		RenderableGame::getGlobalInstance()
		->getRenderingEngineInstance()
		->createModelFromIndex(
		this->modelIndexes[ObjectTypes::Syphillis],
		this->textureIndexes[ObjectTypes::Syphillis],
		this->vertexShaderIndexes[ObjectTypes::Syphillis],
		this->pixelShaderIndexes[ObjectTypes::Syphillis])
		),
		new RenderableMovingObject(
		ObjectTypes::Malaria,
		RenderableGame::getGlobalInstance()
		->getRenderingEngineInstance()
		->createModelFromIndex(
		this->modelIndexes[ObjectTypes::Malaria],
		this->textureIndexes[ObjectTypes::Malaria],
		this->vertexShaderIndexes[ObjectTypes::Malaria],
		this->pixelShaderIndexes[ObjectTypes::Malaria])
		)
	};
	selectionScreenData = new SelectionScreenData(playerObjects);
}

static BaseObject * makeSignallingGameState(ConstructorTable<BaseObject> *thisObj) {
	RenderableGameObjectCtorTable *table = (RenderableGameObjectCtorTable *)thisObj;
	return new SignallingGameState( RenderableGame::getGlobalInstance()->getGameManager(),
																	RenderableGame::getGlobalInstance() );
}

static BaseObject * makeRenderableWallOfDeath(ConstructorTable<BaseObject> *thisObj) {
	RenderableGameObjectCtorTable *table = (RenderableGameObjectCtorTable *)thisObj;

	return new RenderableWallOfDeath(
		RenderableGame::getGlobalInstance()
		->getRenderingEngineInstance()
		->createModelFromIndex(
		table->modelIndexes[ObjectTypes::Wwod],
		table->textureIndexes[ObjectTypes::Wwod],
		table->vertexShaderIndexes[ObjectTypes::Wwod],
		table->pixelShaderIndexes[ObjectTypes::Wwod])
		);
}

void RenderableGameObjectCtorTable::initCtors() {
	GameObjectCtorTable::initCtors();
	RenderingEngine *engine =
		RenderableGame::getGlobalInstance()->getRenderingEngineInstance();

	this->modelIndexes[ObjectTypes::Ecoli] = engine->loadModel( "resources/ecoliii.fbx" );
	this->textureIndexes[ObjectTypes::Ecoli] = engine->loadTexture( "resources/ecolizzz_TXTR.dds" );
	this->vertexShaderIndexes[ObjectTypes::Ecoli] = engine->loadVertexShader( "resources/vertexTentacle.cso" );
	this->pixelShaderIndexes[ObjectTypes::Ecoli] = engine->loadPixelShader( "resources/pixel.cso" );

	this->modelIndexes[ObjectTypes::ChickenPox] = engine->loadModel( "resources/herpes2.fbx" );
	this->textureIndexes[ObjectTypes::ChickenPox] = engine->loadTexture( "resources/herpes_3_TXTR.dds" );
	this->vertexShaderIndexes[ObjectTypes::ChickenPox] = engine->loadVertexShader( "resources/vertexRipple.cso" );
	this->pixelShaderIndexes[ObjectTypes::ChickenPox] = engine->loadPixelShader( "resources/pixel.cso" );

	this->modelIndexes[ObjectTypes::Syphillis] = engine->loadModel( "resources/Pox.fbx" );
	this->textureIndexes[ObjectTypes::Syphillis] = engine->loadTexture( "resources/pox4_TXTR.dds" );
	this->vertexShaderIndexes[ObjectTypes::Syphillis] = engine->loadVertexShader( "resources/vertexSpring.cso" );
	this->pixelShaderIndexes[ObjectTypes::Syphillis] = engine->loadPixelShader( "resources/pixel.cso" );

	this->modelIndexes[ObjectTypes::Malaria] = engine->loadModel( "resources/malaria.fbx" );
	this->textureIndexes[ObjectTypes::Malaria] = engine->loadTexture( "resources/malariazbrush_TXTR.dds" );
	this->vertexShaderIndexes[ObjectTypes::Malaria] = engine->loadVertexShader( "resources/vertexWiggle.cso" );
	this->pixelShaderIndexes[ObjectTypes::Malaria] = engine->loadPixelShader( "resources/pixel.cso" );

	this->modelIndexes[ObjectTypes::WhiteBlood] = engine->loadModel( "resources/WhiteBloodCell.fbx" );
	this->textureIndexes[ObjectTypes::WhiteBlood] = engine->loadTexture( "resources/whiteBloodCell2lowRes_TXTR.dds" );
	this->vertexShaderIndexes[ObjectTypes::WhiteBlood] = engine->loadVertexShader( "resources/vertexRipple.cso" );
	this->pixelShaderIndexes[ObjectTypes::WhiteBlood] = engine->loadPixelShader( "resources/pixel.cso" );

	this->modelIndexes[ObjectTypes::RedBlood] = engine->loadModel( "resources/bloodCell.fbx" );
	this->textureIndexes[ObjectTypes::RedBlood] = engine->loadTexture( "resources/bloodCell_TXTR.dds" );
	this->vertexShaderIndexes[ObjectTypes::RedBlood] = engine->loadVertexShader( "resources/vertexRipple.cso" );
	this->pixelShaderIndexes[ObjectTypes::RedBlood] = engine->loadPixelShader( "resources/pixel.cso" );

	this->modelIndexes[ObjectTypes::Track] = engine->loadModel( "resources/track.trk", false );
	this->textureIndexes[ObjectTypes::Track] = engine->loadTexture( "resources/bloodCell_TXTR.dds" );
	this->bumpIndexes[ObjectTypes::Track] = engine->loadBumpMap( "resources/bloodCellBump.dds" );
	this->vertexShaderIndexes[ObjectTypes::Track] = engine->loadVertexShader( "resources/vertexTrack.cso" );
	this->pixelShaderIndexes[ObjectTypes::Track] = engine->loadPixelShader( "resources/pixelBump.cso" );

	this->modelIndexes[ObjectTypes::Wwod] = this->modelIndexes[ObjectTypes::WhiteBlood];
	this->textureIndexes[ObjectTypes::Wwod] = this->textureIndexes[ObjectTypes::WhiteBlood];
	this->vertexShaderIndexes[ObjectTypes::Wwod] = engine->loadVertexShader("resources/vertexRipple.cso");
	this->pixelShaderIndexes[ObjectTypes::Wwod] = engine->loadPixelShader("resources/pixel.cso");

	this->modelIndexes[ObjectTypes::Adrenaline] = engine->loadModel("resources/adrenaline.obj");
	this->textureIndexes[ObjectTypes::Adrenaline] = engine->loadTexture("resources/Wood.dds");

	this->prepSelectionScreenData();

	this->setConstructor(ObjectTypes::Ecoli, makeRenderableEcoli);
	this->setConstructor( ObjectTypes::ChickenPox, makeRenderableChickenPox );
	this->setConstructor( ObjectTypes::Syphillis, makeRenderableSyphillis );
	this->setConstructor( ObjectTypes::Malaria, makeRenderableMalaria );
	this->setConstructor( ObjectTypes::WhiteBlood, makeRenderableWhiteBlood );
	this->setConstructor( ObjectTypes::RedBlood, makeRenderableRedBlood );

	this->setConstructor( ObjectTypes::Track, makeRenderableTrack );
	this->setConstructor( ObjectTypes::SelectionScreen, makeRenderableSelectionScreen );
	this->setConstructor( ObjectTypes::State, makeSignallingGameState );
	this->setConstructor( ObjectTypes::Wwod, makeRenderableWallOfDeath );
	this->setConstructor(ObjectTypes::Adrenaline, makeRenderableAdrenaline);
}