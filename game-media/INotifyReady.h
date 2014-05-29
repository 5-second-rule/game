#pragma once
#include "game-media.h"

template<class T>
class GAMEMEDIADLL INotifyReady {
public:
	INotifyReady() {}
	~INotifyReady() {}
	void ready(T *);
};

