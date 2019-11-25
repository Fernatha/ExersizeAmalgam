
#include "Player.h"
//default constructor
Player::Player(Type type, const TextureHolder& textures) {
	setType(type ,textures);
	name = "Ally";
	setHealth(20);
	inventory[0] = new Pistol;
	inventory[1] = new GrenadeLauncher;
	equip(0);
}
