#pragma once
#include "Actor.h"

//pure virtual class
class Weapon {

public:
	//virtual funtions will be overriden in derived classes
	virtual void shoot() = 0;
	virtual int getAmmo() = 0;
	virtual int getDamage() = 0;
};