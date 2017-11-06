#pragma once
#include "Action.h"

namespace Library
{
	class FooAction : public Action
	{
	public:
		FooAction();
		~FooAction();

		void Update(WorldState& wState) override;
		int mFoo;
	};

	ActionFactory(FooAction)
}