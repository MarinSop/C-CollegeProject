#pragma once
#include "box2d/box2d.h"
#include "Entity.h"
#include "UserData.h"
class MyContactListener : public b2ContactListener
{
    void BeginContact(b2Contact* contact);

    void EndContact(b2Contact* contact);

    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

