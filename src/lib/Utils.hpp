#ifndef __UTILS_
#define __UTILS_

#include <functional>
#include <vector>

class Utils
{
  public:
    template <class T>
    static std::vector<T> filter_vector(const std::vector<T>& vec,
                                        std::function<bool(const T&)> predicate)
    {
        std::vector<T> filtered;
        for (const T& x : vec) {
            if (predicate(x)) {
                filtered.push_back(x);
            }
        }
        return filtered;
    }

    template <class T>
    static T max(const std::vector<T>& vec)
    {
        if (vec.empty()) {
            throw "Vector must have at least one element";
        }
        T m = vec[0];
        for (const T& x : vec) {
            if (x > m) {
                m = x;
            }
        }
        return m;
    }

    template <class T, class Category>
    static T maxBy(const std::vector<T>& vec, Category&& category)
    {
        if (vec.empty()) {
            throw "Vector must have at least one element";
        }
        T m = vec[0];
        for (auto& x : vec) {
            if (category(x) > category(m)) {
                m = x;
            }
        }
        return m;
    }

    template <class Container, class Action>
    static void forEach(Container&& container, Action&& action)
    {
        for (auto&& x : container) {
            action(x);
        }
    }
};

#endif // !__UTILS_
