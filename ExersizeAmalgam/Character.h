#pragma once
#include "Actor.h"
#include "Weapon.h"
#include "Pistol.h"
#include "GrenadeLauncher.h"
#include <vector>
#include <string.h>
#include <iostream>

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

#include <SFML/Graphics/Sprite.hpp>

using namespace std;
class Character : public Actor {
public:
	enum Type {
		Player,
		Enemy,
	};
private:
	Type mType;
	sf::Sprite mSprite;
	int health;

protected:
	//funtions used to shoot weapon/ set inventory
	Weapon *inventory[2];
	int equippedIndex = 0;

	void fire() const {
		inventory[equippedIndex]->shoot();
	}
public:
	Character();
	Character(Type type, const TextureHolder& textures);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	//funtions used by characters
	virtual  ~Character() {}
	void equip(int index) { equippedIndex = index; }
	void setType(Type type, const TextureHolder& textures);
	void setName(string n);
	void setHealth(int h);
	int getHealth();
	void shoot(Character *target);
	bool isDead();
	string getName();
};