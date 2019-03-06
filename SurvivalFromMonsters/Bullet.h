#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
private:
	sf::RectangleShape mBulletShape;
	sf::Vector2f mPosition;
	
	float mBulletSpeed = 1000;
	float mBulletDistanceX;
	float mBulletDistanceY;
	float mMaxX;
	float mMinX;
	float mMaxY;
	float mMinY;
	bool mbInFlight;

public:
	Bullet();

	void Update(const float& elapsedTime);
	void Shoot(const float& startX, const float& startY, const float& xTarget,
		const float& yTarget);
	bool IsInFlight();
	void Stop();
	
	sf::FloatRect GetPosition();
	sf::RectangleShape GetShape();
};