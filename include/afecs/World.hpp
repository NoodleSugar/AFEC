#pragma once

#include <afecs/ISystem.hpp>
#include <afecs/internal/ComponentContainer.hpp>
#include <afecs/internal/EntityPool.hpp>
#include <afecs/utils/Selection.hpp>
#include <afecs/utils/Signature.hpp>
#include <afecs/utils/id/Id.hpp>
#include <afecs/utils/id/TypeIdFamily.hpp>

#include <EASTL/fixed_map.h>
#include <EASTL/unordered_map.h>

#include <memory>

namespace afecs
{

class World
{
	using SignatureMap = eastl::unordered_map<EntityId, Signature>;

	using ContainerPtr = std::unique_ptr<IComponentContainer>;
	using ContainerMap = eastl::fixed_map<ComponentTypeId, ContainerPtr, MaxComponentTypeNumber>;

	using SystemPtr = std::unique_ptr<ISystem>;
	struct SystemInfo
	{
		bool	  enabled;
		SystemPtr pSystem;
		Selection selection;
	};
	using SystemInfoMap = eastl::fixed_map<SystemTypeId, SystemInfo, MaxSystemTypeNumber>;

public:
	World()				= default;
	World(const World&) = delete;
	World(World&&)		= delete;

	World& operator=(const World&) = delete;
	World& operator=(World&&)	   = delete;

	// Entity methods

	EntityId createEntity();
	void	 deleteEntity(EntityId);

	// Component methods

	template<class C, class... Args>
	void attachComponent(EntityId id, Args&&... rArgs)
	{
		assert(!isComponentAttached<C>(id) &&
			   "Component type is already attached to this entity");

		getComponentContainer<C>().insert(id, std::forward<Args>(rArgs)...);
		enableComponent<C>(id);
	}

	template<class C>
	void detachComponent(EntityId id)
	{
		assert(isComponentAttached<C>(id) &&
			   "Component type is not attached to this entity");

		disableComponent<C>(id);
		getComponentContainer<C>().erase(id);
	}

	template<class C>
	C& getComponent(EntityId id)
	{
		assert(isComponentAttached<C>(id) &&
			   "Component is not attached to this entity");

		return getComponentContainer<C>().at(id);
	}

	template<class C>
	bool isComponentAttached(EntityId id)
	{
		return getComponentContainer<C>().contains(id);
	}

	// Component activation methods

	template<class C>
	void enableComponent(EntityId id)
	{
		assert(isComponentAttached<C>(id) &&
			   "Component is not attached");
		assert(!isComponentEnabled<C>(id) &&
			   "Component is already enabled");

		getSignature(id).template insert<C>();

		for(auto& [i, info]: m_systemInfos)
		{
			if(getSignature(id).doesFitIn(info.pSystem->getSignature()))
				info.selection.insert(id);
		}
	}

	template<class C>
	void disableComponent(EntityId id)
	{
		assert(isComponentAttached<C>(id) &&
			   "Component is not attached");
		assert(isComponentEnabled<C>(id) &&
			   "Component is already disabled");

		getSignature(id).template erase<C>();

		for(auto& [i, info]: m_systemInfos)
		{
			if(info.pSystem->getSignature().template contains<C>())
				info.selection.erase(id);
		}
	}

	template<class C>
	bool isComponentEnabled(EntityId id)
	{
		return getSignature(id).template contains<C>();
	}

	// System methods

	template<class S>
	void attachSystem()
	{
		assert(!isSystemAttached<S>() &&
			   "System type already attached to this world");

		auto&& [pair, b] = m_systemInfos.emplace(SystemTypeIdFamily::idOf<S>(), SystemInfo{true, std::make_unique<S>(), Selection()});
		auto&& [i, info] = *pair;

		for(auto& [id, signature]: m_signatures)
		{
			if(info.pSystem->getSignature().doesFitIn(signature))
				info.selection.insert(id);
		}
	}

	template<class S>
	void detachSystem()
	{
		assert(isSystemAttached<S>() &&
			   "System type is not attached to this world");

		m_systemInfos.erase(SystemTypeIdFamily::idOf<S>());
	}

	template<class S>
	S& getSystem()
	{
		assert(isSystemAttached<S>() &&
			   "System is not attached to this world");

		return static_cast<S&>(*getSystemInfo<S>().pSystem);
	}

	template<class S>
	bool isSystemAttached()
	{
		return m_systemInfos.find(SystemTypeIdFamily::idOf<S>()) != m_systemInfos.cend();
	}

	// Systems activation methods

	template<class S>
	void enableSystem()
	{
		assert(isSystemAttached<S>() &&
			   "System is not attached");
		assert(!isSystemEnabled<S>() &&
			   "System is already enabled");

		getSystemInfo<S>().enabled = true;
	}

	template<class S>
	void disableSystem()
	{
		assert(isSystemAttached<S>() &&
			   "System is not attached");
		assert(isSystemEnabled<S>() &&
			   "System is already disabled");

		getSystemInfo<S>().enabled = false;
	}

	template<class S>
	bool isSystemEnabled()
	{
		return getSystemInfo<S>().enabled;
	}

	// Update world
	void update(float dt);

private:
	Signature& getSignature(EntityId id)
	{
		return m_signatures.at(id);
	}

	void detachAllComponents(EntityId id)
	{
		for(const auto typeId: m_signatures.at(id))
			m_containers.at(typeId)->erase(id);

		getSignature(id).clear();
	}

	template<class C>
	ComponentContainer<C>& getComponentContainer()
	{
		static const ComponentTypeId typeId = ComponentTypeIdFamily::idOf<C>();

		auto* pContainer = m_containers.at(typeId).get();
		if(pContainer == nullptr)
		{
			auto&& [pair, b] = m_containers.emplace(typeId, std::make_unique<ComponentContainer<C>>());

			pContainer = pair->second.get();
		}

		return static_cast<ComponentContainer<C>&>(*pContainer);
	}

	template<class S>
	SystemInfo& getSystemInfo()
	{
		return m_systemInfos.at(SystemTypeIdFamily::idOf<S>());
	}

private:
	EntityPool	  m_entityPool;
	SignatureMap  m_signatures;
	ContainerMap  m_containers;
	SystemInfoMap m_systemInfos;
};

} // namespace afecs