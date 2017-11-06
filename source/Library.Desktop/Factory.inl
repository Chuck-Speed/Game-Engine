#pragma once

#include "Factory.h"

namespace Library
{
	template<class AbstractProductT>
	inline typename Hashmap<std::string, const Factory<AbstractProductT>* const>::Iterator Factory<AbstractProductT>::begin()
	{
		return sFactoryTable.begin();
	}

	template<class AbstractProductT>
	inline typename Hashmap<std::string, const Factory<AbstractProductT>* const>::Iterator Factory<AbstractProductT>::end()
	{
		return sFactoryTable.end();
	}

	template<class AbstractProductT>
	inline const Factory<AbstractProductT>* Factory<AbstractProductT>::Find(const std::string & strClassName)
	{
		Iterator itr = sFactoryTable.Find(strClassName);
		if (itr == sFactoryTable.end())
		{
			return nullptr;
		}
		return itr->second;
	}

	template<class AbstractProductT>
	inline AbstractProductT* Factory<AbstractProductT>::Create(const std::string & strClassName)
	{
		const Factory<AbstractProductT>* factory = Find(strClassName);
		if (factory == nullptr)
		{
			return nullptr;
		}
		return factory->Create();
	}

	template<class AbstractProductT>
	inline void Factory<AbstractProductT>::Add(Factory<AbstractProductT>* pFactory)
	{
		if (pFactory != nullptr)
		{
			std::pair<std::string, Factory<AbstractProductT>*> pair(pFactory->ClassName(), pFactory);
			sFactoryTable.Insert(pair);
		}
	}
	template<class AbstractProductT>
	inline void Factory<AbstractProductT>::Remove(const Factory<AbstractProductT>* pFactory)
	{
		if (pFactory != nullptr)
		{
			sFactoryTable.Remove(pFactory->ClassName());
		}
	}
}