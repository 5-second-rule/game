#pragma once

#include "game-core.h"
#include "State.h"
#include "MovingObject.h"
#include "MoveEvent.h"
#include "ActionType.h"

class MovingObject;

class GAMECOREDLL Move : public State<MovingObject>
{
private:
	Move();
public:
	static Move* instance();
	bool handleEvent(MovingObject *object, Event* evt);
	void enter(MovingObject *object);
	void execute(MovingObject *object);
	void exit(MovingObject *object);
};

class Stop : public State<MovingObject>
{
private:
	Stop();
public:
	static Stop* instance();
	bool handleEvent(MovingObject *object, Event* evt);
	void enter(MovingObject *object);
	void execute(MovingObject *object);
	void exit(MovingObject *object);
};

class Break : public State<MovingObject>
{
private:
	Break();
public:
	static Break* instance();
	bool onEvent(MovingObject *object, Event evt);
	void enter(MovingObject *object);
	void execute(MovingObject *object);
	void exit(MovingObject *object);
};





