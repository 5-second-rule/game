#include <algorithm>

#include "SteeringBehavior.h"

#include "GameInstance.h"


SteeringBehavior::SteeringBehavior(MovingObject *owner) : m_behavior(BehaviorType::none)
{
	assert(Utility::configInstance()->getValue("deceleration_tweaker", k_deceleration_tweaker));
	assert(Utility::configInstance()->getValue("time_tick", k_time_elapsed));
	assert(Utility::configInstance()->getValue("wander_radius", m_wander_radius));
	assert(Utility::configInstance()->getValue("wander_distance", m_wander_distance));
	assert(Utility::configInstance()->getValue("wander_weight", m_wander_weight));

	m_owner = owner;
}


SteeringBehavior::~SteeringBehavior()
{
}

Vector4 SteeringBehavior::seek(Vector4 &p_targetPos){
	Vector4 desiredDirection = Utility::normalize(p_targetPos - m_owner->m_body->m_position);
	Vector4 desiredVelocity = desiredDirection * m_owner->m_max_speed;
	
	return desiredVelocity - m_owner->m_velocity;
}

Vector4 SteeringBehavior::flee(Vector4 &p_targetPos){
	Vector4 desiredDirection = normalize(m_owner->m_body->m_position - p_targetPos);
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
		speed = dist / ((float)deceleration * k_deceleration_tweaker);

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

	tmp = GameInstance::getGlobalInstance()->getEngineInstance()->world->get(p_evader_handle);
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

	tmp = GameInstance::getGlobalInstance()->getEngineInstance()->world->get(p_pursuer_handle);
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
	m_wander_target += Vector4((float)RandomClamped() * k_time_elapsed,
		(float)RandomClamped() * k_time_elapsed,
		(float)RandomClamped() * k_time_elapsed);

	m_wander_target = Utility::normalize(m_wander_target);
	m_wander_target *= m_wander_radius;
	Vector4 target = m_wander_target + Vector4(0, 0, m_wander_distance);

	return target;
}


//--------------------- AccumulateForce ----------------------------------
//
//  This function calculates how much of its max steering force the 
//  vehicle has left to apply and then applies that amount of the
//  force to add.
//------------------------------------------------------------------------
bool SteeringBehavior::accumulateForce(Vector4 &RunningTot,
	Vector4 ForceToAdd)
{

	//calculate how much steering force the vehicle has used so far
	double MagnitudeSoFar = RunningTot.length();

	//calculate how much steering force remains to be used by this vehicle
	double MagnitudeRemaining = m_owner->m_max_force - MagnitudeSoFar;

	//return false if there is no more force left to use
	if (MagnitudeRemaining <= 0.0) return false;

	//calculate the magnitude of the force we want to add
	double MagnitudeToAdd = ForceToAdd.length();

	//if the magnitude of the sum of ForceToAdd and the running total
	//does not exceed the maximum force available to this vehicle, just
	//add together. Otherwise add as much of the ForceToAdd vector is
	//possible without going over the max.
	if (MagnitudeToAdd < MagnitudeRemaining)
	{
		RunningTot += ForceToAdd;
	}

	else
	{
		//add it to the steering force
		RunningTot += (Utility::normalize(ForceToAdd) * MagnitudeRemaining);
	}

	return true;
}

Vector4 SteeringBehavior::calculate(){
	m_steering_force.set(0, 0, 0, 0);

	m_steering_force = calculatePrioritized();

	return m_steering_force;
}

Vector4 SteeringBehavior::calculatePrioritized(){
	Vector4 force;

	if (On(BehaviorType::wander)){
		accumulateForce(force, wander() * m_wander_weight);
	}
	if (On(BehaviorType::arrive)){

	}
	return force;
}

void SteeringBehavior::setTarget(Vector4 p_target){
	m_target_point = p_target;
}

bool SteeringBehavior::On(BehaviorType p_behavior) const{
	return p_behavior == m_behavior;
}

void SteeringBehavior::seekOn(){
	m_behavior = BehaviorType::seek;
}

void SteeringBehavior::fleeOn(){
	m_behavior = BehaviorType::flee;
}

void SteeringBehavior::arriveOn(){
	m_behavior = BehaviorType::arrive;
}

void SteeringBehavior::pursuitOn(Handle *p_evader_handle){
	m_behavior = BehaviorType::pursuit;
	m_target_agent = p_evader_handle;
}

void SteeringBehavior::evadeOn(Handle *p_pursuer_handle){
	m_behavior = BehaviorType::evade;
	m_target_agent = p_pursuer_handle;
}

void SteeringBehavior::wanderOn(){
	m_behavior = BehaviorType::wander;
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