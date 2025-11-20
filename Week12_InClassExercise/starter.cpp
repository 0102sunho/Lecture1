
#include <iostream>
#include <string>
#include <concepts>
#include <stdexcept>
#include <cmath>
#include <type_traits>
#include <algorithm>


// TASK 1 -- Basic Function Templates
// TODO: Implement a function template 'is_equal' that accepts two arguments of type T
//       and returns a bool indicating whether they are equal (using ==).
template <typename T>
bool is_equal(const T& a, const T& b) {
    return a == b;
}



// TODO: Implement a function template 'get_max' that accepts two arguments of type T
//       and returns the greater of the two.
template <typename T>
T get_max(const T& a, const T& b) {
    return (a > b) ? a : b;
}



// TASK 2 -- Templates with Concepts
// TODO: Define a concept named Numeric that requires T to be an arithmetic type
//       (hint: use std::is_arithmetic_v).


template <typename T>
concept Numeric = std::is_arithmetic_v<T>;



// TODO: Use the Numeric concept to implement a function template get_max_numeric
//       that accepts two arguments of type T and returns the greater of the two.
template <typename T>
T get_max_numeric(const T& a, const T& b) requires Numeric<T> {
    return (a > b) ? a : b;
}



// TASK 3 -- Variadic Templates and Fold Expressions
// TODO: Implement a base case that handles the zero-argument call: all_equal().
//       This non-template overload is selected by the compiler when no arguments are provided.

bool all_equal() {
    return true;
}


// TODO: Implement a base case that handles the single-argument call: all_equal(value).
//       Although technically optional for this fold expression, it explicitly defines
//       the base case in which one value is always considered equal to itself.

template <typename T>
bool all_equal(const T& value) {
    return true;
}


// TODO: Implement the main variadic function template for two or more arguments.
//       This function should check whether all subsequent arguments are equal
//       to the first argument using a fold expression. The compiler will select
//       this overload only when the number of arguments > 1.

template <typename T, typename... Args>
bool all_equal(const T& first, const Args&... args) {
    return ((first == args) && ...);
}



// TASK 4 -- Template Class
// TODO: Implement a template class named Accumulator that uses std::integral to ensure
//       that T is a fundamental integer type (e.g., int, long, char, etc.) and automatically
//       reject float, double, bool, and class types (such as std::string).
//
// Members:
// - Variable: total (default value: 0)
// - Functions:
//     (1) add: accepts an argument and adds it to total (no return value)
//     (2) get_total: a getter method that returns the current total

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



// Main Test Function (contains two TODO's)
int main() {
    std::cout << "\"TASK 1 -- Basic Function Templates\"" << std::endl;
    std::cout << "Is 10 equal to 10? " << (is_equal(10, 10) ? "Yes" : "No") << std::endl;
    std::cout << "Is 1.0 equal to 1.1? " << (is_equal(1.0, 1.1) ? "Yes" : "No") << std::endl;
    std::cout << "Max of 'apple' and 'banana': " << get_max(std::string("apple"), std::string("banana")) << std::endl;
    std::cout << std::endl;

    
    std::cout << "\"TASK 2 -- Templates with Concepts\"" << std::endl;
    std::cout << "Max of 42 and 99: " << get_max_numeric(42, 99) << std::endl;
    // TODO: Explain why the commented line below raises an error.
    // std::cout << "Max of 'apple' and 'banana': " << get_max_numeric(std::string("apple"), std::string("banana")) << std::endl;
    // 
    // std::string is not arithmetic, Numeric concept denies it.
    std::cout << std::endl;

    
    std::cout << "\"TASK 3 -- Variadic Templates and Fold Expressions\"" << std::endl;
    
    // Calls the zero-argument base case
    std::cout << "All equal ()? " << (all_equal() ? "True" : "False") << " (Zero args)" << std::endl;
    
    // Calls the one-argument base case
    std::cout << "All equal (5)? " << (all_equal(5) ? "True" : "False") << " (One arg)" << std::endl;
    
    // Calls the variadic template (fold expression)
    std::cout << "All equal (10, 10, 10)? " << (all_equal(10, 10, 10) ? "True" : "False") << std::endl;
    std::cout << "All equal (1, 2, 1)? " << (all_equal(1, 2, 1) ? "True" : "False") << std::endl;
    std::cout << std::endl;
    
    
    std::cout << "\"TASK 4 -- Template Class\"" << std::endl;
    Accumulator<int> integer_acc;
    integer_acc.add(10);
    integer_acc.add(5);
    std::cout << "Accumulated ints: " << integer_acc.get_total() << std::endl;
    
    // TODO: Explain why the commented lines below raises an error.
//    Accumulator<float> float_acc;
//    float_acc.add(1.0);
//    float_acc.add(0.5);
//    std::cout << "Accumulated floats: " << integer_acc.get_total() << std::endl;
//
// using float is not allowed, integral concept denies it

    return 0;
}
