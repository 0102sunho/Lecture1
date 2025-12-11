#ifndef TIGER_HPP
#define TIGER_HPP

#include "Carnivore.hpp"

struct Tiger {
    // TODO: Add member attributes for the Tiger struct.
    // - Carnivore parent: embedded Carnivore struct acting as the base data.
    Carnivore parent;

    Tiger() {
        // Tiger has viewRange: 2 and movingCost: 4
        parent.parent.energy = 5;
        parent.parent.movingCost = 4;  // Different from base Carnivore
        parent.parent.birthThreshold = 40;
        parent.parent.birthCost = 30;
        parent.parent.energyValue = 5;
        parent.parent.viewRange = 2;  // Different from base Carnivore
        parent.parent.map = nullptr;

        // Allocate viewArray with larger size
        int viewSize = 2 * parent.parent.viewRange + 1;
        parent.parent.viewArray = new int* [viewSize];
        for (int i = 0; i < viewSize; i++) {
            parent.parent.viewArray[i] = new int[viewSize];
        }

        // Set function pointers (same behavior as Carnivore)
        parent.parent.observe = Carnivore_observe;
        parent.parent.move = Carnivore_move;
        parent.parent.giveBirth = Carnivore_giveBirth;
    }
    // You may add additional attributes and helper functions if needed.

};

// TODO: Implement Tiger_init_() to initialize a Tiger.
Tiger* Tiger_init();

#endif // TIGER_HPP
