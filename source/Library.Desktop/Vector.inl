#include "pch.h"
#include "Vector.h"

namespace Library
{

	template<typename T>
	inline Vector<T>::Vector(std::uint32_t capacity, bool fixedSize) :
		mSize(0U), mCapacity(0U), mArray(nullptr), mFixedSize(fixedSize)
	{
		Reserve(capacity);
	}

	template<typename T>
	inline Vector<T>::Vector(const Vector & rhs) :
		mSize(0U), mCapacity(0U), mArray(nullptr)
	{
		operator=(rhs);
	}

	template<typename T>
	inline Vector<T>::~Vector()
	{
		Clear();
	}

	template<typename T>
	inline Vector<T>& Vector<T>::operator=(const Vector & rhs)
	{
		if (this != &rhs)
		{
			if (!IsEmpty())
			{
				Clear();
			}
			mFixedSize = false;
			Reserve(rhs.mCapacity);

			for (Iterator itr = rhs.begin(); itr != rhs.end(); ++itr)
			{
				PushBack(*itr);
			}
			mFixedSize = rhs.mFixedSize;
		}
		return *this;
	}

	template<class T>
	inline Vector<T>::Vector(Vector<T>&& rhs) : mSize(rhs.mSize), mCapacity(rhs.mCapacity), mFixedSize(rhs.mFixedSize), mData(rhs.mData)
	{
		rhs.mSize = 0;
		rhs.mCapacity = 0;
		rhs.mFixedSize = false;
		rhs.mData = nullptr;
	}

	template<class T>
	inline Vector<T>& Vector<T>::operator=(Vector && rhs)
	{
		if (this != &rhs)
		{
			Clear();
			mSize = rhs.mSize;
			mCapacity = rhs.mCapacity;
			mFixedSize = rhs.mFixedSize;
			mData = rhs.mData;

			rhs.mSize = 0;
			rhs.mCapacity = 0;
			rhs.mFixedSize = false;
			rhs.mData = nullptr;
		}

		return *this;
	}

	template<typename T>
	inline T& Vector<T>::operator[](std::uint32_t index)
	{
		if(index >= mSize)
		{ 
			throw std::out_of_range("Invalid index.");
		}
		return mArray[index];
	}

	template<typename T>
	inline T& Vector<T>::operator[](std::uint32_t index) const
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Invalid index.");
		}
		return mArray[index];
	}

	template<typename T>
	inline void Vector<T>::PopBack()
	{
		if (mSize > 0)
		{
			mArray[--mSize].~T();
		}
	}

	template<typename T>
	inline typename Vector<T>::Iterator Vector<T>::PushBack(const T & value)
	{
		if (mSize == mCapacity)
		{
			uint32_t newCapacity = (mCapacity + (mCapacity / 2) + 1);
			Reserve(newCapacity);
		}
		new (mArray+mSize)T(value);
		return Iterator(this, mSize++);
	}

	template<typename T>
	inline void Vector<T>::Reserve(std::uint32_t capacity)
	{
		if (capacity > mCapacity)
		{
			mArray = reinterpret_cast<T*>(realloc(mArray, capacity*sizeof(T)));

			//if (!IsEmpty())
			//{
			//	memcpy(temp, mArray, capacity*sizeof(T));
			//	free(mArray);
			//}
			//mArray = temp;
			mCapacity = capacity;
		}
		if (mFixedSize)
		{
			for (uint32_t i = mSize; i < mCapacity; ++i)
			{
				new (mArray + i)T();
			}
			mSize = mCapacity;
		}
	}

	template<typename T>
	inline typename Vector<T>::Iterator Vector<T>::Find(const T & value)
	{
		for (Iterator itr = begin(); itr != end(); ++itr)
		{
			if (*itr == value)
			{
				return itr;
			}
		}
		return end();
	}

	template<typename T>
	inline void Vector<T>::Clear()
	{
		while (!IsEmpty())
		{
			PopBack();
		}

		if (mArray != nullptr)
		{
			free(mArray);
		}
		mCapacity = 0;
		mArray = nullptr;
	}

	template<typename T>
	inline void Vector<T>::Remove(const T& value)
	{
		Iterator itr = Find(value);
		if (itr != end())
		{
			//Shifts all contained data stored after the removed item down by 1 index.
			for (; itr.mIndex < (mSize-1); ++itr)
			{
				mArray[itr.mIndex] = mArray[itr.mIndex + 1];
			}
			PopBack();
		}
	}

	template<typename T>
	inline std::uint32_t Vector<T>::Size() const
	{
		return mSize;
	}

	template<typename T>
	inline std::uint32_t Vector<T>::Capacity() const
	{
		return mCapacity;
	}

	template<typename T>
	inline T & Vector<T>::At(std::uint32_t index)
	{
		if (index >= mSize)
		{
			throw std::out_of_range("Invalid index.");
		}
		return mArray[index];
	}

	template<typename T>
	inline bool Vector<T>::IsEmpty() const
	{
		return (mSize == 0);
	}

	template<typename T>
	inline T & Vector<T>::Front()
	{
		if (mSize == 0)
		{
			throw std::exception("Empty vector.");
		}
		return *mArray;
	}

	template<typename T>
	inline const T & Vector<T>::Front() const
	{
		if (mSize == 0)
		{
			throw std::exception("Empty vector.");
		}
		return *mArray;
	}

	template<typename T>
	inline T & Vector<T>::Back()
	{
		if (mSize == 0)
		{
			throw std::exception("Empty vector.");
		}
		return mArray[mSize-1];
	}

	template<typename T>
	inline const T & Vector<T>::Back() const
	{
		if (mSize == 0)
		{
			throw std::exception("Empty vector.");
		}
		return mArray[mSize-1];
	}

	template<typename T>
	inline Vector<T>::Iterator::Iterator()
		: mVector(nullptr), mIndex(0)
	{
	}

	template<typename T>
	inline Vector<T>::Iterator::Iterator(const Vector* vector, std::uint32_t index) :
		mVector(vector), mIndex(index)
	{
	}

	template<typename T>
	inline Vector<T>::Iterator::Iterator(const Iterator& rhs)
		: mVector(rhs.mVector), mIndex(rhs.mIndex)
	{
		operator=(rhs);
	}

	template<typename T>
	inline typename Vector<T>::Iterator& Vector<T>::Iterator::operator=(const Iterator& rhs)
	{
		if (this != &rhs)
		{
			mVector = rhs.mVector;
			mIndex = rhs.mIndex;
		}
		return *this;
	}

	template<typename T>
	inline bool Vector<T>::Iterator::operator==(const Iterator& rhs) const
	{
		return (mVector == rhs.mVector && mIndex == rhs.mIndex);
	}

	template<typename T>
	inline bool Vector<T>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !(operator==(rhs));
	}

	template<typename T>
	inline typename Vector<T>::Iterator & Vector<T>::Iterator::operator++()
	{
		if (mVector == nullptr || mIndex >= mVector->mSize)
		{
			throw std::exception("Iterator is invalid.");
		}
		mIndex++;
		return *this;
	}

	template<typename T>
	inline typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
	{
		Iterator itr(*this);
		++(*this);
		return itr;
	}

	template<typename T>
	inline T& Vector<T>::Iterator::operator*()
	{
		if (mVector == nullptr || mIndex >= mVector->mSize)
		{
			throw std::exception("Iterator is invalid.");
		}
		return mVector->mArray[mIndex];
	}

	template<typename T>
	inline typename Vector<T>::Iterator Vector<T>::begin() const
	{
		return Iterator(this, 0);
	}

	template<typename T>
	inline typename Vector<T>::Iterator Vector<T>::end() const
	{
		return Iterator(this, mSize);
	}

}