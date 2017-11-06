#pragma once

#include "Reaction.h"
#include "Factory.h"

namespace Library 
{
	class ReactionAttributed : public Reaction
	{
	public:
		/**
		*@brief Constructor for ReactionAttributed
		*/
		ReactionAttributed();

		/*
		*@brief Destructor for ReactionAttributed
		*/
		virtual ~ReactionAttributed();

		/*
		*@brief Copy constructor (deleted) 
		*/
		ReactionAttributed(const ReactionAttributed& rhs) = delete;

		/*
		*@brief Assignment operator (deleted)
		*/
		ReactionAttributed& operator=(const ReactionAttributed& rhs) = delete;

		/*
		*@brief Gets the subtype associated with this ReactionAttributed.
		*@return Datum&
		*/
		const Datum& GetSubtype() const;

		/*
		*@brief Sets the subtype with the given Datum
		*@param subtype Datum that will be used to assign the new subtype
		*/
		void SetSubtype(const Datum& subtype);

		/*
		*@brief When events of the same subtype are published, copies the event's attributes into this ReactionAttribute then calls Update on its ActionList
		*@param publisher Event passed to this subscriber
		*/
		virtual void Notify(const EventPublisher* publisher) override;

	private:
		Datum mSubtype;
	};

	ReactionFactory(ReactionAttributed)
}