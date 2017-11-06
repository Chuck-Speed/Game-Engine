#include "pch.h"

namespace Library
{

	XMLParseHelperEntity* XMLParseHelperEntity::Clone() const
	{
		return new XMLParseHelperEntity();
	}

	bool XMLParseHelperEntity::StartElementHandler(XMLParseMaster::SharedData & sharedData, const std::string & name, const Hashmap<std::string, std::string>& attributes)
	{

		SharedData* tableSharedData = sharedData.As<SharedData>();

		if (tableSharedData == nullptr)
		{
			return false;
		}

		if (name == "World")
		{
			std::string worldName = attributes["name"];
			assert(!worldName.empty());
			World* world = new World();
			world->SetName(worldName);
			tableSharedData->mScope = world;
		}
		else if (name == "Sector")
		{
			std::string sectorName = attributes["name"];
			assert(!sectorName.empty());

			World* world = tableSharedData->mScope->As<World>();
			assert(world != nullptr);

			Sector* sector = world->CreateSector(sectorName);
			tableSharedData->mScope = sector->As<Scope>();
		}
		else if (name == "Entity")
		{
			std::string className = attributes["class"];
			assert(!className.empty());

			std::string instanceName = attributes["instanceName"];
			assert(!instanceName.empty());

			Sector* sector = tableSharedData->mScope->As<Sector>();
			assert(sector != nullptr);

			Entity* entity = sector->CreateEntity(className, instanceName);
			tableSharedData->mScope = entity->As<Scope>();
		}
		else if (name == "Action")
		{
			std::string className = attributes["class"];
			std::string instanceName = attributes["instanceName"];
			Entity* entity = tableSharedData->mScope->As<Entity>();
			if (entity != nullptr)
			{
				Action* action = entity->CreateAction(className, instanceName);
				tableSharedData->mScope = action->As<Scope>();
			}
			else if(tableSharedData->mScope->As<Reaction>() != nullptr)
			{
				Reaction* reaction = tableSharedData->mScope->As<Reaction>();
				assert(reaction != nullptr);
				Action* newAction = Factory<Action>::Create(className);
				assert(newAction != nullptr);
				newAction->SetName(instanceName);
				reaction->As<ActionList>()->Adopt(*newAction, "ActionEntries");
				tableSharedData->mScope = newAction->As<Scope>();
			}
			else
			{
				ActionList* actionList = static_cast<ActionList*>(tableSharedData->mScope);
				assert(actionList != nullptr);
				Action* action = actionList->CreateAction(className, instanceName);
				tableSharedData->mScope = action->As<Scope>();
			}
		}
		else if(attributes.ContainsKey("name") && attributes.ContainsKey("value"))
		{
			if (name == std::string("Integer"))
			{
				mParseType = Datum::DatumType::INTEGER;
			}
			else if (name == std::string("Float"))
			{
				mParseType = Datum::DatumType::FLOAT;
			}
			else if (name == std::string("Vector"))
			{
				mParseType = Datum::DatumType::VECTOR;
			}
			else if (name == std::string("Matrix"))
			{
				mParseType = Datum::DatumType::MATRIX;
			}
			else if (name == std::string("String"))
			{
				mParseType = Datum::DatumType::STRING;
			}
			else
			{
				return false;
			}

			Datum& datum = tableSharedData->mScope->Append(attributes["name"]);

			if (datum.Type() == Datum::DatumType::UNKNOWN)
			{
				datum.SetType(mParseType);
			}


			int index = 0;
			if (attributes.ContainsKey("index"))
			{
				index = stoi(attributes["index"]);
			}
			std::string value = attributes["value"];
			assert(!value.empty());
			datum.SetFromString(attributes["value"], index);
		}
		else
		{
			return false;
		}

		return true;
	}

	bool XMLParseHelperEntity::EndElementHandler(XMLParseMaster::SharedData & sharedData, const std::string & name)
	{
		SharedData* tableSharedData = sharedData.As<SharedData>();

		if (tableSharedData == nullptr)
		{
			return false;
		}

		if (name == "Action")
		{
			Action* currentAction = tableSharedData->mScope->As<Action>();
			assert(currentAction != nullptr);
			tableSharedData->mScope = currentAction->GetEntity();
			if (tableSharedData->mScope == nullptr)
			{
				tableSharedData->mScope = currentAction->GetActionList();
			}
		}
		else if (name == "Entity")
		{
			Entity* currentEntity = tableSharedData->mScope->As<Entity>();
			assert(currentEntity != nullptr);
			tableSharedData->mScope = currentEntity->GetSector();
		}
		else if (name == "Sector")
		{
			Sector* currentSector = tableSharedData->mScope->As<Sector>();
			assert(currentSector != nullptr);
			tableSharedData->mScope = currentSector->GetWorld();
		}
		else
		{
			return false;
		}

		return true;
	}
}