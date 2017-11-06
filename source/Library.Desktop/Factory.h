#pragma once

#include "Hashmap.h"

namespace Library
{
	/**
	*@class Factory
	*@brief Implements factory pattern.
	*/
	template<class AbstractProductT>
	class Factory
	{
		//Interface
	public:
		typedef typename Hashmap<std::string, const Factory<AbstractProductT>* const >::Iterator Iterator;

		/**
		*@brief Destructor for Factory (default)
		*/
		virtual ~Factory() = default;

		/**
		*@brief Return a string representing the name of the class the factory instantiates
		*@return std::string The name of the class the factory instantiates.
		*/
		virtual std::string ClassName() const = 0;

	private:
		/**
		*@brief Return the address of a concrete product associated with this concrete factory class
		*@return AbstractProductT* The address of the product associated with the concrete factory
		*/
		virtual AbstractProductT* Create() const = 0;


		//Manager (Singleton)
	public:
		/**
		*@brief Given a class name (string), return the associated concrete factory
		*@param strClassName Reference to a string containing the name of the class a factory instantiates
		*@return Factory<AbstractProductT>* The associated concrete factory
		*/
		static const Factory<AbstractProductT>* Find(const std::string& strClassName);

		/**
		*@brief Given a class name (string), return a new object of that type. The object returned must be deleted manually.
		*@param strClassName Reference to a string containing the name of the class the factory instantiates
		*@return AbstractProductT* New object of the specified type.
		*/
		static AbstractProductT* Create(const std::string& strClassName);

		/**
		*@brief Returns an interator for the container of factories
		*@return Hashmap<std::string, Factory<AbstractProductT>*>::Iterator
		*/
		static Iterator begin();

		/**
		*@brief Returns an interator one past the last factory in the container
		*@return Hashmap<std::string, Factory<AbstractProductT>*>::Iterator
		*/
		static Iterator end();

	protected:
		/**
		*@brief Given a reference to a concrete factory, add it to the list of factories for this abstract factory
		*@param pFactory Reference to a factory that will be added to the container
		*/
		static void Add(Factory<AbstractProductT>* pFactory);

		/**
		*@brief Given a reference to a concrete factory, remove it from the list of factories for this abstract factory
		*@param pFactory Reference to a factory that will be removed to the container
		*/
		static void Remove(const Factory<AbstractProductT>* pFactory);

	private:
		static Hashmap<std::string, const Factory<AbstractProductT>* const> sFactoryTable;

	public:
#define ConcreteFactory( AbstractProductT, ConcreteProductT )         \
    class ConcreteProductT ## Factory final : Factory<AbstractProductT>\
    {                                                                 \
        public:                                                       \
             ConcreteProductT ## Factory()  { Add ( this ); }         \
            ~ConcreteProductT ## Factory()  { Remove( this ); }       \
            virtual std::string ClassName()	const override			  \
			{ return # ConcreteProductT ; }							  \
            virtual AbstractProductT*  Create()	const override		  \
            {                                                         \
                AbstractProductT* product = new ConcreteProductT();   \
                assert( product != nullptr );                         \
                return product;                                       \
            }                                                         \
	} ;

	};

	//Instance of factory container
	template <class AbstractProductT>
	Hashmap<std::string, const Factory<AbstractProductT>* const> Factory<AbstractProductT>::sFactoryTable;
}

#include "Factory.inl"