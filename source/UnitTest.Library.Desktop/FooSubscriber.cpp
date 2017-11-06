#include "pch.h"
#include "FooSubscriber.h"

namespace Library
{
	void FooSubscriber::Notify(const EventPublisher* publisher)
	{
		Event<int>* e = publisher->As<Event<int>>();
		if (e != nullptr)
		{
			mData = e->Message();
		}
		else
		{
			throw std::exception("EXCEPTION!");
		}
	}
}