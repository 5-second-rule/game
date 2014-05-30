#include "ActionEventCtorTable.h"
#include "MoveEvent.h"
#include "ShootEvent.h"

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

ActionEventCtorTable::ActionEventCtorTable() : ConstructorTable<ActionEvent>(EVENT_TYPE_COUNT) {}

ActionEventCtorTable::~ActionEventCtorTable() {}

static ActionEvent * makeMoveEvent( ConstructorTable<ActionEvent> *thisObj) {

	return new MoveEvent( 0, nullptr );
}

static ActionEvent * makeShootEvent( ConstructorTable<ActionEvent> *thisObj ) {
	return new ShootEvent( 0 );
}

static ActionEvent * makeUseEvent( ConstructorTable<ActionEvent> *thisObj) {
	return nullptr;
}

void ActionEventCtorTable::initCtors() {
	this->setConstructor( static_cast<int>(ActionType::MOVE), makeMoveEvent );
	this->setConstructor( static_cast<int>(ActionType::SHOOT), makeShootEvent );
	this->setConstructor( static_cast<int>(ActionType::USE), makeUseEvent );
}