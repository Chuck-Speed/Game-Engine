#pragma once
#include "WorldState.h"

namespace Library
{
	class Sector final : public Attributed
	{
		RTTI_DECLARATIONS(Sector, Attributed)
	public:
		/**
		*@brief Constructor for Sectors.
		*/
		Sector();

		Sector(const Sector& rhs) = delete;

		Sector& operator=(const Sector& rhs) = delete;

		/**
		*@brief Destructor for Sectors.
		*/
		~Sector();

		/**
		*@brief Gets the name of this sector
		*@return std::string& A string reference representing the sector name
		*/
		const std::string& Name() const;

		/**
		*@brief Sets the name of this sector
		*@param name The new name for this sector
		*/
		void SetName(const std::string& name);

		/**
		*@brief Returns the datum reference that stores the contained entities for this sector
		*@return Datum* Reference to the container of entities
		*/
		Datum& Entities();

		/**
		*@brief Takes an entity class name and its instance name and utilizes the etity factory to make a new object. This object is adopted into the sector.
		*@param className Reference to a string holding the entities class name
		*@param name Reference to a string holding the instance name of the new entity
		*@return Entity* Reference to the newly created entity
		*/
		Entity* CreateEntity(const std::string& className, const std::string& name);

		/**
		*@brief Gets the world that this sector resides in
		*@return World* Reference to the parent world
		*/
		World* GetWorld();

		/**
		*@brief Sets the world that will contain this sector
		*@param parent Reference to a world that will become this sector's parent
		*/
		void SetWorld(World& parent);

		/**
		@brief Calls update on contained entities
		@param wState Reference to the current world state
		*/
		void Update(WorldState& wState);

	private:
		std::string mName;
		Datum& mEntities;
	};
}

