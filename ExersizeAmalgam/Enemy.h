#pragma once
#include "Character.h"
#include "Player.h"
class Enemy : public Character {
public:
	Enemy(Type type, const TextureHolder& textures);

};