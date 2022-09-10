#pragma once

#include <AfecsTests/TestsHeader.hpp>

TEST_CASE("Signature creation", "[Signature::create]")
{
	Signature signature;

	SECTION("Check signature is empty")
	{
		CHECK(!signature.contains<EmptyComponent>());
		CHECK(!signature.contains<BasicComponent>());
	}

	SECTION("Check signature is well created")
	{
		REQUIRE_NOTHROW(signature = Signature::create<EmptyComponent, BasicComponent>());
		CHECK(signature.contains<EmptyComponent>());
		CHECK(signature.contains<BasicComponent>());
	}
}

TEST_CASE("Signature insertion", "[Signature::insert]")
{
	Signature signature;

	SECTION("Check element is well inserted")
	{
		REQUIRE_NOTHROW(signature.insert<EmptyComponent>());
		CHECK(signature.contains<EmptyComponent>());
		CHECK(!signature.contains<BasicComponent>());
	}
}

TEST_CASE("Signature erasure", "[Signature::erase]")
{
	Signature signature = Signature::create<EmptyComponent, BasicComponent>();

	SECTION("Check element is well erased")
	{
		REQUIRE_NOTHROW(signature.erase<EmptyComponent>());
		CHECK(!signature.contains<EmptyComponent>());
		CHECK(signature.contains<BasicComponent>());
	}
}

TEST_CASE("Signature clearing", "[Signature::clear]")
{
	Signature signature = Signature::create<EmptyComponent, BasicComponent>();

	SECTION("Check element is well erased")
	{
		REQUIRE_NOTHROW(signature.clear());
		CHECK(!signature.contains<EmptyComponent>());
		CHECK(!signature.contains<BasicComponent>());
	}
}

TEST_CASE("Signature inclusion", "[Signature::doesFitIn]")
{
	Signature emptySig;
	Signature firstSig	= Signature::create<EmptyComponent>();
	Signature secondSig = Signature::create<BasicComponent>();
	Signature fullSig	= Signature::create<EmptyComponent, BasicComponent>();

	SECTION("Check inclusion is reflexive")
	{
		CHECK(emptySig.doesFitIn(emptySig));
		CHECK(firstSig.doesFitIn(firstSig));
		CHECK(secondSig.doesFitIn(secondSig));
		CHECK(fullSig.doesFitIn(fullSig));
	}

	SECTION("Check inclusions")
	{
		CHECK(emptySig.doesFitIn(firstSig));
		CHECK(emptySig.doesFitIn(secondSig));
		CHECK(emptySig.doesFitIn(fullSig));

		CHECK(!firstSig.doesFitIn(emptySig));
		CHECK(!firstSig.doesFitIn(secondSig));
		CHECK(firstSig.doesFitIn(fullSig));

		CHECK(!secondSig.doesFitIn(emptySig));
		CHECK(!secondSig.doesFitIn(firstSig));
		CHECK(secondSig.doesFitIn(fullSig));

		CHECK(!fullSig.doesFitIn(emptySig));
		CHECK(!fullSig.doesFitIn(firstSig));
		CHECK(!fullSig.doesFitIn(secondSig));
	}
}