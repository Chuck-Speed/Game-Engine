#pragma once

#include "Action.h"

namespace Library
{
	class ActionEvent : public Action
	{
		RTTI_DECLARATIONS(ActionEvent, Action)
	public:
		/*
		*@brief Constructor for Action Event
		*/
		ActionEvent();

		/*
		*@brief Destructor for ActionEvent
		*/
		virtual ~ActionEvent() = default;

		/*
		*@brief Copy constructor (deleted)
		*/
		ActionEvent(const ActionEvent& rhs) = delete;

		/*
		*@brief Assignment operator (delete)
		*/
		ActionEvent& operator=(const ActionEvent& rhs) = delete;

		/*
		*@brief Creates an attributed event, assign its world and subtype, copy all auiliary parameter into the event and queue the event with the given delay.
		*/
		virtual void Update(WorldState& wState) override;

	private:
		std::string mSubtype;
		int mDelay;
	};

	ActionFactory(ActionEvent)
}