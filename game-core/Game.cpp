#include "Game.h"
#include "GameObjectCtorTable.h"


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

	GameObjectCtorTable *ctors = this->makeCtorTable();
	this->engineInstance = this->makeEngineInstance(ctors);
	ctors->initCtors();
}

void Game::run() {
	if (!this->initialized) {
		throw std::runtime_error("Need to call init() first.");
	}

	this->engineInstance->run();
}

GameObjectCtorTable * Game::makeCtorTable() {
	return new GameObjectCtorTable();
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

ActionEvent* Game::MakeActionEvent( int actionType, unsigned int playerGuid, const char* data ) {
	return nullptr;
}