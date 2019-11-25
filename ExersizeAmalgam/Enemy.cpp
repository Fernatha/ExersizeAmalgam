
#include "Enemy.h"

//default constructor
Enemy::Enemy(Type type, const TextureHolder& textures)
{
	setType(type, textures);
	Pistol p(10, 2);
	inventory[0] = new Pistol;
	inventory[1] = new GrenadeLauncher;
	equip(0);
}
