#include "pch.h"


namespace Library
{
	RTTI_DEFINITIONS(World)

	World::World() :
		mSectors(AddNestedScope("Sectors")), mState(WorldState()), mGameClock(), mEventQueue()
	{
		AddExternalAttribute("Name", &mName, 1U);
		mState.mWorld = this;
	}


	World::~World()
	{
	}

	const std::string& World::Name() const
	{
		return mName;
	}

	void World::SetName(const std::string & name)
	{
		mName = name;
	}

	Datum& World::Sectors()
	{
		return mSectors;
	}

	Sector* World::CreateSector(const std::string& instanceName)
	{
		Sector* s = new Sector();
		s->SetName(instanceName);
		s->SetWorld(*this);
		return s;
	}

	WorldState* World::GetWorldState()
	{
		return &mState;
	}

	EventQueue& World::GetEventQueue()
	{
		return mEventQueue;
	}

	void World::Update()
	{
		mGameClock.UpdateGameTime(mState.GetGameTime());
		mEventQueue.Update(mState.GetGameTime());
		Datum& sectors = Sectors();
		for (uint32_t i = 0; i < sectors.Size(); ++i)
		{
			Sector* currentSector = sectors.Get<Scope*>(i)->As<Sector>();
			assert(currentSector != nullptr);
			currentSector->Update(mState);
		}
	}
}