#pragma once

#include "SList.h"
#include "Vector.h"

namespace Library
{

	/**
	*@class DefaultHash
	*@brief Class template for a HashFunctor.
	*/
	template<typename T>
	class DefaultHash
	{
	public:
		std::uint32_t operator()(const T& key) const;
	};

	/**
	*@class DefaultHash
	*@brief Class template specialization for <char*> HashFunctor.
	*/
	template<>
	class DefaultHash<char*>
	{
	public:
		std::uint32_t operator()(const char* key) const
		{
			uint32_t hash = 0;
			const char* byteArray = key;

			for (uint32_t i = 0; i < strlen(key); ++i)
			{
				hash = 33 * hash + byteArray[i];
			}
			return (hash);
		}
	};

	/**
	*@class DefaultHash
	*@brief Class template specialization for <std::string> HashFunctor.
	*/
	template<>
	class DefaultHash<std::string>
	{
	public:
		std::uint32_t operator()(const std::string& key) const
		{
			uint32_t hash = 0;
			for (uint32_t i = 0; i < key.length(); ++i)
			{
				hash = 33 * hash + key[i];
			}
			return (hash);
		}
	};


	/**
	*@class Hashmap
	*@brief Class template for a Hashmap.
	*/
	template<typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	class Hashmap
	{
	public:
		typedef std::pair<TKey, TData> PairType;
		typedef SList<PairType> ChainType;
		typedef Vector<ChainType> BucketType;
		//typedef typename ChainType::Iterator;

		class Iterator;

		/**
		*@brief Initializes a Hashmap of the provide type <TKey, TData, HashFuntor>.
		*/
		Hashmap(std::uint32_t size = 5U);

		/**
		*@brief Copies the provided Hashmap.
		*@param &rhs Constant reference to an Hashmap.
		*/
		Hashmap(const Hashmap& rhs);

		/**
		*@brief Assigns the contents of the provide Hashmap to the calling Hashmap.
		*@param &rhs Constant reference to an Hashmap.
		*/
		Hashmap& operator=(const Hashmap& rhs);

		/**
		*@brief Deletes the contents of the Hashmap.
		*/
		~Hashmap() = default;

		/**
		*@brief Finds the value associated with the key and returns and iterator pointing to it's location.
		*@param key const reference to key of type Tkey.
		*@return Iterator
		*/
		Iterator Find(const TKey& key) const;

		/**
		*@brief Insert the provided entry into the Hashmap.
		*@param key Constant reference to key of type TKey.
		*/
		Iterator Insert(const PairType& entry);
		Iterator Insert(const PairType& entry, bool& inserted);

		/**
		*@brief Takes a key argument of the appropriate type and returns a reference to the TData portion. Creates entry if one doesn't already exist.
		*@param key Reference to a key of type <TKey>.
		*/
		TData& operator[](const TKey& key);

		/**
		*@brief Takes a key argument of the appropriate type and returns a reference to the TData portion. Creates entry if one doesn't already exist.
		*@param key Reference to a key of type <TKey>.
		*/
		TData& operator[](const TKey& key) const;

		/**
		*@brief Removes the entry in the Hashmap associated with the provided key.
		*@param key Constant reference to a key of type <TKey>.
		*/
		void Remove(const TKey& key);

		/**
		*@brief Deletes all entries in the Hashmap.
		*/
		void Clear();

		/**
		*@brief Retrieves the current number of entries in the Hashmap.
		*@return mSize
		*/
		std::uint32_t Size() const;

		/**
		*@brief Returns a boolean indicating the presense of a key within the Hashmap.
		*/
		bool ContainsKey(const TKey& key) const;

		/**
		*@brief Returns an iterator that points to the front of the first ChainType entry.
		*@return Iterator
		*/
		Iterator begin() const;

		/**
		*@brief Returns an iterator that points to the end of the Hashmap.
		*@return Iterator
		*/
		Iterator end() const;
		
		/**
		*@class Iterator
		*@brief Provides an interface to iterate through an ChainType.
		*/
		class Iterator
		{
		public:
			friend class Hashmap;

			/**
			*@brief Initializes a new iterator.
			*/
			Iterator();

			/**
			*@brief Default destructor for Hashmap iterator.
			*/
			~Iterator() = default;

			/**
			*@brief Copies the provided Iterator.
			*@param &rhs Constant reference to an ChainType.
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
			*@brief Pre-increments an iterator to point to the next value in the ChainType.
			*@param rhs Iterator
			*@return Iterator& Reference to the iterator.
			*/
			Iterator& operator++();
			/**
			*@brief Post-increments an iterator to point to the next value in the ChainType.
			*@return Iterator& Reference to the iterator.
			*/
			Iterator operator++(int);
			/**
			*@brief Dereferences an iterator to get its contained value.
			*@return T& Reference to data of type <T>.
			*/
			PairType& operator*();

			PairType* operator->();

		private:
			Iterator(const Hashmap* map, typename ChainType::Iterator chainIterator, std::uint32_t index);
			const Hashmap* mOwner;
			typename ChainType::Iterator mChain;
			std::uint32_t mIndex;
		};


	private:
		std::uint32_t mSize;
		BucketType mBuckets;
	};

}

#include "Hashmap.inl"