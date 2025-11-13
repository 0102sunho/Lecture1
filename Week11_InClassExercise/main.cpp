#include "Vector3D.h"
#include <iostream>

// The main code should run without errors, displaying the expected outputs in the parentheses.
int main() {
    Vector3D v1(1.0, 2.0, 2.0);
    Vector3D v2(5.0, 0.0, 0.0);
    
    std::cout << "v1: " << v1 << std::endl;
    std::cout << "v2: " << v2 << std::endl;

    std::cout << "|v1| = " << v1.magnitude() << " (Expected: 3.0)\n";
    std::cout << "|v2| = " << v2.magnitude() << " (Expected: 5.0)\n";
    
    double dot_product = innerProduct(v1, v2);
    std::cout << "Inner product: v1 . v2 = " << dot_product << " (Expected: 5.0)\n";
    
    Vector3D v_cross = crossProduct(v1, v2);
    std::cout << "Cross product: v1 x v2 = " << v_cross << " (Expected: (0, 10, -10))\n";

    return 0;
}

