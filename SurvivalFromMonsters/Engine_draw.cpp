#include "pch.h"
#include "Engine.h"

void Engine::draw()
{
	mWindow.clear();

	mWindow.setView(mMainView);

	mWindow.draw(mBackground, &mTextureBackground);
	
	if (mAmmoPickup->IsSpawned())
	{
		mWindow.draw(mAmmoPickup->GetSprite());
	}

	if (mHealthPickup->IsSpawned())
	{
		mWindow.draw(mHealthPickup->GetSprite());
	}

	for (int i = 0; i < mNumberOfMonsters; i++)
	{
		mWindow.draw(mMonsters[i].GetSprite());
	}

	for (int i = 0; i < 100; i++)
	{
		if (mBullets[i].IsInFlight())
		{
			mWindow.draw(mBullets[i].GetShape());
		}
	}

	mWindow.draw(mPlayer.GetSprite());

	mWindow.draw(mSpriteCrosshair);

	mWindow.setView(hudView);

	mWindow.draw(mSpriteAmmoIcon);
	mWindow.draw(mGunLoadHelp);
	mWindow.draw(mAmmoText);
	mWindow.draw(mScoreText);
	mWindow.draw(mHighScoreText);
	mWindow.draw(mHealthBar);
	mWindow.draw(mWaveNumberText);
	mWindow.draw(mMonstersRemainingText);


	if (meState == eState::LevelingUp)
	{
		mWindow.draw(mSpriteGameOver);
		mWindow.draw(mLevelUpText);
	}

	if (meState == eState::Paused)
	{
		mWindow.draw(mPausedText);
	}

	if (meState == eState::GameOver)
	{
		mWindow.draw(mSpriteGameOver);
		mWindow.draw(mGameOverText);
		mWindow.draw(mScoreText);
		mWindow.draw(mHighScoreText);
	}

	mWindow.display();
}