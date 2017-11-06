#pragma once

#include "IXMLParseHelper.h"

namespace Library
{
	class XMLParseHelperFoo : public IXMLParseHelper
	{
	public:
		class SharedData : public XMLParseMaster::SharedData
		{
			RTTI_DECLARATIONS(SharedData, XMLParseMaster::SharedData)

		public:
			virtual SharedData* Clone() const override;
			void SetData(std::string& category, std::string& ability);
			void SetPower(int32_t value);
			std::pair<std::string, std::string> GetData();
			int32_t GetPower();

		private:
			std::string mCategory;
			std::string mAbility;
			int32_t mPower;
		};


		XMLParseHelperFoo();
		~XMLParseHelperFoo();

		virtual void Initialize() override;
		virtual XMLParseHelperFoo* Clone() const override;
		virtual bool StartElementHandler(XMLParseMaster::SharedData& sharedData, const std::string& name, const Hashmap<std::string, std::string>& attributes) override;
		virtual bool EndElementHandler(XMLParseMaster::SharedData& sharedData, const std::string& name) override;
		virtual bool CharDataHandler(XMLParseMaster::SharedData& sharedData, const std::string& buffer, uint32_t length) override;
	};

}