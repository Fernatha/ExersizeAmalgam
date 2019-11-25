#include "PickUp.h"
#include "ResourceHolder.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

Textures::ID toTextureID(PickUp::Type type)
{
	switch (type)
	{
	case PickUp::Pistol:
		return Textures::Pistol;

	case PickUp::GrenadeLauncher:
		return Textures::GrenadeLauncher;

	}
}
	PickUp::PickUp(Type type, const TextureHolder& textures)
		: mType(type)
		, mSprite(textures.get(toTextureID(type)))
	{
		sf::FloatRect bounds = mSprite.getLocalBounds();
		mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	}

	void PickUp::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(mSprite, states);
	}