#include "pch.h"
#include "FooEntity.h"

namespace Library
{
	RTTI_DEFINITIONS(FooEntity)

	FooEntity::FooEntity()
	{
		AddExternalAttribute("mFoo", &mFoo, 1U);
	}


	FooEntity::~FooEntity()
	{
	}

	void FooEntity::Update(WorldState & wState)
	{
		Entity::Update(wState);
	}

}