#include "TrackingCameraHandler.h"
#include "game-core/MovingObject.h"
#include "game-core/Game.h"

TrackingCameraHandler::TrackingCameraHandler()
{
}


TrackingCameraHandler::~TrackingCameraHandler()
{
}

void TrackingCameraHandler::updateFor(IHasHandle *playerObject) {
	MovingObject *gameObject = dynamic_cast<MovingObject *>(playerObject);
	
	if (gameObject != nullptr) {
		this->lookAt = Game::getGlobalInstance()->getTrackPath()->nodes[gameObject->getTrackIndex()].point;
		this->position = this->lookAt - (Game::getGlobalInstance()->getTrackPath()->nodes[gameObject->getTrackIndex()].normal * 30);
		this->lookAt = gameObject->getPosition();
	}
}