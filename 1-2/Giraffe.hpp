#ifndef GIRAFFE_HPP
#define GIRAFFE_HPP

#include "Herbivore.hpp"

struct Giraffe {
    // TODO: Add member attributes for the Giraffe struct.
    // - Herbivore parent: embedded Herbivore struct acting as the base data.
    Herbivore parent;

    Giraffe() {
        // Giraffe has viewRange: 2 and movingCost: 2
        parent.parent.energy = 5;
        parent.parent.movingCost = 2;  // Different from base Herbivore
        parent.parent.birthThreshold = 15;
        parent.parent.birthCost = 5;
        parent.parent.energyValue = 5;
        parent.parent.viewRange = 2;  // Different from base Herbivore
        parent.parent.map = nullptr;

        // Allocate viewArray with larger size
        int viewSize = 2 * parent.parent.viewRange + 1;
        parent.parent.viewArray = new int* [viewSize];
        for (int i = 0; i < viewSize; i++) {
            parent.parent.viewArray[i] = new int[viewSize];
        }

        // Set function pointers (same behavior as Herbivore)
        parent.parent.observe = Herbivore_observe;
        parent.parent.move = Herbivore_move;
        parent.parent.giveBirth = Herbivore_giveBirth;
    }
    // You may add additional attributes and helper functions if needed.

};

// TODO: Implement Giraffe_init_() to initialize a Giraffe.
Giraffe* Giraffe_init();

#endif // GIRAFFE_HPP
