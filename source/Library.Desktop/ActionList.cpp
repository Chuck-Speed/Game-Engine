#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(ActionList)

	ActionList::ActionList() :
		mActionEntries(AddNestedScope("ActionEntries"))
	{
	}

	Datum & ActionList::Actions()
	{
		return mActionEntries;
	}

	Action* ActionList::CreateAction(const std::string & className, const std::string & instanceName)
	{
		Action* newAction = Factory<Action>::Create(className);
		assert(newAction != nullptr);
		newAction->SetName(instanceName);
		newAction->SetActionList(*this);
		return newAction;
	}

	void ActionList::Update(WorldState & wState)
	{
		wState.mAction = this;
		for (uint32_t i = 0; i < mActionEntries.Size(); ++i)
		{
			Scope* scope = mActionEntries.Get<Scope*>(i);
			assert(scope->Is(Action::TypeIdClass()));
			Action* currentAction = static_cast<Action*>(scope);
			currentAction->Update(wState);
		}
	}
}