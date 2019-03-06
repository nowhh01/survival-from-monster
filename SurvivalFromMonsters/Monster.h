#pragma once
#include <SFML/Graphics.hpp>

class Monster
{
public:
	void Update(const float& elapsedTime, const sf::Vector2f& playerLocation);
	void Spawn(const float& startX, const float& startY, int type, int seed);
	bool IsAlive();
	bool Hit();

	sf::FloatRect GetPosition();
	sf::Sprite GetSprite();

private:
	const float BEE_SPEED = 70;
	const float RED_BUG_SPEED = 90;
	const float BLUE_BUG_SPEED = 50;

	const float BEE_HEALTH = 5;
	const float RED_BUG_HEALTH = 1;
	const float BLUE_BUG_HEALTH = 3;

	const int MAX_VARRIANCE = 30;
	const int OFFSET = 101 - MAX_VARRIANCE;
	
	sf::Sprite mSprite;
	sf::Vector2f mPosition;
	sf::Vector2f mOrigin;

	float mSpeed;
	float mHealth;
	bool mbAlive;
};