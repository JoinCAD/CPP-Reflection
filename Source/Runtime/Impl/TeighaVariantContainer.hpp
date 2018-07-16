#pragma once

#include "../Type.h"
#include "../Common/Compiler.h"

#if defined(COMPILER_MSVC)

#pragma warning(push)

// unused template parameters
#pragma warning(disable : 4544)

// implicit conversion performance warnings
#pragma warning(disable : 4800)

// possible loss of data
#pragma warning(disable : 4244)

#endif                                                                                          

namespace ursine
{
	namespace meta
	{
		template<typename T>
		TeighaVariantContainer<T>::TeighaVariantContainer(const NonRefType &value)
			: m_value(const_cast<NonRefType&>(value))
		{

		}

		///////////////////////////////////////////////////////////////////////

		template<typename T>
		TeighaVariantContainer<T>::TeighaVariantContainer(const NonRefType &&value)
			: m_value(std::move(const_cast<NonRefType&&>(value)))
		{

		}

		///////////////////////////////////////////////////////////////////////

		template<typename T>
		Type TeighaVariantContainer<T>::GetType(void) const
		{
			return typeof(T);
		}

		///////////////////////////////////////////////////////////////////////

		template<typename T>
		int TeighaVariantContainer<T>::ToInt(void) const
		{
			return getint();
		}

		///////////////////////////////////////////////////////////////////////

		template<typename T>
		bool TeighaVariantContainer<T>::ToBool(void) const
		{
			return getbool();
		}

		///////////////////////////////////////////////////////////////////////

		template<typename T>
		float TeighaVariantContainer<T>::ToFloat(void) const
		{
			return getfloat();
		}

		///////////////////////////////////////////////////////////////////////

		template<typename T>
		double TeighaVariantContainer<T>::ToDouble(void) const
		{
			return getdouble();
		}

		///////////////////////////////////////////////////////////////////////

		template<typename T>
		std::string TeighaVariantContainer<T>::ToString(void) const
		{
			return getString();
		}

		///////////////////////////////////////////////////////////////////////

		template<typename T>
		void *TeighaVariantContainer<T>::GetPtr(void) const
		{
			return (void*)m_value
		}

		///////////////////////////////////////////////////////////////////////

		template<typename T>
		VariantBase *TeighaVariantContainer<T>::Clone(void) const
		{
			// use the non reference type to ensure a copy is made
			return new TeighaVariantContainer<NonRefType>(m_value);
		}

		template<typename T>
		void TeighaVariantContainer<T>::OnSerialize(Json::object &output) const
		{
			// do nothing
		}

		template<typename T>
		void TeighaVariantContainer<T>::OnDeserialize(const Json &input)
		{
			// do nothing
		}

		///////////////////////////////////////////////////////////////////////

		template<typename T>
		template<typename U>
		std::string TeighaVariantContainer<T>::getString(
			typename std::enable_if<
			!std::is_arithmetic<U>::value
			>::type*
		) const
		{
			return std::string();
		}

		template<typename T>
		template<typename U>
		std::string TeighaVariantContainer<T>::getString(
			typename std::enable_if<
			std::is_arithmetic<U>::value
			>::type*
		) const
		{
			return std::to_string(m_value);
		}

		template<typename T>
		template<typename U>
		void TeighaVariantContainer<T>::onSerialize(
			Json::object &output,
			typename std::enable_if<
			!std::is_pointer<U>::value && std::is_base_of<Object, U>::value
			>::type*
		) const
		{
			// do nothing
		}

		template<typename T>
		template<typename U>
		void TeighaVariantContainer<T>::onSerialize(
			Json::object &output,
			typename std::enable_if<
			std::is_pointer<U>::value || !std::is_base_of<Object, U>::value
			>::type*
		) const
		{
			// do nothing
		}

		template<typename T>
		template<typename U>
		void TeighaVariantContainer<T>::onDeserialize(
			const Json &input,
			typename std::enable_if<
			!std::is_pointer<U>::value && std::is_base_of<Object, U>::value
			>::type*
		)
		{
			// do nothing
		}

		template<typename T>
		template<typename U>
		void TeighaVariantContainer<T>::onDeserialize(
			const Json &input,
			typename std::enable_if<
			std::is_pointer<U>::value || !std::is_base_of<Object, U>::value
			>::type*
		)
		{
			// do nothing
		}
	}
}

#if defined(COMPILER_MSVC)

#pragma warning(pop)

#endif
