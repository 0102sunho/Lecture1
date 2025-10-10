#include <iostream>

/*
 * Helper function to print the array elements using pointer arithmetic.
 * - arr: The const array pointer.
 * - size: The size of the array.
 */
void print_array(const int* arr, int size) {
    std::cout << "{";

    // START TODO BLOCK #1
    for (int i = 0; i < size; ++i) {
        std::cout << *(arr + i);
        if (i < size - 1) {
            std::cout << ", ";
        }
    }
    // TODO: 1. Use a 'for' loop to iterate through the array.
    // TODO: 2. Access and print the element at index 'i' using only pointer arithmetic: *(arr + i)
    // TODO: 3. Add ", " after the element unless it is the last element.

    // END TODO BLOCK #1

    std::cout << "}" << std::endl;
}

/*
 * Swaps the values of two integers using references.
 * - a: Reference to the first integer.
 * - b: Reference to the second integer.
 */
void swap_values(int& a, int& b) {
    // START TODO BLOCK #2
    
	int temp = a;
	a = b;
	b = temp;

    // TODO: Use a temporary variable to correctly swap the values of 'a' and 'b'.
    // END TODO BLOCK #2
}

/*
 * Implements the partition scheme for Quicksort.
 * Rearranges elements in the sub-array arr[low...high] around the pivot (arr[high]).
 * - arr: The array pointer.
 * - low: The starting index of the sub-array.
 * - high: The ending index (where the pivot is initially located).
 * Returns the final index of the pivot element.
 */
int partition(int* arr, int low, int high) {
    // Select the last element as the pivot (read using pointer arithmetic)
    int pivot = *(arr + high);

    // Index 'i' is the boundary for elements smaller than the pivot
    int i = (low - 1);


    // START TODO BLOCK #3
    // 
    // TODO 1: Loop through the array from index 'low' up to 'high - 1'. (Use standard 'for' loop with index 'j')

    // TODO 2: Inside the loop, check if the element at index 'j' is less than or equal to 'pivot'.
    //         (Access the element value using pointer arithmetic: *(arr + j))

    // TODO 3: If the condition is met, increment 'i' and call swap_values()
    //         to swap the elements at indices 'i' and 'j'.
    //         (Pass dereferenced pointer results to swap_values: *(arr + i))
    for (int j = low; j < high; ++j) {
        if (*(arr + j) <= pivot) {
            i++;
            swap_values(*(arr + i), *(arr + j));
        }
	}
    // TODO 4: After the main loop, swap the pivot (arr[high]) with the element at arr[i + 1].
    // TODO 5: Return the final index of the pivot.
    swap_values(*(arr + i + 1), *(arr + high));
    return i + 1;


    // END TODO BLOCK #3
}

void quicksort(int* arr, int low, int high) {
    if (low < high) {
        // 1. Divide: Get the pivot's final index (partition point)
        int pivot_index = partition(arr, low, high);

        // 2. Conquer (Recurse Left): Sort the sub-array to the left of the pivot
        quicksort(arr, low, pivot_index - 1);

        // 3. Conquer (Recurse Right): Sort the sub-array to the right of the pivot
        quicksort(arr, pivot_index + 1, high);
    }
}

int main() {
    const int N = 7;
    int data_array[N] = { 80, 10, 40, 70, 20, 90, 30 };

    std::cout << "Initial Array: ";
    print_array(data_array, N);

    // Call partition on the full array (low=0, high=N-1)
    int final_pivot_index = partition(data_array, 0, N - 1);

    std::cout << "\nArray after Partition (Pivot: 30):\n";
    std::cout << "Pivot final position: Index " << final_pivot_index << std::endl;

    // Call the full recursive quicksort function
    quicksort(data_array, 0, N - 1);

    std::cout << "\nArray after full Quicksort:\n";
    std::cout << "Final Array: ";
    print_array(data_array, N);
    // Expected Result: {10, 20, 30, 40, 70, 80, 90}

    return 0;
}
