#pragma once

#include <AfecsTests/TestsHeader.hpp>

TEST_CASE("Entity Pool allocation", "[ReusableIdAllocator::pull]")
{
	EntityPool pool;

	SECTION("Allocate multiple id")
	{
		constexpr int steps = 10;

		std::vector<Id> ids;
		ids.reserve(steps);

		for(int i = 0; i < steps; ++i)
		{
			Id id = pool.pull();
			REQUIRE_THAT(ids, !VectorContains(id));
			ids.push_back(id);
		}
	}

	SECTION("Reallocate released id")
	{
		Id firstId = pool.pull();
		pool.push(firstId);
		Id secondId = pool.pull();

		CHECK(firstId == secondId);
	}
}

TEST_CASE("Entity Pool release", "[EntityPool::push]")
{
	EntityPool pool;

	constexpr int steps = 10;

	std::vector<Id> ids;
	ids.reserve(steps);

	for(int i = 0; i < steps; ++i)
		ids.push_back(pool.pull());

	SECTION("Release multiple ids")
	{
		for(Id i = 0; i < steps; ++i)
			REQUIRE_NOTHROW(pool.push(i));
	}
}

TEST_CASE("Entity Creation", "[World::createEntity]")
{
	World world;

	SECTION("Check uniqueness of entity ids")
	{
		constexpr int steps = 10;

		std::vector<EntityId> entities;
		entities.reserve(steps);

		for(int i = 0; i < steps; ++i)
		{
			EntityId id = world.createEntity();
			REQUIRE_THAT(entities, !VectorContains(id));
			entities.push_back(id);
		}
	}
}