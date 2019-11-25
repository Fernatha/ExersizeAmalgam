#pragma once
#include "weapon.h"

class GrenadeLauncher : public Weapon {
private:
	int ammo;
	int damage;
public:
	GrenadeLauncher();
	GrenadeLauncher(int a, int d);

	void shoot();
	int getAmmo();
	int getDamage();
};