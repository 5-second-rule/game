#include "SteeringBehavior.h"

using namespace Common;

SteeringBehavior::SteeringBehavior(MovingObject *owner) :behavior(BehaviorType::none)
{
	assert(ConfigSettings::config->getValue("time_tick", k_time_elapsed));
	assert(ConfigSettings::config->getValue("deceleration_tweaker", deceleration_tweaker));
	assert(ConfigSettings::config->getValue("wander_jitter", wander_jitter));
	assert(ConfigSettings::config->getValue("wander_radius", wander_radius));
	assert(ConfigSettings::config->getValue("wander_distance", wander_distance));
	assert(ConfigSettings::config->getValue("weight_wander", weight_wander));
	assert(ConfigSettings::config->getValue("weight_follow_path", weight_follow_path));
	assert(ConfigSettings::config->getValue("way_point_seek_distance", way_point_seek_distance));

	way_point_seek_distance_sq = way_point_seek_distance * way_point_seek_distance;
	this->owner = owner;
}


SteeringBehavior::~SteeringBehavior()
{
}

Vector4 SteeringBehavior::seek(Vector4 &p_targetPosition){
	Vector4 desiredDirection = Common::Vector4::normalize(p_targetPosition - owner->getPosition());
	Vector4 desiredVelocity = desiredDirection * owner->getMaxSpeed();

	return desiredVelocity;
}

Vector4 SteeringBehavior::flee(Vector4 &p_targetPosition){
	Vector4 desiredDirection = Common::Vector4::normalize(owner->getPosition() - p_targetPosition);
	Vector4 desiredVelocity = desiredDirection * owner->getMaxSpeed();

	return desiredVelocity - owner->getVelocity();
}

Vector4 SteeringBehavior::arrive(Vector4 &p_targetPosition, Deceleration deceleration){
	Vector4 toTarget;
	Vector4 desiredVelocity;
	float dist, speed;

	toTarget = p_targetPosition - owner->getPosition();

	dist = toTarget.length();

	if (dist > 0){
		speed = dist / ((float)deceleration * deceleration_tweaker);

		//min(speed, object->getMaxVelocity());
		desiredVelocity = toTarget * (speed / dist);

		return desiredVelocity - owner->getVelocity();
	}
	return Vector4(0, 0, 0, 0);
}

Vector4 SteeringBehavior::pursuit(Handle &p_evader_handle){
	IHasHandle* tmp;
	MovingObject* evader;
	Vector4 toEvader;
	float relativeHeading, look_ahead_time;

	tmp = getObject(p_evader_handle);
	if (evader = dynamic_cast<MovingObject*>(tmp)){
		toEvader = evader->getPosition() - owner->getPosition();
		relativeHeading = evader->getHeading().dot(owner->getHeading());

		if (toEvader.dot(owner->getHeading()) > 0 && relativeHeading < -0.95){
			return this->seek(evader->getPosition());
		}

		look_ahead_time = toEvader.length() / (owner->getMaxSpeed() + evader->speed());
		return seek(evader->getPosition() + evader->getVelocity() * look_ahead_time);
	}
	else {
		pursuitOff();
	}
	return Vector4();
}

Vector4 SteeringBehavior::evade(Handle &p_pursuer_handle){
	IHasHandle* tmp;
	MovingObject* pursuer;
	Vector4 toPursuer;
	float look_ahead_time;

	tmp = getObject(p_pursuer_handle);
	if (pursuer = dynamic_cast<MovingObject*>(tmp)){
		toPursuer = pursuer->getPosition() - owner->getPosition();
		look_ahead_time = toPursuer.length() / (owner->getMaxSpeed() + pursuer->speed());
		return flee(pursuer->getPosition() + pursuer->getVelocity() * look_ahead_time);
	}
	else {
		evadeOff();
	}
	return Vector4();
}

Vector4 SteeringBehavior::wander(){
	// Insert a jitter to the variation of the target
	float JitterThisTimeSlice = wander_jitter * k_time_elapsed;

	// Add a small random vector to the target's position
	// random clamped: between [-1, 1]
	wander_target += Vector4((float)randomClamped() * JitterThisTimeSlice,
		(float)randomClamped() * JitterThisTimeSlice,
		(float)randomClamped() * JitterThisTimeSlice);

	// Normalize the target vector
	wander_target = Common::Vector4::normalize(wander_target);
	// Make the target a point at a sphere arround the agent
	wander_target *= wander_radius;
	// Make an offset in the sphere (local space)
	Vector4 target = wander_target + Vector4(0, 0, wander_distance);
	// Convert the target to world space
	target = Transformation::pointToWorldSpace(target,
		Vector4(1, 0, 0),
		Vector4(0, 1, 0),
		Vector4(0, 0, 1),
		owner->getPosition());
	return target - owner->getPosition();
}


Vector4 SteeringBehavior::followPath() {
	// Move to next target if close enough to current target (working in
	// distance squared space)
	if (distanceSquared(*owner->current_way_point, owner->getPosition()) <
		way_point_seek_distance_sq)
	{
		owner->setNextWayPoint();
		cout << "new point: " << owner->current_way_point->toString() << endl;
	}
	if (getWorld()->isTick(60)){
		cout << distanceSquared(*owner->current_way_point, owner->getPosition()) << endl;
	}

	if (!owner->path->finished(owner)) {
		return seek(*owner->current_way_point);
	}
	else {
		return arrive(*owner->current_way_point, normal);
	}
}

Vector4 SteeringBehavior::offsetPursuit(Handle &p_leader, Vector4 &offset) {
	MovingObject* leader = dynamic_cast<MovingObject*> getObject(p_leader);

	if (leader == nullptr) {
		// Leader does not exist anymore
		offsetPursuitOff();
		return Vector4(0, 0, 0);
	}

	// calculate the offset's position in world space
	Vector4 WorldOffsetPos = Transformation::pointToWorldSpace(offset,
		leader->getSide(),
		leader->getTop(),
		leader->getFront(),
		leader->getPosition());

	Vector4 ToOffset = WorldOffsetPos - owner->getPosition();

	// The lookahead time is propotional to the distance between the leader
	// and the pursuer; and is inversely proportional to the sum of both
	// agent's velocities
	float LookAheadTime = ToOffset.length() / (owner->getMaxSpeed() + leader->speed());

	// Arrive at the predicted future position of the offset
	return arrive(WorldOffsetPos + leader->getVelocity() * LookAheadTime, fast);
}


Vector4 SteeringBehavior::separation(const std::vector<Handle> &neighbors)
{
	Vector4 SteeringForce;

	for (unsigned int a = 0; a<neighbors.size(); ++a)
	{
		MovingObject *neighbor = (MovingObject*)getObject(neighbors[a]);
		// Make sure this agent isn't included in the calculations and that
		// the agent being examined is close enough. ***also make sure it doesn't
		// include the evade target ***
		if ((neighbor != nullptr) && (neighbor != owner) && neighbor->isTagged() &&
			(neighbor != getObject(target_agent1)))
		{
			Vector4 ToAgent = owner->getPosition() - neighbor->getPosition();

			//scale the force inversely proportional to the agents distance  
			//from its neighbor.
			SteeringForce += Common::Vector4::normalize(ToAgent) * (1 / ToAgent.length());
		}
	}

	return SteeringForce;
}

Vector4 SteeringBehavior::alignment(const std::vector<Handle> &neighbors)
{
	//used to record the average heading of the neighbors
	Vector4 AverageHeading;

	//used to count the number of vehicles in the neighborhood
	int    NeighborCount = 0;

	//iterate through all the tagged vehicles and sum their heading vectors  
	for (unsigned int a = 0; a<neighbors.size(); ++a)
	{
		MovingObject* neighbor = (MovingObject*)getObject(neighbors[a]);
		//make sure *this* agent isn't included in the calculations and that
		//the agent being examined  is close enough ***also make sure it doesn't
		//include any evade target ***
		if ((neighbor != nullptr) && (neighbor != owner) && neighbor->isTagged() &&
			(neighbor != getObject(target_agent1)))
		{
			AverageHeading += neighbor->getHeading();

			++NeighborCount;
		}
	}

	//if the neighborhood contained one or more vehicles, average their
	//heading vectors.
	if (NeighborCount > 0)
	{
		AverageHeading *= 1 / (float)NeighborCount;

		AverageHeading -= owner->getHeading();
	}

	return AverageHeading;
}

Vector4 SteeringBehavior::cohesion(const std::vector<Handle> &neighbors)
{
	// First find the center of mass of all the agents
	Vector4 CenterOfMass, SteeringForce;

	int NeighborCount = 0;

	// Iterate through the neighbors and sum up all the position vectors
	for (unsigned int a = 0; a<neighbors.size(); ++a)
	{
		MovingObject *neighbor = (MovingObject*)getObject(neighbors[a]);
		// Make sure *this* agent isn't included in the calculations and that
		// the agent being examined is close enough ***also make sure it doesn't
		// include the evade target ***
		if ((neighbor != nullptr) && (neighbor != owner) && neighbor->isTagged() &&
			(neighbor != (MovingObject*)getObject(this->target_agent1)))
		{
			CenterOfMass += neighbor->getPosition();

			++NeighborCount;
		}
	}

	if (NeighborCount > 0)
	{
		// The center of mass is the average of the sum of positions
		CenterOfMass *= 1 / (float)NeighborCount;

		// Seek towards that position
		SteeringForce = seek(CenterOfMass);
	}

	// The magnitude of cohesion is usually much larger than separation or
	// allignment so it usually helps to normalize it.
	return Common::Vector4::normalize(SteeringForce);
}


bool SteeringBehavior::accumulateForce(Vector4 &RunningTot,
	Vector4 ForceToAdd)
{
	// Calculate how much steering force the vehicle has used so far
	float MagnitudeSoFar = RunningTot.length();

	// Calculate how much steering force remains to be used by this vehicle
	float MagnitudeRemaining = owner->getMaxForce() - MagnitudeSoFar;

	// Return false if there is no more force left to use
	if (MagnitudeRemaining <= 0.0) return false;

	// Calculate the magnitude of the force we want to add
	float MagnitudeToAdd = ForceToAdd.length();

	// If the magnitude of the sum of ForceToAdd and the running total
	// does not exceed the maximum force available to this vehicle, just
	// add together. Otherwise add as much of the ForceToAdd vector is
	// possible without going over the max.
	if (MagnitudeToAdd < MagnitudeRemaining) {
		RunningTot += ForceToAdd;
	}
	else {
		RunningTot += (Common::Vector4::normalize(ForceToAdd) * MagnitudeRemaining);
	}

	return true;
}

Vector4 SteeringBehavior::calculate(){
	steering_force.set(0, 0, 0, 0);

	calculatePrioritized();

	return steering_force;
}

Vector4 SteeringBehavior::calculatePrioritized(){
	Vector4 force;

	if (On(BehaviorType::follow_path)){
		force = followPath() * weight_follow_path;
		if (!accumulateForce(steering_force, force)) return steering_force;
	}
	if (On(BehaviorType::wander)){
		force = wander() * weight_wander;
		if (!accumulateForce(steering_force, force)) return steering_force;
	}
	if (On(BehaviorType::arrive)){

	}
	return steering_force;
}

void SteeringBehavior::setTarget(Vector4 p_target){
	target_point = p_target;
}

bool SteeringBehavior::On(BehaviorType p_behavior) const{
	return (behavior & p_behavior) == p_behavior;
}

void SteeringBehavior::seekOn(){
	behavior |= BehaviorType::seek;
}

void SteeringBehavior::fleeOn(){
	behavior |= BehaviorType::flee;
}

void SteeringBehavior::arriveOn(){
	behavior |= BehaviorType::arrive;
}

void SteeringBehavior::pursuitOn(Handle &p_evader_handle){
	behavior |= BehaviorType::pursuit;
	target_agent = p_evader_handle;
}

void SteeringBehavior::evadeOn(Handle &p_pursuer_handle){
	behavior |= BehaviorType::evade;
	target_agent = p_pursuer_handle;
}

void SteeringBehavior::wanderOn(){
	behavior |= BehaviorType::wander;
}

void SteeringBehavior::followPathOn(){
	behavior |= BehaviorType::follow_path;
}

void SteeringBehavior::offsetPursuitOn(Handle &p_leader, const Vector4 p_offset){
	behavior |= BehaviorType::offset_pursuit;
	offset = p_offset;
	target_agent = p_leader;
}

void SteeringBehavior::seekOff(){
	if (On(BehaviorType::seek))
		behavior ^= BehaviorType::seek;
}

void SteeringBehavior::fleeOff(){
	if (On(BehaviorType::flee))
		behavior ^= BehaviorType::flee;
}

void SteeringBehavior::arriveOff(){
	if (On(BehaviorType::arrive))
		behavior ^= BehaviorType::arrive;
}

void SteeringBehavior::pursuitOff(){
	if (On(BehaviorType::pursuit))
		behavior ^= BehaviorType::pursuit;
}

void SteeringBehavior::evadeOff(){
	if (On(BehaviorType::evade))
		behavior ^= BehaviorType::evade;
}

void SteeringBehavior::wanderOff(){
	if (On(BehaviorType::wander))
		behavior ^= BehaviorType::wander;
}

void SteeringBehavior::followPathOff(){
	if (On(BehaviorType::follow_path))
		behavior ^= BehaviorType::follow_path;
}

void SteeringBehavior::offsetPursuitOff(){
	if (On(BehaviorType::offset_pursuit))
		behavior ^= BehaviorType::offset_pursuit;
}