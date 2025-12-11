#include "Tiger.hpp"

// Function to initialize a Tiger
Tiger* Tiger_init() {
    Tiger* tiger = new Tiger();

    // Tiger has viewRange: 2 and movingCost: 4
    tiger->parent.parent.energy = 5;
    tiger->parent.parent.movingCost = 4;
    tiger->parent.parent.birthThreshold = 40;
    tiger->parent.parent.birthCost = 30;
    tiger->parent.parent.energyValue = 5;
    tiger->parent.parent.viewRange = 2;

    // Allocate viewArray with larger size
    int viewSize = 2 * tiger->parent.parent.viewRange + 1;
    tiger->parent.parent.viewArray = new int* [viewSize];
    for (int i = 0; i < viewSize; i++) {
        tiger->parent.parent.viewArray[i] = new int[viewSize];
    }

    // Set function pointers (use Carnivore functions)
    tiger->parent.parent.observe = Carnivore_observe;
    tiger->parent.parent.move = Carnivore_move;
    tiger->parent.parent.giveBirth = Carnivore_giveBirth;

    return tiger;
}