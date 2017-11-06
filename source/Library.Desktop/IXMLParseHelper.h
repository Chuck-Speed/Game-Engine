#pragma once

#include "XMLParseMaster.h"

namespace Library
{
	class IXMLParseHelper
	{
	public:
		typedef XMLParseMaster::SharedData SharedData;
		/**
		*@brief Constructor for IXMLParseHelper.
		*/
		IXMLParseHelper() = default;

		/**
		*@brief Destructor for IXMLParseHelper.
		*/
		virtual ~IXMLParseHelper() = default;

		/**
		*@brief Initializes the helper. Called before each file is parsed.
		*/
		virtual void Initialize() {};

		/**
		*@brief Given a string for the element name and a hashmap of attribute name-value pairs, attempts to handle the element start.
		*@param name const reference to a string holding the name of the start element.
		*@param attributes const reference to a hashmap containing attribute name-value pairs.
		*@return bool Returns true if the routine handles the element.
		*/
		virtual bool StartElementHandler(SharedData& sharedData, const std::string& name, const Hashmap<std::string, std::string>& attributes) = 0;

		/**
		*@brief Given a string for the element name, attempts to handle the element end.
		*@param name const reference to a string holding the name of the end element.
		*@return bool Returns true if the routine handles the element.
		*/
		virtual bool EndElementHandler(SharedData& sharedData, const std::string& name) = 0;

		/**
		*@brief Given a string buffer of character data and an integer length, attempt to handle the character data.
		*@param buffer const reference to a character buffer.
		*@param length number of bytes in the character buffer.
		*@return bool Returns true if the routine handles the element.
		*/
		virtual bool CharDataHandler(SharedData& sharedData, const std::string& buffer, uint32_t length);

		/**
		*@brief Dupicates the helper.
		*/
		virtual IXMLParseHelper* Clone() const = 0;
	};
}