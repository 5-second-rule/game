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
	float position[3];
	position[0] = node.point[0];
	position[1] = node.point[1];
	position[2] = node.point[2];

	this->setPosition(position);
	RenderableObject::render();
}