#pragma once
#include "type_traits.h"

namespace engine {
template<typename T, typename... TypeList>
concept in_type_list_v = in_type_list<T, TypeList...>::value;
} // namespace engine