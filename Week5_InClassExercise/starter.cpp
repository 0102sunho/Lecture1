#include <iostream>
#include <string>

// =========================================================
// For Exercise 2,
// TODO: Define the OOPCourse::Math namespace structure and
//       the internal anonymous namespace here.
namespace {
    void log_calculation(int result) {
        std::cout << "LOG: Calculation performed, result is " << result << "\n";
    }
}

// Primary namespace with a nested namespace for the public API
namespace OOPCourse::Math {

    int add_and_log(int a, int b) {
        int sum = a + b;
        log_calculation(sum);
        return sum;
    }
}
// =========================================================


// Main program
int main()
{
    // --- Exercise 1: String reversal and largest value ---
    std::cout << "--- Exercise 1: String Reversal ---\n";

    std::string num_a, num_b;

    std::cout << "Enter the first 3-digit number: ";
    std::cin >> num_a;
    
    std::cout << "Enter the second 3-digit number: ";
    std::cin >> num_b;

    // empty str for storing rev a/b
    std::string reversed_a = "";
    std::string reversed_b = "";


    // 1. Reversal with a for-loop
    for (int i = (num_a.length() - 1); i >= 0; --i) {
        reversed_a += num_a[i];
    }

    for (int i = (num_b.length() - 1); i >= 0; --i) {
        reversed_b += num_b[i];
    }
    

    // 2. Comparison and Output
    std::cout << "Reversed a: " << reversed_a << " , Reversed b: " << reversed_b << ".\n";
    if (reversed_a > reversed_b) {
        std::cout << "The larger reversed number is: " << reversed_a << "\n";
    }
    else {
        std::cout << "The larger reversed number is: " << reversed_b << "\n";
    }
    
    std::cout << "\n";
    
    
    // --- Exercise 2: Namespaces ---
    std::cout << "--- Exercise 2: Namespaces ---\n";
    
    // TODO: Use the 'using' declaration here to bring ONLY the public
    //       'add_and_log' function into scope.
    using OOPCourse::Math::add_and_log;

    // TODO: Call 'add_and_log(15, 27)' and print the result.
    int result = add_and_log(15, 27);
    std::cout << "The final result from add_and_log is: " << result << std::endl;

    return 0;
}
