#include "Giraffe.hpp"

// Function to initialize a Giraffe
Giraffe* Giraffe_init() {
    Giraffe* giraffe = new Giraffe();

    // Giraffe has viewRange: 2 and movingCost: 2
    giraffe->parent.parent.energy = 5;
    giraffe->parent.parent.movingCost = 2;
    giraffe->parent.parent.birthThreshold = 15;
    giraffe->parent.parent.birthCost = 5;
    giraffe->parent.parent.energyValue = 5;
    giraffe->parent.parent.viewRange = 2;

    // Allocate viewArray with larger size
    int viewSize = 2 * giraffe->parent.parent.viewRange + 1;
    giraffe->parent.parent.viewArray = new int* [viewSize];
    for (int i = 0; i < viewSize; i++) {
        giraffe->parent.parent.viewArray[i] = new int[viewSize];
    }

    // Set function pointers (use Herbivore functions)
    giraffe->parent.parent.observe = Herbivore_observe;
    giraffe->parent.parent.move = Herbivore_move;
    giraffe->parent.parent.giveBirth = Herbivore_giveBirth;

    return giraffe;
}