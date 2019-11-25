
#include "Pistol.h"
//default constructor
Pistol::Pistol() {
	ammo = 10;
	damage = 2;
}
//constructor with values
Pistol::Pistol(int a, int d) {
	ammo = a;
	damage = d;
}
//shoot the gun
void Pistol::shoot() {
	ammo -= 1;
}
//return the amount of ammo
int Pistol::getAmmo() {
	return ammo;
}
//return the amount of damage that can be dealt
int Pistol::getDamage() {
	return damage;
}