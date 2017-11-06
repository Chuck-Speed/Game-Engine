#include "pch.h"
#include "FooAction.h"

namespace Library
{
	FooAction::FooAction()
	{
	}


	FooAction::~FooAction()
	{
	}

	void FooAction::Update(WorldState & wState)
	{
		wState.mAction = this;
		mFoo = 1;
	}
}