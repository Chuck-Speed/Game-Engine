#include "pch.h"
#include "Factory.h"

namespace Library 
{
	RTTI_DEFINITIONS(Sector)

	Sector::Sector() :
		mEntities(AddNestedScope("Entities"))
	{
		AddExternalAttribute("Name", &mName, 1U);
	}


	Sector::~Sector()
	{
	}

	const std::string & Sector::Name() const
	{
		return mName;
	}

	void Sector::SetName(const std::string & name)
	{
		mName = name;
	}

	Datum& Sector::Entities()
	{
		return mEntities;
	}

	Entity* Sector::CreateEntity(const std::string& className, const std::string& name)
	{
		RTTI* product = Factory<RTTI>::Create(className);
		assert(product->Is(Entity::TypeIdClass()));
		Entity* newEntity = static_cast<Entity*>(product);
		newEntity->SetName(name);
		newEntity->SetSector(*this);
		return newEntity;
	}

	World* Sector::GetWorld()
	{
		return GetParent()->As<World>();
	}

	void Sector::SetWorld(World & parent)
	{
		parent.Adopt(*this, "Sectors");
	}

	void Sector::Update(WorldState& wState)
	{
		wState.mSector = this;
		Datum& entities = Entities();
		for (uint32_t i = 0; i < entities.Size(); ++i)
		{
			Entity* currentEntity = entities.Get<Scope*>(i)->As<Entity>();
			assert(currentEntity != nullptr);
			currentEntity->Update(wState);
		}
	}
}