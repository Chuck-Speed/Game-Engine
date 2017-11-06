#include "pch.h"
#include "XMLParseHelperFoo.h"

namespace Library
{
	RTTI_DEFINITIONS(XMLParseHelperFoo::SharedData)

	XMLParseHelperFoo::SharedData* XMLParseHelperFoo::SharedData::Clone() const
	{
		SharedData* newSharedData = new SharedData();
		return newSharedData;
	}

	XMLParseHelperFoo::XMLParseHelperFoo()
	{
		Initialize();
	}

	XMLParseHelperFoo::~XMLParseHelperFoo()
	{
	}

	void XMLParseHelperFoo::Initialize()
	{
	}

	XMLParseHelperFoo * XMLParseHelperFoo::Clone() const
	{
		return new XMLParseHelperFoo();
	}

	bool XMLParseHelperFoo::StartElementHandler(XMLParseMaster::SharedData& sharedData, const std::string & name, const Hashmap<std::string, std::string>& attributes)
	{
		XMLParseMaster::SharedData* temp = &sharedData;
		SharedData* FooSharedData = temp->As<SharedData>();

		if (FooSharedData == nullptr || name != "Boss")
		{
			return false;
		}

		Hashmap<std::string, std::string>::Iterator itr = attributes.Find("stat");
		
		if (itr != attributes.end())
		{
			std::string key = itr->first;
			std::string value = itr->second;
			FooSharedData->SetData(key, value);
		}
		
		return true;
	}
	bool XMLParseHelperFoo::EndElementHandler(XMLParseMaster::SharedData& sharedData, const std::string & name)
	{
		XMLParseMaster::SharedData* temp = &sharedData;
		SharedData* FooSharedData = temp->As<SharedData>();

		if (FooSharedData == nullptr || name != "Boss")
		{
			return false;
		}

		return true;
	}
	bool XMLParseHelperFoo::CharDataHandler(XMLParseMaster::SharedData& sharedData, const std::string & buffer, uint32_t length)
	{
		XMLParseMaster::SharedData* temp = &sharedData;
		SharedData* FooSharedData = temp->As<SharedData>();

		if (FooSharedData == nullptr)
		{
			return false;
		}

		std::string str_value;
		str_value.append(buffer, 0, length);
		FooSharedData->SetPower(atoi(str_value.c_str()));

		return true;
	}

	void XMLParseHelperFoo::SharedData::SetData(std::string & category, std::string & ability)
	{
		mCategory = category;
		mAbility = ability;
	}

	void XMLParseHelperFoo::SharedData::SetPower(int32_t value)
	{
		mPower = value;
	}

	std::pair<std::string, std::string> XMLParseHelperFoo::SharedData::GetData()
	{
		return std::pair<std::string, std::string>(mCategory, mAbility);
	}

	int32_t XMLParseHelperFoo::SharedData::GetPower()
	{
		return mPower;
	}

}