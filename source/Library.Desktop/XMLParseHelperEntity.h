#pragma once

#include "IXMLParseHelper.h"
#include "XMLParseHelperTable.h"

namespace Library
{
	class XMLParseHelperEntity : public IXMLParseHelper
	{
	public:
		/**
		*@brief Constructor for XMLParseHelperEntity.
		*/
		XMLParseHelperEntity() = default;

		/**
		*@brief Destructor for XMLParseHelperEntity.
		*/
		~XMLParseHelperEntity() = default;

		/**
		*@brief Dupicates the helper.
		*/
		virtual XMLParseHelperEntity* Clone() const override;

		/**
		*@brief Given a string for the element name and a hashmap of attribute name-value pairs, attempts to handle the element start.
		*@param name const reference to a string holding the name of the start element.
		*@param attributes const reference to a hashmap containing attribute name-value pairs.
		*@return bool Returns true if the routine handles the element.
		*/
		virtual bool StartElementHandler(XMLParseMaster::SharedData& sharedData, const std::string& name, const Hashmap<std::string, std::string>& attributes) override;

		/**
		*@brief Given a string for the element name, attempts to handle the element end.
		*@param name const reference to a string holding the name of the end element.
		*@return bool Returns true if the routine handles the element.
		*/
		virtual bool EndElementHandler(XMLParseMaster::SharedData& sharedData, const std::string& name) override;

		/**
		*@brief Given a string buffer of character data and an integer length, attempt to handle the character data.
		*@param buffer const reference to a character buffer.
		*@param length number of bytes in the character buffer.
		*@return bool Returns true if the routine handles the element.
		*/
		//virtual bool CharDataHandler(XMLParseMaster::SharedData& sharedData, const std::string& buffer, uint32_t length);

	private:
		Datum::DatumType mParseType;
		typedef XMLParseHelperTable::SharedData SharedData;
	};
}