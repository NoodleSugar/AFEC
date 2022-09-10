#pragma once

#include <AfecsTests/TestsHeader.hpp>

TEST_CASE("System initialization", "[World::attachSystem]")
{
	World world;

	SECTION("Check systems are well attached")
	{
		REQUIRE_NOTHROW(world.attachSystem<EmptySystem>());
		REQUIRE_NOTHROW(world.attachSystem<BasicSystem>());
		REQUIRE_NOTHROW(world.getSystem<EmptySystem>());
		REQUIRE_NOTHROW(world.getSystem<BasicSystem>());
	}
}

TEST_CASE("System activation", "[World::enableSystem]")
{
	World world;

	world.attachSystem<EmptySystem>();
	world.attachSystem<BasicSystem>();

	SECTION("Check systems are well activated")
	{
		CHECK(world.isSystemEnabled<EmptySystem>());
		CHECK(world.isSystemEnabled<BasicSystem>());
	}
}

TEST_CASE("System deactivation", "[World::disableSystem]")
{
	World world;

	world.attachSystem<EmptySystem>();
	world.attachSystem<BasicSystem>();

	SECTION("Check systems are well deactivated")
	{
		REQUIRE_NOTHROW(world.disableSystem<EmptySystem>());
		CHECK(!world.isSystemEnabled<EmptySystem>());
		CHECK(world.isSystemEnabled<BasicSystem>());
	}

	SECTION("Check component is well reactived")
	{
		REQUIRE_NOTHROW(world.disableSystem<EmptySystem>());
		REQUIRE_NOTHROW(world.enableSystem<EmptySystem>());
		CHECK(world.isSystemEnabled<EmptySystem>());
		CHECK(world.isSystemEnabled<BasicSystem>());
	}
}

TEST_CASE("System update", "[World::update]")
{
	World world;

	EntityId id = world.createEntity();

	world.attachSystem<BasicSystem>();
	world.attachComponent<BasicComponent>(id, 0);

	SECTION("Check component is well updated")
	{
		REQUIRE_NOTHROW(world.update(0.0f));
		CHECK(1 == world.getComponent<BasicComponent>(id).integer);
	}
}