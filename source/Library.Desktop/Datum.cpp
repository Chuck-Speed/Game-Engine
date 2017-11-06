#include "pch.h"

namespace Library

{

	Datum::Datum(DatumType type, std::uint32_t capacity) :
		mType(type), dArray{ nullptr }, mSize(0), mCapacity(0), mIsExternal(false)
	{
		Reserve(capacity);
	}

	Datum::~Datum()
	{
		Clear();
	}

	Datum::Datum(const Datum & rhs) :
		Datum(rhs.mType, rhs.mCapacity)
	{
		operator=(rhs);
	}

	Datum & Datum::operator=(const Datum & rhs)
	{
		if (this != &rhs)
		{
			if (!mIsExternal)
			{
				Clear();
			}
			mType = rhs.mType;

			if (rhs.mIsExternal)
			{
				dArray = rhs.dArray;
				mSize = rhs.mSize;
				mCapacity = rhs.mCapacity;
				mIsExternal = true;
			}
			else if (!rhs.mIsExternal)
			{
				dArray.vp = nullptr;
				mIsExternal = rhs.mIsExternal;
				mSize = 0;
				mCapacity = 0;
				Reserve(rhs.mCapacity);

				switch (mType)
				{
				case DatumType::INTEGER:
				{
					for (uint32_t i = 0; i < rhs.Size(); ++i)
					{
						PushBack(rhs.Get<int>(i));
					}
					break;
				}
				case DatumType::FLOAT:
				{
					for (uint32_t i = 0; i < rhs.Size(); ++i)
					{
						PushBack(rhs.Get<float>(i));
					}
					break;
				}
				case DatumType::VECTOR:
				{
					for (uint32_t i = 0; i < rhs.Size(); ++i)
					{
						PushBack(rhs.Get<glm::vec4>(i));
					}
					break;
				}
				case DatumType::MATRIX:
				{
					for (uint32_t i = 0; i < rhs.Size(); ++i)
					{
						PushBack(rhs.Get<glm::mat4>(i));
					}
					break;
				}
				case DatumType::TABLE:
				{
					for (uint32_t i = 0; i < rhs.Size(); ++i)
					{
						PushBack(rhs.Get<Scope*>(i));
					}
					break;
				}
				case DatumType::STRING:
				{
					for (uint32_t i = 0; i < rhs.Size(); ++i)
					{
						PushBack(rhs.Get<std::string>(i));
					}
					break;
				}
				case Library::Datum::DatumType::POINTER:
				{
					for (uint32_t i = 0; i < rhs.Size(); ++i)
					{
						PushBack(rhs.Get<RTTI*>(i));
					}
					break;
				}
				default:
					break;
				}
			}
		}
		return *this;
	}


#pragma region operator=

	Datum& Datum::operator=(const int & rhs)
	{
		if (mType == DatumType::UNKNOWN)
		{
			SetType(DatumType::INTEGER);
		}
		else if (mType != DatumType::INTEGER)
		{
			throw std::invalid_argument("Cannot assign int value to non-int DatumType.");
		}
		else if (mCapacity == 0 && mIsExternal)
		{
			throw std::exception("Cannot increase the size of external storage.");
		}

		if (mSize == 0)
		{
			PushBack(rhs);
		}
		else
		{
			dArray.integer[0] = rhs;
		}
		return *this;
	}

	Datum& Datum::operator=(const float & rhs)
	{
		if (mType == DatumType::UNKNOWN)
		{
			SetType(DatumType::FLOAT);
		}
		else if (mType != DatumType::FLOAT)
		{
			throw std::invalid_argument("Cannot assign float value to non-float DatumType.");
		}
		else if (mCapacity == 0 && mIsExternal)
		{
			throw std::exception("Cannot increase the size of external storage.");
		}

		if (mSize == 0)
		{
			PushBack(rhs);
		}
		else
		{
			dArray.fpoint[0] = rhs;
		}
		return *this;
	}

	Datum & Datum::operator=(const glm::vec4 & rhs)
	{
		if (mType == DatumType::UNKNOWN)
		{
			SetType(DatumType::VECTOR);
		}
		else if (mType != DatumType::VECTOR)
		{
			throw std::invalid_argument("Cannot assign vec4 value to non-vec4 DatumType.");
		}
		else if (mCapacity == 0 && mIsExternal)
		{
			throw std::exception("Cannot increase the size of external storage.");
		}

		if (mSize == 0)
		{
			PushBack(rhs);
		}
		else
		{
			dArray.vector4[0] = rhs;
		}
		return *this;
	}

	Datum & Datum::operator=(const glm::mat4 & rhs)
	{
		if (mType == DatumType::UNKNOWN)
		{
			SetType(DatumType::MATRIX);
		}
		else if (mType != DatumType::MATRIX)
		{
			throw std::invalid_argument("Cannot assign mat4 value to non-mat4 DatumType.");
		}
		else if (mCapacity == 0 && mIsExternal)
		{
			throw std::exception("Cannot increase the size of external storage.");
		}

		if (mSize == 0)
		{
			PushBack(rhs);
		}
		else
		{
			dArray.matrix4[0] = rhs;
		}
		return *this;
	}

	Datum & Datum::operator=(Scope* const rhs)
	{
		if (mType == DatumType::UNKNOWN)
		{
			SetType(DatumType::TABLE);
		}
		else if (mType != DatumType::TABLE)
		{
			throw std::invalid_argument("Cannot assign Scope value to non-table DatumType.");
		}
		else if (mCapacity == 0 && mIsExternal)
		{
			throw std::exception("Cannot increase the size of external storage.");
		}

		if (mSize == 0)
		{
			PushBack(rhs);
		}
		else
		{
			dArray.table[0] = rhs;
		}
		return *this;
	}

	Datum & Datum::operator=(const std::string & rhs)
	{
		if (mType == DatumType::UNKNOWN)
		{
			SetType(DatumType::STRING);
		}
		else if (mType != DatumType::STRING)
		{
			throw std::invalid_argument("Cannot assign string value to non-string DatumType.");
		}
		else if (mCapacity == 0 && mIsExternal)
		{
			throw std::exception("Cannot increase the size of external storage.");
		}

		if (mSize == 0)
		{
			PushBack(rhs);
		}
		else
		{
			dArray.string[0] = rhs;
		}
		return *this;
	}

	Datum & Datum::operator=(RTTI* const rhs)
	{
		if (mType == DatumType::UNKNOWN)
		{
			SetType(DatumType::POINTER);
		}
		else if (mType != DatumType::POINTER)
		{
			throw std::invalid_argument("Cannot assign RTTI value to non-RTTI DatumType.");
		}
		else if (mCapacity == 0 && mIsExternal)
		{
			throw std::exception("Cannot increase the size of external storage.");
		}

		if (mSize == 0)
		{
			PushBack(rhs);
		}
		else
		{
			dArray.pRTTI[0] = rhs;
		}
		return *this;
	}

#pragma endregion

	 Datum::DatumType Datum::Type() const
	{
		return mType;
	}

	 void Datum::SetType(DatumType type)
	 {
		 if (mType != DatumType::UNKNOWN)
		 {
			 throw std::exception("Cannot change Datum types.");
		 } 
		 mType = type;
	 }

	 std::uint32_t Datum::Size() const
	 {
		 return mSize;
	 }

	 void Datum::Clear()
	 {
		 if (mCapacity > 0 && !mIsExternal)
		 {
			 if (mType == DatumType::STRING)
			 {
				 while (mSize > 0)
				 {
					 PopBack();
				 }
			 }
			 if (dArray.vp != nullptr)
			 {
				 free(dArray.vp);
				 dArray.vp = nullptr;
			 }
			 mCapacity = 0;
			 mSize = 0;
		 }
	 }

#pragma region SetStorage

	 void Datum::SetStorage(int* other, std::uint32_t nElements)
	 {
		 if (mType == DatumType::UNKNOWN)
		 {
			 SetType(DatumType::INTEGER);
		 }
		 else if (mType != DatumType::INTEGER)
		 {
			 throw std::exception("Datum types do not match.");
		 }

		 if (!mIsExternal)
		 {
			 Clear();
		 }

		 mIsExternal = true;
		 dArray.integer = other;
		 mSize = nElements;
		 mCapacity = nElements;
	 }

	 void Datum::SetStorage(float* other, std::uint32_t nElements)
	 {
		 if (mType == DatumType::UNKNOWN)
		 {
			 SetType(DatumType::FLOAT);
		 }
		 else if (mType != DatumType::FLOAT)
		 {
			 throw std::exception("Datum types do not match.");
		 }

		 if (!mIsExternal)
		 {
			 Clear();
		 }

		 mIsExternal = true;
		 dArray.fpoint = other;
		 mSize = nElements;
		 mCapacity = nElements;
	 }

	 void Datum::SetStorage(glm::vec4* other, std::uint32_t nElements)
	 {
		 if (mType == DatumType::UNKNOWN)
		 {
			 SetType(DatumType::VECTOR);
		 }
		 else if (mType != DatumType::VECTOR)
		 {
			 throw std::exception("Datum types do not match.");
		 }

		 if (!mIsExternal)
		 {
			 Clear();
		 }

		 mIsExternal = true;
		 dArray.vector4 = other;
		 mSize = nElements;
		 mCapacity = nElements;
	 }

	 void Datum::SetStorage(glm::mat4* other, std::uint32_t nElements)
	 {
		 if (mType == DatumType::UNKNOWN)
		 {
			 SetType(DatumType::MATRIX);
		 }
		 else if (mType != DatumType::MATRIX)
		 {
			 throw std::exception("Datum types do not match.");
		 }

		 if (!mIsExternal)
		 {
			 Clear();
		 }

		 mIsExternal = true;
		 dArray.matrix4 = other;
		 mSize = nElements;
		 mCapacity = nElements;
	 }

	 void Datum::SetStorage(std::string* other, std::uint32_t nElements)
	 {
		 if (mType == DatumType::UNKNOWN)
		 {
			 SetType(DatumType::STRING);
		 }
		 else if (mType != DatumType::STRING)
		 {
			 throw std::exception("Datum types do not match.");
		 }

		 if (!mIsExternal)
		 {
			 Clear();
		 }

		 mIsExternal = true;
		 dArray.string = other;
		 mSize = nElements;
		 mCapacity = nElements;
	 }

	 void Datum::SetStorage(RTTI** other, std::uint32_t nElements)
	 {
		 if (mType == DatumType::UNKNOWN)
		 {
			 SetType(DatumType::POINTER);
		 }
		 else if (mType != DatumType::POINTER)
		 {
			 throw std::exception("Datum types do not match.");
		 }

		 if (!mIsExternal)
		 {
			 Clear();
		 }

		 mIsExternal = true;
		 dArray.pRTTI = other;
		 mSize = nElements;
		 mCapacity = nElements;
	 }

#pragma endregion
	 bool Datum::operator==(const Datum & rhs) const
	 {
		 if(mType == rhs.mType &&
			 mSize == rhs.mSize &&
			 mCapacity == rhs.mCapacity &&
			 mIsExternal == rhs.mIsExternal)
		 { 
			 switch (mType)
			 {
			 case DatumType::UNKNOWN:
				 return true;

			 case DatumType::INTEGER:
				 for (uint32_t i = 0; i < mSize; ++i)
				 {
					 if (*(dArray.integer + i) != *(rhs.dArray.integer + i))
					 {
						 return false;
					 }
				 }
				 return true;

			 case DatumType::FLOAT:
				 for (uint32_t i = 0; i < mSize; ++i)
				 {
					 if (*(dArray.fpoint + i) != *(rhs.dArray.fpoint + i))
					 {
						 return false;
					 }
				 }
				 return true;

			 case DatumType::VECTOR:
				 for (uint32_t i = 0; i < mSize; ++i)
				 {
					 if (*(dArray.vector4 + i) != *(rhs.dArray.vector4 + i))
					 {
						 return false;
					 }
				 }
				 return true;

			 case DatumType::MATRIX:
				 for (uint32_t i = 0; i < mSize; ++i)
				 {
					 if (*(dArray.matrix4 + i) != *(rhs.dArray.matrix4 + i))
					 {
						 return false;
					 }
				 }
				 return true;

			 case DatumType::TABLE:
				 for (uint32_t i = 0; i < mSize; ++i)
				 {
					 if (*(Get<Scope*>(i)) != *(rhs.Get<Scope*>(i)))
					 {
						 return false;
					 }
				 }
				 return true;

			 case DatumType::STRING:
				 for (uint32_t i = 0; i < mSize; ++i)
				 {
					 if (*(dArray.string + i) != *(rhs.dArray.string + i))
					 {
						 return false;
					 }
				 }
				 return true;

			 case DatumType::POINTER:
				 for (uint32_t i = 0; i < mSize; ++i)
				 {
					 if (*(dArray.pRTTI + i) != nullptr && (rhs.dArray.pRTTI + i) != nullptr)
					 {
						 if (!(*(dArray.pRTTI + i))->Equals(*(rhs.dArray.pRTTI + i)))
						 {
							 return false;
						 }
					 }
					 else
					 {
						 throw std::exception("Dereferenced null pointer.");
					 }
				 }
				 return true;

			 default:
				 break;
			 }
		 }
		 return false;
	 }

	 bool Datum::operator!=(const Datum & rhs) const
	 {
		 return !(operator==(rhs));
	 }

#pragma region ComparisonOperators(==, !=)

	 bool Datum::operator==(const int & rhs) const
	 {
		 if (dArray.integer == nullptr || mType != DatumType::INTEGER)
		 {
			 throw std::exception("Invalid Datum.");
		 }
		 else
		 {
			 return (*dArray.integer == rhs);
		 }
	 }

	 bool Datum::operator==(const float & rhs) const
	 {
		 if (dArray.fpoint == nullptr || mType != DatumType::FLOAT)
		 {
			 throw std::exception("Invalid Datum.");
		 }
		 else
		 {
			 return (*dArray.fpoint == rhs);
		 }
	 }

	 bool Datum::operator==(const glm::vec4 & rhs) const
	 {
		 if (dArray.vector4 == nullptr || mType != DatumType::VECTOR)
		 {
			 throw std::exception("Invalid Datum.");
		 }
		 else
		 {
			 return (*dArray.vector4 == rhs);
		 }
	 }

	 bool Datum::operator==(const glm::mat4 & rhs) const
	 {
		 if (dArray.matrix4 == nullptr || mType != DatumType::MATRIX)
		 {
			 throw std::exception("Invalid Datum.");
		 }
		 else
		 {
			 return (*dArray.matrix4 == rhs);
		 }
	 }

	 bool Datum::operator==(const Scope * rhs) const
	 {
		 if (dArray.table == nullptr || mType != DatumType::TABLE)
		 {
			 throw std::exception("Invalid Datum.");
		 }
		 else
		 {
			 return (**dArray.table == *rhs);
		 }
	 }

	 bool Datum::operator==(const std::string & rhs) const
	 {
		 if (dArray.string == nullptr || mType != DatumType::STRING)
		 {
			 throw std::exception("Invalid Datum.");
		 }
		 else
		 {
			 return (*dArray.string == rhs);
		 }
	 }

	 bool Datum::operator==(const RTTI* rhs) const
	 {
		 if (dArray.pRTTI == nullptr || mType != DatumType::POINTER)
		 {
			 throw std::exception("Invalid Datum.");
		 }
		 else
		 {
			 return (*dArray.pRTTI == rhs);
		 }
	 }

	 bool Datum::operator!=(const int & rhs) const
	 {
		 return !(operator==(rhs));
	 }

	 bool Datum::operator!=(const float & rhs) const
	 {
		 return !(operator==(rhs));
	 }

	 bool Datum::operator!=(const glm::vec4 & rhs) const
	 {
		 return !(operator==(rhs));
	 }

	 bool Datum::operator!=(const glm::mat4 & rhs) const
	 {
		 return !(operator==(rhs));
	 }

	 bool Datum::operator!=(const Scope * rhs) const
	 {
		 return !(operator==(rhs));
	 }

	 bool Datum::operator!=(const std::string & rhs) const
	 {
		 return !(operator==(rhs));
	 }

	 bool Datum::operator!=(const RTTI* rhs) const
	 {
		 return !(operator==(rhs));
	 }

#pragma endregion

	 void Datum::SetFromString(const std::string& value, std::uint32_t index)
	 {		
		 switch (mType)
		 {

		 case DatumType::INTEGER:
		 {
			 int intValue;
			 sscanf_s(value.c_str(), "%d", &intValue);
			 Set(intValue, index);
			 break;
		 }
		 case DatumType::FLOAT:
		 {
			 float floatValue;
			 sscanf_s(value.c_str(), "%f", &floatValue);
			 Set(floatValue, index);
			 break;
		 }
		 case DatumType::VECTOR:
		 {
			 glm::vec4 vector;
			 sscanf_s(value.c_str(), "%f %f %f %f", &vector.x, &vector.y, &vector.z, &vector.w);
			 Set(vector, index);
			 break;
		 }
		 case DatumType::MATRIX:
		 {
			 glm::mat4 matrix;
			 sscanf_s(value.c_str(), "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", &matrix[0].x, &matrix[0].y, &matrix[0].z, &matrix[0].w, 
																							&matrix[1].x, &matrix[1].y, &matrix[1].z, &matrix[1].w, 
																								&matrix[2].x, &matrix[2].y, &matrix[2].z, &matrix[2].w, 
																									&matrix[3].x, &matrix[3].y, &matrix[3].z, &matrix[3].w);
			 Set(matrix, index);
			 break;
		 }
		 case DatumType::STRING:
			 Set(value, index);
			 break;
		 case DatumType::POINTER:
			 throw std::exception("Cannot set RTTI* from string.");
			 break;
		 default:
			 break;
		 }
	 }

	 std::string Datum::ToString(std::uint32_t index) const
	 {
			 switch (mType)
			 {
			 case DatumType::INTEGER:
			 {
				 return std::to_string(Get<int>(index));
			 }
			 case DatumType::FLOAT:
			 {
				 return std::to_string(Get<float>(index));
			 }
			 case DatumType::VECTOR:
			 {
				 glm::vec4 vector = Get<glm::vec4>(index);
				 return glm::to_string(vector);
			 }
			 case DatumType::MATRIX:
			 {
				 glm::mat4 matrix = Get<glm::mat4>(index);
				 return glm::to_string(matrix);
			 }
			 case DatumType::STRING:
				 return Get<std::string>(index);
			 case DatumType::POINTER:
				 if (dArray.pRTTI[index] != nullptr)
				 {
					 dArray.pRTTI[index]->ToString();
				 }
			 default:
				 throw std::exception("Cannot convert to string.");
			 }
	 }

	 void Datum::Reserve(std::uint32_t capacity)
	 {
		 if (capacity > mCapacity)
		 {
			 switch (mType)
			 {
			 case DatumType::INTEGER:
			 {
				 size_t size = capacity*sizeof(int);
				 dArray.integer = reinterpret_cast<int*>(realloc(dArray.integer, size));
				 break;
			 }

			 case DatumType::FLOAT:
			 {
				 size_t size = capacity*sizeof(float);
				 dArray.fpoint = reinterpret_cast<float*>(realloc(dArray.fpoint, size));
				 break;
			 }
			 case DatumType::VECTOR:
			 {
				 size_t size = capacity*sizeof(glm::vec4);
				 dArray.vector4 = reinterpret_cast<glm::vec4*>(realloc(dArray.vector4, size));
				 break;
			 }
			 case DatumType::MATRIX:
			 {
				 size_t size = capacity*sizeof(glm::mat4);
				 dArray.matrix4 = reinterpret_cast<glm::mat4*>(realloc(dArray.matrix4, size));
				 break;
			 }
			 case DatumType::TABLE:
			 {
				 size_t size = capacity*sizeof(Scope**);
				 dArray.table = reinterpret_cast<Scope**>(realloc(dArray.table, size));
				 break;
			 }
			 case DatumType::STRING:
			 {
				 size_t size = capacity*sizeof(std::string);
				 dArray.string = reinterpret_cast<std::string*>(realloc(dArray.string, size));
				 break;
			 }
			 case DatumType::POINTER:
			 {
				 size_t size = capacity*sizeof(RTTI**);
				 dArray.pRTTI = reinterpret_cast<RTTI**>(realloc(dArray.pRTTI, size));
				 break;
			 }
			 default:
				throw std::exception("Invalid type.");
			 }
			 mCapacity = capacity;
		 }
	}

#pragma region PushBack

	 void Datum::PushBack(const int & value)
	 {
		 if (mIsExternal && mSize == mCapacity)
		 {
			 throw std::exception("Cannot increase capacity of external storage.");
		 }
		 else if (!mIsExternal && mSize == mCapacity)
		 {
			 uint32_t capacity = (mCapacity + (mCapacity / 2) + 1);
			 Reserve(capacity);
		 }

		 new (dArray.integer + mSize)int(value);
		 ++mSize;
	 }

	 void Datum::PushBack(const float & value)
	 {
		 if (mIsExternal && mSize == mCapacity)
		 {
			 throw std::exception("Cannot increase capacity of external storage.");
		 }
		 else if (!mIsExternal && mSize == mCapacity)
		 {
			 uint32_t capacity = (mCapacity + (mCapacity / 2) + 1);
			 Reserve(capacity);
		 }

		 new (dArray.fpoint + mSize)float(value);
		 ++mSize;
	 }

	 void Datum::PushBack(const glm::vec4 & value)
	 {
		 if (mIsExternal && mSize == mCapacity)
		 {
			 throw std::exception("Cannot increase capacity of external storage.");
		 }
		 else if (!mIsExternal && mSize == mCapacity)
		 {
			 uint32_t capacity = (mCapacity + (mCapacity / 2) + 1);
			 Reserve(capacity);
		 }

		 new (dArray.vector4 + mSize)glm::vec4(value);
		 ++mSize;
	 }

	 void Datum::PushBack(const glm::mat4 & value)
	 {
		 if (mIsExternal && mSize == mCapacity)
		 {
			 throw std::exception("Cannot increase capacity of external storage.");
		 }
		 else if (!mIsExternal && mSize == mCapacity)
		 {
			 uint32_t capacity = (mCapacity + (mCapacity / 2) + 1);
			 Reserve(capacity);
		 }

		 new (dArray.matrix4 + mSize)glm::mat4(value);
		 ++mSize;
	 }

	 void Datum::PushBack(Scope* const value)
	 {
		 if (mIsExternal && mSize == mCapacity)
		 {
			 throw std::exception("Cannot increase capacity of external storage.");
		 }
		 else if (!mIsExternal && mSize == mCapacity)
		 {
			 if (mType == DatumType::UNKNOWN)
			 {
				 SetType(DatumType::TABLE);
			 }
			 uint32_t capacity = (mCapacity + (mCapacity / 2) + 1);
			 Reserve(capacity);
		 }
		 new (dArray.table + mSize)Scope*(value);
		 ++mSize;
	 }

	 void Datum::PushBack(const std::string & value)
	 {
		 if (mIsExternal && mSize == mCapacity)
		 {
			 throw std::exception("Cannot increase capacity of external storage.");
		 }
		 else if (!mIsExternal && mSize == mCapacity)
		 {
			 uint32_t capacity = (mCapacity + (mCapacity / 2) + 1);
			 Reserve(capacity);
		 }
		 new (dArray.string + mSize)std::string(value);
		 ++mSize;
	 }

	 void Datum::PushBack(RTTI* const value)
	 {
		 if (mIsExternal && mSize == mCapacity)
		 {
			 throw std::exception("Cannot increase capacity of external storage.");
		 }
		 else if (!mIsExternal && mSize == mCapacity)
		 {
			 uint32_t capacity = (mCapacity + (mCapacity / 2) + 1);
			 Reserve(capacity);
		 }
		 new (dArray.pRTTI + mSize)RTTI*(value);
		 ++mSize;
	 }

#pragma endregion

	 void Datum::PopBack()
	 {
		 if (!mIsExternal && mSize > 0)
		 {
			 switch (mType)
			 {
			 case DatumType::VECTOR:
			 {
				 (dArray.vector4 + (mSize - 1))->glm::vec4::~vec4();
				 break;
			 }
			 case DatumType::MATRIX:
			 {
				 (dArray.matrix4 + (mSize - 1))->glm::mat4::~mat4();
				 break;
			 }
			 case DatumType::STRING:
			 {
				 (dArray.string + (mSize - 1))->~basic_string();
				 break;
			 }
			 default:
				 break;
			 }
			 --mSize;
		 }
	 }

#pragma region Remove

	 void Datum::Remove(std::uint32_t index)
	 {
		 if (index < mSize && mSize > 0)
		 {
			 switch (mType)
			 {
			 case DatumType::INTEGER:
				 memmove((dArray.integer + index), (dArray.integer + (index + 1)), sizeof(int)*(mSize - index - 1));
				 break;
			 case DatumType::FLOAT:
				 memmove((dArray.fpoint + index), (dArray.fpoint + (index + 1)), sizeof(float)*(mSize - index - 1));
				 break;
			 case DatumType::VECTOR:
				 memmove((dArray.vector4 + index), (dArray.vector4 + (index + 1)), sizeof(glm::vec4)*(mSize - index - 1));
				 break;
			 case DatumType::MATRIX:
				 memmove((dArray.matrix4 + index), (dArray.matrix4 + (index + 1)), sizeof(glm::mat4)*(mSize - index - 1));
				 break;
			 case DatumType::TABLE:
				 memmove((dArray.table + index), (dArray.table + (index + 1)), sizeof(Scope*)*(mSize - index - 1));
				 break;
			 case DatumType::STRING:
				 dArray.string[index].~basic_string();
				 memmove((dArray.string + index), (dArray.string + (index + 1)), sizeof(std::string)*(mSize - index - 1));
				 break;
			 case DatumType::POINTER:
				 memmove((dArray.pRTTI + index), (dArray.pRTTI + (index + 1)), sizeof(RTTI*)*(mSize - index - 1));
				 break;
			 default:
				 break;
			 }
			 --mSize;
		 }
	 }

	 Scope & Datum::operator[](std::uint32_t index)
	 {
		 return *Get<Scope*>(index);
	 }

#pragma endregion

#pragma region Set

	 void Datum::Set(const int & value, std::uint32_t index)
	 {
		 if (mType == DatumType::UNKNOWN)
		 {
			 SetType(DatumType::INTEGER);
		 }
		 else if (mType != DatumType::INTEGER)
		 {
			 throw std::exception("Datum types do not match.");
		 }

		 if (index >= mSize && mIsExternal)
		 {
			 throw std::out_of_range("Index out of range.");
		 }
		 else if (index >= mSize && !mIsExternal)
		 {
			 PushBack(value);
		 }
		 else
		 {
			 dArray.integer[index] = value;
		 }
	 }

	 void Datum::Set(const float & value, std::uint32_t index)
	 {
		 if (mType == DatumType::UNKNOWN)
		 {
			 SetType(DatumType::FLOAT);
		 }
		 else if (mType != DatumType::FLOAT)
		 {
			 throw std::exception("Datum types do not match.");
		 }

		 if (index >= mSize && mIsExternal)
		 {
			 throw std::out_of_range("Index out of range.");
		 }
		 else if (index >= mSize && !mIsExternal)
		 {
			 PushBack(value);
		 }
		 else
		 {
			 dArray.fpoint[index] = value;
		 }
	 }

	 void Datum::Set(const glm::vec4 & value, std::uint32_t index)
	 {
		 if (mType == DatumType::UNKNOWN)
		 {
			 SetType(DatumType::VECTOR);
		 }
		 else if (mType != DatumType::VECTOR)
		 {
			 throw std::exception("Datum types do not match.");
		 }

		 if (index >= mSize && mIsExternal)
		 {
			 throw std::out_of_range("Index out of range.");
		 }
		 else if (index >= mSize && !mIsExternal)
		 {
			 PushBack(value);
		 }
		 else
		 {
			 dArray.vector4[index] = value;
		 }
	 }

	 void Datum::Set(const glm::mat4 & value, std::uint32_t index)
	 {
		 if (mType == DatumType::UNKNOWN)
		 {
			 SetType(DatumType::MATRIX);
		 }
		 else if (mType != DatumType::MATRIX)
		 {
			 throw std::exception("Datum types do not match.");
		 }

		 if (index >= mSize && mIsExternal)
		 {
			 throw std::out_of_range("Index out of range.");
		 }
		 else if (index >= mSize && !mIsExternal)
		 {
			 PushBack(value);
		 }
		 else
		 {
			 dArray.matrix4[index] = value;
		 }
	 }

	 void Datum::Set(Scope * value, std::uint32_t index)
	 {
		 if (mType == DatumType::UNKNOWN)
		 {
			 SetType(DatumType::TABLE);
		 }
		 else if (mType != DatumType::TABLE)
		 {
			 throw std::exception("Datum types do not match.");
		 }

		 if (index >= mSize && mIsExternal)
		 {
			 throw std::out_of_range("Index out of range.");
		 }
		 else if (index >= mSize && !mIsExternal)
		 {
			 PushBack(value);
		 }
		 else
		 {
			 dArray.table[index] = value;
		 }
	 }

	 void Datum::Set(const std::string & value, std::uint32_t index)
	 {
		 if (mType == DatumType::UNKNOWN)
		 {
			 SetType(DatumType::STRING);
		 }
		 else if (mType != DatumType::STRING)
		 {
			 throw std::exception("Datum types do not match.");
		 }

		 if (index >= mSize && mIsExternal)
		 {
			 throw std::out_of_range("Index out of range.");
		 }
		 else if (index >= mSize && !mIsExternal)
		 {
			 PushBack(value);
		 }
		 else
		 {
			 dArray.string[index] = value;
		 }
	 }

	 void Datum::Set(RTTI* value, std::uint32_t index)
	 {
		 if (mType == DatumType::UNKNOWN)
		 {
			 SetType(DatumType::POINTER);
		 }
		 else if (mType != DatumType::POINTER)
		 {
			 throw std::exception("Datum types do not match.");
		 }

		 if (index >= mSize && mIsExternal)
		 {
			 throw std::out_of_range("Index out of range.");
		 }
		 else if (index >= mSize && !mIsExternal)
		 {
			 PushBack(value);
		 }
		 else
		 {
			 dArray.pRTTI[index] = value;
		 }
	 }

#pragma endregion

#pragma region Get<> Specializations

	 template<>
	 int& Datum::Get<int>(std::uint32_t index) const
	 {
		 if (mType != DatumType::INTEGER)
		 {
			 throw std::exception("Datum types do not match.");
		 }

		 if (index >= mSize)
		 {
			 throw std::out_of_range("Index out of range.");
		 }
		 else
		 {
			 return dArray.integer[index];
		 }
	 }

	 template<>
	 float& Datum::Get<float>(std::uint32_t index) const
	 {
		 if (mType != DatumType::FLOAT)
		 {
			 throw std::exception("Datum types do not match.");
		 }

		 if (index >= mSize)
		 {
			 throw std::out_of_range("Index out of range.");
		 }
		 else
		 {
			 return dArray.fpoint[index];
		 }
	 }

	 template<>
	 glm::vec4& Datum::Get<glm::vec4>(std::uint32_t index) const
	 {
		 if (mType != DatumType::VECTOR)
		 {
			 throw std::exception("Datum types do not match.");
		 }

		 if (index >= mSize)
		 {
			 throw std::out_of_range("Index out of range.");
		 }
		 else
		 {
			 return dArray.vector4[index];
		 }
	 }

	 template<>
	 glm::mat4& Datum::Get<glm::mat4>(std::uint32_t index) const
	 {
		 if (mType != DatumType::MATRIX)
		 {
			 throw std::exception("Datum types do not match.");
		 }

		 if (index >= mSize)
		 {
			 throw std::out_of_range("Index out of range.");
		 }
		 else
		 {
			 return dArray.matrix4[index];
		 }
	 }

	 template<>
	 Scope*& Datum::Get<Scope*>(std::uint32_t index) const
	 {
		 if (mType != DatumType::TABLE)
		 {
			 throw std::exception("Datum types do not match.");
		 }

		 if (index >= mSize)
		 {
			 throw std::out_of_range("Index out of range.");
		 }
		 else
		 {
			 return dArray.table[index];
		 }
	 }

	 template<>
	 std::string& Datum::Get<std::string>(std::uint32_t index) const
	 {
		 if (mType != DatumType::STRING)
		 {
			 throw std::exception("Datum types do not match.");
		 }

		 if (index >= mSize)
		 {
			 throw std::out_of_range("Index out of range.");
		 }
		 else
		 {
			 return dArray.string[index];
		 }
	 }

	 template<>
	 RTTI*& Datum::Get<RTTI*>(std::uint32_t index) const
	 {
		 if (mType != DatumType::POINTER)
		 {
			 throw std::exception("Datum types do not match.");
		 }

		 if (index >= mSize)
		 {
			 throw std::out_of_range("Index out of range.");
		 }
		 else
		 {
			 return dArray.pRTTI[index];
		 }
	 }

#pragma endregion

}