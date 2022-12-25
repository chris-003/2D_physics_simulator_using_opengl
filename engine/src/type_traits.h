#pragma once
#include <type_traits>

namespace engine {
template<typename T, typename... TypeList>
struct in_type_list : std::false_type {};

template<typename T>
struct in_type_list<T> : std::false_type {};

template<typename T>
struct in_type_list<T, T> : std::true_type {};

template<typename T, typename FirstType>
struct in_type_list<T, FirstType> : std::false_type {};

template<typename T, typename... TypeList>
struct in_type_list<T, T, TypeList...> : std::true_type {};

template<typename T, typename FirstType, typename... TypeList>
struct in_type_list<T, FirstType, TypeList...> : in_type_list<T, TypeList...> {
};

// template<typename T, typename... TypeList>
// struct in_type_list : std::false_type {};

template<typename T1, typename T2>
struct same_as : std::false_type {};

template<typename T>
struct same_as<T, T> : std::true_type {};
} // namespace engine