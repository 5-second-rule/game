#pragma once

#include "../../common/common/4D/Matrix4.h"
#include "../../engine/engine-core/ConfigSettings.h"

#include "../../common/common/misc/utils.h"
#include "game-core.h"
#include "Transformation.h"
#include "MovingObject.h"

class GAMECOREDLL MovingObject;

enum BehaviorType{
	none = 0x00,
	seek = 0x01,
	flee = 0x02,
	arrive = 0x04,
	wander = 0x08,
	pursuit = 0x10,
	evade = 0x20
};

using namespace Common;
class GAMECOREDLL SteeringBehavior
{
private:
	enum Deceleration
	{
		slow = 3,
		normal = 2,
		fast = 1
	};
	
	/* Configuration constants */
	float k_deceleration_tweaker;
	float k_time_elapsed;

	Vector4 m_steering_force;
	int m_behavior;

	/* Wander Parameters */
	float m_wander_radius;
	float m_wander_distance;
	float m_wander_weight;

	Vector4 m_target_point;
	Vector4 m_wander_target;
	Handle *m_target_agent;
	MovingObject *m_owner;

	Vector4 seek(Vector4 &p_point);
	Vector4 flee(Vector4 &p_point);
	Vector4 arrive(Vector4 &p_point, Deceleration deceleration = slow);
	Vector4 pursuit(Handle *p_prey_handle);
	Vector4 evade(Handle *p_predator_handle);
	Vector4 wander();

	bool accumulateForce(Vector4 &RunningTot, Vector4 ForceToAdd);
public:
	SteeringBehavior(MovingObject*);
	~SteeringBehavior();
	Vector4 calculate();
	Vector4 calculatePrioritized();
	bool On(BehaviorType) const;
	void setTarget(Vector4 p_target);
	void seekOn();
	void fleeOn();
	void arriveOn();
	void pursuitOn(Handle *p_preyHandle);
	void evadeOn(Handle *p_predatorHandle);
	void wanderOn();
	void seekOff();
	void fleeOff();
	void arriveOff();
	void pursuitOff();
	void evadeOff();
	void wanderOff();
};

