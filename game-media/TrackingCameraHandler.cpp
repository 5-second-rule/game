#include "TrackingCameraHandler.h"
#include "game-core/MovingObject.h"
#include "game-core/RotateCameraObject.h"
#include "game-core/Game.h"

#define CAMERABACKSCALE 130
#define POINTDISTANCESCALE 0.5

TrackingCameraHandler::TrackingCameraHandler()
{
}


TrackingCameraHandler::~TrackingCameraHandler()
{
}

void TrackingCameraHandler::updateFor(IHasHandle *playerObject) {
	
	if (playerObject == nullptr) return;

	MovingObject *gameObject = dynamic_cast<MovingObject *>(playerObject);
	if (gameObject != nullptr) {
		this->handleMovingObject(gameObject);
		return;
	}

	RotateCameraObject *rotateGameObject = dynamic_cast<RotateCameraObject *>(playerObject);
	if (rotateGameObject != nullptr)
	{
		this->handleRotateCam(rotateGameObject);
		return;
	}

	DeathCamera* deathCamera = dynamic_cast<DeathCamera*>(playerObject);
	if (deathCamera != nullptr) {
		this->handleDeathCam(deathCamera);
		return;
	}

}

void TrackingCameraHandler::handleMovingObject(MovingObject* gameObject){
	TrackPath *track = Game::getGlobalInstance()->getTrackPath();
	//PathNode node = track->nodes[gameObject->getTrackIndex()];
	PathNode node = track->interpolateNode(gameObject->getPosition(), gameObject->getTrackIndex());
	Common::Vector4 moveVec = gameObject->getPosition() - node.point;
	this->position = node.point - (node.normal * CAMERABACKSCALE) - (node.normal * POINTDISTANCESCALE * node.distanceTo(gameObject->getPosition()));
	//PathNode cameraTrackPos = track->nodes[track->locateIndex(this->position, gameObject->getTrackIndex())];
	this->position = this->position + moveVec * 0.75;


	PathNode cameraTrackPos = track->interpolateNode(this->position, track->locateIndex(this->position, gameObject->getTrackIndex()));

	Common::Vector4 changeVec = cameraTrackPos.point - this->position;

	float camDistanceFromTube = changeVec.length();

	float difference = camDistanceFromTube - 0.75f*(cameraTrackPos.radius);
	if (difference > 0){
		changeVec.normalize();
		this->position = this->position + (changeVec * difference);
	}

	this->lookAt = gameObject->getPosition();// +((node.point - gameObject->getPosition()) * 0.5);

	this->up = gameObject->getUp();
}

void TrackingCameraHandler::handleRotateCam(RotateCameraObject* rotateGameObject){
	Vector4 target = rotateGameObject->getTarget();

	Vector4 delta = rotateGameObject->getDelta();
	//delta[3] = 0;
	delta.normalize();


	this->position = target + (delta * CAMERABACKSCALE);
	this->lookAt = target;
	this->up = rotateGameObject->getUp();
}

void TrackingCameraHandler::handleDeathCam(DeathCamera* deathCamera){
	this->position = deathCamera->getPosition();
	this->lookAt = deathCamera->getTarget();
	this->up = Vector(0.0f, 1.0f, 0.0f);
}