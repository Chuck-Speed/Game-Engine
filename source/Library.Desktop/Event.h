#pragma once

#include <chrono>
#include "Vector.h"
#include "RTTI.h"

namespace Library
{
	class EventPublisher;
	class EventSubscriber
	{
	public:
		/*
		*@brief Updates the subscriber when they are notified by a publisher
		*@param publisher Holds the message being sent to the subscriber
		*/
		virtual void Notify(const EventPublisher* publisher) = 0;
	};

	class EventPublisher : public RTTI
	{
		RTTI_DECLARATIONS(EventPublisher, RTTI)
	public:
		/*
		*@brief Constructor for EventPublisher
		*@param subscriberList Reference to a list of EventSubscriber*
		*/
		EventPublisher(Vector<EventSubscriber*>& subscriberList, std::mutex* mutex);

		/*
		*@brief Destructor for EventPublisher
		*/
		virtual ~EventPublisher() = default;

		/*
		*@brief Copy constructor for EventPublisher
		*@param rhs Reference to an EventPublisher
		*/
		EventPublisher(const EventPublisher& rhs);

		/*
		*@brief Assignment operator for EventPublisher
		*@param rhs Reference to an EventPublisher
		*@return EventPublisher&
		*/
		EventPublisher& operator=(const EventPublisher& rhs);

		/*
		*@brief Move constructor for EventPublisher
		*@param rhs R-value reference to an EventPublisher
		*/
		EventPublisher(EventPublisher&& rhs);

		/*
		*@brief Move assignment operator for EventPublisher
		*@param rhs R-value reference to an EventPublisher
		*@return EventPublisher&
		*/
		EventPublisher& operator=(EventPublisher&& rhs);


		/*
		*@brief Assignment operator for EventPublisher
		*@param currentTime time point used to set the enqueue time
		*@param delay Time to wait before the event is enqueued
		*/
		void SetTime(const std::chrono::high_resolution_clock::time_point& currentTime, std::chrono::milliseconds delay = std::chrono::milliseconds(0));

		/*
		*@brief Gets the time enqueued for this publisher
		*@return std::chrono::high_resolution_clock::time_point&
		*/
		const std::chrono::high_resolution_clock::time_point& TimeEnqueued() const;

		/*
		*@brief Gets the delay in milliseconds before this event is published
		*@return std::chrono::milliseconds
		*/
		const std::chrono::milliseconds& Delay() const;

		/*
		*@brief Checks if an event delay timer has expired
		*@param currentTime GameTime object used to get the current time
		*@return bool
		*/
		bool IsExpired(const GameTime& currentTime) const;

		/*
		*@brief Notify all subscribers of this event
		*/
		void Deliver() const;

	private:
		Vector<EventSubscriber*>* mSubscriberList;
		std::chrono::high_resolution_clock::time_point mTime;
		std::chrono::milliseconds mDelay;
		mutable std::mutex* mEventMutex;
	};

	template<class T>
	class Event final : public EventPublisher
	{
		RTTI_DECLARATIONS(Event<T>, EventPublisher)
	public:
		/*
		*@brief Constructor for Event
		*/
		explicit Event(const T& message);

		/*
		*@brief Destructor for Event
		*/
		virtual ~Event() = default;

		/*
		*@brief Copy constructor for Event
		*@param rhs Reference to an Event<T> for copying
		*/
		Event(const Event<T>& rhs);

		/*
		*@brief Assignment operator for Event
		*@param rhs Reference to an Event<T> for assignment
		*/
		Event<T>& operator=(const Event<T>& rhs);

		/*
		*@brief Move constructor for Event
		*@param rhs R-value reference to an Event<T>
		*/
		Event(Event<T>&& rhs);

		/*
		*@brief Move assignment operator for Event
		*@param rhs R-value reference to an Event<T> for assignment
		*/
		Event<T>& operator=(Event<T>&& rhs);
		
		/*
		*@brief Adds the given subscriber to the list of this event type
		*@param subscriber Address of the subscriber to be added to the list
		*/
		static void Subscribe(EventSubscriber* subscriber);

		/*
		*@brief Removes the given subscriber from the list of this event type
		*@param subscriber Address of the subscriber to be removed from the list
		*/
		static void Unsubscribe(EventSubscriber* subscriber);

		/*
		*@brief Removes all subscribers from the list of this event type
		*/
		static void UnsubscribeAll();

		/*
		*@brief Returns the message object
		*@return T&
		*/
		const T& Message() const;

	private:
		T mMessage;
		static Vector<EventSubscriber*> sSubscriberList;
		static std::mutex sMutex;
	};

	class GameTime;
	class EventQueue
	{
	public:

		/*
		*@brief Constructor for EventQueue
		*/
		EventQueue() = default;

		/*
		*@brief Destructor for EventQueue
		*/
		~EventQueue() = default;

		/*
		*@brief Copy constructor for EventQueue (deleted)
		*/
		EventQueue(const EventQueue& rhs) = delete;

		/*
		*@brief Assignment operator for EventQueue (deleted)
		*/
		EventQueue& operator=(const EventQueue& rhs) = delete;

		/*
		*@brief Enqueues the given event into the the list
		*@param event Reference to the event to be enqueued
		*@param time GameTime reference used to get the current game time
		*@param delay Time to wait until the event is enqueued
		*/
		void Enqueue(const std::shared_ptr<EventPublisher>& event, const GameTime& time, std::chrono::milliseconds delay = std::chrono::milliseconds(0));

		/*
		*@brief Sends an event immediately
		*@param publisher Reference to an event publisher that will deliver the event
		*/
		void Send(const std::shared_ptr<EventPublisher>& publisher);

		/*
		*@brief Publishes all events in the queue that have expired
		*@param time GameTime reference used to get the current game time
		*/
		void Update(GameTime& time);

		/*
		*@brief Clears the event queue. Expired events will not be sent.
		*/
		void Clear();

		/*
		*@brief Returns a boolean indicating if the queue is empty or not
		*@return bool
		*/
		bool IsEmpty() const;

		/*
		*@brief Returns the number of events in the queue
		*@return std::uint32_t
		*/
		std::uint32_t Size() const;

	private:
		Vector<std::shared_ptr<EventPublisher>> mEvents;
		Vector<std::shared_ptr<EventPublisher>> mExpiredEvents;
		mutable std::mutex mMutex;
	};

}

#include "Event.inl"