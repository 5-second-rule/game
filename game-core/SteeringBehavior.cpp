#include <sstream>

#include "SteeringBehavior.h"

using namespace Common;

#define random_clamped() (((float)(rand()) / (float)(INT_MAX)) * 2.0f - 1.0f)


SteeringBehavior::SteeringBehavior(AutonomousObject *owner) :behavior(BehaviorType::none)
{

	this->owner = owner;
}

SteeringBehavior::~SteeringBehavior()
{
}

void SteeringBehavior::init(){
	this->k_time_elapsed = 0.016667f; //ConfigSettings::config->k_time_elapsed;
	this->deceleration_tweaker = 0.3f; //ConfigSettings::config->deceleration_tweaker;
	this->wander_jitter = 50.0f; //ConfigSettings::config->wander_jitter;
	this->wander_radius = 3.0f; //ConfigSettings::config->wander_radius;
	this->wander_distance = 10.0f; //ConfigSettings::config->wander_distance;
	this->weight_wander = 80.0f; //ConfigSettings::config->weight_wander;
	this->weight_follow_path = 10.0f; //ConfigSettings::config->weight_follow_path;
	this->way_point_seek_distance = 5.0f; //ConfigSettings::config->way_point_seek_distance;
	this->way_point_seek_distance_sq = way_point_seek_distance * way_point_seek_distance;
}

Vector4 SteeringBehavior::seek(Vector4 &p_targetPosition){
	Vector4 desiredDirection = Common::Vector4::normalize(p_targetPosition - owner->getPosition());
	Vector4 desiredVelocity = desiredDirection * MovingObject::max_speed;

	return desiredVelocity;
}

Vector4 SteeringBehavior::flee(Vector4 &p_targetPosition){
	Vector4 desiredDirection = Common::Vector4::normalize(owner->getPosition() - p_targetPosition);
	Vector4 desiredVelocity = desiredDirection * MovingObject::max_speed;

	return desiredVelocity;
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

	tmp = theWorld.get(p_evader_handle);
	if (evader = dynamic_cast<MovingObject*>(tmp)){
		toEvader = evader->getPosition() - owner->getPosition();
		relativeHeading = evader->getHeading().dot(owner->getHeading());

		if (toEvader.dot(owner->getHeading()) > 0 && relativeHeading < -0.95){
			return this->seek(evader->getPosition());
		}

		look_ahead_time = toEvader.length() / (MovingObject::max_speed + evader->getSpeed());
		return seek(evader->getPosition() + evader->getVelocity() * look_ahead_time);
	}
	else {
		off(BehaviorType::pursuit);
	}
	return Vector4(0, 0, 0);
}

Vector4 SteeringBehavior::evade(Handle &p_pursuer_handle){
	IHasHandle* tmp;
	MovingObject* pursuer;
	Vector4 toPursuer;
	float look_ahead_time;

	tmp = theWorld.get(p_pursuer_handle);
	if (pursuer = dynamic_cast<MovingObject*>(tmp)){
		toPursuer = pursuer->getPosition() - owner->getPosition();
		look_ahead_time = toPursuer.length() / (MovingObject::max_speed + pursuer->getSpeed());
		return flee(pursuer->getPosition() + pursuer->getVelocity() * look_ahead_time);
	}
	else {
		off(BehaviorType::evade);
	}
	return Vector4();
}

Vector4 SteeringBehavior::wander(){
	// Insert a jitter to the variation of the target
	float JitterThisTimeSlice = wander_jitter * k_time_elapsed;

	// Add a small random vector to the target's position
	// random clamped: between [-1, 1]
	wander_target += Vector4((float)random_clamped() * JitterThisTimeSlice,
		(float)random_clamped() * JitterThisTimeSlice,
		(float)random_clamped() * JitterThisTimeSlice);

	// Normalize the target vector
	wander_target = Common::Vector4::normalize(wander_target);
	// Make the target a point at a sphere arround the agent
	wander_target *= wander_radius;
	// Make an offset in the sphere (local space)
	return wander_target + Vector4::normalize(owner->getHeading()) * wander_distance;

}


Vector4 SteeringBehavior::followPath() {
	// Move to next target if close enough to current target (working in
	// distance squared space)
	if ((*owner->current_way_point - owner->getPosition()).lengthSquared() <
		way_point_seek_distance_sq)
	{
		owner->setNextWayPoint();
		//cout << "new point: " << owner->current_way_point->toString() << endl;
	}

	if (!owner->path->finished(owner)) {
		return seek(*owner->current_way_point);
	}
	else {
		return arrive(*owner->current_way_point, normal);
	}
}

Vector4 SteeringBehavior::offsetPursuit(Handle &p_leader, Vector4 &offset) {
	MovingObject* leader = dynamic_cast<MovingObject*>(theWorld.get(p_leader));

	if (leader == nullptr) {
		// Leader does not exist anymore
		off(BehaviorType::offset_pursuit);
		return Vector4(0, 0, 0);
	}

	// calculate the offset's position in world space
	Vector4 WorldOffsetPos = leader->getPosition() + offset;

	Vector4 ToOffset = WorldOffsetPos - owner->getPosition();

	// The lookahead time is propotional to the distance between the leader
	// and the pursuer; and is inversely proportional to the sum of both
	// agent's velocities
	float LookAheadTime = ToOffset.length() / (MovingObject::max_speed + leader->getSpeed());

	// Arrive at the predicted future position of the offset
	return arrive(WorldOffsetPos + leader->getVelocity() * LookAheadTime, fast);
}

/*
Vector4 SteeringBehavior::separation(const std::vector<Handle> &neighbors)
{
	Vector4 SteeringForce;

	for (unsigned int a = 0; a<neighbors.size(); ++a)
	{
		AutonomousObject *neighbor = dynamic_cast<AutonomousObject*>(m_getObject(neighbors[a]));
		// Make sure this agent isn't included in the calculations and that
		// the agent being examined is close enough. ***also make sure it doesn't
		// include the evade target ***
		if ((neighbor != nullptr) && (neighbor != owner) && neighbor->isTagged() &&
			(neighbor != m_getObject(target_agent_evade)))
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
		AutonomousObject *neighbor = dynamic_cast<AutonomousObject*>(m_getObject(neighbors[a]));
		//make sure *this* agent isn't included in the calculations and that
		//the agent being examined  is close enough ***also make sure it doesn't
		//include any evade target ***
		if ((neighbor != nullptr) && (neighbor != owner) && neighbor->isTagged() &&
			(neighbor != m_getObject(target_agent_evade)))
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
		AutonomousObject *neighbor = dynamic_cast<AutonomousObject*>(m_getObject(neighbors[a]));
		// Make sure *this* agent isn't included in the calculations and that
		// the agent being examined is close enough ***also make sure it doesn't
		// include the evade target ***
		if ((neighbor != nullptr) && (neighbor != owner) && neighbor->isTagged() &&
			(neighbor != dynamic_cast<MovingObject*>(m_getObject(this->target_agent_evade))))
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
*/

bool SteeringBehavior::accumulateForce(Vector4 &RunningTot,
	Vector4 ForceToAdd)
{
	// Calculate how much steering force the vehicle has used so far
	float MagnitudeSoFar = RunningTot.length();

	// Calculate how much steering force remains to be used by this vehicle
	float MagnitudeRemaining = MovingObject::max_force - MagnitudeSoFar;

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

	if (isOn(BehaviorType::pursuit)){
		force = pursuit(target_agent_pursuit);
		if (!accumulateForce(steering_force, force)) return steering_force;
	}
	if (isOn(BehaviorType::evade)){
		force = evade(target_agent_evade);
		if (!accumulateForce(steering_force, force)) return steering_force;
	}
	if (isOn(BehaviorType::follow_path)){
		force = followPath() * weight_follow_path;
		if (!accumulateForce(steering_force, force)) return steering_force;
	}
	if (isOn(BehaviorType::wander)){
		force = wander() * weight_wander;
		if (!accumulateForce(steering_force, force)) return steering_force;
	}
	if (isOn(BehaviorType::arrive)){

	}

	return steering_force;
}

void SteeringBehavior::setTarget(Vector4 p_target){
	target_point = p_target;
}

bool SteeringBehavior::isOn(BehaviorType p_behavior) const {
	return (behavior & p_behavior) == p_behavior;
}

bool SteeringBehavior::on(BehaviorType t) {
	if (t == BehaviorType::pursuit || t == BehaviorType::evade) return false;
	behavior |= t;
	return true;
}

void SteeringBehavior::pursuitOn(Handle &p_evader_handle){
	behavior |= BehaviorType::pursuit;
	target_agent_pursuit = p_evader_handle;
}

void SteeringBehavior::evadeOn(Handle &p_pursuer_handle){
	behavior |= BehaviorType::evade;
	target_agent_evade = p_pursuer_handle;
}

void SteeringBehavior::offsetPursuitOn(Handle &p_leader, const Vector4 p_offset){
	behavior |= BehaviorType::offset_pursuit;
	offset = p_offset;
	target_agent_leader = p_leader;
}

void SteeringBehavior::off(BehaviorType t) {
	if (this->isOn(t)) {
		behavior ^= t;
	}
}

BehaviorType SteeringBehavior::toBehaviorType(string str){
	if (str == "seek")
		return BehaviorType::seek;
	if (str == "flee")
		return BehaviorType::flee;
	if (str == "arrive")
		return BehaviorType::arrive;
	if (str == "wander")
		return BehaviorType::wander;
	if (str == "pursuit")
		return BehaviorType::pursuit;
	if (str == "evade")
		return BehaviorType::evade;
	if (str == "follow_path")
		return BehaviorType::follow_path;
	if (str == "offset_pursuit")
		return BehaviorType::offset_pursuit;
	return BehaviorType::none;
}

string SteeringBehavior::toString(){
	stringstream buffer;
	buffer << "Steering Behaviors: ";
	if (isOn(BehaviorType::seek)){
		buffer << "seek|";
	}
	if (isOn(BehaviorType::flee)){
		buffer << "flee|";
	}
	if (isOn(BehaviorType::arrive)){
		buffer << "arrive|";
	}
	if (isOn(BehaviorType::wander)){
		buffer << "wander|";
	}
	if (isOn(BehaviorType::pursuit)){
		buffer << "pursuit|";
	}
	if (isOn(BehaviorType::evade)){
		buffer << "evade|";
	}
	if (isOn(BehaviorType::follow_path)){
		buffer << "follow_path|";
	}
	if (isOn(BehaviorType::offset_pursuit)){
		buffer << "offset_pursuit|";
	}

	return buffer.str().substr(0, buffer.str().size() - 1);
}
