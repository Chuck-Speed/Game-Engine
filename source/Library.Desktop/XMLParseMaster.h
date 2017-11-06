#pragma once

#include "RTTI.h"
#include <fstream>
#include "expat.h"

namespace Library
{
	class IXMLParseHelper;

	/**
	*@class XMLParseMaster
	*@brief Class for XML parse master.
	*/
	class XMLParseMaster final
	{
	public:
		/**
		*@class SharedData
		*@brief Class for shared data.
		*/
		class SharedData : public RTTI
		{
			RTTI_DECLARATIONS(SharedData, RTTI)

		public:
			/**
			*@brief Constructor for SharedData objects.
			*/
			SharedData();

			/**
			*@brief Virtual destructor for SharedData objects.
			*/
			virtual ~SharedData() = default;

			/**
			*@brief Creates a clone of the SharedData object that is ready to process a new file.
			*@return SharedData* reference to the cloned SharedData object.
			*/
			virtual SharedData* Clone() const;

			/**
			*@brief Given the address of an XMLParseMaster, assign it to a private member.
			*/
			void SetXMLParseMaster(XMLParseMaster* master);

			/**
			*@brief Returns the address of the XMLParseMaster associated with this object.
			*@return XMLParseMaster* reference to the XMLParseMaster.
			*/
			XMLParseMaster* GetXMLParseMaster() const;

			/**
			*@brief Increment counter tracking the "nesting depth".
			*/
			void IncrementDepth();

			/**
			*@brief Decrement counter tracking the "nesting depth".
			*/
			void DecrementDepth();

			/**
			*@brief Return the current nesting depth.
			*@return uint32_t Nesting depth of this SharedData object.
			*/
			uint32_t Depth() const;

		private:
			XMLParseMaster* mMaster;
			uint32_t mDepth;
		};

		/**
		*@brief Constructor to initialize XMLParseMaster.
		*/
		explicit XMLParseMaster(SharedData& sharedData);

		/**
		*@brief Destructor for XMLParseMaster.
		*/
		~XMLParseMaster();

		/**
		*@brief Copy Constructor (deleted).
		*@param rhs const reference to an XMLParseMaster
		*/
		XMLParseMaster(const XMLParseMaster& rhs) = delete;

		/**
		*@brief Assignment Operator (deleted).
		*@param rhs const reference to an XMLParseMaster
		*/
		XMLParseMaster& operator=(const XMLParseMaster& rhs) = delete;

		/**
		*@brief Duplicates this object and returns its address.
		*@return XMLParseMaster* reference to the newly cloned parser.
		*/
		XMLParseMaster* Clone() const;

		/**
		*@brief Adds the given IXMLParseHelper object to the list.
		*@param IXMLParseHelper& reference to an IXMLParseHelper.
		*/
		void AddHelper(IXMLParseHelper& helper);

		/**
		*@brief Removes the given IXMLParseHelper object from the list.
		*@param IXMLParseHelper& reference to an IXMLParseHelper.
		*/
		void RemoveHelper(IXMLParseHelper& helper);

		/**
		*@brief Resets parse master in order to parse a new file.
		*/
		void Reset();

		/**
		*@brief Wrapper for Expat parse call.
		*@param buffer const char* to parse.
		*@param length number of characters in the buffer.
		*@param isFirst bool indicating whether the first chunk of the file is being read.
		*@param isFinal bool indicating whether the last chunk of the file is being read.
		*/
		void Parse(const char* buffer, std::uint32_t length, bool isFinal);

		/**
		*@brief Given a filename, read in the file and parse it.
		*@param filename reference to a string that holds the name of the file to be parsed.
		*/
		void ParseFromFile(const std::string& filename);

		/**
		*@brief Return the path for the file being parsed.
		*@return string& const reference to a string holding the name of the file being parsed.
		*/
		const std::string& GetFileName() const;

		/**
		*@brief Return the address of a SharedData object.
		*@return SharedData& reference to the SharedData object.
		*/
		SharedData& GetSharedData() const;

		/**
		*@brief Given the address of a SharedData object, associate it with this object.
		*@param sharedData reference to a SharedData object.
		*/
		void SetSharedData(SharedData& sharedData);

	private:
		static void StartElementHandler(void* userData, const XML_Char* elementName, const XML_Char** atts);
		static void EndElementHandler(void* userData, const XML_Char* elementName);
		static void CharDataHandler(void* userData, const XML_Char* s, int len);

		XML_Parser mParser;
		SharedData* mSharedData;
		Vector<IXMLParseHelper*> mHelpers;
		std::string mFileName;
		bool mIsClone;
	};
}
