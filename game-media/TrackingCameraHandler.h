#pragma once
#include "engine-renderer/PlayerCameraHandler.h"

#include "game-core/MovingObject.h"
#include "game-core/RotateCameraObject.h"
#include "game-core/DeathCamera.h"

class TrackingCameraHandler : public PlayerCameraHandler
{
public:
	TrackingCameraHandler();
	~TrackingCameraHandler();

	virtual void updateFor(IHasHandle *playerObject);
private:
	void handleMovingObject(MovingObject* gameObject);
	void handleRotateCam(RotateCameraObject* rotateGameObject);
	void handleDeathCam(DeathCamera* deathCamera);
};

