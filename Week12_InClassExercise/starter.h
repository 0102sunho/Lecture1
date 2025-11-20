#ifndef STARTER_H
#define STARTER_H

#include <concepts>
#include <type_traits> 
#include <algorithm> 
#include <string>


template <typename T>
bool is_equal(const T& a, const T& b) {
    return a == b;
}

template <typename T>
const T& get_max(const T& a, const T& b) {
    return (a > b) ? a : b;
}

template <typename T>
concept Numeric = std::is_arithmetic_v<T>;


template <typename T>
T get_max_numeric(const T& a, const T& b) requires Numeric<T> {
    return (a > b) ? a : b;
}


bool all_equal() {
    return true;
}

template <typename T>
bool all_equal(const T& value) {
    return true;
}

template <typename T, typename... Args>
bool all_equal(const T& first, const Args&... args) {
    // Binary logical AND fold expression
    return ((first == args) && ...);
}

template <std::integral T>
class Accumulator {
private:
    T total = 0;
public:
    void add(const T& value) {
        total += value;
    }
    T get_total() const {
        return total;
    }
};


#endif // STARTER_H