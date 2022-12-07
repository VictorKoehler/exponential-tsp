#ifndef _UTILS_
#define _UTILS_

#include <vector>
#include <type_traits>

typedef std::tuple<std::vector<int>, std::vector<int>, double> GraphPartition;


// https://stackoverflow.com/a/62292282
template<typename T, typename F>
constexpr auto has_member_impl(F&& f) -> decltype(f(std::declval<T>()), true) {
  return true;
}

template<typename>
constexpr bool has_member_impl(...) { return false; }

#define has_member(T, EXPR, obj) has_member_impl<T>( [](auto&& obj)->decltype(obj.EXPR){} )

template<typename T>
int getSizeOf(const T& obj) {
    if constexpr (has_member(T, size(), obj)) return obj.size();
    else return obj.getSize();
}

#endif
