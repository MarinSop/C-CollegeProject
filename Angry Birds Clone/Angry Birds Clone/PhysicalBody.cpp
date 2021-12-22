#include "PhysicalBody.h"

PhysicalBody::PhysicalBody(b2World* world, b2BodyType type, b2Vec2 position, b2Vec2 size)
{
	_bodyDef = new b2BodyDef();
	_bodyDef->type = type;
	_bodyDef->position.Set(position.x / SCALE, position.y / SCALE);
	_body = world->CreateBody(_bodyDef);
	_shape = new b2PolygonShape();
	_shape->SetAsBox((size.x / 2) / SCALE, (size.y / 2) / SCALE);
	_body->CreateFixture(_shape, 1.0f);
}

PhysicalBody::~PhysicalBody()
{
	_body->GetWorld()->DestroyBody(_body);
	delete _shape;
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

void PhysicalBody::setPosition(b2Vec2 pos)
{

}
