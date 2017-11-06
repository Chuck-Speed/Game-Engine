#pragma once

#include <string>
#include "glm.hpp"
#include "gtx\string_cast.hpp"
#include "RTTI.h"

namespace Library
{
	class Scope;

	/**
	*@class Datum
	*@brief Datum objects hold data of a type specified at run-time.
	*/
	class Datum final
	{

	public:

		enum class DatumType
		{
			UNKNOWN,
			INTEGER,
			FLOAT,
			VECTOR,
			MATRIX,
			TABLE,
			STRING,
			POINTER
		};

		/**
		*@brief Default constructor for Datum objects.
		*@param type Optional value to specify the type this Datum will hold.
		*@param capacity Optional value to specify reserved memory for this Datum object.
		*/
		explicit Datum(DatumType type = DatumType::UNKNOWN, std::uint32_t capacity = 0U);

		/**
		*@brief Destructor for Datum objects.
		*/
		~Datum();

		/**
		*@brief Copy constructor for Datum object using another Datum.
		*@param rhs const reference to a Datum object.
		*/
		Datum(const Datum& rhs);

		/**
		*@brief Assignment operator
		*@param rhs const reference to a Datum object.
		*@return Datum& reference to the newly assigned Datum object.
		*/
		Datum& operator=(const Datum& rhs);

#pragma region operator=

		/**
		*@brief Assignment operator
		*@param rhs const reference to a Datum value.
		*@return Datum& reference to the newly assigned Datum object.
		*/
		Datum& operator=(const int& rhs);
		Datum& operator=(const float& rhs);
		Datum& operator=(const glm::vec4& rhs);
		Datum& operator=(const glm::mat4& rhs);
		Datum& operator=(Scope* const rhs);
		Datum& operator=(const std::string& rhs);
		Datum& operator=(RTTI* const rhs);

#pragma endregion

		/**
		*@brief Returns type enum associated with the Datum object.
		*@return DatumType
		*/
		 DatumType Type() const;

		/**
		*@brief Assign the type of data the Datum will store.
		*@param type DatumType that will be assigned to the Datum.
		*/
		void SetType(DatumType type);

		/**
		*@brief Return unsigned integer number of values.
		*@return size
		*/
		std::uint32_t Size() const;

		/**
		*@brief Clear the array.
		*/
		void Clear();

#pragma region SetStorage
		/**
		*@brief Assigns the internal values array to the given array, and the size and capacity to the given number of elements.
		*@param other Array of values to assign to the internal array of values.
		*@param nElements Number of elements in the given array.
		*/
		void SetStorage(int* other, std::uint32_t nElements);
		void SetStorage(float* other, std::uint32_t nElements);
		void SetStorage(glm::vec4* other, std::uint32_t nElements);
		void SetStorage(glm::mat4* other, std::uint32_t nElements);
		void SetStorage(std::string* other, std::uint32_t nElements);
		void SetStorage(RTTI** other, std::uint32_t nElements);

#pragma endregion

		/**
		*@brief Compares the entire contents of another Datum to the contents of this one.
		*@param Datum& const reference to a Datum object.
		*@return bool True if the Datum objects are the same.
		*/
		bool operator==(const Datum& rhs) const;

		/**
		*@brief Compares the entire contents of another Datum to the contents of this one.
		*@param Datum& const reference to a Datum object.
		*@return bool True if the Datum objects are different.
		*/
		bool operator!=(const Datum& rhs) const;

#pragma region ComparisonOperators(==, !=)

		/**
		*@brief Compares the value of the Datum to the value of this one.
		*@param rhs const reference to a Datum object.
		*@return bool True if the Datum values are the same.
		*/
		bool operator==(const int& rhs) const;
		bool operator==(const float& rhs) const;
		bool operator==(const glm::vec4& rhs) const;
		bool operator==(const glm::mat4& rhs) const;
		bool operator==(const Scope* rhs) const;
		bool operator==(const std::string& rhs) const;
		bool operator==(const RTTI* rhs) const;

		/**
		*@brief Compares the value of the Datum to the value of this one.
		*@param rhs const reference to a Datum object.
		*@return bool True if the Datum values are different.
		*/
		bool operator!=(const int& rhs) const;
		bool operator!=(const float& rhs) const;
		bool operator!=(const glm::vec4& rhs) const;
		bool operator!=(const glm::mat4& rhs) const;
		bool operator!=(const Scope* rhs) const;
		bool operator!=(const std::string& rhs) const;
		bool operator!=(const RTTI* rhs) const;

#pragma endregion

#pragma region Set

		/**
		*@brief Given a value and an optional index (default 0), assigns the approriate element in the values array to the given value.
		*@param value const reference to a value held by a Datum object.
		*@param index Optional parameter to specify what element to set in the values array.
		*/
		void Set(const int& value, std::uint32_t index = 0);
		void Set(const float& value, std::uint32_t index = 0);
		void Set(const glm::vec4& value, std::uint32_t index = 0);
		void Set(const glm::mat4& value, std::uint32_t index = 0);
		void Set(Scope* value, std::uint32_t index = 0);
		void Set(const std::string& value, std::uint32_t index = 0);
		void Set(RTTI* value, std::uint32_t index = 0);

#pragma endregion

#pragma region Get_<>Specialization

		/**
		*@brief Returns the appropriate element in the values array.
		*@param index Optional parameter to specify what element to get in the values array.
		*@return T const reference to value in the Datum of type <T>.
		*/
		template<typename T>
		T& Get(std::uint32_t index = 0) const;
		template<>
		int& Get<int>(std::uint32_t index) const;
		template<>
		float& Get<float>(std::uint32_t index) const;
		template<>
		glm::vec4& Get<glm::vec4>(std::uint32_t index) const;
		template<>
		glm::mat4& Get<glm::mat4>(std::uint32_t index) const;
		template<>
		Scope*& Get<Scope*>(std::uint32_t index) const;
		template<>
		std::string& Get<std::string>(std::uint32_t index) const;
		template<>
		RTTI*& Get<RTTI*>(std::uint32_t index) const;

#pragma endregion

		/**
		*@brief Assigns the appropriate element in the values array to the given String.
		*@param index Optional parameter to specify what element to set in the values array.
		*/
		void SetFromString(const std::string& value, std::uint32_t index = 0);

		/**
		*@brief Returns a string representing the appropriate element in the values array.
		*@param index Optional parameter to specify what element to use for the method.
		*/
		std::string ToString(std::uint32_t index = 0) const;
		
		/**
		*@brief Allocates memory for the Datum to hold more items and preserves the existing items.
		*@param capacity The new capacity for the Datum object.
		*@param fixedSize Keep the storage size of the datum fixed.
		*/
		void Reserve(std::uint32_t capacity);

#pragma region PushBack

		/**
		*@brief Pushes data to the back of the Vector.
		*@param value const reference to data of type <T>.
		*/
		void PushBack(const int& value);
		void PushBack(const float& value);
		void PushBack(const glm::vec4& value);
		void PushBack(const glm::mat4& value);
		void PushBack(Scope* const value);
		void PushBack(const std::string& value);
		void PushBack(RTTI* const value);

#pragma endregion

		/**
		*@brief Pop the back of the Datum if it's using internal storage and delete its contents.
		*/
		void PopBack();

		/**
		*@brief Removes the given value in the Datum.
		*@param index Optional value to set the index of the element to be removed.
		*/
		void Remove(std::uint32_t index = 0U);

		/**
		*@brief Simplify dereferencing nested Scopes.
		*@param index Index to access in the datum.
		*@return Scope& reference to the accessed Scope.
		*/
		Scope& operator[](std::uint32_t index);

	private:
		union DatumUnion
		{
			int* integer;
			float* fpoint;
			glm::vec4* vector4;
			glm::mat4* matrix4;
			Scope** table;
			std::string* string;
			RTTI** pRTTI;
			void* vp;
		} dArray;

		DatumType mType;
		std::uint32_t mSize;
		std::uint32_t mCapacity;
		bool mIsExternal;
	};

}