#pragma once

#include "Event.h"

namespace Library 
{
	class World final : public Attributed
	{
		RTTI_DECLARATIONS(World, Attributed)
	public:
		/**
		*@brief Constructor for World.
		*/
		World();

		World(const World& rhs) = delete;

		World& operator=(const World& rhs) = delete;

		/**
		*@brief Destructor for World.
		*/
		~World();

		/**
		*@brief Gets the name of this world
		*@return std::string& A string reference representing the world name
		*/
		const std::string& Name() const;

		/**
		*@brief Sets the name of this world
		*@param name The new name for this world
		*/
		void SetName(const std::string& name);

		/**
		*@brief Returns the datum reference that stores the contained sectors for this world
		*@return Datum* Reference to the container of sectors
		*/
		Datum& Sectors();

		/**
		*@brief Instantiates a new sector and adopts it into the world.
		*@param name Reference to a string holding the instance name of the new sector
		*@return Sector* Reference to the newly created sector
		*/
		Sector* CreateSector(const std::string& instanceName);

		/**
		*@brief Gets the current world state
		*@return WorldState*
		*/
		WorldState* GetWorldState();

		EventQueue& GetEventQueue();

		/**
		@brief Calls update on contained sectors
		@param wState Reference to the current world state
		*/
		void Update();

	private:
		std::string mName;
		Datum& mSectors;
		WorldState mState;
		EventQueue mEventQueue;
		GameClock mGameClock;
	};
}
