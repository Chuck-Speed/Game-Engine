#include "pch.h"

namespace Library
{

	template<typename T>
	inline SList<T>::SList()
		: mFront(nullptr), mBack(nullptr), mSize(0)
	{
	}

	template<typename T>
	inline SList<T>& SList<T>::operator=(const SList<T> & rhs)
	{
		if (this != &rhs)
		{
			Clear();
			Node* helper = rhs.mFront;
			
			while (mSize != rhs.mSize)
			{
				PushBack(helper->mData);
				helper = helper->mNext;
			}
		}
		return *this;
	}

	template<typename T>
	inline typename SList<T>::Iterator SList<T>::PushFront(const T & value)
	{
		Node* newNode = new Node(value, mFront);
		mFront = newNode;

		if (mSize == 0)
		{
			mBack = mFront;
		}

		mSize++;
		return Iterator(this, mFront);
	}

	template<typename T>
	inline typename SList<T>::Iterator SList<T>::PushBack(const T & value)
	{
		Node* newNode = new Node(value);

		if (mSize == 0)
		{
			mFront = newNode;
		}
		else
		{
			mBack->mNext = newNode;
		}

		mSize++;
		mBack = newNode;
		return Iterator(this, mBack);
	}

	template<typename T>
	inline void SList<T>::PopFront()
	{
		if (mFront == nullptr)
		{
			throw std::exception("Attempted to access element from an empty list.");
		}
		else
		{
			Node* helper = mFront;
			mFront = mFront->mNext;
			delete helper;
			mSize--;		
		}
	}

	template<typename T>
	inline bool SList<T>::IsEmpty() const
	{
		return (mSize == 0);
	}

	template<typename T>
	inline typename T& SList<T>::Front()
	{
		if (mFront == nullptr)
		{
			throw std::exception("Empty List.");	
		}
		return mFront->mData;
	}

	template<typename T>
	inline T& SList<T>::Back()
	{
		if (mBack == nullptr)
		{
			throw std::exception("Empty List.");
		}
		return mBack->mData;	
	}

	template<typename T>
	inline void SList<T>::Clear()
	{
		while (mSize > 0)
		{
			PopFront();
		}

		mFront = nullptr;
		mBack = nullptr;
	}

	template<typename T>
	inline std::uint32_t SList<T>::Size() const
	{
		return mSize;
	}

	template<typename T>
	inline SList<T>::~SList()
	{
		Clear();
	}

	template<typename T>
	inline SList<T>::SList(const SList<T>& rhs) :
		SList<T>::SList()
	{
		operator=(rhs);
	}

	template<typename T>
	inline SList<T>::Iterator::Iterator()
		: mNode(nullptr), mList(nullptr)
	{
	}

	template<typename T>
	inline SList<T>::Iterator::Iterator(const SList* list, Node* node) 
		: mList(list), mNode(node)
	{
	}

	template<typename T>
	inline SList<T>::Iterator::Iterator(const Iterator& rhs)
		: mNode(rhs.mNode), mList(rhs.mList)
	{
		operator=(rhs);
	}

	template<typename T>
	inline typename SList<T>::Iterator& SList<T>::Iterator::operator=(const Iterator& rhs)
	{
		if (this != &rhs)
		{
			mList = rhs.mList;
			mNode = rhs.mNode;
		}

		return *this;
	}

	template<typename T>
	inline bool SList<T>::Iterator::operator==(const Iterator& rhs) const
	{
		return (mNode == rhs.mNode && mList == rhs.mList);
	}

	template<typename T>
	inline bool SList<T>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !(operator==(rhs));
	}

	template<typename T>
	inline typename SList<T>::Iterator & SList<T>::Iterator::operator++()
	{
		if (mNode == nullptr)
		{
			throw std::exception("Iterator is invalid.");
		}
		mNode = mNode->mNext;
		return *this;
	}

	template<typename T>
	inline typename SList<T>::Iterator SList<T>::Iterator::operator++(int)
	{
		Iterator itr(*this);
		++(*this);
		return itr;
	}

	template<typename T>
	inline T& SList<T>::Iterator::operator*()
	{
		if (mNode == nullptr)
		{
			throw std::exception("Iterator is invalid.");
		}
		return mNode->mData;
	}

	template<typename T>
	inline typename SList<T>::Iterator SList<T>::begin() const
	{
		return Iterator(this, mFront);
	}

	template<typename T>
	inline typename SList<T>::Iterator SList<T>::end() const
	{
		return Iterator(this);
	}

	template<typename T>
	inline typename SList<T>::Iterator SList<T>::Find(const T & value) const
	{
		Iterator itr;
		for (itr = begin(); itr != end(); ++itr)
		{
			if (*itr == value)
			{
				return itr;
			}
		}
		return itr;
	}

	template<typename T>
	inline void SList<T>::Remove(const T & value)
	{
		if (mSize > 0 && mFront->mData == value)
		{
			PopFront();
		}
		else if(mSize > 0)
		{
			Iterator itr = begin();
			Iterator removeItr = begin();
			++removeItr;

			for (; removeItr != end(); ++removeItr)
			{
				if (*removeItr == value)
				{
					Node* temp = removeItr.mNode->mNext;
					delete removeItr.mNode;
					itr.mNode->mNext = temp;
					mSize--;
					break;
				}
				++itr;
			}
		}
	}

	template<typename T>
	inline void SList<T>::InsertAfter(const Iterator & itr, const T & value)
	{

		if (itr.mList != this)
		{
			throw std::exception("Invalid iterator.");
		}

		if (itr == end() || itr.mNode == mBack)
		{
			PushBack(value);
		}
		else
		{
			Node* insertedNode = new Node(value);
			Node* temp = itr.mNode->mNext;
			itr.mNode->mNext = insertedNode;
			insertedNode->mNext = temp;
			mSize++;	
		}
	}

}