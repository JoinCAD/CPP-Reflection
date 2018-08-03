#pragma once

#include "Variant.h"
#include "VariantBase.h"
#include "VariantContainer.h"
#include "VariantPolicy.h"

#include "Array.h"
#include "TypeConfig.h"
#include "ObjectWrapper.h"
#include "Object.h"

#pragma once

#include "VariantBase.h"
#include "MetaTraits.h"
#include "Object.h"

namespace ursine
{
	namespace meta
	{
		template<typename T>
		class TeighaVariantContainer : public ursine::meta::VariantContainer<T>
		{
		public:
			typedef typename std::remove_reference<T>::type NonRefType;

			TeighaVariantContainer(const NonRefType &value) : VariantContainer<T>(value)
			{
			}

			TeighaVariantContainer(const NonRefType &&value) : VariantContainer<T>(value)
			{
			}

			void *GetPtr(void) const override;
		};
	}
}

#include "Impl/TeighaVariantContainer.hpp"

