#pragma once
#include "ActionList.h"

namespace Library
{
	class ActionListIf final : public Action
	{
		RTTI_DECLARATIONS(ActionListIf, Action)
	public:
		/**
		@brief Constructor for ActionListIf
		*/
		ActionListIf();

		/**
		*@brief Destructor for ActionListIf
		*/
		virtual ~ActionListIf() = default;

		/**
		*@brief Creates an action that will be adopted into an actionlist for a "then" conditional block
		*@param className Name of the action class to be instantiated
		*@param instanceName Name of the action instance
		*@return Action* Reference to the newly created action object
		*/
		Action* CreateThenAction(const std::string& className, const std::string& instanceName);

		/**
		*@brief Creates an action that will be adopted into an actionlist for a "else" conditional block
		*@param className Name of the action class to be instantiated
		*@param instanceName Name of the action instance
		*@return Action* Reference to the newly created action object
		*/
		Action* CreateElseAction(const std::string& className, const std::string& instanceName);

		/**
		*@brief Sets the value of the conditional that decides which block to execute
		*@param condition 0 evaluates to false, anything else evaluates to true
		*/
		void SetCondition(int condition);

		/**
		@brief Calls update on contained actions
		@param wState Reference to the current world state
		*/
		virtual void Update(WorldState& wState) override;

	private:
		int mCondition;
		Datum mThenBlock;
		Datum mElseBlock;
	};

	ActionFactory(ActionListIf)
}
