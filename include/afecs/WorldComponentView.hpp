#pragma once

#include <afecs/World.hpp>
#include <afecs/utils/id/Id.hpp>

namespace afecs
{

class WorldComponentView
{
public:
	WorldComponentView(World& world) :
		m_rWorld(world) {}

	template<class C>
	C& get(EntityId id)
	{
		return m_rWorld.getComponent<C>(id);
	}

private:
	World& m_rWorld;
};

} // namespace sngine
