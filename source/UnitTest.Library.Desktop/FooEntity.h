#pragma once
#include "Entity.h"
#include "Factory.h"

namespace Library
{
	class WorldState;

	class FooEntity : public Entity
	{
		RTTI_DECLARATIONS(FooEntity, Entity)
	public:
		FooEntity();
		~FooEntity();
		virtual void Update(WorldState& wState);

		std::string mFoo;
		ConcreteFactory(RTTI, FooEntity)
	};
}
