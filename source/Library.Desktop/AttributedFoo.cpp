#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(AttributedFoo)

	AttributedFoo::AttributedFoo() :
		mInternalInt(0),
		mInternalFloat(0.0f),
		mInternalVector(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)),
		mInternalMatrix(glm::mat4(0.0f)),
		mInternalString(std::string()),
		mScopePtr(nullptr),
		mInternalPtr(nullptr),
		mExternalInt(new int()),
		mExternalFloat(new float()),
		mExternalVector(new glm::vec4()),
		mExternalMatrix(new glm::mat4()),
		mExternalString(new std::string()),
		mPointer(new RTTI*())
	{
		InitializePrescribed();
	}

	AttributedFoo::~AttributedFoo()
	{
		Clear();
	}

	AttributedFoo::AttributedFoo(const AttributedFoo& rhs) :
		mExternalInt(new int(*(rhs.mExternalInt))), 
		mExternalFloat(new float(*(rhs.mExternalFloat))),
		mExternalVector(new glm::vec4(*(rhs.mExternalVector))),
		mExternalMatrix(new glm::mat4(*(rhs.mExternalMatrix))),
		mExternalString(new std::string(*(rhs.mExternalString))),
		mPointer(new RTTI*(*(rhs.mPointer))),
		Attributed(rhs)
	{

		Attributed::operator=(rhs);
		(*this)["Int"].SetStorage(mExternalInt, 1U);
		(*this)["Float"].SetStorage(mExternalFloat, 1U);
		(*this)["Vector"].SetStorage(mExternalVector, 1U);
		(*this)["Matrix"].SetStorage(mExternalMatrix, 1U);
		(*this)["String"].SetStorage(mExternalString, 1U);
		(*this)["Pointer"].SetStorage(mPointer, 1U);
	}

	AttributedFoo & AttributedFoo::operator=(const AttributedFoo & rhs)
	{
		if (this != &rhs)
		{
			Clear();

			mInternalInt = rhs.mInternalInt;
			mInternalFloat = rhs.mInternalFloat;
			mInternalVector = rhs.mInternalVector;
			mInternalMatrix = rhs.mInternalMatrix;
			mInternalString = rhs.mInternalString;
			mInternalPtr = rhs.mInternalPtr;

			mExternalInt = new int(*(rhs.mExternalInt));
			mExternalFloat = new float(*(rhs.mExternalFloat));
			mExternalVector = new glm::vec4(*(rhs.mExternalVector));
			mExternalMatrix = new glm::mat4(*(rhs.mExternalMatrix));
			mExternalString = new std::string(*(rhs.mExternalString));
			mPointer = new RTTI*(*(rhs.mPointer));

			Attributed::operator=(rhs);

			(*this)["Int"].SetStorage(mExternalInt, 1U);
			(*this)["Float"].SetStorage(mExternalFloat, 1U);
			(*this)["Vector"].SetStorage(mExternalVector, 1U);
			(*this)["Matrix"].SetStorage(mExternalMatrix, 1U);
			(*this)["String"].SetStorage(mExternalString, 1U);
			(*this)["Pointer"].SetStorage(mPointer, 1U);
		}
		return *this;
	}

	Attributed::~Attributed()
	{
	}

	void AttributedFoo::InitializePrescribed()
	{
		glm::vec4 vector(1.0f, 2.0f, 3.0f, 4.0f);
		glm::mat4 matrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
		std::string testString = "Test!";
		std::string name = "Int";
		mScopePtr = new Scope();
		mScopePtr->Append("Scope Jr.");


		AddInternalAttribute("Int", DatumType::INTEGER, 1, 1);
		AddInternalAttribute("Float", DatumType::FLOAT, 1.0f, 1); 
		AddInternalAttribute("Vector", DatumType::VECTOR, vector, 1);
		AddInternalAttribute("Matrix", DatumType::MATRIX, matrix, 1);
		AddInternalAttribute("String", DatumType::STRING, testString, 1);
		AddNestedScope("Scope", mScopePtr);
		AddInternalAttribute("Pointer", DatumType::POINTER, nullptr, 1);

		AddExternalAttribute("IntExt", mExternalInt, 1);
		AddExternalAttribute("FloatExt", mExternalFloat, 1);
		AddExternalAttribute("VectorExt", mExternalVector, 1);
		AddExternalAttribute("MatrixExt", mExternalMatrix, 1);
		AddExternalAttribute("StringExt", mExternalString, 1);
		AddExternalAttribute("PointerExt", mPointer, 1);
	}

	void AttributedFoo::Clear()
	{
		delete mExternalInt;
		delete mExternalFloat;
		delete mExternalVector;
		delete mExternalMatrix;
		delete mExternalString;
		delete mPointer;
	}
}