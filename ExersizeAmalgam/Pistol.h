#pragma once
#include "Weapon.h"

class Pistol : public Weapon {
private:
	int ammo;
	int damage;
public:
	Pistol();
	Pistol(int a, int d);

	void shoot();
	int getAmmo();
	int getDamage();
};