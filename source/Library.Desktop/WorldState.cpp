#include "pch.h"


namespace Library 
{
	WorldState::WorldState() :
		mWorld(nullptr), mSector(nullptr), mEntity(nullptr), mAction(nullptr), mGameTime()
	{
	}

	WorldState::~WorldState()
	{
	}

	GameTime& WorldState::GetGameTime()
	{
		return mGameTime;
	}

	void WorldState::SetGameTime(GameTime& time)
	{
		mGameTime = time;
	}
}
