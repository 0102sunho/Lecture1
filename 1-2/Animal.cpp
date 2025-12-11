#include "Animal.hpp"
#include "SimulationHelper.hpp"
#include "Utils.hpp"
#include <vector>
#include <cstdlib>

// Constructor function for Animal
Animal* Animal_create(Location loc, int energy, int movingCost,
    int birthThreshold, int birthCost, int energyValue,
    int viewRange, FieldGrid* map) {

    Animal* animal = new Animal();

    animal->loc = loc;
    animal->energy = energy;
    animal->movingCost = movingCost;
    animal->birthThreshold = birthThreshold;
    animal->birthCost = birthCost;
    animal->energyValue = energyValue;
    animal->viewRange = viewRange;
    animal->map = map;

    // Allocate viewArray (size is (2*viewRange+1) x (2*viewRange+1))
    int viewSize = 2 * viewRange + 1;
    animal->viewArray = new int* [viewSize];
    for (int i = 0; i < viewSize; i++) {
        animal->viewArray[i] = new int[viewSize];
    }

    // Initialize function pointers to nullptr (will be set by child classes)
    animal->observe = nullptr;
    animal->move = nullptr;
    animal->giveBirth = nullptr;

    return animal;
}




// Destructor function for Animal
void Animal_destroy(Animal* animal) {
    if (animal == nullptr) return;

    // Free viewArray
    if (animal->viewArray != nullptr) {
        int viewSize = 2 * animal->viewRange + 1;
        for (int i = 0; i < viewSize; i++) {
            delete[] animal->viewArray[i];
        }
        delete[] animal->viewArray;
    }

    delete animal;
}




// Common move implementation
int Animal_move(Animal* self) {
    // Find the maximum preference value in viewArray
    int viewSize = 2 * self->viewRange + 1;
    int maxPref = -1000000000; // Very low initial value

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
                // Convert viewArray indices to world coordinates
                int dx = i - self->viewRange;
                int dy = j - self->viewRange;
                Location newLoc = wrapLocation(self->loc.x + dx, self->loc.y + dy);
                bestLocations.push_back(newLoc);
            }
        }
    }

    // Randomly select one of the best locations
    Location targetLoc = randomSelection(bestLocations);

    // Mark current location as having grass (value 1) since animal is leaving
    (*self->map)[self->loc.x][self->loc.y] = 1;

    // Check if there's an animal at target location to eat
    int eatenIndex = 100000; // Default: no animal eaten
    int targetValue = (*self->map)[targetLoc.x][targetLoc.y];

    if (targetValue < -10000) {
        // There's an animal here - extract its index
        // Format: -10nnnnn or -20nnnnn
        int absValue = -targetValue;
        eatenIndex = absValue % 100000;

        // Get the animal's energy value (need to calculate based on type)
        // For now, we'll assume energyValue = 5 for all animals
        self->energy += 5; // Will be overridden in Carnivore implementation
    }

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



// Common giveBirth implementation
Animal* Animal_giveBirth(Animal* self, Animal* (*createChild)(Location, FieldGrid*)) {
    // Check if animal has enough energy
    if (self->energy < self->birthThreshold) {
        return nullptr;
    }

    // Find unoccupied neighboring cells
    std::vector<Location> emptyCells;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue; // Skip current location

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
    Animal* child = createChild(childLoc, self->map);

    // Deduct birth cost from parent
    self->energy -= self->birthCost;

    return child;
}


