#pragma once

#include <afecs/utils/id/Id.hpp>

#include <EASTL/vector_map.h>

#include <cassert>
#include <utility>

namespace afecs
{

class IComponentContainer
{
public:
	virtual ~IComponentContainer() {}

	virtual void erase(EntityId) = 0;
};

template<class C>
class ComponentContainer : public IComponentContainer
{
	using ThisType = ComponentContainer<C>;

public:
	ComponentContainer()				= default;
	ComponentContainer(const ThisType&) = delete;
	ComponentContainer(ThisType&&)		= delete;

	ThisType& operator=(const ThisType&) = delete;
	ThisType& operator=(ThisType&&)		 = delete;

	template<class... Args>
	void insert(EntityId id, Args&&... rArgs)
	{
		assert(!contains(id) &&
			   "Component is already attached to this entity");
		m_components.emplace(id, C{std::forward<Args>(rArgs)...});
	}

	void erase(EntityId id) override
	{
		assert(contains(id) &&
			   "Component is not attached to this entity");

		m_components.erase(id);
	}

	C& at(EntityId id)
	{
		assert(contains(id) &&
			   "Component is not attached to this entity");

		return m_components.at(id).second;
	}

	const C& at(EntityId id) const
	{
		return at(id);
	}

	bool contains(EntityId id) const
	{
		return m_components.find(id) != m_components.end();
	}

private:
	eastl::vector_map<EntityId, C> m_components;
};

} // namespace afecs