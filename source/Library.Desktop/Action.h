#pragma once

#include "Attributed.h"
#include "Factory.h"

namespace Library
{
	class Entity;
	class ActionListIf;
	class ActionList;
	class WorldState;

	class Action : public Attributed
	{
		RTTI_DECLARATIONS(Action, Attributed)

		public:
			Action();
			virtual ~Action() = default;

			/*
			*@brief Copy constructor for Action (deleted)
			*/
			Action(const Action& rhs) = delete;

			/*
			*@brief Assignment operator for Action (deleted)
			*/
			Action& operator=(const Action& rhs) = delete;

			/**
			*@brief Gets the name of this action
			*@return std::string& A string reference representing the action name
			*/
			const std::string& Name() const;

			/**
			*@brief Sets the name of this action
			*@param name The new name for this action
			*/
			void SetName(const std::string& name);

			/**
			*@brief Gets the entity that this action resides in
			*@return Entity* Reference to the parent entity
			*/
			Entity* GetEntity();

			/**
			*@brief Sets the entity that will contain this action
			*@param parent Reference to a entity that will become this action's parent
			*/
			void SetEntity(Entity& parent);

			/**
			*@brief Gets the ActionList that this action resides in
			*@return ActionList* Reference to the parent ActionList
			*/
			ActionList* GetActionList();

			/**
			*@brief Sets the entity that will contain this action
			*@param parent Reference to a entity that will become this action's parent
			*/
			void SetActionList(ActionList& parent);

			/**
			*@brief Sets the ActionListIf that will contain this ActionList
			*@param parent Reference to a ActionListIf that will become this ActionList's parent
			*/
			void SetActionListIf(ActionListIf& parent);

			/**
			*@brief Used to call update on all contained actions
			*@param parent Reference to a entity that will become this action's parent
			*/
			virtual void Update(WorldState& wState) = 0;

		private:
			std::string mName;

		public:
			#define ActionFactory(ConcreteProductT) ConcreteFactory(Action, ConcreteProductT)
	};
}