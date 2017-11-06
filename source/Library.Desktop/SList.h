#pragma once

namespace Library
{

	/**
	*@class SList
	*@brief Class template for singly-linked list.
	*/
	template <typename T>
	class SList
	{

	private:
		class Node
		{
		public:
			Node(const T& data, Node* next = nullptr) :
				mData(data), mNext(next)
			{
			}
			Node* mNext;
			T mData;
		};

		Node* mFront;
		Node* mBack;
		std::uint32_t mSize;

	public:
		/**
		*@class Iterator
		*@brief Provides an interface to iterate through an SList.
		*/
		class Iterator
		{
		public:
			friend class SList;

			/**
			*@brief Initializes a new iterator.
			*/
			Iterator();
			/**
			*@brief Copies the provided Iterator.
			*@param &rhs Constant reference to an SList.
			*/
			Iterator(const Iterator& rhs);
			/**
			*@brief Assigns the contents of the provide Iterator to the calling Iterator.
			*@param &rhs Constant reference to an Iterator.
			*/
			Iterator& operator=(const Iterator& rhs);
			/**
			*@brief Returns true when two iterators point to the same node.
			*@param &rhs Constant reference to an Iterator.
			*@return bool
			*/
			bool operator==(const Iterator& rhs) const;
			/**
			*@brief Returns true when two iterators point to different nodes.
			*@param rhs Constant reference to an Iterator.
			*@return bool
			*/
			bool operator!=(const Iterator& rhs) const;
			/**
			*@brief Pre-increments an iterator to point to the next value in the SList.
			*@param rhs Iterator
			*@return Iterator& Reference to the iterator.
			*/
			Iterator& operator++();
			/**
			*@brief Post-increments an iterator to point to the next value in the SList.
			*@return Iterator& Reference to the iterator.
			*/
			Iterator operator++(int);
			/**
			*@brief Dereferences an iterator to get its contained value.
			*@return T& Reference to data of type <T>.
			*/
			T& operator*();

		private:
			Iterator(const SList* list, Node* node = nullptr);
			const SList* mList;
			Node* mNode;
		};

		/**
		*@brief Initializes a singly-linked list of the provide type <T>.
		*/
		SList();
		/**
		*@brief Deletes the SList and its contents.
		*/
		~SList();
		/**
		*@brief Copies the provided SList.
		*@param &rhs Constant reference to an SList.
		*/
		SList(const SList& rhs);
		/**
		*@brief Assigns the contents of the provide SList to the calling list.
		*@param &rhs Constant reference to an SList.
		*/
		SList& operator=(const SList& rhs);
		/**
		*@brief Pushes data to the front of the SList.
		*@param value Constant reference to data of type <T>.
		*@return Iterator Points to the node that contains 'data'.
		*/
		Iterator PushFront(const T& value);
		/**
		*@brief Pushes data to the back of the SList.
		*@param value Constant reference to data of type <T>.
		*@return Iterator Points to the node that contains 'data'.
		*/
		Iterator PushBack(const T& value);
		/**
		*@brief Pop the front of the SList and delete its contents.
		*/
		void PopFront();
		/**
		*@brief Checks if the SList is empty.
		*@return bool
		*/
		bool IsEmpty() const;
		/**
		*@brief Accesses the data stored at the front of the SList.
		*@return T& reference to value of type <T>
		*/
		T& Front();
		/**
		*@brief Accesses the data stored at the back of the SList.
		*@return T& reference to value of type <T>
		*/
		T& Back();
		/**
		*@brief Deletes the SList and its contents.
		*/
		void Clear();
		/**
		*@brief Retrieves the current size of the SList.
		*@return mSize
		*/
		std::uint32_t Size() const;
		/**
		*@brief Returns an iterator that points to the front of the SList.
		*@return Iterator
		*/
		Iterator begin() const;
		/**
		*@brief Returns an iterator that points past the back of the SList.
		*@return Iterator
		*/
		Iterator end() const;
		/**
		*@brief Append the given value after the value that the provided iterator points to.
		*@param itr Constant reference to an iterator.
		*@param value Constant reference to data 
		*/
		void InsertAfter(const Iterator& itr, const T& value);
		/**
		*@brief Finds the given value in the SList and returns and iterator pointing to it's location.
		*@return Iterator
		*/
		Iterator Find(const T& value) const;
		/**
		*@brief Removes the given value in the SList.
		*@param value Constant reference to data of type <T>.
		*/
		void Remove(const T& value);
	};

}

#include "SList.inl"