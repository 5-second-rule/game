#include "GameInstance.h"
#include "GameObjectCtorTable.h"

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
	this->engineInstance = new EngineInstance(
		this->makeWorld(),
		this->makeCtorTable());
}

World * GameInstance::makeWorld() {
	return new World();
}

ObjectCtorTable * GameInstance::makeCtorTable() {
	return new GameObjectCtorTable();
}