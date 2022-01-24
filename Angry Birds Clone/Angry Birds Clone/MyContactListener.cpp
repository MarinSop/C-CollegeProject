#include "MyContactListener.h"

void MyContactListener::BeginContact(b2Contact* contact)
{

}

void MyContactListener::EndContact(b2Contact* contact)
{
}

void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
    UserData* bodyUserDataA = (UserData*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    UserData* bodyUserDataB = (UserData*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
    float a = impulse->normalImpulses[0];
    float b = impulse->normalImpulses[1];
    if (bodyUserDataA)
    {
        float velX = contact->GetFixtureA()->GetBody()->GetLinearVelocity().x;
        float velY = contact->GetFixtureA()->GetBody()->GetLinearVelocity().y;
        float velocity = sqrt(velX * velX + velY * velY);
        float momentum = contact->GetFixtureA()->GetBody()->GetMass() * velocity;
        if (momentum > 1.0f)
        {
            if (bodyUserDataA->data == "wood")
            {
                ((Entity*)bodyUserDataA->pointer)->takeDamage(abs(a) * 0.2f * 50.0f);
            }
            else if (bodyUserDataA->data == "stone")
            {
                ((Entity*)bodyUserDataA->pointer)->takeDamage(abs(a) * 0.2f * 50.0f);
            }
            else if (bodyUserDataA->data == "pig")
            {
                ((Entity*)bodyUserDataA->pointer)->takeDamage(abs(a) * 0.2f * 50.0f);
            }
        }
    }
    if (bodyUserDataB)
    {
        float velX = contact->GetFixtureB()->GetBody()->GetLinearVelocity().x;
        float velY = contact->GetFixtureB()->GetBody()->GetLinearVelocity().y;
        float velocity = sqrt(velX * velX + velY * velY);
        float momentum = contact->GetFixtureB()->GetBody()->GetMass() * velocity;
        if (momentum > 1.0f)
        {
            if (bodyUserDataB->data == "wood")
            {
                ((Entity*)bodyUserDataB->pointer)->takeDamage(abs(b) * 0.2f * 50.0f);
            }
            else if (bodyUserDataB->data == "stone")
            {
                ((Entity*)bodyUserDataB->pointer)->takeDamage(abs(b) * 0.2f * 50.0f);
            }
            else if (bodyUserDataB->data == "pig")
            {
                ((Entity*)bodyUserDataB->pointer)->takeDamage(abs(b) * 0.2f * 50.0f);
            }
        }
    }
}
