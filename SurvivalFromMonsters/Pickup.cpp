#include "pch.h"
#include "Pickup.h"
#include "ContentHolder.h"

Pickup::Pickup(int type)
{
	mType = type;

	if (mType == 1)
	{
		mSprite = sf::Sprite(ContentHolder::FindTexture("graphics/health_pickup.png"));
		
		mValue = HEALTH_START_VALUE;
	}
	else
	{
		mSprite = sf::Sprite(ContentHolder::FindTexture("graphics/ammo_pickup.png"));

		mValue = AMMO_START_VALUE;
	}

	mSprite.setOrigin(17, 17);

	mSecondsToLive = START_SECONDS_TO_LIVE;
	mSecondsToWait = START_WAIT_TIME;
}

void Pickup::SetArena(const sf::IntRect& arena)
{
	mArena.left = arena.left + TILE_SIZE;
	mArena.width = arena.width - TILE_SIZE;
	mArena.top = arena.top + TILE_SIZE;
	mArena.height = arena.height - TILE_SIZE;

	Spawn();
}

void Pickup::Spawn()
{
	srand((int)time(0) / mType);
	int x = (rand() % (mArena.width - TILE_SIZE)) + TILE_SIZE;
	srand((int)time(0) * mType);
	int y = (rand() % (mArena.height - TILE_SIZE)) + TILE_SIZE;

	mSecondsSinceSpawn = 0;
	mSpawned = true;

	mSprite.setPosition(x, y);
}

sf::FloatRect Pickup::GetPosition()
{
	return mSprite.getGlobalBounds();
}

sf::Sprite Pickup::GetSprite()
{
	return mSprite;
}

bool Pickup::IsSpawned()
{
	return mSpawned;
}

int Pickup::GotIt()
{
	mSpawned = false;
	mSecondsSinceDeSpawn = 0;
	
	return mValue;
}

void Pickup::Update(const float& elapsedTime)
{
	if (mSpawned)
	{
		mSecondsSinceSpawn += elapsedTime;
	}
	else
	{
		mSecondsSinceDeSpawn += elapsedTime;
	}

	if (mSecondsSinceSpawn > mSecondsToLive && mSpawned)
	{
		mSpawned = false;
		mSecondsSinceDeSpawn = 0;
	}

	if (mSecondsSinceDeSpawn > mSecondsToWait && !mSpawned)
	{
		Spawn();
	}
}

void Pickup::Upgrade()
{
	if (mType == 1)
	{
		mValue += (HEALTH_START_VALUE * .5);
	}
	else
	{
		mValue += (AMMO_START_VALUE * .5);
	}

	mSecondsToLive += (START_SECONDS_TO_LIVE / 10);
	mSecondsToWait -= (START_WAIT_TIME / 10);
}