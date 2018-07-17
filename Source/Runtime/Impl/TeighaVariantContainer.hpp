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
		void *TeighaVariantContainer<T>::GetPtr(void) const
		{
			//return teigha object pointer
			return (void*)m_value;
		}
	}
}

#if defined(COMPILER_MSVC)

#pragma warning(pop)

#endif
