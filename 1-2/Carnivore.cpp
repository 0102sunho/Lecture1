#include "Carnivore.hpp"
#include "Utils.hpp"
#include "SimulationHelper.hpp"
#include <vector>
#include <iostream>

// Carnivore-specific observe function
void Carnivore_observe(Animal* self) {
    int viewSize = 2 * self->viewRange + 1;

    // Calculate preferences based on prey availability
    for (int i = 0; i < viewSize; i++) {
        for (int j = 0; j < viewSize; j++) {
            int dx = i - self->viewRange;
            int dy = j - self->viewRange;
            Location targetLoc = wrapLocation(self->loc.x + dx, self->loc.y + dy);

            int cellValue = (*self->map)[targetLoc.x][targetLoc.y];

            // Check if this is the current location
            if (dx == 0 && dy == 0) {
                self->viewArray[i][j] = -1000;
                continue;
            }

            // Check if location has another carnivore
            if (cellValue <= -2000000) {
                self->viewArray[i][j] = -10000;
                continue;
            }

            // Check if location has a herbivore (prey!)
            if (cellValue <= -1000000 && cellValue >= -1999999) {
                // Herbivore present - preference is its energyValue (5)
                self->viewArray[i][j] = 5;
                continue;
            }

            // Empty location (grass or nothing) - preference is 0
            self->viewArray[i][j] = 0;
        }
    }
}

// Carnivore-specific move function
int Carnivore_move(Animal* self) {
    // Find the maximum preference value in viewArray
    int viewSize = 2 * self->viewRange + 1;
    int maxPref = -1000000000;

    for (int i = 0; i < viewSize; i++) {
        for (int j = 0; j < viewSize; j++) {
            if (self->viewArray[i][j] > maxPref) {
                maxPref = self->viewArray[i][j];
            }
        }
    }

    // Collect all locations with max preference
    std::vector<Location> bestLocations;
    for (int i = 0; i < viewSize; i++) {
        for (int j = 0; j < viewSize; j++) {
            if (self->viewArray[i][j] == maxPref) {
                int dx = i - self->viewRange;
                int dy = j - self->viewRange;
                Location newLoc = wrapLocation(self->loc.x + dx, self->loc.y + dy);
                bestLocations.push_back(newLoc);
            }
        }
    }

    // Randomly select one of the best locations
    Location targetLoc = randomSelection(bestLocations);

    // Check if there's a herbivore at target location to eat BEFORE moving
    int eatenIndex = 100000; // Default: no animal eaten
    int targetValue = (*self->map)[targetLoc.x][targetLoc.y];

    if (targetValue <= -1000000 && targetValue >= -1999999) {
        // There's a herbivore here - eat it!
        int absValue = -targetValue;
        eatenIndex = absValue % 100000;

        // Gain energy from eating the herbivore (energyValue = 5)
        self->energy += 5;
    }

    // Mark current location as having grass (value 1)
    (*self->map)[self->loc.x][self->loc.y] = 1;

    // Move to new location
    self->loc = targetLoc;

    // Deduct moving cost
    self->energy -= self->movingCost;

    // Check if animal dies from hunger
    if (self->energy <= 0) {
        return -eatenIndex; // Negative indicates this animal also died
    }

    return eatenIndex;
}

// Helper function to create a child carnivore
Animal* Carnivore_createChild(Location loc, FieldGrid* map) {
    Carnivore* child = new Carnivore();

    // Initialize parent Animal attributes
    child->parent.loc = loc;
    child->parent.energy = 5;
    child->parent.movingCost = 2;
    child->parent.birthThreshold = 40;
    child->parent.birthCost = 30;
    child->parent.energyValue = 5;
    child->parent.viewRange = 1;
    child->parent.map = map;

    // Allocate viewArray
    int viewSize = 2 * child->parent.viewRange + 1;
    child->parent.viewArray = new int* [viewSize];
    for (int i = 0; i < viewSize; i++) {
        child->parent.viewArray[i] = new int[viewSize];
    }

    // Set function pointers
    child->parent.observe = Carnivore_observe;
    child->parent.move = Carnivore_move;
    child->parent.giveBirth = Carnivore_giveBirth;

    return &(child->parent);
}

// Carnivore-specific giveBirth function
Animal* Carnivore_giveBirth(Animal* self) {
    // Check if animal has enough energy
    if (self->energy < self->birthThreshold) {
        return nullptr;
    }

    // Find unoccupied neighboring cells
    std::vector<Location> emptyCells;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;

            Location neighborLoc = wrapLocation(self->loc.x + dx, self->loc.y + dy);
            int cellValue = (*self->map)[neighborLoc.x][neighborLoc.y];

            // Cell is empty if it has positive value (grass) or 0
            if (cellValue >= 0) {
                emptyCells.push_back(neighborLoc);
            }
        }
    }

    // If no empty cells, cannot give birth
    if (emptyCells.empty()) {
        return nullptr;
    }

    // Randomly select a location for the child
    Location childLoc = randomSelection(emptyCells);

    // Create the child
    Animal* child = Carnivore_createChild(childLoc, self->map);

    // Deduct birth cost from parent
    self->energy -= self->birthCost;

    return child;
}

// Function to initialize a Carnivore
Carnivore* Carnivore_init() {
    Carnivore* carn = new Carnivore();

    // Initialize parent Animal attributes with default values
    carn->parent.energy = 5;
    carn->parent.movingCost = 2;
    carn->parent.birthThreshold = 40;
    carn->parent.birthCost = 30;
    carn->parent.energyValue = 5;
    carn->parent.viewRange = 1;
    carn->parent.map = nullptr;  // Will be set by simulation

    // Allocate viewArray
    int viewSize = 2 * carn->parent.viewRange + 1;
    carn->parent.viewArray = new int* [viewSize];
    for (int i = 0; i < viewSize; i++) {
        carn->parent.viewArray[i] = new int[viewSize];
    }

    // Set function pointers
    carn->parent.observe = Carnivore_observe;
    carn->parent.move = Carnivore_move;
    carn->parent.giveBirth = Carnivore_giveBirth;

    return carn;
}