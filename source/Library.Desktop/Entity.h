#pragma once
#include "Sector.h"
#include "WorldState.h"

namespace Library
{
	class Entity : public Attributed
	{
		RTTI_DECLARATIONS(Entity, Attributed)
	public:

		/**
		*@brief Constructor for Entities.
		*/
		Entity();

		Entity(const Entity& rhs) = delete;

		Entity& operator=(const Entity& rhs) = delete;

		/**
		*@brief Destructor for Entities.
		*/
		~Entity();

		/**
		*@brief Gets the name of this entity
		*@return std::string& A string reference representing the entity name
		*/
		const std::string& Name() const;

		/**
		*@brief Sets the name of this entity
		*@param name The new name for this entity
		*/
		void SetName(const std::string& name);

		/**
		*@brief Returns the datum reference that stores the contained actions for this entity
		*@return Datum* Reference to the container of actions
		*/
		Datum& Actions();

		/**
		*@brief Takes an entity class name and its instance name and utilizes the action factory to make a new object. This object is adopted into the entity.
		*@param className Reference to a string holding the actions class name
		*@param name Reference to a string holding the instance name of the new actions
		*@return Entity* Reference to the newly created axtions
		*/
		Action* CreateAction(const std::string& className, const std::string& instanceName);

		/**
		*@brief Gets the sector that this entity resides in
		*@return Sector* Reference to the parent sector
		*/
		Sector* GetSector();

		/**
		*@brief Sets the sector that will contain this entity
		*@param parent Reference to a sector that will become this entities parent
		*/
		void SetSector(Sector& parent);

		/**
		*@brief Update entity reference in the current world state
		*@param wState Reference to the current world state
		*/
		virtual void Update(WorldState& wState);

	private:
		std::string mName;
		Datum& mActions;
	};
}