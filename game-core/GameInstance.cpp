#include "GameInstance.h"
#include "GameObjectCtorTable.h"


GameInstance * GameInstance::globalInstance;

GameInstance::GameInstance() {
	this->initHasRun = false;
	this->engineInstance = nullptr;
}

GameInstance::~GameInstance() {
}

void GameInstance::init() {
	if (this->initHasRun) {
		return;
	}

	this->initHasRun = true;
	setGlobalInstance(this);

	GameObjectCtorTable *ctors = this->makeCtorTable();
	this->engineInstance = this->makeEngineInstance(ctors);
	ctors->initCtors();
}

void GameInstance::run() {
	if (!this->initHasRun) {
		throw std::runtime_error("Need to call init() first.");
	}

	this->engineInstance->run();
}

GameObjectCtorTable * GameInstance::makeCtorTable() {
	return new GameObjectCtorTable();
}

Engine * GameInstance::getEngineInstance() {
	return this->engineInstance;
}

void GameInstance::setGlobalInstance(GameInstance *instance){
	globalInstance = instance;
}

GameInstance * GameInstance::getGlobalInstance() {
	return globalInstance;
}

ActionEvent* GameInstance::MakeActionEvent( int actionType, unsigned int playerGuid, const char* data ) {
	return nullptr;
}