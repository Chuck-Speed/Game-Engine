#pragma once

#include "Event.h"

namespace Library
{
	class FooSubscriber : public EventSubscriber
	{
	public:
		FooSubscriber() = default;
		virtual ~FooSubscriber() = default;

		FooSubscriber(const FooSubscriber& rhs) = delete;
		FooSubscriber& operator=(const FooSubscriber& rhs) = delete;

		virtual void Notify(const EventPublisher* publisher);
		int mData;
	};
}