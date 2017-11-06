#include "pch.h"


namespace Library

{
	RTTI_DEFINITIONS(Scope)

	Scope::Scope(std::uint32_t capacity) :
		mArray(capacity), mTable(), mParent(nullptr)
	{
	}

	Scope::~Scope()
	{
		Clear();
	}

	Scope::Scope(const Scope & rhs) :
		mParent(nullptr), mTable(), mArray(0)
	{
		operator=(rhs);
	}

	Scope & Scope::operator=(const Scope & rhs)
	{
		if (this != &rhs)
		{
			Clear();
			for (uint32_t i = 0; i < rhs.mArray.Size(); ++i)
			{
				Datum& datumToCopy = rhs.mArray[i]->second;
				if (datumToCopy.Type() == Datum::DatumType::TABLE)
				{
					for (uint32_t j = 0; j < datumToCopy.Size(); ++j)
					{
						Scope* s = new Scope(datumToCopy[j]);
						Adopt(*s, rhs.mArray[i]->first);
					}
				}
				else
				{
					Datum& newDatum = Append(rhs.mArray[i]->first);
					newDatum = datumToCopy;
				}
			}
		}
		return *this;
	}

	Datum* Scope::Find(const std::string& name) const
	{
		if (!name.empty())
		{
			auto result = mTable.Find(name);
			if (result != mTable.end())
			{
				return &result->second;
			}
		}
		return nullptr;
	}

	Datum * Scope::Search(const std::string& name,  const Scope ** foundScope) const
	{
		Datum* foundDatum = Find(name);
		if (foundDatum != nullptr)
		{
			if (foundScope != nullptr)
			{
				*foundScope = this;
			}
			return foundDatum;
		}
		else if (mParent != nullptr)
		{
			return mParent->Search(name, foundScope);
		}
		else
		{
			if (foundScope != nullptr)
			{
				*foundScope = nullptr;
			}
		}
		return nullptr;
	}

	Datum & Scope::Append(const std::string& name)
	{
		if (name.empty())
		{
			throw std::invalid_argument("Name cannot be empty.");
		}

		bool inserted;
		PairType pair = PairType(name, Datum());
		auto result = mTable.Insert(pair, inserted);
		if (inserted)
		{
			mArray.PushBack(&(*result));
		}
		return (*result).second;
	}

	Scope & Scope::AppendScope(const std::string& name)
	{
		Datum& result = Append(name);

		if (result.Type() == Datum::DatumType::UNKNOWN)
		{
			result.SetType(Datum::DatumType::TABLE);
		}
		else if (result.Type() != Datum::DatumType::TABLE)
		{
			throw std::exception("Cannot append scope with a non-table Datum.");
		}

		Scope* scope = new Scope();
		scope->mParent = this;
		result.PushBack(scope);
		return *scope;
	}

	void Scope::Adopt(Scope & child, const std::string& name)
	{
		if (name.empty())
		{
			throw std::invalid_argument("Name cannot be empty.");
		}

		if (this != &child)
		{
			child.Orphan();
			Datum& datum = Append(name);
			datum.PushBack(&child);
			child.mParent = this;
		}
	}

	void Scope::Orphan()
	{
		if (mParent == nullptr)
		{
			return;
		}

		uint32_t index;
		Datum* foundChild = mParent->FindContainedScope(*this, index);
		if (foundChild == nullptr)
		{
			throw std::exception("Non-mutual relation between parent and child.");
		}

		foundChild->Remove(index);
		mParent = nullptr;
	}

	Scope * Scope::GetParent()
	{
		return mParent;
	}

	std::uint32_t Scope::Size() const
	{
		return mArray.Size();
	}

	std::string& Scope::GetNameAt(uint32_t index) const
	{
		return mArray[index]->first;
	}

	Datum & Scope::operator[](const std::string& name)
	{
		return Append(name);
	}

	Datum& Scope::operator[](const std::uint32_t index)
	{
		if (index >= mArray.Size())
		{
			throw std::out_of_range("Index out of bounds.");
		}
		return mArray[index]->second;
	}

	bool Scope::operator==(const Scope & rhs) const
	{
		if (this == &rhs)
		{
			return true;
		}

		if (mArray.Size() == rhs.mArray.Size())
		{
			for (uint32_t i = 0; i < mArray.Size(); ++i)
			{
				if (*(mArray[i]) != *(rhs.mArray[i]))
				{
					return false;
				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Scope::operator!=(const Scope & rhs) const
	{
		return !operator==(rhs);
	}

	std::string Scope::FindName(const Scope & scope) const
	{
		if (scope.mParent == this)
		{
			for (uint32_t i = 0; i < mArray.Size(); ++i)
			{
				Datum& datum = mArray[i]->second;
				if (datum.Type() == Datum::DatumType::TABLE)
				{
					for (uint32_t j = 0; j < datum.Size(); ++j)
					{
						if (datum[j] == scope)
						{
							return mArray[i]->first;
						}
					}
				}
			}
		}
		return std::string();
	}

	Datum * Scope::FindContainedScope(Scope & scope, std::uint32_t & index) const
	{
		for (uint32_t i = 0; i < mArray.Size(); ++i)
		{
			Datum& datum = mArray[i]->second;
			if (datum.Type() == Datum::DatumType::TABLE)
			{
				for (uint32_t j = 0; j < datum.Size(); ++j)
				{
					if (&(datum[j]) == &scope)
					{
						index = j;
						return &datum;
					}
				}
			}
		}
		return nullptr;
	}

	void Scope::Clear()
	{
		Orphan();
		for (uint32_t i = 0; i < mArray.Size(); ++i)
		{
			Datum& datum = mArray[i]->second;
			if (datum.Type() == Datum::DatumType::TABLE)
			{
				for (int32_t j = datum.Size() - 1; j >= 0; --j)
				{
					mParent = nullptr; //Short-circuit orphan call
					delete (datum.Get<Scope*>(j));
				}
			}
		}
		mArray.Clear();
		mTable.Clear();
	}
}