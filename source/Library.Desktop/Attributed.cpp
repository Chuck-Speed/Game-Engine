#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(Attributed)

	Attributed::Attributed() :
		mAttributes()
	{
		(*this)["this"] = (RTTI*)this;
		mAttributes.PushBack("this");
	}


	Attributed::Attributed(const Attributed & rhs) :
		mAttributes()
	{
		operator=(rhs);
	}

	Attributed & Attributed::operator=(const Attributed & rhs)
	{
		if (this != &rhs)
		{
			Scope::operator=(rhs);
			mAttributes = rhs.mAttributes;
			(*this)["this"] = (RTTI*)this;
		}
		return *this;
	}

	bool Attributed::IsPrescribedAttribute(const std::string & name) const 
	{
		if (IsAttribute(name))
		{
			for (uint32_t i = 0; i < mAttributes.Size(); ++i)
			{
				if (mAttributes[i] == name)
				{
					return true;
				}
			}
		}
		return false;
	}

	bool Attributed::IsAuxiliaryAttribute(const std::string & name) const
	{
		return (IsAttribute(name) && !IsPrescribedAttribute(name));
	}

	bool Attributed::IsAttribute(const std::string & name) const 
	{
		return (Find(name) != nullptr);
	}

	Datum & Attributed::AppendAuxiliaryAttribute(const std::string & name)
	{
		if (IsPrescribedAttribute(name))
		{
			throw std::exception("Attribute is already prescribed!");
		}
		return Append(name);
	}

	std::uint32_t Attributed::AuxiliaryBegin() const
	{
		return mAttributes.Size();
	}

	void Attributed::AddNestedScope(const std::string& name, Scope * child)
	{
		if (IsPrescribedAttribute(name))
		{
			throw std::exception("Attribute is already prescribed!");
		}
		Adopt(*child, name);
		mAttributes.PushBack(name);
	}

	Datum& Attributed::AddNestedScope(const std::string& name)
	{
		if (IsPrescribedAttribute(name))
		{
			throw std::exception("Attribute is already prescribed!");
		}
		Datum& datum = Append(name);
		datum.SetType(DatumType::TABLE);
		mAttributes.PushBack(name);
		return datum;
	}

	void Attributed::AddInternalAttribute(const std::string & name, Datum::DatumType type, const int & initial, std::uint32_t size)
	{
		if (IsPrescribedAttribute(name))
		{
			throw std::exception("Attribute is already prescribed!");
		}
		Datum& datum = Append(name);
		datum.SetType(type);
		datum.Reserve(size);
		for (uint32_t i = 0; i < size; ++i)
		{
			datum.PushBack(initial);
		}
		mAttributes.PushBack(name);
	}

	void Attributed::AddInternalAttribute(const std::string & name, Datum::DatumType type, const float & initial, std::uint32_t size)
	{
		if (IsPrescribedAttribute(name))
		{
			throw std::exception("Attribute is already prescribed!");
		}
		Datum& datum = Append(name);
		datum.SetType(type);
		datum.Reserve(size);
		for (uint32_t i = 0; i < size; ++i)
		{
			datum.PushBack(initial);
		}
		mAttributes.PushBack(name);
	}

	void Attributed::AddInternalAttribute(const std::string & name, Datum::DatumType type, const glm::vec4 & initial, std::uint32_t size)
	{
		if (IsPrescribedAttribute(name))
		{
			throw std::exception("Attribute is already prescribed!");
		}
		Datum& datum = Append(name);
		datum.SetType(type);
		datum.Reserve(size);
		for (uint32_t i = 0; i < size; ++i)
		{
			datum.PushBack(initial);
		}
		mAttributes.PushBack(name);
	}

	void Attributed::AddInternalAttribute(const std::string & name, Datum::DatumType type, const glm::mat4 & initial, std::uint32_t size)
	{
		if (IsPrescribedAttribute(name))
		{
			throw std::exception("Attribute is already prescribed!");
		}
		Datum& datum = Append(name);
		datum.SetType(type);
		datum.Reserve(size);
		for (uint32_t i = 0; i < size; ++i)
		{
			datum.PushBack(initial);
		}
		mAttributes.PushBack(name);
	}

	void Attributed::AddInternalAttribute(const std::string & name, Datum::DatumType type, const std::string & initial, std::uint32_t size)
	{
		if (IsPrescribedAttribute(name))
		{
			throw std::exception("Attribute is already prescribed!");
		}
		Datum& datum = Append(name);
		datum.SetType(type);
		datum.Reserve(size);
		for (uint32_t i = 0; i < size; ++i)
		{
			datum.PushBack(initial);
		}
		mAttributes.PushBack(name);
	}

	void Attributed::AddInternalAttribute(const std::string & name, Datum::DatumType type,  RTTI * const initial, std::uint32_t size)
	{
		if (IsPrescribedAttribute(name))
		{
			throw std::exception("Attribute is already prescribed!");
		}
		Datum& datum = Append(name);
		datum.SetType(type);
		datum.Reserve(size);
		for (uint32_t i = 0; i < size; ++i)
		{
			datum.PushBack(initial);
		}
		mAttributes.PushBack(name);
	}

	void Attributed::AddExternalAttribute(const std::string & name, int* const storage, std::uint32_t size)
	{
		if (IsPrescribedAttribute(name))
		{
			throw std::exception("Attribute is already prescribed!");
		}
		Datum& external = Append(name);
		external.SetStorage(storage, size);
		mAttributes.PushBack(name);
	}

	void Attributed::AddExternalAttribute(const std::string & name, float * const storage, std::uint32_t size)
	{
		if (IsPrescribedAttribute(name))
		{
			throw std::exception("Attribute is already prescribed!");
		}
		Datum& external = Append(name);
		external.SetStorage(storage, size);
		mAttributes.PushBack(name);
	}

	void Attributed::AddExternalAttribute(const std::string & name, glm::vec4 * const storage, std::uint32_t size)
	{
		if (IsPrescribedAttribute(name))
		{
			throw std::exception("Attribute is already prescribed!");
		}
		Datum& external = Append(name);
		external.SetStorage(storage, size);
		mAttributes.PushBack(name);
	}

	void Attributed::AddExternalAttribute(const std::string & name, glm::mat4 * const storage, std::uint32_t size)
	{
		if (IsPrescribedAttribute(name))
		{
			throw std::exception("Attribute is already prescribed!");
		}
		Datum& external = Append(name);
		external.SetStorage(storage, size);
		mAttributes.PushBack(name);
	}

	void Attributed::AddExternalAttribute(const std::string & name, std::string * const storage, std::uint32_t size)
	{
		if (IsPrescribedAttribute(name))
		{
			throw std::exception("Attribute is already prescribed!");
		}
		Datum& external = Append(name);
		external.SetStorage(storage, size);
		mAttributes.PushBack(name);
	}

	void Attributed::AddExternalAttribute(const std::string & name, RTTI ** const storage, std::uint32_t size)
	{
		if (IsPrescribedAttribute(name))
		{
			throw std::exception("Attribute is already prescribed!");
		}
		Datum& external = Append(name);
		external.SetStorage(storage, size);
		mAttributes.PushBack(name);
	}

}