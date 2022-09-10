#pragma once

#include <afecs/utils/id/Id.hpp>

#include <boost/range/iterator_range_core.hpp>

#include <EASTL/vector_set.h>

namespace afecs
{

using Selection = eastl::vector_set<EntityId>;
using SelectionRange = boost::iterator_range<Selection::const_iterator>;

} // namespace afecs
