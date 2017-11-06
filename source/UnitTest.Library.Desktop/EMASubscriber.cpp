#include "pch.h"
#include "EMASubscriber.h"

namespace Library
{
	EMASubscriber::EMASubscriber()
	{
	}


	EMASubscriber::~EMASubscriber()
	{
	}

	void EMASubscriber::Notify(const EventPublisher* publisher)
	{
		Event<EventMessageAttributed>* e = publisher->As<Event<EventMessageAttributed>>();
		if (e != nullptr && e->Message().GetSubtype() != "NotifiedSubType")
		{
			World* world = e->Message().GetWorld();

			EventMessageAttributed newEMA("NotifiedSubType", world);
			std::shared_ptr<Event<EventMessageAttributed>> newEvent = std::make_shared<Event<EventMessageAttributed>>(newEMA);
			e->Message().GetWorld()->GetEventQueue().Enqueue(newEvent, world->GetWorldState()->GetGameTime(), std::chrono::milliseconds());
		}
	}
}