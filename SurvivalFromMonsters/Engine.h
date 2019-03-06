#pragma once
#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "ContentHolder.h"
#include "Bullet.h"
#include "Pickup.h"
#include "Monster.h"

class Engine
{
public:
	Engine();

	void Run();
	int CreateBackground(const sf::IntRect& arena, 
		sf::VertexArray* const outVertexes);
	Monster* CreateMonsters(int numMonsters, const sf::IntRect& arena);

private:
	enum class eState
	{
		Paused,
		LevelingUp,
		GameOver,
		Playing
	};

	const int TILE_SIZE = 48;

	eState meState = eState::GameOver;

	Monster* mMonsters = nullptr;
	Pickup* mHealthPickup;
	Pickup* mAmmoPickup;
	Bullet mBullets[100];

	ContentHolder mContentHolder;
	Player mPlayer;

	sf::RenderWindow mWindow;
	sf::View mMainView;
	sf::View hudView;
	sf::Sprite mSpriteCrosshair;
	sf::Sprite mSpriteGameOver;
	sf::Sprite mSpriteAmmoIcon;
	sf::Texture mTextureBackground;
	sf::Texture mTextureGameOver;
	
	sf::Sound mHit;
	sf::Sound mSplat;
	sf::Sound mShoot;
	sf::Sound mReload;
	sf::Sound mReloadFailed;
	sf::Sound mPowerup;
	sf::Sound mPickup;

	sf::SoundBuffer mHitBuffer;
	sf::SoundBuffer mSplatBuffer;
	sf::SoundBuffer mShootBuffer;
	sf::SoundBuffer mReloadBuffer;
	sf::SoundBuffer mReloadFailedBuffer;
	sf::SoundBuffer mPowerupBuffer;
	sf::SoundBuffer mPickupBuffer;
	
	sf::Font mFont;
	std::stringstream mLevelUpStream;
	std::stringstream mStringStream;
	sf::Text mPausedText;
	sf::Text mGameOverText;
	sf::Text mLevelUpText;
	sf::Text mGunLoadHelp;
	sf::Text mAmmoText;
	sf::Text mScoreText;
	sf::Text mWaveNumberText;
	sf::Text mHighScoreText;
	sf::Text mMonstersRemainingText;

	sf::Clock mClock;
	sf::Time mTimeSinceLastUpdate;
	sf::Time mGameTimeTotal;
	sf::Time mLastPressed;

	sf::VertexArray mBackground;
	sf::RectangleShape mHealthBar;
	sf::Vector2f mResolution;
	sf::Vector2f mMouseWorldPosition;
	sf::Vector2i mMouseScreenPosition;
	sf::IntRect mArena;

	float mFireRate = 1;
	int mNumberOfMonsters;
	int mNumberOfMonstersAlive;
	int mCurrentBullet;
	int mBulletsSpare = 24;
	int mBulletsInClip = 6;
	int mClipSize = 6;
	int mScore;
	int mHighScore;
	int mWave;
	int mFramesSinceLastHudUpdate;
	int mFpsMeasurementFrameInterval = 100;

	void loadTextSets(const float& characterSize, const float& positionX, 
		const float& positionY, const sf::Font& font, sf::Text* outText);
	void loadSoundEffects(const std::string& path, 
		sf::SoundBuffer* const outSoundBuffer, sf::Sound* const outSound);

	void input();
	void update();
	void draw();
};