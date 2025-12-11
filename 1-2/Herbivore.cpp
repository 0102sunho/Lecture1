#include "Herbivore.hpp"
#include "Utils.hpp"
#include "SimulationHelper.hpp"
#include <vector>

// Herbivore-specific observe function
void Herbivore_observe(Animal* self) {
    int viewSize = 2 * self->viewRange + 1;

    // First pass: Calculate base preferences based on grass
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

            // Check if location is occupied by another animal
            if (cellValue < 0) {
                self->viewArray[i][j] = -10000;
                continue;
            }

            // Location is empty, preference = grass amount (1-5)
            self->viewArray[i][j] = cellValue;
        }
    }

    // Second pass: Adjust preferences for cells next to predators
    for (int i = 0; i < viewSize; i++) {
        for (int j = 0; j < viewSize; j++) {
            // Skip if already blocked or current location
            if (self->viewArray[i][j] <= -1000) continue;

            int dx = i - self->viewRange;
            int dy = j - self->viewRange;
            Location targetLoc = wrapLocation(self->loc.x + dx, self->loc.y + dy);

            // Check all adjacent cells (8 directions) for predators
            // BUT only if those adjacent cells are within viewRange
            bool nextToPredator = false;
            for (int pDx = -1; pDx <= 1; pDx++) {
                for (int pDy = -1; pDy <= 1; pDy++) {
                    if (pDx == 0 && pDy == 0) continue;

                    // Calculate the predator's offset from herbivore
                    int predatorDx = dx + pDx;
                    int predatorDy = dy + pDy;

                    // Check if predator location is within viewRange
                    if (predatorDx < -self->viewRange || predatorDx > self->viewRange ||
                        predatorDy < -self->viewRange || predatorDy > self->viewRange) {
                        continue;  // Predator is outside viewRange, ignore it
                    }

                    Location neighborLoc = wrapLocation(targetLoc.x + pDx, targetLoc.y + pDy);
                    int neighborValue = (*self->map)[neighborLoc.x][neighborLoc.y];

                    // Check if neighbor is a carnivore (marker -20)
                    if (neighborValue <= -200000) {
                        nextToPredator = true;
                        break;
                    }
                }
                if (nextToPredator) break;
            }

            // Adjust preference if next to predator
            if (nextToPredator) {
                self->viewArray[i][j] -= 100;
            }
        }
    }
}

// Herbivore-specific move function
int Herbivore_move(Animal* self) {
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

    // Mark current location as having grass (value 1)
    (*self->map)[self->loc.x][self->loc.y] = 1;

    // Get grass energy at target location
    int targetValue = (*self->map)[targetLoc.x][targetLoc.y];
    if (targetValue > 0) {
        // Eat the grass
        self->energy += targetValue;
    }

    // Move to new location
    self->loc = targetLoc;

    // Deduct moving cost
    self->energy -= self->movingCost;

    // Check if animal dies from hunger
    if (self->energy <= 0) {
        return -100000; // Negative indicates this animal died, no animal eaten
    }

    return 100000; // No animal was eaten
}

// Helper function to create a child herbivore
Animal* Herbivore_createChild(Location loc, FieldGrid* map) {
    Herbivore* child = new Herbivore();

    // Initialize parent Animal attributes
    child->parent.loc = loc;
    child->parent.energy = 5;
    child->parent.movingCost = 1;
    child->parent.birthThreshold = 15;
    child->parent.birthCost = 5;
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
    child->parent.observe = Herbivore_observe;
    child->parent.move = Herbivore_move;
    child->parent.giveBirth = Herbivore_giveBirth;

    return &(child->parent);
}

// Herbivore-specific giveBirth function
Animal* Herbivore_giveBirth(Animal* self) {
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
    Animal* child = Herbivore_createChild(childLoc, self->map);

    // Deduct birth cost from parent
    self->energy -= self->birthCost;

    return child;
}

// Function to initialize a Herbivore
Herbivore* Herbivore_init() {
    Herbivore* herb = new Herbivore();

    // Initialize parent Animal attributes with default values
    herb->parent.energy = 5;
    herb->parent.movingCost = 1;
    herb->parent.birthThreshold = 15;
    herb->parent.birthCost = 5;
    herb->parent.energyValue = 5;
    herb->parent.viewRange = 1;

    // Allocate viewArray
    int viewSize = 2 * herb->parent.viewRange + 1;
    herb->parent.viewArray = new int* [viewSize];
    for (int i = 0; i < viewSize; i++) {
        herb->parent.viewArray[i] = new int[viewSize];
    }

    // Set function pointers
    herb->parent.observe = Herbivore_observe;
    herb->parent.move = Herbivore_move;
    herb->parent.giveBirth = Herbivore_giveBirth;

    return herb;
}