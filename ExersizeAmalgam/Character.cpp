
#include "Character.h"
#include "ResourceHolder.h"
#include "Utility.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

Textures::ID toTextureID(Character::Type type)
{
	switch (type)
	{
	case Character::Player:
		return Textures::Player;

	case Character::Enemy:
		return Textures::Enemy;
	}
	return Textures::Player;
}
//////////////////////
Character::Character(){}
//////////////////////
Character::Character(Type type, const TextureHolder& textures)
	: mType(type)
	, mSprite(textures.get(toTextureID(type)))
{
	centerOrigin(mSprite);
	setHealth(20);
	inventory[0] = new Pistol;
	inventory[1] = new GrenadeLauncher;
	equip(0);
}


//set character health
void Character::setHealth(int h) {
	health = h;
}
//function for character to shoot another
void Character::shoot(Character* target) {
	fire();
	target->setHealth(target->getHealth() - inventory[equippedIndex]->getDamage());
}
//checks to see if character is dead
bool Character::isDead() {
	if (getHealth() <= 0) {

		return true;
	}
	else return false;
}
int Character::getHealth()
{
	return health;
}

void Character::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

void Character::setType(Type type, const TextureHolder& textures) {
	mType = type;
	mSprite.setTexture(textures.get(toTextureID(type)));
}
unsigned int Character::getCategory() const
{
	switch(mType)
		{
	case Player:
			return Category::Player;

		default:
			return Category::Enemy;
		}
	
}