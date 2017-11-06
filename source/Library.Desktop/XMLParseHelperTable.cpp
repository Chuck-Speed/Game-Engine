#include "pch.h"
#include "XMLParseHelperTable.h"

namespace Library
{
	RTTI_DEFINITIONS(XMLParseHelperTable::SharedData)

#pragma region SharedData

	XMLParseHelperTable::SharedData::SharedData(Scope& scope) :
		mScope(&scope), mIsClone(false)
	{
	}

	XMLParseHelperTable::SharedData::~SharedData()
	{
		if (mIsClone)
		{
			delete mScope;
		}
	}

	XMLParseHelperTable::SharedData* XMLParseHelperTable::SharedData::Clone() const
	{
		Scope* s = new Scope;
		XMLParseHelperTable::SharedData* clone = new XMLParseHelperTable::SharedData(*s);
		clone->mIsClone = true;
		return clone;
	}

	Scope * XMLParseHelperTable::SharedData::GetScopeData() const
	{
		return mScope;
	}

#pragma endregion 

	XMLParseHelperTable::XMLParseHelperTable()
	{
	}

	XMLParseHelperTable * XMLParseHelperTable::Clone() const
	{
		return new XMLParseHelperTable();
	}

	bool XMLParseHelperTable::StartElementHandler(XMLParseMaster::SharedData & sharedData, const std::string & name, const Hashmap<std::string, std::string>& attributes)
	{
		XMLParseMaster::SharedData* temp = &sharedData;
		SharedData* tableSharedData = temp->As<SharedData>();

		if (tableSharedData == nullptr)
		{
			return false;
		}

		if (name == "Scope")
		{
			mParseType = Datum::DatumType::TABLE;

			if (tableSharedData->Depth() != 1)
			{
				assert(!attributes["name"].empty());
				tableSharedData->mScope = &tableSharedData->mScope->AppendScope(attributes["name"]);
			}
		}
		else
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
			datum.SetFromString(attributes["value"], index);
		}
		return true;
	}

	bool XMLParseHelperTable::EndElementHandler(XMLParseMaster::SharedData & sharedData, const std::string & name)
	{
		XMLParseMaster::SharedData* temp = &sharedData;
		SharedData* tableSharedData = temp->As<SharedData>();

		if (tableSharedData == nullptr)
		{
			return false;
		}

		if (name == std::string("Scope"))
		{
			if (tableSharedData->mScope->GetParent() != nullptr)
			{
				tableSharedData->mScope = tableSharedData->mScope->GetParent();
			}
		}

		return true;
	}

	XMLParseHelperTable::~XMLParseHelperTable()
	{
	}
}