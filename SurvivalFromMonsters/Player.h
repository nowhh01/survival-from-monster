#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	sf::Sprite GetSprite();
	sf::FloatRect GetPosition();
	sf::Vector2f GetCenter();
	sf::Time GetLastHitTime();

	void Update(const float& elapsedTime, const sf::Vector2i& mousePosition);
	void Spawn(const sf::IntRect& arena, const sf::Vector2f& resolution, int tileSize);
	
	float GetRotation();
	int GetHealth();
	
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	void StopLeft();
	void StopRight();
	void StopUp();
	void StopDown();

	void UpgradeSpeed();
	void UpgradeHealth();
	void IncreaseHealthLevel(int amount);

	bool IsHit(const sf::Time& timeHit);
	void ResetPlayerStates();

private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;
	const int MARGIN = 10;

	sf::Sprite mSprite;
	sf::Texture mTexture;
	sf::IntRect mArena;
	sf::Vector2f mPosition;
	sf::Vector2f mResolution;
	sf::Time mLastHit;

	float mSpeed;
	int mHealth;
	int mTileSize;
	int mMaxHealth;

	bool mUpPressed;
	bool mDownPressed;
	bool mLeftPressed;
	bool mRightPressed;
};