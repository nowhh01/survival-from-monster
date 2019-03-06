#include "pch.h"
#include "Engine.h"

void Engine::input()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Return && meState == eState::Playing)
			{
				meState = eState::Paused;
			}

			else if (event.key.code == sf::Keyboard::Return 
				&& meState == eState::Paused)
			{
				meState = eState::Playing;
				mClock.restart();
			}

			else if (event.key.code == sf::Keyboard::Return 
				&& meState == eState::GameOver)
			{
				meState = eState::LevelingUp;
				mWave = 0;
				mScore = 0;

				mCurrentBullet = 0;
				mBulletsSpare = 24;
				mBulletsInClip = 6;
				mClipSize = 6;
				mFireRate = 1;

				mPlayer.ResetPlayerStates();
			}

			if (meState == eState::Playing)
			{
				if (event.key.code == sf::Keyboard::R)
				{
					if (mBulletsSpare >= mClipSize)
					{
						mBulletsInClip = mClipSize;
						mBulletsSpare -= mClipSize;
						mReload.play();
					}
					else if (mBulletsSpare > 0)
					{
						mBulletsInClip = mBulletsSpare;
						mBulletsSpare = 0;
						mReload.play();
					}
					else
					{
						mReloadFailed.play();
					}
				}
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		mWindow.close();
	}

	if (meState == eState::Playing)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			mPlayer.MoveUp();
		}
		else
		{
			mPlayer.StopUp();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			mPlayer.MoveDown();
		}
		else
		{
			mPlayer.StopDown();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			mPlayer.MoveLeft();
		}
		else
		{
			mPlayer.StopLeft();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			mPlayer.MoveRight();
		}
		else
		{
			mPlayer.StopRight();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (mGameTimeTotal.asMilliseconds() - mLastPressed.asMilliseconds() 
				> 1000 / mFireRate && mBulletsInClip > 0)
			{
				mBullets[mCurrentBullet].Shoot(mPlayer.GetCenter().x, 
					mPlayer.GetCenter().y, mMouseWorldPosition.x, 
					mMouseWorldPosition.y);

				mCurrentBullet++;

				if (mCurrentBullet > 99)
				{
					mCurrentBullet = 0;
				}

				mLastPressed = mGameTimeTotal;
				mShoot.play();
				mBulletsInClip--;
			}
		}
	}

	if (meState == eState::LevelingUp)
	{
		if (event.key.code == sf::Keyboard::Num1)
		{
			mFireRate++;
			meState = eState::Playing;
		}

		if (event.key.code == sf::Keyboard::Num2)
		{
			mClipSize += mClipSize;
			meState = eState::Playing;
		}

		if (event.key.code == sf::Keyboard::Num3)
		{
			mPlayer.UpgradeHealth();
			meState = eState::Playing;
		}

		if (event.key.code == sf::Keyboard::Num4)
		{
			mPlayer.UpgradeSpeed();
			meState = eState::Playing;
		}

		if (event.key.code == sf::Keyboard::Num5)
		{
			mHealthPickup->Upgrade();
			meState = eState::Playing;
		}

		if (event.key.code == sf::Keyboard::Num6)
		{
			mAmmoPickup->Upgrade();
			meState = eState::Playing;
		}

		if (meState == eState::Playing)
		{
			mWave++;
			mArena.width = 960;
			mArena.height = 960;
			mArena.left = 0;
			mArena.top = 0;

			int tileSize = CreateBackground(mArena, &mBackground);

			mPlayer.Spawn(mArena, mResolution, tileSize);

			mHealthPickup->SetArena(mArena);
			mAmmoPickup->SetArena(mArena);

			mNumberOfMonsters = 5 * mWave;

			// Delete the previously allocated memory (if it exists)
			delete[] mMonsters;

			mMonsters = CreateMonsters(mNumberOfMonsters, mArena);
			mNumberOfMonstersAlive = mNumberOfMonsters;

			mPowerup.play();
			mClock.restart();
		}
	}
}