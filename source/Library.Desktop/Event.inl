#include "Event.h"

namespace Library
{
	template <class T>
	RTTI_DEFINITIONS(Event<T>)

	template <class T>
	Vector<EventSubscriber*> Event<T>::sSubscriberList;

	template <class T>
	std::mutex Event<T>::sMutex;

	template <class T>
	Event<T>::Event(const T& message) : EventPublisher(sSubscriberList, &sMutex), mMessage(message)
	{
	}

	template<class T>
	Event<T>::Event(const Event<T>& rhs) : EventPublisher(sSubscriberList, &sMutex)
	{
		operator=(rhs);
	}

	template<class T>
	Event<T>& Event<T>::operator=(const Event<T>& rhs)
	{
		if (this != &rhs)
		{
			mMessage = rhs.mMessage;
		}
		return *this;
	}

	template<class T>
	Event<T>::Event(Event<T>&& rhs) : Event<T>(rhs)
	{
	}

	template<class T>
	Event<T>& Event<T>::operator=(Event<T>&& rhs)
	{
		return operator=(rhs);
	}

	template <class T>
	void Event<T>::Subscribe(EventSubscriber* subscriber)
	{
		std::lock_guard<std::mutex> lock(sMutex);
		if (sSubscriberList.Find(subscriber) == sSubscriberList.end())
		{
			sSubscriberList.PushBack(subscriber);
		}
	}

	template<class T>
	void Event<T>::Unsubscribe(EventSubscriber* subscriber)
	{
		std::lock_guard<std::mutex> lock(sMutex);
		sSubscriberList.Remove(subscriber);
	}

	template<class T>
	void Event<T>::UnsubscribeAll()
	{
		std::lock_guard<std::mutex> lock(sMutex);
		sSubscriberList.Clear();
	}

	template<class T>
	const T& Event<T>::Message() const
	{
		return mMessage;
	}

}