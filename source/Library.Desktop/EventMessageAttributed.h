#pragma once
#include "Attributed.h"

namespace Library
{
	class EventMessageAttributed : public Attributed
	{
		RTTI_DECLARATIONS(EventMessageAttributed, Attributed)
	public:
		/*
		*@brief Constructor for EventMessageAttributed
		*/
		explicit EventMessageAttributed(const std::string& subtype, World* world = nullptr);

		/*
		*@brief Destructor for EventMessageAttributed
		*/
		virtual ~EventMessageAttributed() = default;

		/*
		*@brief Gets the subtype of the EventMessageAttributed object
		*@return std::string& 
		*/
		const std::string& GetSubtype() const ;

		/*
		*@brief Sets the subtype of the EventMessageAttributed object using the one provided 
		*@param subtype A string holding the subtype that will be assigned to this EventMessageAttributed
		*/
		void SetSubtype(const std::string& subtype);


		/*
		*@brief Gets the world that contains this EventMessageAttributed 
		*@return World* Reference to the parent world
		*/
		World* GetWorld() const;

		/**
		*@brief Sets the world that will contain this EvenetMessageAttributed
		*@param parent Reference to a world that will become this EvenetMessageAttributed's parent
		*/
		void SetWorld(World* world);


	private:
		std::string mSubtype;
		World* mWorld;
	};
}