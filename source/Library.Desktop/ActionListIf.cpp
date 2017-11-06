#include "pch.h"



namespace Library
{
	RTTI_DEFINITIONS(ActionListIf)

	ActionListIf::ActionListIf() :
		mCondition(0), mThenBlock(AddNestedScope("Then")), mElseBlock(AddNestedScope("Else"))
	{
		AddExternalAttribute("Condition", &mCondition, 1U);
	}

	Action* ActionListIf::CreateThenAction(const std::string & className, const std::string & instanceName)
	{
		Action* newAction = Factory<Action>::Create(className);
		assert(newAction != nullptr);
		newAction->SetName(instanceName);
		mThenBlock.PushBack(newAction);
		newAction->SetActionListIf(*this);
		return newAction;
	}

	Action* ActionListIf::CreateElseAction(const std::string & className, const std::string & instanceName)
	{
		Action* newAction = Factory<Action>::Create(className);
		assert(newAction != nullptr);
		newAction->SetName(instanceName);
		mElseBlock.PushBack(newAction);
		newAction->SetActionListIf(*this);
		return newAction;
	}

	void ActionListIf::SetCondition(int condition)
	{
		mCondition = condition;
	}

	void ActionListIf::Update(WorldState & wState)
	{
		wState.mAction = this;
		if (mCondition)
		{
			for (uint32_t i = 0; i < mThenBlock.Size(); ++i)
			{
				mThenBlock.Get<Scope*>()->As<Action>()->Update(wState);
			}
		}
		else
		{
			for (uint32_t i = 0; i < mElseBlock.Size(); ++i)
			{
				mElseBlock.Get<Scope*>()->As<Action>()->Update(wState);
			}
		}
	}
}