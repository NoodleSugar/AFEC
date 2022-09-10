#pragma once

#include <cstddef>
#include <limits>

namespace afecs
{

using id_t			  = size_t;
using EntityId		  = id_t;
using ComponentTypeId = id_t;
using SystemTypeId	  = id_t;

const size_t MaxComponentTypeNumber = 64;
const size_t MaxSystemTypeNumber	= 32;

} // namespace afecs