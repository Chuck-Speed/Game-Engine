#pragma once

#include "IXMLParseHelper.h"

namespace Library
{
	class XMLParseHelperTable : public IXMLParseHelper
	{
	public:
		class SharedData : public XMLParseMaster::SharedData
		{
			friend class XMLParseHelperTable;
			friend class XMLParseHelperEntity;
			friend class XMLParseHelperAction;
			friend class XMLParseHelperReaction;
			RTTI_DECLARATIONS(SharedData, XMLParseMaster::SharedData)

		public:
			/**
			*@brief Constructor for SharedData objects.
			*/
			explicit SharedData(Scope& scope);

			/**
			*@brief Destructor for SharedData objects.
			*/
			virtual ~SharedData() override;

			/**
			@brief Copy Constructor (deleted).
			*/
			SharedData(const SharedData& rhs) = delete;

			/**
			*@brief Assignment Operator (deleted).
			*/
			SharedData& operator=(const SharedData& rhs) = delete;

			/**
			*@brief Creates a new SharedData instance.
			*@return SharedData*
			*/
			virtual SharedData* Clone() const override;

			/**
			*@brief Gets a pointer to the current scope.
			*@return Scope*
			*/
			Scope* GetScopeData() const;

		private:
			Scope* mScope;
			bool mIsClone;
		};

		/**
		*@brief Constructor for XMLParseHelperTable.
		*/
		XMLParseHelperTable();

		/**
		*@brief Destructor for XMLParseHelperTable.
		*/
		~XMLParseHelperTable();

		/**
		*@brief Dupicates the helper.
		*/
		virtual XMLParseHelperTable* Clone() const override;

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
	};
}