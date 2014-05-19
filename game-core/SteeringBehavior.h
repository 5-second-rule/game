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
	Common::Vector4 target_point;
	Handle target_agent1;
	Handle target_agent2;
	Common::Vector4 wander_target;

	// Offset pursuit attributes
	Common::Vector4 offset;

	// Active behaviors
	int behavior;

	Common::Vector4 steering_force;
	Handle target_agent;
	MovingObject *owner;

	Common::Vector4 seek(Common::Vector4 &p_point);
	Common::Vector4 flee(Common::Vector4 &p_point);
	Common::Vector4 arrive(Common::Vector4 &p_point, Deceleration deceleration = slow);
	Common::Vector4 pursuit(Handle &p_prey_handle);
	Common::Vector4 evade(Handle &p_predator_handle);
	Common::Vector4 wander();

	//------------------------------- FollowPath -----------------------------
	//
	//  Given a series of Vector2Ds, this method produces a force that will
	//  move the agent along the waypoints in order. The agent uses the
	// 'Seek' behavior to move to the next waypoint - unless it is the last
	//  waypoint, in which case it 'Arrives'
	//------------------------------------------------------------------------
	Common::Vector4 followPath();

	//------------------------- Offset Pursuit -------------------------------
	//
	//  Produces a steering force that keeps a vehicle at a specified offset
	//  from a leader vehicle
	//------------------------------------------------------------------------
	Common::Vector4 offsetPursuit(Handle &p_leader, Common::Vector4 &offset);

	//---------------------------- Separation --------------------------------
	//
	// this calculates a force repelling from the other neighbors
	//------------------------------------------------------------------------
	Common::Vector4 separation(const std::vector<Handle> &neighbors);

	//---------------------------- Alignment ---------------------------------
	//
	//  returns a force that attempts to align this agents heading with that
	//  of its neighbors
	//------------------------------------------------------------------------
	Common::Vector4 alignment(const std::vector<Handle> &neighbors);

	//-------------------------------- Cohesion ------------------------------
	//
	//  returns a steering force that attempts to move the agent towards the
	//  center of mass of the agents in its immediate area
	//------------------------------------------------------------------------
	Common::Vector4 cohesion(const std::vector<Handle> &neighbors);

	Common::Vector4 calculatePrioritized();

	//--------------------- AccumulateForce ----------------------------------
	//
	//  This function calculates how much of its max steering force the 
	//  vehicle has left to apply and then applies that amount of the
	//  force to add.
	//------------------------------------------------------------------------
	bool accumulateForce(Common::Vector4 &RunningTot, Common::Vector4 ForceToAdd);
	template< class T, class container_T >
	void tagNeighbors(const T* p_entity, container_T &p_container_entities, float radius);
public:
	SteeringBehavior(MovingObject*);
	~SteeringBehavior();
	Common::Vector4 calculate();
	bool On(BehaviorType) const;
	void setTarget(Common::Vector4 p_target);

	void seekOn();
	void fleeOn();
	void arriveOn();
	void pursuitOn(Handle &p_preyHandle);
	void evadeOn(Handle &p_predatorHandle);
	void wanderOn();
	void followPathOn();
	void offsetPursuitOn(Handle &p_leader, const Common::Vector4 p_offset);
	void seekOff();
	void fleeOff();
	void arriveOff();
	void pursuitOff();
	void evadeOff();
	void wanderOff();
	void followPathOff();
	void offsetPursuitOff();
};