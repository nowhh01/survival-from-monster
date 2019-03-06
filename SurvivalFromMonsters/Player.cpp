#include "pch.h"
#include "Player.h"
#include "ContentHolder.h"

Player::Player()
{
	mSpeed = START_SPEED;
	mHealth = START_HEALTH;
	mMaxHealth = START_HEALTH;
	mSprite = sf::Sprite(ContentHolder::FindTexture("graphics/hitman1_machine.png"));
	mSprite.setOrigin(15, 21);
}

void Player::Spawn(const sf::IntRect& arena, const sf::Vector2f& resolution, 
	int tileSize)
{
	mPosition.x = arena.width / 2;
	mPosition.y = arena.height / 2;

	mArena.left = arena.left;
	mArena.width = arena.width;
	mArena.top = arena.top;
	mArena.height = arena.height;

	mTileSize = tileSize;

	mResolution.x = resolution.x;

	mResolution.y = resolution.y;
}

void Player::ResetPlayerStates()
{
	mSpeed = START_SPEED;
	mHealth = START_HEALTH;
	mMaxHealth = START_HEALTH;
}

sf::Time Player::GetLastHitTime()
{
	return mLastHit;
}

bool Player::IsHit(const sf::Time& timeHit)
{
	if (timeHit.asMilliseconds() - mLastHit.asMilliseconds() > 200)
	{
		mLastHit = timeHit;
		mHealth -= 10;
		return true;
	}
	else
	{
		return false;
	}
}

sf::FloatRect Player::GetPosition()
{
	return mSprite.getGlobalBounds();
}

sf::Vector2f Player::GetCenter()
{
	return mPosition;
}

float Player::GetRotation()
{
	return mSprite.getRotation();
}

sf::Sprite Player::GetSprite()
{
	return mSprite;
}

int Player::GetHealth()
{
	return mHealth;
}

void Player::MoveLeft()
{
	mLeftPressed = true;
}

void Player::MoveRight()
{
	mRightPressed = true;
}

void Player::MoveUp()
{
	mUpPressed = true;
}

void Player::MoveDown()
{
	mDownPressed = true;
}

void Player::StopLeft()
{
	mLeftPressed = false;
}

void Player::StopRight()
{
	mRightPressed = false;
}

void Player::StopUp()
{
	mUpPressed = false;
}

void Player::StopDown()
{
	mDownPressed = false;
}

void Player::Update(const float& elapsedTime, const sf::Vector2i& mousePosition)
{
	if (mUpPressed)
	{
		mPosition.y -= mSpeed * elapsedTime;
	}

	if (mDownPressed)
	{
		mPosition.y += mSpeed * elapsedTime;
	}

	if (mRightPressed)
	{
		mPosition.x += mSpeed * elapsedTime;
	}

	if (mLeftPressed)
	{
		mPosition.x -= mSpeed * elapsedTime;
	}

	mSprite.setPosition(mPosition);

	if (mPosition.x > mArena.width - mTileSize - MARGIN)
	{
		mPosition.x = mArena.width - mTileSize - MARGIN;
	}

	if (mPosition.x < mArena.left + mTileSize + MARGIN)
	{
		mPosition.x = mArena.left + mTileSize + MARGIN;
	}

	if (mPosition.y > mArena.height - mTileSize - MARGIN)
	{
		mPosition.y = mArena.height - mTileSize - MARGIN;
	}

	if (mPosition.y < mArena.top + mTileSize + MARGIN)
	{
		mPosition.y = mArena.top + mTileSize + MARGIN;
	}

	float angle = (atan2(mousePosition.y - mResolution.y / 2, mousePosition.x - mResolution.x / 2)
		* 180) / 3.141;

	mSprite.setRotation(angle);
}

void Player::UpgradeSpeed()
{
	mSpeed += (START_SPEED * .2);
}

void Player::UpgradeHealth()
{
	mMaxHealth += (START_HEALTH * .2);
}

void Player::IncreaseHealthLevel(int amount)
{
	mHealth += amount;

	if (mHealth > mMaxHealth)
	{
		mHealth = mMaxHealth;
	}
}