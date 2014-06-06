#include "RenderableWallOfDeath.h"

#include "game-core/TrackPath.h"
#include "game-core/Game.h"

RenderableWallOfDeath::RenderableWallOfDeath(Transmission::Model* model)
	: WallOfDeath()
	, RenderableObject(model)
{
}


RenderableWallOfDeath::~RenderableWallOfDeath()
{
}

void RenderableWallOfDeath::render() {
	TrackPath *track = Game::getGlobalInstance()->getTrackPath();
	PathNode node = track->nodes[this->getTrackIndex()];
	this->getMoveable()->setPosition(node.point);
	this->getMoveable()->setScale(node.radius / 6.0f);

	this->getMoveable()->setRotation(0, 0, 0);

	Vector4 heading = Vector4::normalize(node.normal);

	if (heading != Vector4() && heading != Vector(0.0f, 0.0f, -1.0f)) {

		// rotate the z vector to face the new heading
		this->getMoveable()->rotate(
			Vector4::cross(heading, Vector(0.0f, 0.0f, -1.0f)),
			Vector4::angle(heading, Vector(0.0f, 0.0f, -1.0f))
			);

	}

	RenderableObject::render();
}