#include "pch.h"
#include "Foo.h"


Foo::Foo(int data) :
	mData(data), mMoreData(new int)
{
}

Foo::~Foo()
{
	delete mMoreData;
}

Foo::Foo(const Foo & rhs) :
	mData(rhs.mData), mMoreData(new int(*rhs.mMoreData))
{
	operator=(rhs);
}

Foo & Foo::operator=(const Foo & rhs)
{
	if (this != &rhs)
	{
		delete mMoreData;
		mData = rhs.mData;
		mMoreData = new int(*rhs.mMoreData);
	}

	return *this;
}

bool Foo::operator==(const Foo & rhs) const
{
	if (mData == rhs.mData && *mMoreData == *(rhs.mMoreData))
	{
		return true;
	}
	return false;
}

int Foo::Data() const
{
	return mData;
}

 int Foo::MoreData() const
{
	return *mMoreData;
}