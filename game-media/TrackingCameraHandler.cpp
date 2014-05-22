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
		PathNode node = Game::getGlobalInstance()->getTrackPath()->nodes[gameObject->getTrackIndex()];
		this->position = node.point - (node.normal * (30 - node.distanceTo(gameObject->getPosition())));
		this->lookAt = gameObject->getPosition();
	}
}