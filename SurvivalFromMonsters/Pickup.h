#pragma once
#include <SFML/Graphics.hpp>

class Pickup
{
public:
	Pickup(int type);

	void Update(const float& elapsedTime);
	void SetArena(const sf::IntRect& arena);
	void Spawn();
	void Upgrade();

	sf::FloatRect GetPosition();
	sf::Sprite GetSprite();

	bool IsSpawned();
	int GotIt();

private:
	const int TILE_SIZE = 48;
	const int HEALTH_START_VALUE = 50;
	const int AMMO_START_VALUE = 12;
	const int START_WAIT_TIME = 10;
	const int START_SECONDS_TO_LIVE = 5;

	sf::Sprite mSprite;
	sf::IntRect mArena;

	float mSecondsSinceSpawn;
	float mSecondsSinceDeSpawn;
	float mSecondsToLive;
	float mSecondsToWait;
	int mValue;
	int mType;
	bool mSpawned;
};