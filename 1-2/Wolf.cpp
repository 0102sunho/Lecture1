#include "Wolf.hpp"

// Function to initialize a Wolf
Wolf* Wolf_init() {
    Wolf* wolf = new Wolf();

    // Wolf has identical attributes to base Carnivore (already set in constructor)
    wolf->parent.parent.energy = 5;
    wolf->parent.parent.movingCost = 2;
    wolf->parent.parent.birthThreshold = 40;
    wolf->parent.parent.birthCost = 30;
    wolf->parent.parent.energyValue = 5;
    wolf->parent.parent.viewRange = 1;

    // Allocate viewArray
    int viewSize = 2 * wolf->parent.parent.viewRange + 1;
    wolf->parent.parent.viewArray = new int* [viewSize];
    for (int i = 0; i < viewSize; i++) {
        wolf->parent.parent.viewArray[i] = new int[viewSize];
    }

    // Set function pointers (use Carnivore functions)
    wolf->parent.parent.observe = Carnivore_observe;
    wolf->parent.parent.move = Carnivore_move;
    wolf->parent.parent.giveBirth = Carnivore_giveBirth;

    return wolf;
}