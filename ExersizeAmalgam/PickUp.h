#pragma once
#include "Actor.h"
#include "ResourceIdentifiers.h"

#include <SFML/Graphics/Sprite.hpp>

class PickUp : public Actor
{
public:
	enum Type
	{
		Pistol,
		GrenadeLauncher,
	};

public:
	PickUp(Type type, const TextureHolder& textures);

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Type mType;
	sf::Sprite mSprite;
};