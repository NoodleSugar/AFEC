#include <afecs/World.hpp>
#include <afecs/WorldComponentView.hpp>

#include <afecs/ISystem.hpp>

namespace afecs
{

EntityId World::createEntity()
{
	EntityId id = m_entityPool.pull();
	m_signatures.insert(id);
	return id;
}

void World::deleteEntity(EntityId id)
{
	m_signatures.erase(id);
	m_entityPool.push(id);
}

void World::update(float dt)
{
	WorldComponentView view(*this);

	for(auto& [typeId, info]: m_systemInfos)
	{
		SelectionRange range(info.selection.cbegin(), info.selection.cend());
		info.pSystem->update(view, range, dt);
	}
}

} // namespace afecs
