
#include "GrenadeLauncher.h"

//default no arguments constructor
GrenadeLauncher::GrenadeLauncher() {
	ammo = 2;
	damage = 10;
}
//constructor with arguments
GrenadeLauncher::GrenadeLauncher(int a, int d) {
	ammo = a;
	damage = d;
}
//shoot the gun
void GrenadeLauncher::shoot() {
	ammo -= 1;
}
//return amount of amo
int GrenadeLauncher::getAmmo() {
	return ammo;
}
//return the amount of damamge that can be dealt
int GrenadeLauncher::getDamage() {
	return damage;
}