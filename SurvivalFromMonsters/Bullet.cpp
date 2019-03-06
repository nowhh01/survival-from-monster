#include "pch.h"
#include "Bullet.h"

Bullet::Bullet()
{
	mBulletShape.setSize(sf::Vector2f(2, 2));
}

void Bullet::Shoot(const float& startX, const float& startY, const float& targetX, 
	const float& targetY)
{
	mbInFlight = true;
	mPosition.x = startX;
	mPosition.y = startY;

	float gradient = (startX - targetX) / (startY - targetY);

	if (gradient < 0)
	{
		gradient *= -1;
	}

	float ratioXY = mBulletSpeed / (1 + gradient);

	mBulletDistanceY = ratioXY;
	mBulletDistanceX = ratioXY * gradient;

	if (targetX < startX)
	{
		mBulletDistanceX *= -1;
	}

	if (targetY < startY)
	{
		mBulletDistanceY *= -1;
	}

	float range = 500;
	mMinX = startX - range;
	mMaxX = startX + range;
	mMinY = startY - range;
	mMaxY = startY + range;

	mBulletShape.setPosition(mPosition);
}

void Bullet::Stop()
{
	mbInFlight = false;
}

bool Bullet::IsInFlight()
{
	return mbInFlight;
}

sf::FloatRect Bullet::GetPosition()
{
	return mBulletShape.getGlobalBounds();
}

sf::RectangleShape Bullet::GetShape()
{
	return mBulletShape;
}

void Bullet::Update(const float& elapsedTime)
{
	mPosition.x += mBulletDistanceX * elapsedTime;
	mPosition.y += mBulletDistanceY * elapsedTime;

	mBulletShape.setPosition(mPosition);

	if (mPosition.x < mMinX || mPosition.x > mMaxX 
		|| mPosition.y < mMinY || mPosition.y > mMaxY)
	{
		mbInFlight = false;
	}
}