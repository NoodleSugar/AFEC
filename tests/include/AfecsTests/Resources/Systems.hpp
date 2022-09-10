#pragma once

#include <afecs/ISystem.hpp>
#include <afecs/WorldComponentView.hpp>
#include <afecs/utils/Selection.hpp>
#include <afecs/utils/Signature.hpp>

using afecs::SelectionRange;
using afecs::Signature;
using afecs::WorldComponentView;

class EmptySystem : public afecs::ISystem
{
public:
	void update(WorldComponentView&, SelectionRange&, float) override {}

	const Signature& getSignature() const override
	{
		static const Signature s = Signature::template create<EmptyComponent>();
		return s;
	}
};

class BasicSystem : public afecs::ISystem
{
public:
	void update(WorldComponentView& view, SelectionRange& selection, float) override
	{
		for(auto id: selection)
			view.get<BasicComponent>(id).integer++;
	}

	const Signature& getSignature() const override
	{
		static const Signature s = Signature::template create<BasicComponent>();
		return s;
	}
};
