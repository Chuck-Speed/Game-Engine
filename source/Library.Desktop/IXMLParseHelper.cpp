#include "pch.h"

namespace Library
{
	bool IXMLParseHelper::CharDataHandler(SharedData& sharedData, const std::string& buffer, uint32_t length)
	{
		UNREFERENCED_PARAMETER(sharedData);
		UNREFERENCED_PARAMETER(buffer);
		UNREFERENCED_PARAMETER(length);
		return true;
	}
}
