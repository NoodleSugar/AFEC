#pragma once

#include "Id.hpp"

namespace afecs
{

namespace internal
{

template<class Tag>
class TypeIdFamily final
{
public:
	static id_t next() noexcept
	{
		static id_t value = 0;
		return value++;
	}
};

struct ComponentTag;
struct SystemTag;

} // namespace internal

template<class Tag>
class TypeIdFamily final
{
public:
	template<class T>
	static id_t idOf() noexcept
	{
		static const id_t id = internal::TypeIdFamily<Tag>::next();
		return id;
	}
};

using ComponentTypeIdFamily = TypeIdFamily<internal::ComponentTag>;
using SystemTypeIdFamily	= TypeIdFamily<internal::SystemTag>;

} // namespace afecs