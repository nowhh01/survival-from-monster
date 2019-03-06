#include "pch.h"
#include "Engine.h"

void Engine::update()
{
	if (meState == eState::Playing)
	{
		sf::Time dt = mClock.restart();
		mGameTimeTotal += dt;
		float dtAsSeconds = dt.asSeconds();

		mMouseScreenPosition = sf::Mouse::getPosition();

		mMouseWorldPosition = 
			mWindow.mapPixelToCoords(sf::Mouse::getPosition(), mMainView);

		mSpriteCrosshair.setPosition(mMouseWorldPosition);

		mPlayer.Update(dtAsSeconds, sf::Mouse::getPosition());

		sf::Vector2f playerPosition(mPlayer.GetCenter());

		mMainView.setCenter(mPlayer.GetCenter());

		for (int i = 0; i < mNumberOfMonsters; i++)
		{
			if (mMonsters[i].IsAlive())
			{
				mMonsters[i].Update(dt.asSeconds(), playerPosition);
			}
		}

		for (int i = 0; i < 100; i++)
		{
			if (mBullets[i].IsInFlight())
			{
				mBullets[i].Update(dtAsSeconds);
			}
		}

		mHealthPickup->Update(dtAsSeconds);
		mAmmoPickup->Update(dtAsSeconds);

		Bullet* bullet;
		Monster* monster;

		for (int i = 0; i < 100; i++)
		{
			bullet = &mBullets[i];
			
			for (int j = 0; j < mNumberOfMonsters; j++)
			{
				monster = &mMonsters[j];
				
				if (bullet->IsInFlight() && monster->IsAlive())
				{
					if (bullet->GetPosition().intersects(monster->GetPosition()))
					{
						bullet->Stop();

						if (monster->Hit())
						{
							mScore += 10;
							if (mScore >= mHighScore)
							{
								mHighScore = mScore;
							}

							mNumberOfMonstersAlive--;

							if (mNumberOfMonstersAlive == 0)
							{
								meState = eState::LevelingUp;
							}

							mSplat.play();
						}
					}
				}
			}
		}
		
		for (int i = 0; i < mNumberOfMonsters; i++)
		{
			if (mPlayer.GetPosition().intersects(mMonsters[i].GetPosition()) 
				&& mMonsters[i].IsAlive())
			{
				if (mPlayer.IsHit(mGameTimeTotal))
				{
					mHit.play();
				}

				if (mPlayer.GetHealth() <= 0)
				{
					meState = eState::GameOver;
					std::ofstream outputFile("gamedata/scores.txt");
					outputFile << mHighScore;
					outputFile.close();
				}
			}
		}

		if (mPlayer.GetPosition().intersects(mHealthPickup->GetPosition()) 
			&& mHealthPickup->IsSpawned())
		{
			mPlayer.IncreaseHealthLevel(mHealthPickup->GotIt());
			mPickup.play();
		}

		if (mPlayer.GetPosition().intersects(mAmmoPickup->GetPosition()) 
			&& mAmmoPickup->IsSpawned())
		{
			mBulletsSpare += mAmmoPickup->GotIt();
			mReload.play();
		}

		mHealthBar.setSize(sf::Vector2f(mPlayer.GetHealth() * 3, 70));

		mFramesSinceLastHudUpdate++;

		if (mFramesSinceLastHudUpdate > mFpsMeasurementFrameInterval)
		{
			std::stringstream ssAmmo;
			std::stringstream ssScore;
			std::stringstream ssHiScore;
			std::stringstream ssWave;
			std::stringstream ssMonstersAlive;

			ssAmmo << mBulletsInClip << "/" << mBulletsSpare;
			mAmmoText.setString(ssAmmo.str());

			ssScore << "Score:" << mScore;
			mScoreText.setString(ssScore.str());

			ssHiScore << "Hi Score:" << mHighScore;
			mHighScoreText.setString(ssHiScore.str());

			ssWave << "Wave:" << mWave;
			mWaveNumberText.setString(ssWave.str());

			ssMonstersAlive << "Monsters:" << mNumberOfMonstersAlive;
			mMonstersRemainingText.setString(ssMonstersAlive.str());

			mFramesSinceLastHudUpdate = 0;
		}
	}
}