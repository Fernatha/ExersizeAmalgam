#include "World.h"

#include <SFML/Graphics/RenderWindow.hpp>


World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mTextures()
	, mSceneGraph()
	, mSceneLayers()
	, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f)
	, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
	, mScrollSpeed(-50.f)
	, mPlayerModel(nullptr)
{
	loadTextures();
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
	// Scroll the world
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());

	// Move the player sidewards (plane scouts follow the main aircraft)
	sf::Vector2f position = mPlayerModel->getPosition();
	sf::Vector2f velocity = mPlayerModel->getVelocity();

	// If player touches borders, flip its X velocity
	if (position.x <= mWorldBounds.left + 150.f
		|| position.x >= mWorldBounds.left + mWorldBounds.width - 150.f)
	{
		velocity.x = -velocity.x;
		mPlayerModel->setVelocity(velocity);
	}

	// Apply movements
	mSceneGraph.update(dt);
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

void World::loadTextures()
{
	mTextures.load(Textures::Player, "Media/Textures/Eagle.png");
	mTextures.load(Textures::Enemy, "Media/Textures/Raptor.png");
	mTextures.load(Textures::Desert, "Media/Textures/Desert.png");
	mTextures.load(Textures::Pistol, "Media/Textures/Pistol.png");
	mTextures.load(Textures::GrenadeLauncher, "Media/Textures/GrenadeLauncher.png");
}

void World::buildScene()
{
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	// Prepare the tiled background
	sf::Texture& texture = mTextures.get(Textures::Desert);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	// Add the background sprite to the scene
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	// Add player's aircraft
	std::unique_ptr<Character> leader(new Character(Character::Player, mTextures));
	mPlayerModel = leader.get();
	mPlayerModel->setPosition(mSpawnPosition);
	mPlayerModel->setVelocity(40.f, mScrollSpeed);
	mSceneLayers[Air]->attachChild(std::move(leader));

	// Add two escorting aircrafts, placed relatively to the main plane
	std::unique_ptr<Character> leftEscort(new Character(Character::Enemy, mTextures));
	leftEscort->setPosition(-80.f, 50.f);
	mPlayerModel->attachChild(std::move(leftEscort));

	std::unique_ptr<Character> rightEscort(new Character(Character::Enemy, mTextures));
	rightEscort->setPosition(80.f, 50.f);
	mPlayerModel->attachChild(std::move(rightEscort));

	std::unique_ptr<PickUp> rightPick(new PickUp(PickUp::Pistol, mTextures));
	rightPick->setPosition(120.f, 100.f);
	mPlayerModel->attachChild(std::move(rightPick));

	std::unique_ptr<PickUp> LeftPick(new PickUp(PickUp::GrenadeLauncher, mTextures));
	LeftPick->setPosition(-120.f, 100.f);
	mPlayerModel->attachChild(std::move(LeftPick));
}
