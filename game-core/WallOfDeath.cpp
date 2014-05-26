#include "WallOfDeath.h"

#include "ObjectTypes.h"
#include "TrackPath.h"
#include "Game.h"

WallOfDeath::WallOfDeath()
	: BaseObject(ObjectTypes::Wwod)
{
	this->trackIndex = 0;
	this->defaultVelocity = 1;
}

WallOfDeath::~WallOfDeath()
{
}

int WallOfDeath::getTrackIndex() {
	return this->trackIndex;
}

bool WallOfDeath::handleEvent(Event *evt){
	// Does nothing lol
	return false;
}

void WallOfDeath::reset() {
	TrackPath *track = Game::getGlobalInstance()->getTrackPath();
	this->trackIndex = track->nodes.size() - 200;
}

void WallOfDeath::update(float dt){
	BaseObject::update(dt);
	
	TrackPath *track = Game::getGlobalInstance()->getTrackPath();
	this->trackIndex = (this->trackIndex + this->defaultVelocity) % track->nodes.size();
	cout << "wall of death is at : " << this->trackIndex << endl;
}

void WallOfDeath::reserveSize(IReserve& buffer) const {
	BaseObject::reserveSize(buffer);
	buffer.reserve(sizeof(WallOfDeathData));
}

void WallOfDeath::fillBuffer(IFill& buffer) const {
	BaseObject::fillBuffer(buffer);
	WallOfDeathData* data = reinterpret_cast<WallOfDeathData*>(buffer.getPointer());

	data->trackIndex = this->trackIndex;

	buffer.filled();
}

void WallOfDeath::deserialize(BufferReader& reader) {
	BaseObject::deserialize(reader);

	const WallOfDeathData* data = reinterpret_cast<const WallOfDeathData*>(reader.getPointer());

	this->trackIndex = data->trackIndex;

	reader.finished(sizeof(WallOfDeathData));
}
