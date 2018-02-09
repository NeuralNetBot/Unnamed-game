#pragma once
#include <glm\glm.hpp>
#include "btBulletDynamicsCommon.h"
#define DEFAULT_GRAVITY -9.81
class Physics
{
private:
	btBroadphaseInterface * broadphase;

	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;

	btSequentialImpulseConstraintSolver* solver;

	btDiscreteDynamicsWorld* dynamicsWorld;

	btVector3 gravity;
public:
	Physics();
	void AddObject(btCollisionShape* shape);
	void SetGravity(btVector3 Gravity);
	btVector3 GetGravity();
	~Physics();
};

