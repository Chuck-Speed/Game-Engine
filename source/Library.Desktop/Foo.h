#pragma once
#include "RTTI.h"

/**
*@class Foo
*@brief Foo class for foo objects.
*/

class Foo
{
public:
	/**
	* @brief Constructor for Foo object.
	* @param data Assigns the value of the "data" parameter to the mData member in the Foo object.
	*/
	Foo(int data = 0);

	/**
	*@brief Deletes Foo object.
	*/
	~Foo();

	/**
	*@brief Copies the provided Foo object.
	*@param &rhs Constant reference to the Foo object.
	*@return Copy of the Foo object.
	*/
	Foo(const Foo& rhs);

	/**
	*@brief Assigns the contents of the provide Foo object to the calling object.
	*@param &rhs Constant reference to a Foo object.
	*@return Copy of Foo object.
	*/
	Foo& operator=(const Foo& rhs);

	/**
	*@brief Returns true when two Foo objects are equivalent.
	*@param &rhs Constant reference to an Iterator.
	*@return bool
	*/
	bool Foo::operator==(const Foo& rhs) const;

	/**
	*@brief Gets a reference to mData.
	*@return A reference to mData.
	*/
	int Data() const;

	/**
	*@brief Gets a pointer to mMoreData.
	*@return int* MoreData.
	*/
	int MoreData() const;

private:
	int mData;
	int *mMoreData;
};

