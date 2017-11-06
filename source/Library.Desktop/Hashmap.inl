#include "pch.h"

namespace Library

{
	template<typename T>
	inline std::uint32_t DefaultHash<T>::operator()(const T & key) const
	{
		uint32_t hash = 0;
		const char* byteArray = reinterpret_cast<const char*>(&key);

		for (uint32_t i = 0; i < sizeof(key); ++i)
		{
			hash = 33 * hash + byteArray[i];
		}
		return hash;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline Hashmap<TKey, TData, HashFunctor>::Hashmap(std::uint32_t size) :
		mSize(0/*size*/), mBuckets(BucketType(size, true))
	{
		if (size == 0)
		{
			throw std::exception("Cannot insert into a Hashmap with 0 buckets.");
		}
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline Hashmap<TKey, TData, HashFunctor>::Hashmap(const Hashmap & rhs)
	{
		operator=(rhs);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline Hashmap<TKey, TData, HashFunctor>& Hashmap<TKey, TData, HashFunctor>::operator=(const Hashmap & rhs)
	{
		if (this != &rhs)
		{
			Clear();
			for (uint32_t i = 0; i < rhs.mSize; ++i)
			{
				mBuckets[i] = rhs.mBuckets[i];
			}
			mSize = rhs.mSize;
		}
		return *this;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename Hashmap<TKey, TData, HashFunctor>::Iterator Hashmap<TKey, TData, HashFunctor>::Find(const TKey & key) const
	{

		HashFunctor hash;
		uint32_t bucketIndex = hash(key) % mBuckets.Capacity();
		typename ChainType& chain = mBuckets[bucketIndex];

		auto itr = chain.begin();

		for (; itr != chain.end(); ++itr)
		{
			if ((*itr).first == key)
			{
				return Iterator(this, itr, bucketIndex);
			}
		}
		return end();
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename Hashmap<TKey, TData, HashFunctor>::Iterator Hashmap<TKey, TData, HashFunctor>::Insert(const PairType & entry)
	{
		auto itr = Find(entry.first);
		auto size = itr.mOwner->mBuckets.Size();
		if (itr.mChain != mBuckets[size-1].end())
		{
			return Iterator(this, itr.mChain, itr.mIndex);
		}
		HashFunctor hash;
		uint32_t bucketIndex = hash(entry.first) % mBuckets.Capacity();

		auto itr2 = mBuckets[bucketIndex].PushBack(entry);
		++mSize;
		return Iterator(this, itr2, bucketIndex);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename Hashmap<TKey, TData, HashFunctor>::Iterator Hashmap<TKey, TData, HashFunctor>::Insert(const PairType & entry, bool & inserted)
	{
		auto itr = Find(entry.first);
		auto size = itr.mOwner->mBuckets.Size();
		if (itr.mChain != mBuckets[size - 1].end())
		{
			inserted = false;
			return Iterator(this, itr.mChain, itr.mIndex);
		}
		HashFunctor hash;
		uint32_t bucketIndex = hash(entry.first) % mBuckets.Capacity();

		auto itr2 = mBuckets[bucketIndex].PushBack(entry);
		++mSize;
		inserted = true;
		return Iterator(this, itr2, bucketIndex);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline void Hashmap<TKey, TData, HashFunctor>::Clear()
	{
		for (uint32_t i = 0; i < mBuckets.Capacity(); ++i)
		{
			mBuckets[i].Clear();
		}
		mSize = 0;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline std::uint32_t Hashmap<TKey, TData, HashFunctor>::Size() const
	{
		return mSize;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline void Hashmap<TKey, TData, HashFunctor>::Remove(const TKey & key)
	{
		Iterator itr = Find(key);
		if (itr != end())
		{
			mBuckets[itr.mIndex].Remove(*itr);
			--mSize;
		}
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline TData & Hashmap<TKey, TData, HashFunctor>::operator[](const TKey & key)
	{
		Iterator itr = Insert(PairType(key, TData()));
		return itr->second;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline TData & Hashmap<TKey, TData, HashFunctor>::operator[](const TKey & key) const
	{
		Iterator itr = Find(key);
		if (itr == end())
		{
			throw std::exception("Invalid index.");
		}
		return itr->second;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline bool Hashmap<TKey, TData, HashFunctor>::ContainsKey(const TKey& key) const
	{
		return (Find(key) != end());
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename Hashmap<TKey, TData, HashFunctor>::Iterator Hashmap<TKey, TData, HashFunctor>::begin() const
	{
		for (uint32_t i = 0; i < mBuckets.Capacity(); ++i)
		{
			if (!mBuckets[i].IsEmpty())
			{
				typename ChainType::Iterator itr = mBuckets[i].begin();
				return Iterator(this, itr, i);
			}
		}
		return end();
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename Hashmap<TKey, TData, HashFunctor>::Iterator Hashmap<TKey, TData, HashFunctor>::end() const
	{
		return Iterator(this, mBuckets[mBuckets.Capacity() - 1].end(), mBuckets.Capacity());
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline Hashmap<TKey, TData, HashFunctor>::Iterator::Iterator()
		: mOwner(nullptr)
	{
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline Hashmap<TKey, TData, HashFunctor>::Iterator::Iterator(const Hashmap* map, typename ChainType::Iterator chainIterator, std::uint32_t index)
		: mOwner(map), mChain(chainIterator), mIndex(index)
	{
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline Hashmap<TKey, TData, HashFunctor>::Iterator::Iterator(const Iterator& rhs) :
		mOwner(rhs.mOwner), mChain(rhs.mChain), mIndex(rhs.mIndex)
	{
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename Hashmap<TKey, TData, HashFunctor>::Iterator& Hashmap<TKey, TData, HashFunctor>::Iterator::operator=(const Iterator& rhs)
	{
		if (this != &rhs)
		{
			mOwner = rhs.mOwner;
			mChain = rhs.mChain;
			mIndex = rhs.mIndex;
		}
		return *this;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline bool Hashmap<TKey, TData, HashFunctor>::Iterator::operator==(const Iterator& rhs) const
	{
		return (mOwner == rhs.mOwner && mIndex == rhs.mIndex && mChain == rhs.mChain);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline bool Hashmap<TKey, TData, HashFunctor>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !(operator==(rhs));
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename Hashmap<TKey, TData, HashFunctor>::Iterator& Hashmap<TKey, TData, HashFunctor>::Iterator::operator++()
	{
		if (mOwner == nullptr || mIndex >= mOwner->mBuckets.Capacity())
		{
			throw std::exception("Iterator is invalid.");
		}

		if (mChain != mOwner->mBuckets[mIndex].end())
		{
			++mChain;
		}
		else
		{
			for (uint32_t i = mIndex + 1; i < mOwner->mBuckets.Capacity(); ++i)
			{
				if (!mOwner->mBuckets[i].IsEmpty())
				{
					mIndex = i;
					break;
				}
			}
			mIndex = mOwner->mBuckets.Capacity();
		}
		return *this;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename Hashmap<TKey, TData, HashFunctor>::Iterator Hashmap<TKey, TData, HashFunctor>::Iterator::operator++(int)
	{
		Iterator itr = *this;
		++(*this);
		return itr;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename Hashmap<TKey, TData, HashFunctor>::PairType& Hashmap<TKey, TData, HashFunctor>::Iterator::operator*()
	{
		if (mOwner == nullptr || mIndex >= mOwner->mBuckets.Capacity() || mOwner->mBuckets[mIndex].IsEmpty())
		{
			throw std::exception("Iterator is invalid.");
		}
		return *mChain;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename Hashmap<TKey, TData, HashFunctor>::PairType* Hashmap<TKey, TData, HashFunctor>::Iterator::operator->()
	{
		if (mOwner == nullptr)
		{
			throw std::exception("Iterator is invalid");
		}
		return &operator*();
	}

}