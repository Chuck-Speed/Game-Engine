#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(Entity)

	Entity::Entity() : 
		mActions(AddNestedScope("Actions"))
	{
		AddExternalAttribute("Name", &mName, 1U);
	}

	Entity::~Entity()
	{
	}

	const std::string & Entity::Name() const
	{
		return mName;
	}

	void Entity::SetName(const std::string & name)
	{
		mName = name;
	}

	Datum & Entity::Actions()
	{
		return mActions;
	}

	Action * Entity::CreateAction(const std::string & className, const std::string & instanceName)
	{
		Action* newAction = Factory<Action>::Create(className)->As<Action>();
		assert(newAction != nullptr);
		newAction->SetName(instanceName);
		newAction->SetEntity(*this);
		return newAction;
	}

	Sector * Entity::GetSector()
	{
		return GetParent()->As<Sector>();
	}

	void Entity::SetSector(Sector& parent)
	{
		parent.Adopt(*this, "Entities");
	}

	void Entity::Update(WorldState & wState)
	{
		wState.mEntity = this;
		Datum& actions = Actions();
		for (uint32_t i = 0; i < actions.Size(); ++i)
		{
			Action* currentAction = actions.Get<Scope*>(i)->As<Action>();
			assert(currentAction != nullptr);
			currentAction->Update(wState);
		}
	}
}
