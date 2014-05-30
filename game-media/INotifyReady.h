#pragma once
#include "game-media.h"

template<class T>
class GAMEMEDIADLL INotifyReady {
public:
	INotifyReady() {}
	~INotifyReady() {}
	virtual void ready(T *) = 0;
};

