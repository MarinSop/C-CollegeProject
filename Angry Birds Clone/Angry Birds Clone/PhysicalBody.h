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
	float getAngle();
	b2World* getWorld();
	b2Vec2 getLinerVelocity();
	b2Body* bd();
	void setPosition(b2Vec2 pos);

	void setAwake(bool state);

	void applyImpulse(b2Vec2 vec);

private:
	b2BodyDef* _bodyDef;
	b2Body* _body;
	b2PolygonShape* _shape;
	b2World* _world;
};

