#pragma once

#include <AfecsTests/TestsHeader.hpp>

using BasicContainer = afecs::ComponentContainer<BasicComponent>;

TEST_CASE("Testing Component Containers insertion", "[ComponentContainer::insert]")
{
	BasicContainer container;

	SECTION("Check element is well inserted")
	{
		REQUIRE_NOTHROW(container.insert(0, 10));
		CHECK(container.contains(0));
		CHECK(10 == container.at(0).integer);
	}
}

TEST_CASE("Testing Component Containers erasure", "[ComponentContainer::erase]")
{
	BasicContainer container;

	container.insert(0, 10);

	SECTION("Check element is well erased")
	{
		REQUIRE_NOTHROW(container.erase(0));
		CHECK(!container.contains(0));
	}
}