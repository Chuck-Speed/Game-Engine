#pragma once

#include "Datum.h"
#include "Hashmap.h"


namespace Library
{
	/**
	*@class Scope
	*@brief Scope objects are tables that create a dictionary of name-value pairs where Datum objects are the values.
	*/
	class Scope : public RTTI
	{
		RTTI_DECLARATIONS(Scope, RTTI)

	public:
		typedef std::pair<std::string, Datum> PairType;

		/**
		*@brief Default constructor for Scope objects.
		*@param capacity Optional value to specify the initial capacity of the Scope.
		*/
		explicit Scope(std::uint32_t capacity = 0U);

		/**
		*@brief Destructor for Scope objects.
		*/
		virtual ~Scope();

		/**
		*@brief Copy constructor for Scope object.
		*@param rhs const reference to a Scope object.
		*/
		Scope(const Scope& rhs);

		/**
		*@brief Assignment operator
		*@param rhs const reference to a Scope object.
		*@return Scope& reference to the newly assigned Scope object.
		*/
		Scope& operator=(const Scope& rhs);

		/**
		*@brief Finds the Datum associated with the given name in this Scope if it exists.
		*@param value const string that holds the name of a Datum.
		*@return Datum* address of the found Datum.
		*/
		Datum* Find(const std::string& name) const;

		/**
		*@brief Searches for the most-closely nested Datum associated with the given name in this Scope or its ancestors.
		*@param value const string that holds the name of a Datum.
		*@param scope Optional parameter to get the scope that contains the Datum.
		*@return Datum* address of the found Datum.
		*/
		Datum* Search(const std::string& name, const Scope** foundScope = nullptr) const;


		/**
		*@brief Appends a new Datum into the table if it doesn't already exist, otherwise return the existing Datum.
		*@param value const string that corresponds to a Datum.
		*@return Datum& reference to a Datum.
		*/
		Datum& Append(const std::string& name);

		/**
		*@brief Returns a reference to a Scope with the associated name, if it doesn't exist, one is created.
		*@param value const string that corresponds to a Scope.
		*@return Scope& reference to a Scope.
		*/
		Scope& AppendScope(const std::string& name);

		/**
		*@brief Places the given child into this table with the given name.
		*@param child const reference to a Scope.
		*@param name const string that holds the name of the child.
		*/
		void Adopt(Scope& child, const std::string& name);

		/**
		*@brief Sever the connections between parent and child scopes.
		*/
		void Orphan();

		/**
		*@brief Returns the address of the Scope's parent if it's a child.
		*@return Scope* address of the Scope's parent.
		*/
		Scope* GetParent();

		/**
		*@brief Wrapper for Append method.
		*@param value const string that corresponds to a Datum.
		*@return Datum& reference to a Datum.
		*/
		Datum& operator[](const std::string& name);

		/**
		*@brief Returns reference to a PairType* at the given index.
		*@param index Corresponds to the order the item was appended to the table.
		*@return PairType* reference to a key value pair of type <std::string, Datum>.
		*/
		Datum& operator[](const std::uint32_t index);

		/**
		*@brief Compares the values of the Scope to the values of this one.
		*@param rhs const reference to a Scope object.
		*@return bool True if the Scope values are the same.
		*/
		bool operator==(const Scope& rhs) const;

		/**
		*@brief Compares the values of the Scope to the values of this one.
		*@param rhs const reference to a Scope object.
		*@return bool False if the Scope values are different.
		*/
		bool operator!=(const Scope& rhs) const;

		/**
		*@brief Returns the name of the member that corresponds to the given scope.
		*@param scope const address of a Scope.
		*@return std:string The name of the corresponding member.
		*/
		std::string FindName(const Scope& scope) const;

		/**
		*@brief Deletes all memory allocated by this object.
		*/
		void Clear();

		std::uint32_t Size() const;

		std::string& GetNameAt(std::uint32_t index) const;


	protected:
		/**
		*@brief Finds the given scope if it's contained with  this scope.
		*@param scope Address of the scope to search through.
		*@param index reference to the index of the Datum that contains the found scope.
		*@return Datum* reference to the Datum that contains the given scope.
		*/
		Datum* FindContainedScope(Scope& scope, std::uint32_t& index) const;
		Vector<PairType*> mArray;
		Hashmap<std::string, Datum> mTable;
		Scope* mParent;
	};
}