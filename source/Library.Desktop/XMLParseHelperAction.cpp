#include "pch.h"


namespace Library
{
	XMLParseHelperAction::XMLParseHelperAction()
	{
	}


	XMLParseHelperAction::~XMLParseHelperAction()
	{
	}

	XMLParseHelperAction* XMLParseHelperAction::Clone() const
	{
		return new XMLParseHelperAction();
	}

	bool XMLParseHelperAction::StartElementHandler(XMLParseMaster::SharedData & sharedData, const std::string & name, const Hashmap<std::string, std::string>& attributes)
	{
		SharedData* tableSharedData = sharedData.As<SharedData>();

		if (tableSharedData == nullptr)
		{
			return false;
		}

		UNREFERENCED_PARAMETER(attributes);

		if (tableSharedData->mScope->Is("ActionListIf"))
		{
			if (name == "then")
			{
				ActionListIf* actionList = tableSharedData->mScope->As<ActionListIf>();
				assert(actionList != nullptr);
				Action* action = actionList->CreateThenAction("ActionList", "Then");
				tableSharedData->mScope = action->As<Scope>();
			}
			else if (name == "else")
			{
				ActionListIf* actionList = tableSharedData->mScope->As<ActionListIf>();
				assert(actionList != nullptr);
				Action* action = actionList->CreateElseAction("ActionList", "Else");
				tableSharedData->mScope = action->As<Scope>();
			}
		}
		else
		{
			return false;
		}

		return true;
	}

	bool XMLParseHelperAction::EndElementHandler(XMLParseMaster::SharedData & sharedData, const std::string & name)
	{
		SharedData* tableSharedData = sharedData.As<SharedData>();

		if (tableSharedData == nullptr)
		{
			return false;
		}

		if (name != "then" && name != "else")
		{
			return false;
		}

		if (tableSharedData->mScope->As<ActionList>() != nullptr)
		{
			tableSharedData->mScope = tableSharedData->mScope->GetParent();
		}

		return true;
	}
}