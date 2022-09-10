#pragma once

#include <afecs/utils/id/Id.hpp>

#include <EASTL/priority_queue.h>

namespace afecs
{

class EntityPool
{
public:
	EntityId pull()
	{
		if(m_queue.empty())
			return m_topId++;

		size_t id = m_queue.top();
		m_queue.pop();

		return id;
	}

	void push(EntityId id)
	{
		m_queue.push(id);
	}

private:
	EntityId m_topId = 0;

	eastl::priority_queue<EntityId> m_queue;
};

} // namespace afecs
