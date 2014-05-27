#include "TrackingCameraHandler.h"
#include "game-core/MovingObject.h"
#include "game-core/Game.h"

#define CAMERABACKSCALE 100
#define POINTDISTANCESCALE 0.5

TrackingCameraHandler::TrackingCameraHandler()
{
}


TrackingCameraHandler::~TrackingCameraHandler()
{
}

void TrackingCameraHandler::updateFor(IHasHandle *playerObject) {
	MovingObject *gameObject = dynamic_cast<MovingObject *>(playerObject);
	
	if (gameObject != nullptr) {
		TrackPath *track = Game::getGlobalInstance()->getTrackPath();
		//PathNode node = track->nodes[gameObject->getTrackIndex()];
		PathNode node = track->interpolateNode(gameObject->getPosition(), gameObject->getTrackIndex());
		this->position = node.point - (node.normal * CAMERABACKSCALE) -(node.normal * POINTDISTANCESCALE * node.distanceTo(gameObject->getPosition()));
		//PathNode cameraTrackPos = track->nodes[track->locateIndex(this->position, gameObject->getTrackIndex())];
		PathNode cameraTrackPos = track->interpolateNode(this->position, track->locateIndex(this->position, gameObject->getTrackIndex()));
		float camDistanceFromTube = cameraTrackPos.distanceTo(this->position);

		//TODO: replace 100 with track radius
		float difference = camDistanceFromTube - 0.75f*(100.0f);
		if (difference > 0){
			Common::Vector4 changeVec = cameraTrackPos.point - this->position;
			changeVec.normalize();
			this->position = this->position + (changeVec * difference);
		}

		this->lookAt = gameObject->getPosition() +((node.point - gameObject->getPosition()) * 0.5);

		this->up = gameObject->getUp();
	}
}