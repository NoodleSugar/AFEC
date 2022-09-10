#pragma once

#include <afecs/utils/id/Id.hpp>
#include <afecs/utils/id/TypeIdFamily.hpp>

#include <EASTL/bitset.h>
#include <EASTL/initializer_list.h>
#include <EASTL/iterator.h>

namespace afecs
{

class Signature
{
	using BitSet = eastl::bitset<MaxComponentTypeNumber>;

	class Iterator
	{
		Iterator(BitSet& rBitSet, size_t pos) :
			m_rBitSet(rBitSet), m_id(pos) {}

	public:
		using iterator_category = eastl::input_iterator_tag;
		using difference_type	= size_t;
		using value_type		= ComponentTypeId;
		using pointer			= const value_type*;
		using reference			= const value_type&;

		static Iterator createBegin(BitSet& rBitSet)
		{
			return Iterator(rBitSet, rBitSet.find_first());
		}

		static Iterator createEnd(BitSet& rBitSet)
		{
			return Iterator(rBitSet, rBitSet.find_last());
		}

		value_type operator*() const
		{
			return m_id;
		}

		Iterator& operator++()
		{
			m_id = m_rBitSet.find_next(m_id);
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator tmp = *this;
			(*this)++;
			return tmp;
		}

		friend bool operator==(const Iterator& it1, const Iterator& it2)
		{
			return &it1.m_rBitSet == &it2.m_rBitSet && it1.m_id == it2.m_id;
		};

		friend bool operator!=(const Iterator& it1, const Iterator& it2)
		{
			return !(it1 == it2);
		};

	private:
		BitSet&			m_rBitSet;
		ComponentTypeId m_id;
	};

public:
	Signature(std::initializer_list<ComponentTypeId> typeIdList)
	{
		for(auto typeId: typeIdList)
			m_bits.set(typeId);
	}

	Signature()					= default;
	Signature(const Signature&) = default;
	Signature(Signature&&)		= default;

	Signature& operator=(const Signature&) = default;
	Signature& operator=(Signature&&)	   = default;

	auto begin() { return Iterator::createBegin(m_bits); }
	auto end() { return Iterator::createEnd(m_bits); }

	template<class C>
	void insert()
	{
		m_bits.set(ComponentTypeIdFamily::idOf<C>());
	}

	template<class C>
	void erase()
	{
		m_bits.set(ComponentTypeIdFamily::idOf<C>(), false);
	}

	void clear()
	{
		m_bits.reset();
	}

	template<class C>
	bool contains() const
	{
		return m_bits[ComponentTypeIdFamily::idOf<C>()];
	}

	bool doesFitIn(const Signature& signature) const
	{
		return (signature.m_bits | this->m_bits) == signature.m_bits;
	}

	template<class... Types>
	static Signature create()
	{
		return Signature({ComponentTypeIdFamily::idOf<Types>()...});
	}

private:
	BitSet m_bits;
};

} // namespace afecs