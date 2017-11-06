#include "pch.h"

namespace Library
{

	template<typename T>
	inline Stack<T>::Stack() :
		mVector(new Vector<T>())
	{
	}

	template<typename T>
	inline Stack<T>::~Stack()
	{
		Clear();
	}

	template<typename T>
	inline Stack<T>::Stack(const Stack & rhs) :
		Stack<T>::Stack()
	{
		operator=(rhs);
	}

	template<typename T>
	inline Stack<T>& Stack<T>::operator=(const Stack & rhs)
	{
		if (this != &rhs)
		{
			*mVector = *(rhs.mVector);
		}
		return *this;
	}

	template<typename T>
	inline void Stack<T>::Pop()
	{
		 mVector->PopBack();
	}

	template<typename T>
	inline void Stack<T>::Push(const T & value)
	{
		mVector->PushBack(value);
	}

	template<typename T>
	inline T & Stack<T>::Top()
	{
		return mVector->Back();
	}

	template<typename T>
	inline const T & Stack<T>::Top() const
	{
		return mVector->Back();
	}

	template<typename T>
	inline bool Stack<T>::IsEmpty()
	{
		return mVector->IsEmpty();
	}

	template<typename T>
	inline std::uint32_t Stack<T>::Size()
	{
		return mVector->Size();
	}

	template<typename T>
	inline void Stack<T>::Clear()
	{
		mVector->Clear();
	}

}