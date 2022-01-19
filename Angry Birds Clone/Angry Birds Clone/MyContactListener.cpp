#include "MyContactListener.h"

void MyContactListener::BeginContact(b2Contact* contact)
{
         UserData* bodyUserDataA = (UserData*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
         if (bodyUserDataA)
         {
         }
         UserData* bodyUserDataB = (UserData*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
         if (bodyUserDataB)
         { 
         }
}

void MyContactListener::EndContact(b2Contact* contact)
{
}
