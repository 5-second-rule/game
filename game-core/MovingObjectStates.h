#pragma once

#include "..\Common\FSM\State.h"
#include "..\Common\Messaging\Telegram.h"

#include "MovingObject.h"
#include "Transformation.h"
#include "MoveEvent.h"
#include "ActionType.h"

class MovingObject;

using namespace MsgGame;
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
	bool onMessage(MovingObject *object, Telegram msg);
	void enter(MovingObject *object);
	void execute(MovingObject *object);
	void exit(MovingObject *object);
};

class Move : public State<MovingObject>
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



