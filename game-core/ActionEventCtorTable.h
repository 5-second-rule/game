#pragma once
#include "engine-core\ConstructorTable.h"
#include "engine-core\ActionEvent.h"

class ActionEventCtorTable : public ConstructorTable < ActionEvent > {
public:
	static const int EVENT_TYPE_COUNT = 10;

	ActionEventCtorTable();
	~ActionEventCtorTable();

	virtual void initCtors();
};

