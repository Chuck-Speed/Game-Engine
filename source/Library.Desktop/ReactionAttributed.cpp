#include "pch.h"


namespace Library
{
	ReactionAttributed::ReactionAttributed() : mSubtype(AddNestedScope("Subtype"))
	{
		Event<EventMessageAttributed>::Subscribe(this);
	}


	ReactionAttributed::~ReactionAttributed()
	{
		Event<EventMessageAttributed>::Unsubscribe(this);
	}

	const Datum& ReactionAttributed::GetSubtype() const
	{
		return mSubtype;
	}

	void ReactionAttributed::SetSubtype(const Datum& subtype)
	{
		 mSubtype = subtype;
	}

	void ReactionAttributed::Notify(const EventPublisher* publisher)
	{
		Event<EventMessageAttributed>* e = publisher->As<Event<EventMessageAttributed>>();
		if (e != nullptr)
		{
			std::string eSubtype = e->Message().GetSubtype();
			for (uint32_t i = 0; i < mSubtype.Size(); ++i)
			{
				if (eSubtype == mSubtype.Get<std::string>(i))
				{
					EventMessageAttributed message = e->Message();
					for (uint32_t j = message.AuxiliaryBegin(); j < message.Size(); ++j)
					{
						std::string datumName = message.GetNameAt(j);
						AppendAuxiliaryAttribute(datumName) = *(message.Find(datumName));
					}

					ActionList::Update(*e->Message().GetWorld()->GetWorldState());
					break;
				}
			}
		}
	}
}