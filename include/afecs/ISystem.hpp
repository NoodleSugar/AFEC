#pragma once

#include <afecs/utils/Selection.hpp>

namespace afecs
{

class WorldComponentView;
class Signature;

class ISystem
{
public:
	virtual ~ISystem() = default;

	virtual void update(WorldComponentView& components, SelectionRange& entities, float dt) = 0;

	virtual const Signature& getSignature() const = 0;
};

} // namespace afecs