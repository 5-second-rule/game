#pragma once
#include "game-core.h"
#include "MovingObject.h"
#include "ObjectTypes.h"
#include "SelectionEvent.h"
#include "ActionType.h"

class GAMECOREDLL Player : public MovingObject {
protected:
	unsigned int guid;
	int deathCount;
	int tempSelection;
	int selection;

public:
	Player();
	Player(unsigned int guid);
	~Player();

	void die();
	void updateTempSelection(int tempSelection);
	void makeSelection(int selection);
	int getDeathCount();
	int getTempSelection();
	int getSelection();

	virtual bool handleEvent(Event* evt);
};

