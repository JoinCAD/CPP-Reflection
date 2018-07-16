#pragma once

#include "Variant.h"
#include "VariantBase.h"
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
		class TeighaVariantContainer : public VariantBase
		{
		public:
			typedef typename std::remove_reference<T>::type NonRefType;

			TeighaVariantContainer(const NonRefType &value);
			TeighaVariantContainer(const NonRefType &&value);

			Type GetType(void) const override;

			void *GetPtr(void) const override;

			int ToInt(void) const override;
			bool ToBool(void) const override;
			float ToFloat(void) const override;
			double ToDouble(void) const override;
			std::string ToString(void) const override;

			VariantBase *Clone(void) const override;

			void OnSerialize(Json::object &output) const override;
			void OnDeserialize(const Json &input) override;
		private:
			friend class Variant;

			T m_value;

			TeighaVariantContainer  &operator=(const TeighaVariantContainer &rhs) = delete;

			template<typename U = T>
			std::string getString(
				typename std::enable_if<
				!std::is_arithmetic<U>::value
				>::type* = nullptr
			) const;

			template<typename U = T>
			std::string getString(
				typename std::enable_if<
				std::is_arithmetic<U>::value
				>::type* = nullptr
			) const;

			template<typename U = T>
			void onSerialize(
				Json::object &output,
				typename std::enable_if<
				!std::is_pointer<U>::value && std::is_base_of<Object, U>::value
				>::type* = nullptr
			) const;

			template<typename U = T>
			void onSerialize(
				Json::object &output,
				typename std::enable_if<
				std::is_pointer<U>::value || !std::is_base_of<Object, U>::value
				>::type* = nullptr
			) const;

			template<typename U = T>
			void onDeserialize(
				const Json &input,
				typename std::enable_if<
				!std::is_pointer<U>::value && std::is_base_of<Object, U>::value
				>::type* = nullptr
			);

			template<typename U = T>
			void onDeserialize(
				const Json &input,
				typename std::enable_if<
				std::is_pointer<U>::value || !std::is_base_of<Object, U>::value
				>::type* = nullptr
			);
		};
	}
}

