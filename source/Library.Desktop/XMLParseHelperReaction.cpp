#include "pch.h"

namespace Library
{

	XMLParseHelperReaction* Library::XMLParseHelperReaction::Clone() const
	{
		return new XMLParseHelperReaction();
	}

	bool Library::XMLParseHelperReaction::StartElementHandler(XMLParseMaster::SharedData & sharedData, const std::string & name, const Hashmap<std::string, std::string>& attributes)
	{
		SharedData* tableSharedData = sharedData.As<SharedData>();

		if (tableSharedData == nullptr)
		{
			return false;
		}

		if (name == "Reaction")
		{
			if(attributes.ContainsKey("class") && attributes.ContainsKey("subType"))
			{
				std::string className = attributes["class"];
				std::string subType = attributes["subType"];

				Reaction* reaction = Factory<Reaction>::Create(className);
				Datum subTypeDatum;
				subTypeDatum = subType;
				reaction->As<ReactionAttributed>()->SetSubtype(subTypeDatum);

				tableSharedData->mScope->Adopt(*reaction, subType);
				tableSharedData->mScope = reaction;
			}

			return true;
		}
		return false;
	}
	bool XMLParseHelperReaction::EndElementHandler(XMLParseMaster::SharedData & sharedData, const std::string & name)
	{

		SharedData* tableSharedData = sharedData.As<SharedData>();

		if (tableSharedData == nullptr)
		{
			return false;
		}

		if (name == "Reaction")
		{
			tableSharedData->mScope = tableSharedData->mScope->GetParent();
			return true;
		}

		return false;
	}
}