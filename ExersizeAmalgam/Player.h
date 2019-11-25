#pragma once
#include "Character.h"
#include "Enemy.h"
#include "ResourceIdentifiers.h"

class Player : public Character {
private:
	string name;
public:
	Player(Type type, const TextureHolder& textures);
	Player(string n, int h);
	string getName();
	bool canShoot(Character *c);
};