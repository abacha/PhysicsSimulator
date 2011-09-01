#ifndef PHYSICSSIMULATOR_H_
#define PHYSICSSIMULATOR_H_

#include "../gs2d/src/gs2dframework.h"
#include <Box2D/Box2D.h>
#include <map>
#include <vector>

class PhysicsSimulator
{
	boost::shared_ptr<b2World> m_world;
	int m_velocityIterations;
	int m_positionIterations;	
	const float m_worldScale;
	std::map<int, b2Body*> m_bodies;
	int m_idCounter;

	inline float ConvertToB2d(const float &value);
	inline gs2d::math::Vector2 ConvertToB2d(const gs2d::math::Vector2 &value);
	inline b2Vec2 ConvertFromB2d(const b2Vec2 &value);
	inline gs2d::math::Vector2 PhysicsSimulator::b2Vec2ToVector2(const b2Vec2 &vector);
	b2Vec2 Vector2Tob2Vec2(const gs2d::math::Vector2 &vector);


	int GetNewId();

	public:
		void SetContactListener(b2ContactListener *contact);
		PhysicsSimulator(gs2d::math::Vector2 gravity, bool doSleep, float worldScale = 5.0f, int velocityIterations = 6, int positionIterations = 2);
		int CreateEdge(float x1, float x2, float y);
		int CreatePolygon(gs2d::math::Rect2Df polygon, float density = 0, float friction = 0, float restitution = 0, float angle = 0);
		int CreateSphere(float radius, gs2d::math::Vector2 pos, float density = 1, float friction = 0, float restitution = 0);
		gs2d::math::Vector2 GetPosition(int bodyIndex);
		float GetAngle(int bodyIndex);
		void ApplyForce(int bodyIndex, gs2d::math::Vector2 force);		
		void ApplySpin(int bodyIndex, gs2d::math::Vector2 force);
		void SetVelocity(int bodyIndex, gs2d::math::Vector2 velocity);
		void Step(float timeStep = 1.0f/30.0f);
};
typedef boost::shared_ptr<PhysicsSimulator> PhysicsSimulatorPtr;

#endif