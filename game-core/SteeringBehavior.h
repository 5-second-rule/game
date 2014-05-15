#pragma once

#include "game-core.h"
#include "Game.h"
#include "MovingObject.h"
#include "BehaviorType.h"

class GAMECOREDLL MovingObject;

class GAMECOREDLL SteeringBehavior
{
private:
	enum Deceleration
	{
		slow = 3,
		normal = 2,
		fast = 1
	};

	// Configuration constants
	float k_time_elapsed;

	// Arrive parameters
	float deceleration_tweaker;

	// Wander parameters
	float wander_radius;
	float wander_distance;
	float wander_jitter;

	// Follow path parameters
	float way_point_seek_distance;
	float way_point_seek_distance_sq;

	// Caculate prioritized parameters (weights)
	float weight_wander;
	float weight_follow_path;

	// Steering behavior attributes
	Vector4 target_point;
	Handle target_agent1;
	Handle target_agent2;
	Vector4 wander_target;

	// Offset pursuit attributes
	Vector4 offset;

	// Active behaviors
	int behavior;

	Vector4 steering_force;
	Handle target_agent;
	MovingObject *owner;

	Vector4 seek(Vector4 &p_point);
	Vector4 flee(Vector4 &p_point);
	Vector4 arrive(Vector4 &p_point, Deceleration deceleration = slow);
	Vector4 pursuit(Handle &p_prey_handle);
	Vector4 evade(Handle &p_predator_handle);
	Vector4 wander();

	//------------------------------- FollowPath -----------------------------
	//
	//  Given a series of Vector2Ds, this method produces a force that will
	//  move the agent along the waypoints in order. The agent uses the
	// 'Seek' behavior to move to the next waypoint - unless it is the last
	//  waypoint, in which case it 'Arrives'
	//------------------------------------------------------------------------
	Vector4 followPath();

	//------------------------- Offset Pursuit -------------------------------
	//
	//  Produces a steering force that keeps a vehicle at a specified offset
	//  from a leader vehicle
	//------------------------------------------------------------------------
	Vector4 offsetPursuit(Handle &p_leader, Vector4 &offset);

	//---------------------------- Separation --------------------------------
	//
	// this calculates a force repelling from the other neighbors
	//------------------------------------------------------------------------
	Vector4 separation(const std::vector<Handle> &neighbors);

	//---------------------------- Alignment ---------------------------------
	//
	//  returns a force that attempts to align this agents heading with that
	//  of its neighbors
	//------------------------------------------------------------------------
	Vector4 alignment(const std::vector<Handle> &neighbors);

	//-------------------------------- Cohesion ------------------------------
	//
	//  returns a steering force that attempts to move the agent towards the
	//  center of mass of the agents in its immediate area
	//------------------------------------------------------------------------
	Vector4 cohesion(const std::vector<Handle> &neighbors);

	Vector4 calculatePrioritized();

	//--------------------- AccumulateForce ----------------------------------
	//
	//  This function calculates how much of its max steering force the 
	//  vehicle has left to apply and then applies that amount of the
	//  force to add.
	//------------------------------------------------------------------------
	bool accumulateForce(Vector4 &RunningTot, Vector4 ForceToAdd);
	template< class T, class container_T >
	void tagNeighbors(const T* p_entity, container_T &p_container_entities, float radius);
public:
	SteeringBehavior(MovingObject*);
	~SteeringBehavior();
	Vector4 calculate();
	bool On(BehaviorType) const;
	void setTarget(Vector4 p_target);

	void seekOn();
	void fleeOn();
	void arriveOn();
	void pursuitOn(Handle &p_preyHandle);
	void evadeOn(Handle &p_predatorHandle);
	void wanderOn();
	void followPathOn();
	void offsetPursuitOn(Handle &p_leader, const Vector4 p_offset);
	void seekOff();
	void fleeOff();
	void arriveOff();
	void pursuitOff();
	void evadeOff();
	void wanderOff();
	void followPathOff();
	void offsetPursuitOff();
};