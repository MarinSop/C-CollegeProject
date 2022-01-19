#include "PhysicalBody.h"

PhysicalBody::PhysicalBody(b2World* world, b2BodyType type, b2Vec2 position, b2Vec2 size,UserData* objPointer)
{
	_bodyDef = new b2BodyDef();
	_bodyDef->type = type;
	_bodyDef->position.Set(position.x / SCALE, position.y / SCALE);
	_bodyDef->userData.pointer = reinterpret_cast<uintptr_t>(objPointer);
	_body = world->CreateBody(_bodyDef);
	_shape = new b2PolygonShape();
	_shape->SetAsBox((size.x / 2) / SCALE, (size.y / 2) / SCALE);
	_body->CreateFixture(_shape, 1.0f);
	_circleShape = nullptr;
}
PhysicalBody::PhysicalBody(b2World* world, b2BodyType type, b2Vec2 position, float radius, UserData* objPointer)
{
	_bodyDef = new b2BodyDef();
	_bodyDef->type = type;
	_bodyDef->position.Set(position.x / SCALE, position.y / SCALE);
	_bodyDef->userData.pointer = reinterpret_cast<uintptr_t>(objPointer);
	_body = world->CreateBody(_bodyDef);
	_circleShape = new b2CircleShape();
	_circleShape->m_radius = radius/SCALE/2.0f;
	_body->CreateFixture(_circleShape, 1.0f);
	_shape = nullptr;
}

PhysicalBody::~PhysicalBody()
{
	_body->GetWorld()->DestroyBody(_body);
	delete _shape;
	delete _circleShape;
	delete _bodyDef;
}

b2Vec2 PhysicalBody::getPosition()
{
	return _body->GetPosition();
}

b2Vec2 PhysicalBody::getPositionScaled()
{
	return b2Vec2(_body->GetPosition().x*SCALE,_body->GetPosition().y*SCALE);
}

float PhysicalBody::getAngle()
{
	return _body->GetAngle();;
}

b2World* PhysicalBody::getWorld()
{
	return _body->GetWorld();;
}

float PhysicalBody::getMass()
{
	return _body->GetMass();
}

b2Vec2 PhysicalBody::getLinerVelocity()
{
	return _body->GetLinearVelocity();
}

void PhysicalBody::setPosition(b2Vec2 pos)
{
	_body->SetTransform(pos,_body->GetAngle());
}

void PhysicalBody::setAwake(bool state)
{
	_body->SetAwake(state);
}

bool PhysicalBody::isAwake()
{
	return _body->IsAwake();
}

void PhysicalBody::setEnabled(bool state)
{
	_body->SetEnabled(state);
}

void PhysicalBody::applyImpulse(b2Vec2 vec)
{
	_body->ApplyLinearImpulseToCenter(vec, true);
}
