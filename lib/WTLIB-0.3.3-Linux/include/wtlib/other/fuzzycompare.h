#ifndef WTL_FUZZYCOMPARE_H
#define WTL_FUZZYCOMPARE_H

#include <algorithm>
#include <limits>

namespace wtl {

template<typename T>
bool fuzzyCompare(T first, T second)
{
    static_assert(std::is_floating_point<T>(), "Fuzzy compare compares floating point values for near similarity");
    return std::abs(first - second) <= std::numeric_limits<T>::epsilon() * std::max(std::abs(first), std::abs(first));
}

} // namespace wtl

#endif // WTL_FUZZYCOMPARE_H
