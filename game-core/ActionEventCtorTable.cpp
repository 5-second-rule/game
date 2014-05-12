#include "ActionEventCtorTable.h"
#include "MoveEvent.h"
#include "ShootEvent.h"


ActionEventCtorTable::ActionEventCtorTable() : ConstructorTable<ActionEvent>(EVENT_TYPE_COUNT) {}

ActionEventCtorTable::~ActionEventCtorTable() {}

static ActionEvent * makeMoveEvent( ConstructorTable<ActionEvent> *thisObj, Args* arg ) {

	return new MoveEvent( 0, nullptr );
}

static ActionEvent * makeShootEvent( ConstructorTable<ActionEvent> *thisObj, Args* arg ) {
	return new ShootEvent( 0 );
}

static ActionEvent * makeUseEvent( ConstructorTable<ActionEvent> *thisObj, Args* arg ) {
	return nullptr;
}

void ActionEventCtorTable::initCtors() {
	this->setConstructor( static_cast<int>(ActionType::MOVE), makeMoveEvent );
	this->setConstructor( static_cast<int>(ActionType::SHOOT), makeShootEvent );
	this->setConstructor( static_cast<int>(ActionType::USE), makeUseEvent );
}