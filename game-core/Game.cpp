#include "Game.h"

#include "GameObjectCtorTable.h"
#include "ActionEventCtorTable.h"
#include "ActionType.h"
#include "MoveEvent.h"
#include "ObjectTypes.h"

#include "engine-core/ConfigSettings.h"

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

Game * Game::globalInstance;

Game::Game() {
	this->initialized = false;
	this->engineInstance = nullptr;
}

Game::~Game() {
	delete this->engineInstance;
	delete this->track;
	this->backgroundLoader->join();
}

void Game::init() {
	if (this->initialized) {
		return;
	}

	this->objectCtors = this->makeCtorTable();
	ActionEventCtorTable* eventCtors = new ActionEventCtorTable();
	this->engineInstance = this->makeEngineInstance( this->objectCtors, eventCtors );
	this->initialized = true;
	setGlobalInstance(this);

	eventCtors->initCtors();
	this->track = TrackPath::fromFile("resources/track.path");
	this->backgroundLoader = new std::thread( [=] {
		this->loading = true;
		this->objectCtors->initCtors();
		this->loading = false;
	} );
}

void Game::stop() {
	if (!this->initialized) {
		throw std::runtime_error("Need to call init() first.");
	}

	this->engineInstance->stop();
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

TrackPath * Game::getTrackPath() {
	return this->track;
}

WallOfDeath * Game::getWallOfDeath() {
	return this->wallOfDeath;
}