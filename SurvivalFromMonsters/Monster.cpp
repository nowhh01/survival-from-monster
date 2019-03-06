#include <cstdlib>
#include <ctime>
#include "pch.h"
#include "Monster.h"
#include "ContentHolder.h"

void Monster::Spawn(const float& startX, const float& startY, int type, int seed)
{
	switch (type)
	{
	case 0:
		mSprite = sf::Sprite(ContentHolder::FindTexture("graphics/bee.png"));
		mSpeed = BEE_SPEED;
		mHealth = BEE_HEALTH;
		mOrigin = sf::Vector2f(35, 33);
		break;
	case 1:
		mSprite = sf::Sprite(ContentHolder::FindTexture("graphics/red_bug.png"));
		mSpeed = RED_BUG_SPEED;
		mHealth = RED_BUG_HEALTH;
		mOrigin = sf::Vector2f(26, 23);
		break;
	case 2:
		mSprite = sf::Sprite(ContentHolder::FindTexture("graphics/blue_bug.png"));
		mSpeed = BLUE_BUG_SPEED;
		mHealth = BLUE_BUG_HEALTH;
		mOrigin = sf::Vector2f(34, 25);
		break;
	default:
		break;
	}

	srand((int)time(0) * seed);
	float modifier = (rand() % MAX_VARRIANCE) + OFFSET;

	modifier /= 100;
	mSpeed *= modifier;

	mPosition.x = startX;
	mPosition.y = startY;

	mSprite.setOrigin(mOrigin);

	mSprite.setPosition(mPosition);
}

bool Monster::Hit()
{
	mHealth--;

	if (mHealth <= 0)
	{
		mbAlive = false;
		mSprite.setTexture(ContentHolder::FindTexture("graphics/blood.png"));

		return true;
	}

	return false;
}

bool Monster::IsAlive()
{
	return mbAlive;
}

sf::FloatRect Monster::GetPosition()
{
	return mSprite.getGlobalBounds();
}

sf::Sprite Monster::GetSprite()
{
	return mSprite;
}

void Monster::Update(const float& elapsedTime, const sf::Vector2f& playerLocation)
{
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	if (playerX > mPosition.x)
	{
		mPosition.x = mPosition.x + mSpeed * elapsedTime;
	}

	if (playerY > mPosition.y)
	{
		mPosition.y = mPosition.y + mSpeed * elapsedTime;
	}

	if (playerX < mPosition.x)
	{
		mPosition.x = mPosition.x - mSpeed * elapsedTime;
	}

	if (playerY < mPosition.y)
	{
		mPosition.y = mPosition.y - mSpeed * elapsedTime;
	}

	mSprite.setPosition(mPosition);

	float angle = (atan2(playerY - mPosition.y, playerX - mPosition.x) * 180) / 3.14;

	mSprite.setRotation(angle);
}