#ifndef HERBIVORE_HPP
#define HERBIVORE_HPP
#include "Animal.hpp"

// Herbivore-specific observe function
void Herbivore_observe(Animal* self);

// Herbivore-specific move function (uses Animal_move but handles eating)
int Herbivore_move(Animal* self);

// Herbivore-specific giveBirth function
Animal* Herbivore_giveBirth(Animal* self);

// Helper function to create a child herbivore
Animal* Herbivore_createChild(Location loc, FieldGrid* map);


struct Herbivore {
    // TODO: Add member attributes for the Herbivore struct.
    // - Animal parent: embedded Animal struct acting as the base data.
    Animal parent;

    // You may add additional attributes and helper functions if needed.
    Herbivore() {
        // Initialize parent Animal attributes
        parent.energy = 5;
        parent.movingCost = 1;
        parent.birthThreshold = 15;
        parent.birthCost = 5;
        parent.energyValue = 5;
        parent.viewRange = 1;
        parent.map = nullptr;  // Will be set by simulation

        // Allocate viewArray
        int viewSize = 2 * parent.viewRange + 1;
        parent.viewArray = new int* [viewSize];
        for (int i = 0; i < viewSize; i++) {
            parent.viewArray[i] = new int[viewSize];
        }

        // Set function pointers
        parent.observe = Herbivore_observe;
        parent.move = Herbivore_move;
        parent.giveBirth = Herbivore_giveBirth;
    }
};

// TODO: Implement Herbivore_init_() to initialize a Herbivore.
Herbivore* Herbivore_init();


#endif // HERBIVORE_HPP
