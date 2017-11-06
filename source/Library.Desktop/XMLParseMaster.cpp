#include "pch.h"

namespace Library
{

	RTTI_DEFINITIONS(XMLParseMaster::SharedData)

#pragma region XMLParseMaster

	XMLParseMaster::XMLParseMaster(SharedData& sharedData) :
		mParser(XML_ParserCreate("US-ASCII")), mSharedData(&sharedData), mHelpers(), mFileName(), mIsClone(false)
	{
		mSharedData->SetXMLParseMaster(this);
		XML_SetElementHandler(mParser, StartElementHandler, EndElementHandler);
		XML_SetCharacterDataHandler(mParser, CharDataHandler);
		XML_SetUserData(mParser, mSharedData);
	}


	XMLParseMaster::~XMLParseMaster()
	{
		if (mIsClone)
		{
			for (uint32_t i = 0; i < mHelpers.Size(); ++i)
			{
				delete mHelpers[i];
			}
			delete mSharedData;
		}
		XML_ParserFree(mParser);
	}

	XMLParseMaster * XMLParseMaster::Clone() const
	{
		if (mSharedData == nullptr)
		{
			throw std::exception("Invalid SharedData.");
		}

		XMLParseMaster* clone = new XMLParseMaster(*mSharedData->Clone());

		for (uint32_t i = 0; i < mHelpers.Size(); ++i)
		{
			clone->mHelpers.PushBack(mHelpers[i]->Clone());
		}
		clone->mIsClone = true;
		return clone;
	}

	void XMLParseMaster::AddHelper(IXMLParseHelper & helper)
	{
		if (mIsClone)
		{
			throw std::exception("Clone cannot add helpers.");
		}
		mHelpers.PushBack(&helper);
	}

	void XMLParseMaster::RemoveHelper(IXMLParseHelper & helper)
	{
		if (mIsClone)
		{
			throw std::exception("Clone cannot remove helpers.");
		}
		mHelpers.Remove(&helper);
	}

	void XMLParseMaster::Reset()
	{
		XML_ParserReset(mParser, "US-ASCII");
		for (uint32_t i = 0; i < mHelpers.Size(); ++i)
		{
			mHelpers[i]->Initialize();
		}
		XML_SetElementHandler(mParser, StartElementHandler, EndElementHandler);
		XML_SetCharacterDataHandler(mParser, CharDataHandler);
		XML_SetUserData(mParser, mSharedData);
		mFileName = "";
	}

	void XMLParseMaster::Parse(const char * buffer, std::uint32_t length, bool isFinal)
	{
		if (mSharedData == nullptr)
		{
			throw std::exception("Invalid SharedData.");
		}

		XML_Status status = XML_Parse(mParser, buffer, length, isFinal);
		if (status == XML_STATUS_ERROR)
		{
			throw std::exception("String failed to parse.");
		}
	}

	void XMLParseMaster::ParseFromFile(const std::string & filename)
	{
		mFileName = filename;
		std::ifstream input(filename);
		std::string str((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
		Parse(str.c_str(), static_cast<int>(str.length()), true);
	}

	const std::string & XMLParseMaster::GetFileName() const
	{
		return mFileName;
	}

	XMLParseMaster::SharedData& XMLParseMaster::GetSharedData() const
	{
		return *mSharedData;
	}

	void XMLParseMaster::SetSharedData(SharedData & sharedData)
	{
		if (mIsClone)
		{
			delete mSharedData;
		}

		mSharedData = &sharedData;
		mSharedData->SetXMLParseMaster(this);
		XML_SetUserData(mParser, mSharedData);
	}

	void XMLParseMaster::StartElementHandler(void * userData, const XML_Char * elementName, const XML_Char ** atts)
	{
		assert(userData != nullptr);

		SharedData* sharedData = reinterpret_cast<SharedData*>(userData);
		XMLParseMaster* parseMaster = sharedData->GetXMLParseMaster();
		Hashmap<std::string, std::string> attributeTable(10U);

		for (uint32_t i = 0; atts[i] != nullptr; i+=2)
		{
			attributeTable.Insert(std::pair<std::string, std::string>(atts[i], atts[i + 1]));
		}
		sharedData->IncrementDepth();

		for (std::uint32_t i = 0; i < parseMaster->mHelpers.Size(); ++i)
		{
			if (parseMaster->mHelpers[i]->StartElementHandler(*sharedData, elementName, attributeTable))
			{
				break;
			}
		}
	}

	void XMLParseMaster::EndElementHandler(void * userData, const XML_Char * elementName)
	{
		assert(userData != nullptr);

		SharedData* sharedData = reinterpret_cast<SharedData*>(userData);
		XMLParseMaster* parseMaster = sharedData->GetXMLParseMaster();

		for (std::uint32_t i = 0; i < parseMaster->mHelpers.Size(); ++i)
		{
			if (parseMaster->mHelpers[i]->EndElementHandler(*sharedData, elementName))
			{
				break;
			}
		}

		sharedData->DecrementDepth();
	}

	void XMLParseMaster::CharDataHandler(void * userData, const XML_Char * s, int len)
	{
		assert(userData != nullptr);

		SharedData* sharedData = reinterpret_cast<SharedData*>(userData);
		XMLParseMaster* parseMaster = sharedData->GetXMLParseMaster();

		for (std::uint32_t i = 0; i < parseMaster->mHelpers.Size(); ++i)
		{
			if (parseMaster->mHelpers[i]->CharDataHandler(*sharedData, s, len))
			{
				break;
			}
		}
	}

#pragma endregion

#pragma region SharedData

	XMLParseMaster::SharedData::SharedData() :
		mMaster(nullptr), mDepth(0)
	{
	}

	XMLParseMaster::SharedData * XMLParseMaster::SharedData::Clone() const
	{
		SharedData* newSharedData = new SharedData();
		return newSharedData;
	}

	void XMLParseMaster::SharedData::SetXMLParseMaster(XMLParseMaster* master)
	{
		mMaster = master;
	}

	XMLParseMaster* XMLParseMaster::SharedData::GetXMLParseMaster() const
	{
		return mMaster;
	}

	void XMLParseMaster::SharedData::IncrementDepth()
	{
		++mDepth;
	}

	void XMLParseMaster::SharedData::DecrementDepth()
	{
		if (mDepth <= 0)
		{
			throw std::exception("Depth cannot be negative.");
		}
		--mDepth;
	}

	std::uint32_t XMLParseMaster::SharedData::Depth() const
	{
		return mDepth;
	}

#pragma endregion

}