#include "Game.h"

#include "GameObjectCtorTable.h"
#include "ActionEventCtorTable.h"
#include "ActionType.h"
#include "MoveEvent.h"

Game * Game::globalInstance;

Game::Game() {
	this->initialized = false;
	this->engineInstance = nullptr;
}

Game::~Game() {
}

void Game::init() {
	if (this->initialized) {
		return;
	}

	this->initialized = true;
	setGlobalInstance(this);

	GameObjectCtorTable* objectCtors = this->makeCtorTable();
	ActionEventCtorTable* eventCtors = new ActionEventCtorTable();
	this->engineInstance = this->makeEngineInstance(objectCtors, eventCtors);
	objectCtors->initCtors();
	eventCtors->initCtors();
}

void Game::run() {
	if (!this->initialized) {
		throw std::runtime_error("Need to call init() first.");
	}

	this->engineInstance->run();
}

Engine * Game::getEngineInstance() {
	return this->engineInstance;
}

void Game::setGlobalInstance(Game *instance){
	globalInstance = instance;
}

Game * Game::getGlobalInstance() {
	return globalInstance;
}


GameObjectCtorTable * Game::makeCtorTable() {
	return new GameObjectCtorTable();
}