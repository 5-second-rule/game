#pragma once

#include "..\Common\FSM\State.h"
#include "..\Common\Messaging\Telegram.h"

#include "MovingObject.h"
#include "Transformation.h"

class MovingObject;

using namespace Game;
class Stop : public State<MovingObject>
{
private:
	Stop();
public:
	static Stop* instance();
	bool onMessage(MovingObject *object, const Telegram&);
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
	bool onMessage(MovingObject *object, const Telegram&);
	void enter(MovingObject *object);
	void execute(MovingObject *object);
	void exit(MovingObject *object);
};



