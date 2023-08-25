#include "ContactListener.h"
#include "Frame/Actor.h"
#include "Frame/Component/CollisionComponent.h"

namespace max
{
	void max::ContactListener::BeginContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer)
		{
			Actor* actorA = reinterpret_cast<Actor*>(fixtureA->GetUserData().pointer);
			Actor* actorB = reinterpret_cast<Actor*>(fixtureB->GetUserData().pointer);

			if (actorA->destroyed || actorB->destroyed) return;

			actorA->OnCollisionEnter(actorB);
			actorB->OnCollisionEnter(actorA);
		}
	}

	void max::ContactListener::EndContact(b2Contact* contact)
	{

	}
}