#include <iostream>
#include "math.h"
#include <string>

int main() {
    int x, y;

    std::cout << "Enter two integers: ";
    std::cin >> x >> y;

    std::cout << "Sum: " << add(x, y) << std::endl;
    std::cout << "Product: " << multiply(x, y) << std::endl;

    // overload examples
    std::cout << "Sum of three integers (x, y, 10): " << add(x, y, 10) << std::endl;

    double a = 3.5, b = 2.5;
    std::cout << "Sum of two doubles (3.5 + 2.5): " << add(a, b) << std::endl;

    return 0;
}