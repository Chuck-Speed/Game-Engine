#pragma once

#include "Scope.h"

namespace Library
{
	class AttributedFoo;

	/**
	*@class Attributed
	*@brief Class for attributed objects.
	*/
	class Attributed : public Scope
	{
		RTTI_DECLARATIONS(Attributed, Scope)

	public:
		typedef Datum::DatumType DatumType;

		/**
		*@brief Default constructor for Attributed objects.
		*/
		Attributed();

		/**
		*@brief Pure virtual destructor for Attributed objects.
		*/
		virtual ~Attributed() = 0;

		/**
		*@brief Copy constructor for Attributed object.
		*@param rhs const reference to an Attributed object.
		*/
		Attributed(const Attributed& rhs);

		/**
		*@brief Assignment operator
		*@param rhs const reference to a Attributed object.
		*@return Attributed& reference to the newly assigned Attributed object.
		*/
		Attributed& operator=(const Attributed& rhs);

		/**
		*@brief Move constructor for Attributed object.
		*@param rhs r-value reference of an Attributed object.
		*/
		Attributed(Attributed&& rhs);

		/**
		*@brief Given a string, return a bool indicating whether it is the name of a prescribed attribute for this class.
		*@param name Name to check against the prescribed attribute.
		*@return bool Returns true if the given name matches the name of a prescribed attribute.
		*/
		bool IsPrescribedAttribute(const std::string& name) const;

		/**
		*@brief Given a string, return a bool indicating whether it is the name of an auxilary attribute for this object.
		*@param name Name to check against the auxiliary attribute.
		*@return bool Returns true if the given name matches the name of an auxiliary attribute for this object.
		*/
		bool IsAuxiliaryAttribute(const std::string& name) const;

		/**
		*@brief Given a string, return a bool indicating whether it is the name of an attribute for this object.
		*@param name Name to check against an attribute.
		*@return bool Returns true if the given name matches the name of an attribute for this object.
		*/
		bool IsAttribute(const std::string& name) const;

		/**
		*@brief Given a string, appends a Datum to this Scope with the given name and returns a reference to that Datum. If it already existed, the Datum is returned.
		*@param name Name of the Datum to be appended. (Name cannot match the name of a prescribed attribute).
		*@return Datum& reference to the Datum appended to this Scope.
		*/
		Datum& AppendAuxiliaryAttribute(const std::string& name);

		/**
		*@brief Retrieves the index of the first auxiliary attribute.
		*@return std::uint32_t Index of the first auxiliary attribute for this object.
		*/
		std::uint32_t AuxiliaryBegin() const;

	protected:
#pragma region AddAttribute

		void AddInternalAttribute(const std::string& name, Datum::DatumType type, const int& initial, std::uint32_t size);
		void AddInternalAttribute(const std::string& name, Datum::DatumType type, const float& initial, std::uint32_t size);
		void AddInternalAttribute(const std::string& name, Datum::DatumType type, const glm::vec4& initial, std::uint32_t size);
		void AddInternalAttribute(const std::string& name, Datum::DatumType type, const glm::mat4& initial, std::uint32_t size);
		void AddInternalAttribute(const std::string& name, Datum::DatumType type, const std::string& initial, std::uint32_t size);
		void AddInternalAttribute(const std::string& name, Datum::DatumType type, RTTI* const initial, std::uint32_t size);

		void AddExternalAttribute(const std::string& name, int* const storage, std::uint32_t size);
		void AddExternalAttribute(const std::string& name, float* const storage, std::uint32_t size);
		void AddExternalAttribute(const std::string& name, glm::vec4* const storage, std::uint32_t size);
		void AddExternalAttribute(const std::string& name, glm::mat4* const storage, std::uint32_t size);
		void AddExternalAttribute(const std::string& name, std::string* const storage, std::uint32_t size);
		void AddExternalAttribute(const std::string& name, RTTI** const storage, std::uint32_t size);
		//void AddExternalAttribute(const std::string& name, DatumType type, Datum& const storage, std::uint32_t size);

		void AddNestedScope(const std::string& name, Scope* child);
		Datum& AddNestedScope(const std::string& name);

#pragma endregion

	private:
		Vector<std::string> mAttributes;
	};
}