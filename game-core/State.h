#pragma once

template< class object_type >
class State
{
private:
public:
	virtual ~State();
	virtual bool onEvent(object_type *object) = 0;
	virtual void enter(object_type *object) = 0;
	virtual void execute(object_type *object) = 0;
	virtual void exit(object_type *object) = 0;
};