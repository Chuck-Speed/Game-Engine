#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(ActionEvent)

	ActionEvent::ActionEvent() : mSubtype(), mDelay()
	{
		AddExternalAttribute("Subtype", &mSubtype, 1U);
		AddExternalAttribute("Delay", &mDelay, 1U);
	}

	void ActionEvent::Update(WorldState & wState)
	{
		EventMessageAttributed newEma(mSubtype, wState.mWorld);
		for (uint32_t i = AuxiliaryBegin(); i < mArray.Size(); ++i)
		{
			newEma.AppendAuxiliaryAttribute(mArray[i]->first) = mArray[i]->second;
		}
		std::shared_ptr<Event<EventMessageAttributed>> e = std::make_shared<Event<EventMessageAttributed>>(newEma);
		wState.mWorld->GetEventQueue().Enqueue(e, wState.GetGameTime(), std::chrono::milliseconds(mDelay));
	}
}