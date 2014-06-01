#include "Game.h"

#include "GameObjectCtorTable.h"
#include "ActionEventCtorTable.h"
#include "ActionType.h"
#include "MoveEvent.h"

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
}

void Game::init() {
	if (this->initialized) {
		return;
	}

	this->initialized = true;
	setGlobalInstance(this);

	this->track = TrackPath::fromFile("resources/track.path");

	this->objectCtors = this->makeCtorTable();
	ActionEventCtorTable* eventCtors = new ActionEventCtorTable();
	this->engineInstance = this->makeEngineInstance(this->objectCtors, eventCtors);
	this->objectCtors->initCtors();
	eventCtors->initCtors();

}

void Game::stop() {
	if( !this->initialized ) {
		throw std::runtime_error( "Need to call init() first." );
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

BaseObject *Game::invoke(ObjectTypes object_type){
	return this->objectCtors->invoke(object_type);
}