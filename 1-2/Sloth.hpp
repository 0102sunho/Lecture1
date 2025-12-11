#ifndef SLOTH_HPP
#define SLOTH_HPP

#include "Herbivore.hpp"

// Sloth-specific functions that handle the "skip every other turn" behavior
void Sloth_observe(Animal* self);
int Sloth_move(Animal* self);
Animal* Sloth_giveBirth(Animal* self);

struct Sloth  {
    // TODO: Add member attributes for the Sloth struct.
    // - Herbivore parent: embedded Herbivore struct acting as the base data.
    Herbivore parent;


    // Sloths move only once every two turns.
    // They should move on the first turn in which movement is allowed.
    // When they skip a turn, they do not consume movingCost.
    bool shouldActThisTurn;

    // You may add additional attributes and helper functions if needed.
    Sloth() {
        // Sloth has same base attributes as Herbivore
        parent.parent.energy = 5;
        parent.parent.movingCost = 1;
        parent.parent.birthThreshold = 15;
        parent.parent.birthCost = 5;
        parent.parent.energyValue = 5;
        parent.parent.viewRange = 1;
        parent.parent.map = nullptr;

        // Sloth acts on first turn
        shouldActThisTurn = true;

        // Allocate viewArray
        int viewSize = 2 * parent.parent.viewRange + 1;
        parent.parent.viewArray = new int* [viewSize];
        for (int i = 0; i < viewSize; i++) {
            parent.parent.viewArray[i] = new int[viewSize];
        }

        // Set function pointers to Sloth-specific versions
        parent.parent.observe = Sloth_observe;
        parent.parent.move = Sloth_move;
        parent.parent.giveBirth = Sloth_giveBirth;
    }
};

// TODO: Implement Sloth_init_() to initialize a Sloth.
Sloth* Sloth_init();

#endif // SLOTH_HPP
