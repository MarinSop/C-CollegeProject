#pragma once
#include <box2d/box2d.h>
#define SCALE 30.0f
class PhysicalBody
{
public:
	PhysicalBody(b2World* world,b2BodyType type,b2Vec2 position,b2Vec2 size);
	~PhysicalBody();


	b2Vec2 getPosition();
	b2Vec2 getPositionScaled();
	void setPosition(b2Vec2 pos);

private:
	b2BodyDef* _bodyDef;
	b2Body* _body;
	b2PolygonShape* _shape;
	b2World* _world;
};

