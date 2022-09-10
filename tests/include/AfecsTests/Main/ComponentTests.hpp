#pragma once

#include <AfecsTests/TestsHeader.hpp>

TEST_CASE("Component attachment", "[World::attachComponent]")
{
	World world;

	EntityId entity = world.createEntity();

	SECTION("Check component is well attached")
	{
		REQUIRE_NOTHROW(world.attachComponent<EmptyComponent>(entity));
		REQUIRE_NOTHROW(world.attachComponent<BasicComponent>(entity));
		REQUIRE(world.isComponentAttached<EmptyComponent>(entity));
		REQUIRE(world.isComponentAttached<BasicComponent>(entity));
	}

	SECTION("Check attached component reference")
	{
		world.attachComponent<EmptyComponent>(entity);
		CHECK(&world.getComponent<EmptyComponent>(entity) ==
			  &world.getComponent<EmptyComponent>(entity));
	}

	SECTION("Check attached component value")
	{
		world.attachComponent<BasicComponent>(entity, 2);
		CHECK(2 == world.getComponent<BasicComponent>(entity).integer);
	}
}

TEST_CASE("Component detachment", "[World::detachComponent]")
{
	World world;

	EntityId entity = world.createEntity();
	world.attachComponent<EmptyComponent>(entity);
	world.attachComponent<BasicComponent>(entity);

	SECTION("Check component is well detached")
	{
		REQUIRE_NOTHROW(world.detachComponent<EmptyComponent>(entity));
		REQUIRE(!world.isComponentAttached<EmptyComponent>(entity));
		REQUIRE(world.isComponentAttached<BasicComponent>(entity));
	}
}

TEST_CASE("Component activation", "[World::enableComponent]")
{
	World world;

	EntityId entity = world.createEntity();
	world.attachComponent<EmptyComponent>(entity);
	world.attachComponent<BasicComponent>(entity);

	SECTION("Check component is well activated")
	{
		REQUIRE(world.isComponentEnabled<EmptyComponent>(entity));
		REQUIRE(world.isComponentEnabled<BasicComponent>(entity));
	}
}

TEST_CASE("Component deactivation", "[Componworld::disableComponent]")
{
	World world;

	EntityId entity = world.createEntity();
	world.attachComponent<EmptyComponent>(entity);
	world.attachComponent<BasicComponent>(entity);

	SECTION("Check component is well deactivated")
	{
		REQUIRE_NOTHROW(world.disableComponent<EmptyComponent>(entity));
		REQUIRE(!world.isComponentEnabled<EmptyComponent>(entity));
		REQUIRE(world.isComponentEnabled<BasicComponent>(entity));
	}

	SECTION("Check component is well reactived")
	{
		REQUIRE_NOTHROW(world.disableComponent<EmptyComponent>(entity));
		REQUIRE_NOTHROW(world.enableComponent<EmptyComponent>(entity));
		REQUIRE(world.isComponentEnabled<EmptyComponent>(entity));
		REQUIRE(world.isComponentEnabled<BasicComponent>(entity));
	}
}