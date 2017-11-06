#pragma once

namespace Library
{

	/**
	*@class Vector
	*@brief Class template for a Vector.
	*/
	template <typename T>
	class Vector
	{
	public:

		/**
		*@class Iterator
		*@brief Provides an interface to iterate through a Vector.
		*/
		class Iterator
		{
		public:
			friend class Vector;

			/**
			*@brief Initializes a new iterator.
			*/
			Iterator();
			/**
			*@brief Copies the provided Iterator.
			*@param &rhs Constant reference to an Vector.
			*/
			Iterator(const Iterator& rhs);
			/**
			*@brief Assigns the contents of the provide Iterator to the calling Iterator.
			*@param &rhs Constant reference to an Iterator.
			*/
			Iterator& operator=(const Iterator& rhs);
			/**
			*@brief Returns true when two iterators point to the same Vector and value.
			*@param &rhs Constant reference to an Iterator.
			*@return bool
			*/
			bool operator==(const Iterator& rhs) const;
			/**
			*@brief Returns true when two iterators point to different Vectors or values.
			*@param rhs Constant reference to an Iterator.
			*@return bool
			*/
			bool operator!=(const Iterator& rhs) const;
			/**
			*@brief Pre-increments an iterator to point to the next value in the Vector.
			*@param rhs Iterator
			*@return Iterator& Reference to the iterator.
			*/
			Iterator& operator++();
			/**
			*@brief Post-increments an iterator to point to the next value in the Vector.
			*@return Iterator& Reference to the iterator.
			*/
			Iterator operator++(int);
			/**
			*@brief Dereferences an iterator to get its contained value.
			*@return T& Reference to data of type <T>.
			*/
			T& operator*();

		private:
			Iterator(const Vector* vector, std::uint32_t index);
			const Vector* mVector;
			std::uint32_t mIndex;
		};

		/**
		*@brief Initializes a Vector of the provide type <T>.
		*/
		explicit Vector(std::uint32_t capacity = (0U), bool fixedSize = false);

		/**
		*@brief Deletes the Vector and its contents.
		*/
		~Vector();

		/**
		*@brief Copies the provided Vector.
		*@param &rhs Constant reference to an Vector.
		*/
		Vector(const Vector& rhs);

		/**
		*@brief Assigns the contents of the provide Vector to the calling list.
		*@param &rhs Constant reference to an Vector.
		*/
		Vector& operator=(const Vector& rhs);

		Vector(Vector<T>&& rhs);
		Vector<T>& operator=(Vector&& rhs);

		/**
		*@brief Access the Vector at the provided index.
		*@param index Index used to access specific location in the container.
		*@return T& Reference to data of type <T>.
		*/
		T& operator[](std::uint32_t index);

		/**
		*@brief Provides const access to the Vector at the provided index.
		*@param index Index used to access specific location in the container.
		*@return T& Reference to data of type <T>.
		*/
		T& operator[](std::uint32_t index) const;

		/**
		*@brief Pop the back of the Vector and delete its contents.
		*/
		void PopBack();

		/**
		*@brief Pushes data to the back of the Vector.
		*@param value Constant reference to data of type <T>.
		*@return Iterator Points to the container holds 'data'.
		*/
		Iterator PushBack(const T& value);

		/**
		*@brief Checks if the Vector is empty.
		*@return bool
		*/
		bool IsEmpty() const;

		/**
		*@brief Accesses the data stored at the front of the Vector.
		*@return T& reference to value of type <T>
		*/
		T& Front();

		/**
		*@brief Accesses the data stored at the front of the Vector.
		*@return T& const reference to value of type <T>
		*/
		const T& Front() const;

		/**
		*@brief Accesses the data stored at the back of the Vector.
		*@return T& reference to value of type <T>
		*/
		T& Back();

		/**
		*@brief Accesses the data stored at the back of the Vector.
		*@return T& const reference to value of type <T>
		*/
		const T& Back() const;

		/**
		*@brief Retrieves the current size of the Vector.
		*@return mSize
		*/
		std::uint32_t Size() const;

		/**
		*@brief Retrieves the current capacity of the Vector.
		*@return mSize
		*/
		std::uint32_t Capacity() const;

		/**
		*@brief Returns an iterator that points to the front of the Vector.
		*@return Iterator
		*/
		Iterator begin() const;

		/**
		*@brief Returns an iterator that points past the back of the Vector.
		*@return Iterator
		*/
		Iterator end() const;

		/**
		*@brief Returns a reference to the item at the given index.
		*@return T&
		*/
		T& At(std::uint32_t index);

		/**
		*@brief Allocates memory for the Vector to hold more items and preserves the existing items.
		*@param capacity New capacity of the vector.
		*/
		void Reserve(std::uint32_t capacity);

		/**
		*@brief Finds the given value in the Vector and returns and iterator pointing to it's location.
		*@param capacity Maximum number of items that the vector can hold.
		*@return Iterator
		*/
		Iterator Find(const T& value);

		/**
		*@brief Deletes the Vector and its contents, capacity is reset to 0.
		*@param value Constant reference to data of type <T>.
		*/
		void Clear();

		/**
		*@brief Removes the given value in the Vector.
		*@param value Constant reference to data of type <T>.
		*/
		void Remove(const T& value);

	private:
		T* mArray;
		std::uint32_t mSize;
		std::uint32_t mCapacity;
		bool mFixedSize;
	};

}

#include "Vector.inl"