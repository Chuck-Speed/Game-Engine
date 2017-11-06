#include "pch.h"
#include "Action.h"

namespace Library
{
	RTTI_DEFINITIONS(Action)

		Action::Action()
		{
			AddExternalAttribute("Name", &mName, 1U);
		}

		const std::string & Action::Name() const
		{
			return mName;
		}

		void Action::SetName(const std::string& name)
		{
			mName = name;
		}

		Entity* Action::GetEntity()
		{
			return GetParent()->As<Entity>();
		}

		void Action::SetEntity(Entity& parent)
		{
			parent.Adopt(*this, "Actions");
		}

		ActionList* Action::GetActionList()
		{
			return GetParent()->As<ActionList>();
		}

		void Action::SetActionList(ActionList & parent)
		{
			return parent.Adopt(*this, "ActionEntries");
		}

		void Action::SetActionListIf(ActionListIf & parent)
		{
			return parent.Adopt(*this, "ActionEntries");
		}
}