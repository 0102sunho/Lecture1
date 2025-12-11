#ifndef CARNIVORE_HPP
#define CARNIVORE_HPP

#include "Animal.hpp"

// Forward declarations of functions (must come before struct)
void Carnivore_observe(Animal* self);
int Carnivore_move(Animal* self);
Animal* Carnivore_giveBirth(Animal* self);
Animal* Carnivore_createChild(Location loc, FieldGrid* map);

struct Carnivore {
    // Animal parent: embedded Animal struct acting as the base data
    Animal parent;

    // Constructor (C++ style, but using it for initialization)
    Carnivore() {
        // Initialize parent Animal attributes
        parent.energy = 5;
        parent.movingCost = 2;
        parent.birthThreshold = 40;
        parent.birthCost = 30;
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
        parent.observe = Carnivore_observe;
        parent.move = Carnivore_move;
        parent.giveBirth = Carnivore_giveBirth;
    }

    // You may add additional attributes if needed
};

// Function to initialize a Carnivore
Carnivore* Carnivore_init();

#endif // CARNIVORE_HPP