#pragma once

namespace Library
{

	/**
	*@class Stack
	*@brief Class template for a stack data structure.
	*/
	template <typename T>
	class Stack
	{
	public:
		/**
		*@brief Initializes a Stack of the provide type <T>.
		*/
		Stack();

		/**
		*@brief Deletes the Stack and its contents.
		*/
		~Stack();

		/**
		*@brief Copies the provided Stack.
		*@param &rhs Constant reference to an Stack.
		*/
		Stack(const Stack& rhs);

		/**
		*@brief Assigns the contents of the provide Stack to the calling list.
		*@param &rhs Constant reference to an Stack.
		*/
		Stack& operator=(const Stack& rhs);

		/**
		*@brief Pop the back of the Stack and delete its contents.
		*/
		void Pop();

		/**
		*@brief Pushes data to the back of the Stack.
		*@param value Constant reference to data of type <T>.
		*/
		void Push(const T& value);

		/**
		*@brief Accesses the data stored at the back of the Stack.
		*@return T& reference to value of type <T>
		*/
		T& Top();

		/**
		*@brief Accesses the data stored at the back of the Stack.
		*@return T& const reference to value of type <T>
		*/
		const T& Top() const;

		/**
		*@brief Checks if the Stack is empty.
		*@return bool
		*/
		bool IsEmpty();

		/**
		*@brief Retrieves the current size of the Stack.
		*@return mSize
		*/
		std::uint32_t Size();

		/**
		*@brief Deletes the Stack and its contents.
		*/
		void Clear();

	private:
		Vector<T>* mVector;
	};

}

#include "Stack.inl"