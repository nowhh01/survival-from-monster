#include "pch.h"
#include "Engine.h"

Engine::Engine()
{
	mResolution.x = sf::VideoMode::getDesktopMode().width;
	mResolution.y = sf::VideoMode::getDesktopMode().height;

	mWindow.create(sf::VideoMode(mResolution.x, mResolution.y),
		"Survive From Monster", sf::Style::Fullscreen);

	mMainView.setSize(mResolution);
	mTextureBackground = ContentHolder::FindTexture("graphics/background_sheet.png");

	mWindow.setMouseCursorVisible(false);
	mSpriteCrosshair.setTexture(ContentHolder::FindTexture("graphics/crossair_black.png"));
	mSpriteCrosshair.setOrigin(16, 16);

	mHealthPickup = new Pickup(1);
	mAmmoPickup = new Pickup(2);

	mTextureGameOver = ContentHolder::FindTexture("graphics/start_background.png");
	mSpriteGameOver.setScale(2, 2.2f);
	mSpriteGameOver.setTexture(mTextureGameOver);
	mSpriteGameOver.setPosition(0, 0);

	hudView.reset(sf::FloatRect(0, 0, mResolution.x, mResolution.y));

	mSpriteAmmoIcon.setTexture(ContentHolder::FindTexture("graphics/ammo_icon.png"));
	mSpriteAmmoIcon.setPosition(100, 980);

	mFont.loadFromFile("fonts/square.ttf");

	loadTextSets(90, 400, 400, mFont, &mPausedText);
	mPausedText.setString("Press Enter \nto continue");

	loadTextSets(90, 250, 850, mFont, &mGameOverText);
	mGameOverText.setString("Press Enter to play");

	loadTextSets(60, 150, 250, mFont, &mLevelUpText);
	mLevelUpStream <<
		"1-  Increased rate of fire" << "\n2-  Increased clip size(next reload)"
		<< "\n3-  Increased max health" << "\n4-  Increased run speed"
		<< "\n5-  More and better health pickups" << "\n6-  More and better ammo pickups";
	mLevelUpText.setString(mLevelUpStream.str());

	loadTextSets(30, 100, 920, mFont, &mGunLoadHelp);
	mGunLoadHelp.setString("R key to load");
	
	loadTextSets(40, 200, 980, mFont, &mAmmoText);

	loadTextSets(40, 100, 0, mFont, &mScoreText);

	std::ifstream inputFile("gamedata/scores.txt");
	if (inputFile.is_open())
	{
		inputFile >> mHighScore;
		inputFile.close();
	}

	loadTextSets(40, 1300, 0, mFont, &mHighScoreText);
	mStringStream << "High Score:" << mHighScore;
	mHighScoreText.setString(mStringStream.str());

	loadTextSets(40, 1500, 980, mFont, &mMonstersRemainingText);
	mMonstersRemainingText.setString("Monsters: 100");

	loadTextSets(40, 1250, 980, mFont, &mWaveNumberText);
	mWaveNumberText.setString("Wave: 0");

	mHealthBar.setFillColor(sf::Color::Red);
	mHealthBar.setPosition(450, 980);

	loadSoundEffects("sound/hit.wav", &mHitBuffer, &mHit);
	loadSoundEffects("sound/splat.wav", &mSplatBuffer, &mSplat);
	loadSoundEffects("sound/shoot.wav", &mShootBuffer, &mShoot);
	loadSoundEffects("sound/reload.wav", &mReloadBuffer, &mReload);
	loadSoundEffects("sound/reload_failed.wav", &mReloadFailedBuffer, &mReloadFailed);
	loadSoundEffects("sound/powerup.wav", &mPowerupBuffer, &mPowerup);
	loadSoundEffects("sound/pickup.wav", &mPickupBuffer, &mPickup);
}

void Engine::Run()
{
	while (mWindow.isOpen())
	{
		input();
		update();
		draw();
	}
	// Delete the previously allocated memory (if it exists)
	delete[] mMonsters;
}

void Engine::loadTextSets(const float& characterSize, const float& positionX, 
	const float& positionY, const sf::Font& font, sf::Text* const outText)
{
	outText->setFillColor(sf::Color::White);
	outText->setCharacterSize(characterSize);
	outText->setPosition(positionX, positionY);
	outText->setFont(font);
}

void Engine::loadSoundEffects(const std::string& path, 
	sf::SoundBuffer* const outSoundBuffer, sf::Sound* const outSound)
{
	outSoundBuffer->loadFromFile(path);
	outSound->setBuffer(*outSoundBuffer);
}
