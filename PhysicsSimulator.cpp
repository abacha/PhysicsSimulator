#include "PhysicsSimulator.h"
using namespace gs2d;
using namespace math;

inline float PhysicsSimulator::ConvertToB2d(const float &value)
{
	return value / m_worldScale;
}

inline Vector2 PhysicsSimulator::ConvertToB2d(const Vector2 &value)
{
	return value / m_worldScale;
}


inline b2Vec2 PhysicsSimulator::ConvertFromB2d(const b2Vec2 &value)
{
	return b2Vec2(value.x * m_worldScale, value.y * m_worldScale);
}

b2Vec2 PhysicsSimulator::Vector2Tob2Vec2(const Vector2 &vector)
{
	return b2Vec2(vector.x, vector.y);
}

Vector2 PhysicsSimulator::b2Vec2ToVector2(const b2Vec2 &vector)
{
	return Vector2(vector.x, vector.y);
}


PhysicsSimulator::PhysicsSimulator(Vector2 gravity, bool doSleep, float worldScale, int velocityIterations, int positionIterations): 
	m_idCounter(0),
	m_worldScale(worldScale),
	m_velocityIterations(velocityIterations),
	m_positionIterations(positionIterations) 
{
	m_world = boost::shared_ptr<b2World>(new b2World(Vector2Tob2Vec2(gravity), doSleep));
}
int PhysicsSimulator::GetNewId()
{
	return m_idCounter++;
}

int PhysicsSimulator::CreateEdge(float x1, float x2, float y)
{	
	b2BodyDef bodyDef;
	b2Body* body = m_world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsEdge(b2Vec2(x1, y), b2Vec2(x2, y));	
	body->CreateFixture(&dynamicBox, 0.0f);
	const int newId = GetNewId();
	m_bodies[newId] = body;
	return newId;
}

void PhysicsSimulator::ApplyForce(int bodyIndex, Vector2 force)
{
	b2Vec2 realForce = Vector2Tob2Vec2(force);	
	m_bodies[bodyIndex]->ApplyLinearImpulse(realForce, m_bodies[bodyIndex]->GetWorldCenter());
}

void PhysicsSimulator::ApplySpin(int bodyIndex, Vector2 force)
{
	m_bodies[bodyIndex]->ApplyAngularImpulse(force.x * 1000);
}

void PhysicsSimulator::SetVelocity(int bodyIndex, Vector2 velocity)
{
	m_bodies[bodyIndex]->SetLinearVelocity(Vector2Tob2Vec2(velocity));
}


int PhysicsSimulator::CreateSphere(float radius, Vector2 pos, float density, float friction, float restitution)
{	
	pos = ConvertToB2d(pos);
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x, pos.y);
	if (density != 0)
	{
		bodyDef.type = b2_dynamicBody;
	}
	b2Body* body = m_world->CreateBody(&bodyDef);
	b2CircleShape shape;
	shape.m_radius = ConvertToB2d(radius);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	body->CreateFixture(&fixtureDef);
	const int newId = GetNewId();
	m_bodies[newId] = body;
	return newId;
}

int PhysicsSimulator::CreatePolygon(Rect2Df polygon, float density, float friction, float restitution, float angle)
{
	Vector2 pos = ConvertToB2d(polygon.pos);
	if (pos.x != 0) std::cout << pos.x << "," << pos.y << std::endl;
	b2BodyDef bodyDef;
	bodyDef.angle = DegreeToRadian(angle);
	bodyDef.position.Set(pos.x, pos.y);
	if (density != 0)
	{
		bodyDef.type = b2_dynamicBody;
	}
	b2Body* body = m_world->CreateBody(&bodyDef);
	b2PolygonShape shape;

	shape.SetAsBox(ConvertToB2d(polygon.size.x / 2), ConvertToB2d(polygon.size.y / 2));
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	body->CreateFixture(&fixtureDef);	
	const int newId = GetNewId();
	m_bodies[newId] = body;
	return newId;
}

Vector2 PhysicsSimulator::GetPosition(int bodyIndex)
{
	return b2Vec2ToVector2(m_bodies[bodyIndex]->GetPosition()) * m_worldScale;
}

float PhysicsSimulator::GetAngle(int bodyIndex)
{
	return m_bodies[bodyIndex]->GetAngle();
}

void PhysicsSimulator::Step(float timeStep)
{
	m_world->Step(timeStep, m_velocityIterations, m_positionIterations);
}

void PhysicsSimulator::SetContactListener(b2ContactListener *contact)
{
	m_world->SetContactListener(contact);
}
