#include "TrackingCameraHandler.h"
#include "game-core/MovingObject.h"

TrackingCameraHandler::TrackingCameraHandler()
{
}


TrackingCameraHandler::~TrackingCameraHandler()
{
}

void TrackingCameraHandler::updateFor(IHasHandle *playerObject) {
	MovingObject *gameObject = dynamic_cast<MovingObject *>(playerObject);
	
	//if (gameObject != nullptr) {
		this->lookAt = gameObject->getPosition();
		this->position = this->lookAt - Vector4(0,0,30);
	//}
}