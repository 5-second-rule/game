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
	RenderableObject::render();
}