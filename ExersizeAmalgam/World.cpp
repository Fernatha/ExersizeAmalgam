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
	// Scroll the world, reset player velocity
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
	mPlayerModel->setVelocity(0.f, 0.f);

	// Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);
	adaptPlayerVelocity();

	// Regular update step, adapt position (correct if outside view)
	mSceneGraph.update(dt);
	adaptPlayerPosition();
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
CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}
void World::adaptPlayerPosition()
{
	// Keep player's position inside the screen bounds, at least borderDistance units from the border
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayerModel->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mPlayerModel->setPosition(position);
}

void World::adaptPlayerVelocity()
{
	sf::Vector2f velocity = mPlayerModel->getVelocity();

	// If moving diagonally, reduce velocity (to have always same velocity)
	if (velocity.x != 0.f && velocity.y != 0.f)
		mPlayerModel->setVelocity(velocity / std::sqrt(2.f));

	// Add scrolling velocity
	mPlayerModel->accelerate(0.f, mScrollSpeed);
}