#pragma once
#include "engine-renderer/PlayerCameraHandler.h"

class TrackingCameraHandler : public PlayerCameraHandler
{
public:
	TrackingCameraHandler();
	~TrackingCameraHandler();

	virtual void updateFor(IHasHandle *playerObject);
};

