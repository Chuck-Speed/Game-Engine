#pragma once

#include "Action.h"

namespace Library
{
	class ActionList : public Action
	{
		RTTI_DECLARATIONS(ActionList, Action)
	public:
		/*
		*@brief Constructor for ActionList
		*/
		ActionList();

		/*
		*@brief Destructor for ActionList
		*/
		virtual ~ActionList() = default;

		/**
		*@brief Returns the datum reference that stores the contained actions for this entity
		*@return Datum* Reference to the container of actions
		*/
		Datum& Actions();

		/**
		*@brief Takes an action class name and its instance name and utilizes the action factory to make a new object. This object is adopted into the action list.
		*@param className Reference to a string holding the actions class name
		*@param name Reference to a string holding the instance name of the new actions
		*@return Entity* Reference to the newly created axtions
		*/
		Action* CreateAction(const std::string& className, const std::string& instanceName);

		/**
		@brief Calls update on contained actions
		@param wState Reference to the current world state
		*/
		virtual void Update(WorldState& wState) override;

	private:
		Datum& mActionEntries;
	};

	ActionFactory(ActionList)
}