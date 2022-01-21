#pragma once
#include <box2d/box2d.h>
#include "UserData.h"
#define SCALE 30.0f
class PhysicalBody
{
public:
	PhysicalBody(b2World* world,b2BodyType type,b2Vec2 position,b2Vec2 size,UserData* objPointer = NULL);
	PhysicalBody(b2World* world, b2BodyType type, b2Vec2 position, float radius, UserData* objPointer = NULL);
	~PhysicalBody();


	b2Vec2 getPosition();
	b2Vec2 getPositionScaled();
	float getAngle();
	b2World* getWorld();
	float getMass();
	b2Vec2 getLinerVelocity();
	void setPosition(b2Vec2 pos);

	void setAwake(bool state);
	bool isAwake();
	void setEnabled(bool state);
	b2Vec2 getLinearVelocity();

	void applyImpulse(b2Vec2 vec);

private:
	b2BodyDef* _bodyDef;
	b2Body* _body;
	b2PolygonShape* _shape;
	b2CircleShape* _circleShape;
	b2World* _world;
};

