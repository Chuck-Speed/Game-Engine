#include "pch.h"

namespace Library
{
#pragma region EventPublisher
	RTTI_DEFINITIONS(EventPublisher)
	EventPublisher::EventPublisher(Vector<EventSubscriber*>& subscriberList, std::mutex* mutex) :
		mSubscriberList(&subscriberList), mTime(), mDelay(), mEventMutex(mutex)
	{
	}

	EventPublisher::EventPublisher(const EventPublisher & rhs)
	{
		operator=(rhs);
	}

	EventPublisher & EventPublisher::operator=(const EventPublisher & rhs)
	{
		if (this != &rhs)
		{
			mTime = rhs.mTime;
			mDelay = rhs.mDelay;
			mEventMutex = rhs.mEventMutex;
		}
		return *this;
	}

	EventPublisher::EventPublisher(EventPublisher&& rhs) : EventPublisher(rhs)
	{
	}

	EventPublisher& EventPublisher::operator=(EventPublisher && rhs)
	{
		return operator=(rhs);
	}

	void EventPublisher::SetTime(const std::chrono::high_resolution_clock::time_point& currentTime, std::chrono::milliseconds delay)
	{
		std::lock_guard<std::mutex> lock(*mEventMutex);
		mTime = currentTime;
		mDelay = delay;
	}

	const std::chrono::high_resolution_clock::time_point& EventPublisher::TimeEnqueued() const
	{
		std::lock_guard<std::mutex> lock(*mEventMutex);
		return mTime;
	}

	const std::chrono::milliseconds& EventPublisher::Delay() const
	{
		std::lock_guard<std::mutex> lock(*mEventMutex);
		return mDelay;
	}

	bool EventPublisher::IsExpired(const GameTime & currentTime) const
	{
		std::lock_guard<std::mutex> lock(*mEventMutex);
		if (currentTime.CurrentTime() >= (mTime + mDelay))
		{
			return true;
		}
		return false;
	}

	void EventPublisher::Deliver() const
	{
		std::vector<std::future<void>> futures;
		{
			std::lock_guard<std::mutex> lock(*mEventMutex);
			for (auto& s : *mSubscriberList)
			{
				futures.emplace_back(std::async(&EventSubscriber::Notify, s, this));
			}
		}

		for (auto& f : futures)
		{
			f.get();
		}
	}

#pragma endregion

#pragma region EventQueue

	void EventQueue::Enqueue(const std::shared_ptr<EventPublisher>& event, const GameTime & time, std::chrono::milliseconds delay)
	{
		std::lock_guard<std::mutex> lock(mMutex);
		event->SetTime(time.CurrentTime(), delay);
		mEvents.PushBack(event);
	}

	void EventQueue::Send(const std::shared_ptr<EventPublisher>& publisher)
	{
		publisher->Deliver();
	}

	void EventQueue::Update(GameTime & time)
	{
		std::vector<std::future<void>> futures;
		{
			std::lock_guard<std::mutex> lock(mMutex);
			for (auto& itr : mEvents)
			{
				if (itr->IsExpired(time))
				{
					mExpiredEvents.PushBack(itr);
					futures.emplace_back(std::async(&EventPublisher::Deliver, itr));
				}
			}
		}

		for (auto& f : futures)
		{
			f.get();
		}

		{
			std::lock_guard<std::mutex> lock(mMutex);
			for (auto& itr : mExpiredEvents)
			{
				mEvents.Remove(itr);
			}
			mExpiredEvents.Clear();
		}
	}

	void EventQueue::Clear()
	{
		std::lock_guard<std::mutex> lock(mMutex);
		mEvents.Clear();
	}

	bool EventQueue::IsEmpty() const
	{
		std::lock_guard<std::mutex> lock(mMutex);
		return mEvents.IsEmpty();
	}

	std::uint32_t EventQueue::Size() const
	{
		std::lock_guard<std::mutex> lock(mMutex);
		return mEvents.Size();
	}

#pragma endregion

}