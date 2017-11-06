#pragma once

#include "Attributed.h"

namespace Library
{
	class AttributedFoo : public Attributed
	{
		RTTI_DECLARATIONS(AttributedFoo, Attributed)

	public:
		AttributedFoo();
		~AttributedFoo();
		AttributedFoo(const AttributedFoo& rhs);
		AttributedFoo& operator=(const AttributedFoo& rhs);
		void InitializePrescribed();
		void Clear();

	private:
		int mInternalInt;
		float mInternalFloat;
		glm::mat4 mInternalMatrix;
		glm::vec4 mInternalVector;
		std::string mInternalString;
		Scope* mScopePtr;
		RTTI** mInternalPtr;

		int* mExternalInt;
		float* mExternalFloat;
		glm::mat4* mExternalMatrix;
		glm::vec4* mExternalVector;
		std::string* mExternalString;
		RTTI** mPointer;
	};

}