#pragma once
#include "Event.h"

namespace Library
{
	class EMASubscriber : public EventSubscriber
	{
	public:
		EMASubscriber();
		~EMASubscriber();

		virtual void Notify(const EventPublisher* publisher);
	};
}