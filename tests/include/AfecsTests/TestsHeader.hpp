#pragma once

#include <catch2/catch.hpp>

#include "Resources/Components.hpp"
#include "Resources/Systems.hpp"

#include <afecs/World.hpp>
#include <afecs/internal/ComponentContainer.hpp>
#include <afecs/internal/EntityPool.hpp>
#include <afecs/utils/Signature.hpp>
#include <afecs/utils/id/Id.hpp>

#include <vector>

using Catch::Matchers::VectorContains;

using afecs::EntityPool;
using afecs::Signature;
using afecs::World;

using Id			  = afecs::id_t;
using EntityId		  = afecs::EntityId;
using ComponentTypeId = afecs::ComponentTypeId;
using SystemTypeId	  = afecs::SystemTypeId;