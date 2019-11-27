
#include "Actor.h"

void Actor::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

void Actor::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

sf::Vector2f Actor::getVelocity() const
{
	return mVelocity;
}
void Actor::updateCurrent(sf::Time dt)
{
	move(mVelocity * dt.asSeconds());
}
void Actor::accelerate(sf::Vector2f velocity)
{
	mVelocity += velocity;
}

void Actor::accelerate(float vx, float vy)
{
	mVelocity.x += vx;
	mVelocity.y += vy;
}