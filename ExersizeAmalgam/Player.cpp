
#include "Player.h"
struct PlayerMover
{
	PlayerMover(float vx, float vy)
		: velocity(vx, vy)
	{}
	void operator() (Character& character, sf::Time)const)
	{
	character.accelerate(velocity * character.getMaxSpeed());
	}

	sf::Vector2f velocity;
};

