#pragma once

#include "ActionList.h"
#include "Event.h"

namespace Library
{
	class Reaction : public ActionList, public EventSubscriber
	{
		RTTI_DECLARATIONS(Reaction, ActionList)
	public:
		/*
		*@brief Constructor for Reaction
		*/
		Reaction() = default;

		/*
		*@brief Destructor for Reaction
		*/
		virtual ~Reaction() = default;

		/*
		*@brief Copy constructor (deleted)
		*/
		Reaction(const Reaction& rhs) = delete;

		/*
		*@brief Assignment operator (deleted)
		*/
		Reaction& operator=(const Reaction& rhs) = delete;

		/*
		*@brief Updates the subscriber when they are notified by a publisher
		*@param publisher Holds the message being sent to the subscriber
		*/
		virtual void Notify(const EventPublisher* publisher) = 0;

		/*
		*@brief Does nothing. Only implemented to prevent action lists from potentially updating every frame.
		*@param wState Worldstate
		*/
		virtual void Update(WorldState& wState) override;

	#define ReactionFactory(ConcreteProductT) ConcreteFactory(Reaction, ConcreteProductT)
	};
}