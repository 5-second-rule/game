#include <algorithm>

#include "SteeringBehavior.h"


SteeringBehavior::SteeringBehavior(MovingObject *owner) :m_behavior(BehaviorType::none)
{
	assert(ConfigSettings::configInstance()->getValue("time_tick", k_time_elapsed));
	assert(ConfigSettings::configInstance()->getValue("deceleration_tweaker", m_deceleration_tweaker));
	assert(ConfigSettings::configInstance()->getValue("wander_jitter", m_wander_jitter));
	assert(ConfigSettings::configInstance()->getValue("wander_radius", m_wander_radius));
	assert(ConfigSettings::configInstance()->getValue("wander_distance", m_wander_distance));
	assert(ConfigSettings::configInstance()->getValue("weight_wander", m_weight_wander));
	assert(ConfigSettings::configInstance()->getValue("weight_follow_path", m_weight_follow_path));
	assert(ConfigSettings::configInstance()->getValue("way_point_seek_distance", m_way_point_seek_distance));

	m_way_point_seek_distance_sq = m_way_point_seek_distance * m_way_point_seek_distance;
	m_owner = owner;
}


SteeringBehavior::~SteeringBehavior()
{
}

Vector4 SteeringBehavior::seek(Vector4 &p_targetPos){
	Vector4 desiredDirection = Common::Vector4::normalize(p_targetPos - m_owner->m_body->m_position);
	Vector4 desiredVelocity = desiredDirection * m_owner->m_max_speed;
	
	return desiredVelocity;
}

Vector4 SteeringBehavior::flee(Vector4 &p_targetPos){
	Vector4 desiredDirection = Common::Vector4::normalize(m_owner->m_body->m_position - p_targetPos);
	Vector4 desiredVelocity = desiredDirection * m_owner->m_max_speed;

	return desiredVelocity - m_owner->m_velocity;
}

Vector4 SteeringBehavior::arrive(Vector4 &p_targetPos, Deceleration deceleration){
	Vector4 toTarget;
	Vector4 desiredVelocity;
	float dist, speed;

	toTarget = p_targetPos - m_owner->m_body->m_position;

	dist = toTarget.length();

	if (dist > 0){
		speed = dist / ((float)deceleration * m_deceleration_tweaker);

		//min(speed, m_object->getMaxVelocity());
		desiredVelocity = toTarget * (speed / dist);

		return desiredVelocity - m_owner->m_velocity;
	}
	return Vector4(0,0,0,0);
}

Vector4 SteeringBehavior::pursuit(Handle *p_evader_handle){
	IHasHandle* tmp;
	MovingObject* evader;
	Vector4 toEvader;
	float relativeHeading, look_ahead_time;

	tmp = getObject(p_evader_handle);
	if (evader = dynamic_cast<MovingObject*>(tmp)){
		toEvader = evader->m_body->m_position - m_owner->m_body->m_position;
		relativeHeading = evader->heading().dot(m_owner->heading());

		if (toEvader.dot(m_owner->heading()) > 0 && relativeHeading < -0.95){
			return this->seek(evader->m_body->m_position);
		}

		look_ahead_time = toEvader.length() / (m_owner->m_max_speed + evader->speed());
		return seek(evader->m_body->m_position + evader->m_velocity * look_ahead_time);
	}
	else {
		pursuitOff();
	}
	return Vector4();
}

Vector4 SteeringBehavior::evade(Handle *p_pursuer_handle){
	IHasHandle* tmp;
	MovingObject* pursuer;
	Vector4 toPursuer;
	float look_ahead_time;

	tmp = getObject(p_pursuer_handle);
	if (pursuer = dynamic_cast<MovingObject*>(tmp)){
		toPursuer = pursuer->m_body->m_position - m_owner->m_body->m_position;
		look_ahead_time = toPursuer.length() / (m_owner->m_max_speed + pursuer->speed());
		return flee(pursuer->m_body->m_position + pursuer->m_velocity * look_ahead_time);
	}
	else {
		evadeOff();
	}
	return Vector4();
}

Vector4 SteeringBehavior::wander(){
	// Insert a jitter to the variation of the target
	float JitterThisTimeSlice = m_wander_jitter * k_time_elapsed;

	// Add a small random vector to the target's position
	// random clamped: between [-1, 1]
	m_wander_target += Vector4((float)RandomClamped() * JitterThisTimeSlice,
		(float)RandomClamped() * JitterThisTimeSlice,
		(float)RandomClamped() * JitterThisTimeSlice);

	// Normalize the target vector
	m_wander_target = Common::Vector4::normalize(m_wander_target);
	// Make the target a point at a sphere arround the agent
	m_wander_target *= m_wander_radius;
	// Make an offset in the sphere (local space)
	Vector4 target = m_wander_target + Vector4(0, 0, m_wander_distance);
	// Convert the target to world space
	target = Transformation::pointToWorldSpace(target,
												Vector4(1, 0, 0),
												Vector4(0, 1, 0),
												Vector4(0, 0, 1),
												m_owner->m_body->m_position);
	return target - m_owner->m_body->m_position;
}


Vector4 SteeringBehavior::followPath() {
	// Move to next target if close enough to current target (working in
	// distance squared space)
	if (distanceSquared(*m_owner->m_current_way_point, m_owner->m_body->m_position) <
		m_way_point_seek_distance_sq)
	{
		m_owner->setNextWayPoint();
		cout << "new point: " << m_owner->m_current_way_point->toString() << endl;
	}
	if (getWorld()->isTick(60)){
		cout << distanceSquared(*m_owner->m_current_way_point, m_owner->m_body->m_position) << endl;
	}

	if (!m_owner->m_path->finished(m_owner)) {
		return seek(*m_owner->m_current_way_point);
	} else {
		return arrive(*m_owner->m_current_way_point, normal);
	}
}

Vector4 SteeringBehavior::offsetPursuit(Handle *p_leader, Vector4 &offset) {
	MovingObject* leader = dynamic_cast<MovingObject*> getObject(p_leader);
	
	if (leader == nullptr) {
		// Leader does not exist anymore
		offsetPursuitOff();
		return Vector4(0, 0, 0);
	}

	// calculate the offset's position in world space
	Vector4 WorldOffsetPos = Transformation::pointToWorldSpace(offset,
		leader->side(),
		leader->top(),
		leader->front(),
		leader->m_body->m_position);

	Vector4 ToOffset = WorldOffsetPos - m_owner->m_body->m_position;

	// The lookahead time is propotional to the distance between the leader
	// and the pursuer; and is inversely proportional to the sum of both
	// agent's velocities
	float LookAheadTime = ToOffset.length() / (m_owner->m_max_speed + leader->speed());

	// Arrive at the predicted future position of the offset
	return arrive(WorldOffsetPos + leader->m_velocity * LookAheadTime, fast);
}

/*
Vector4 SteeringBehavior::separation(const std::vector<Handle> &neighbors)
{
	Vector4 SteeringForce;

	for (unsigned int a = 0; a<neighbors.size(); ++a)
	{
		//make sure this agent isn't included in the calculations and that
		//the agent being examined is close enough. ***also make sure it doesn't
		//include the evade target ***
		if ((neighbors[a] != m_owner) && neighbors[a]->IsTagged() &&
			(neighbors[a] != m_pTargetAgent1))
		{
			Vector4 ToAgent = m_owner->Pos() - neighbors[a]->Pos();

			//scale the force inversely proportional to the agents distance  
			//from its neighbor.
			SteeringForce += Vec2DNormalize(ToAgent) / ToAgent.Length();
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
		//make sure *this* agent isn't included in the calculations and that
		//the agent being examined  is close enough ***also make sure it doesn't
		//include any evade target ***
		if ((neighbors[a] != m_owner) && neighbors[a]->IsTagged() &&
			(neighbors[a] != m_pTargetAgent1))
		{
			AverageHeading += neighbors[a]->Heading();

			++NeighborCount;
		}
	}

	//if the neighborhood contained one or more vehicles, average their
	//heading vectors.
	if (NeighborCount > 0)
	{
		AverageHeading /= (float)NeighborCount;

		AverageHeading -= m_owner->Heading();
	}

	return AverageHeading;
}

Vector4 SteeringBehavior::cohesion(const std::vector<Handle> &neighbors)
{
	//first find the center of mass of all the agents
	Vector4 CenterOfMass, SteeringForce;

	int NeighborCount = 0;

	//iterate through the neighbors and sum up all the position vectors
	for (unsigned int a = 0; a<neighbors.size(); ++a)
	{
		//make sure *this* agent isn't included in the calculations and that
		//the agent being examined is close enough ***also make sure it doesn't
		//include the evade target ***
		if ((neighbors[a] != m_owner) && neighbors[a]->IsTagged() &&
			(neighbors[a] != m_pTargetAgent1))
		{
			CenterOfMass += neighbors[a]->Pos();

			++NeighborCount;
		}
	}

	if (NeighborCount > 0)
	{
		//the center of mass is the average of the sum of positions
		CenterOfMass /= (float)NeighborCount;

		//now seek towards that position
		SteeringForce = Seek(CenterOfMass);
	}

	//the magnitude of cohesion is usually much larger than separation or
	//allignment so it usually helps to normalize it.
	return Vec2DNormalize(SteeringForce);
}
*/

bool SteeringBehavior::accumulateForce(Vector4 &RunningTot,
	Vector4 ForceToAdd)
{
	// Calculate how much steering force the vehicle has used so far
	float MagnitudeSoFar = RunningTot.length();

	// Calculate how much steering force remains to be used by this vehicle
	float MagnitudeRemaining = m_owner->m_max_force - MagnitudeSoFar;

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
	} else {
		RunningTot += (Common::Vector4::normalize(ForceToAdd) * MagnitudeRemaining);
	}

	return true;
}

Vector4 SteeringBehavior::calculate(){
	m_steering_force.set(0, 0, 0, 0);

	calculatePrioritized();

	return m_steering_force;
}

Vector4 SteeringBehavior::calculatePrioritized(){
	Vector4 force;

	if (On(BehaviorType::follow_path)){
		force = followPath() * m_weight_follow_path;
		if (!accumulateForce(m_steering_force, force)) return m_steering_force;
	}
	if (On(BehaviorType::wander)){
		force = wander() * m_weight_wander;
		if (!accumulateForce(m_steering_force, force)) return m_steering_force;
	}
	if (On(BehaviorType::arrive)){

	}
	return m_steering_force;
}

void SteeringBehavior::setTarget(Vector4 p_target){
	m_target_point = p_target;
}

bool SteeringBehavior::On(BehaviorType p_behavior) const{
	return (m_behavior & p_behavior) == p_behavior;
}

void SteeringBehavior::seekOn(){
	m_behavior |= BehaviorType::seek;
}

void SteeringBehavior::fleeOn(){
	m_behavior |= BehaviorType::flee;
}

void SteeringBehavior::arriveOn(){
	m_behavior |= BehaviorType::arrive;
}

void SteeringBehavior::pursuitOn(Handle *p_evader_handle){
	m_behavior |= BehaviorType::pursuit;
	m_target_agent = p_evader_handle;
}

void SteeringBehavior::evadeOn(Handle *p_pursuer_handle){
	m_behavior |= BehaviorType::evade;
	m_target_agent = p_pursuer_handle;
}

void SteeringBehavior::wanderOn(){
	m_behavior |= BehaviorType::wander;
}

void SteeringBehavior::followPathOn(){
	m_behavior |= BehaviorType::follow_path;
}

void SteeringBehavior::offsetPursuitOn(Handle * p_leader, const Vector4 p_offset){
	m_behavior |= BehaviorType::offset_pursuit;
	m_offset = p_offset;
	m_target_agent = p_leader;
}

void SteeringBehavior::seekOff(){
	if (On(BehaviorType::seek))
		m_behavior ^= BehaviorType::seek;
}

void SteeringBehavior::fleeOff(){
	if (On(BehaviorType::flee))
		m_behavior ^= BehaviorType::flee;
}

void SteeringBehavior::arriveOff(){
	if (On(BehaviorType::arrive))
		m_behavior ^= BehaviorType::arrive;
}

void SteeringBehavior::pursuitOff(){
	if (On(BehaviorType::pursuit))
		m_behavior ^= BehaviorType::pursuit;
}

void SteeringBehavior::evadeOff(){
	if (On(BehaviorType::evade))
		m_behavior ^= BehaviorType::evade;
}

void SteeringBehavior::wanderOff(){
	if (On(BehaviorType::wander))
		m_behavior ^= BehaviorType::wander;
}

void SteeringBehavior::followPathOff(){
	if (On(BehaviorType::follow_path))
		m_behavior ^= BehaviorType::follow_path;
}

void SteeringBehavior::offsetPursuitOff(){
	if (On(BehaviorType::offset_pursuit))
		m_behavior ^= BehaviorType::offset_pursuit;
}