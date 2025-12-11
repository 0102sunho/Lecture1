#include "Sloth.hpp"
#include "Utils.hpp"
#include "SimulationHelper.hpp"

// Helper function to get Sloth pointer from Animal pointer
Sloth* getSloth(Animal* self) {
    // The Animal* points to the parent.parent field of Sloth
    // We need to calculate the offset back to the Sloth struct
    // self points to Sloth.parent.parent
    // First get pointer to Herbivore (go back by offset of parent in Herbivore)
    char* herbivorePtr = reinterpret_cast<char*>(self) - offsetof(Herbivore, parent);
    // Then get pointer to Sloth (go back by offset of parent in Sloth)
    char* slothPtr = herbivorePtr - offsetof(Sloth, parent);
    return reinterpret_cast<Sloth*>(slothPtr);
}

// Sloth-specific observe function
void Sloth_observe(Animal* self) {
    Sloth* sloth = getSloth(self);

    // If not acting this turn, do nothing
    if (!sloth->shouldActThisTurn) {
        return;
    }

    // Otherwise, use the standard Herbivore observe
    Herbivore_observe(self);
}

// Sloth-specific move function
int Sloth_move(Animal* self) {
    Sloth* sloth = getSloth(self);

    // If not acting this turn, don't move (but toggle for next turn)
    if (!sloth->shouldActThisTurn) {
        sloth->shouldActThisTurn = true;  // Act next turn
        return 100000;  // No animal eaten, this animal didn't die
    }

    // Otherwise, use the standard Herbivore move
    int result = Herbivore_move(self);

    // Toggle shouldActThisTurn for next turn (skip next turn)
    sloth->shouldActThisTurn = false;

    return result;
}

// Helper function to create a child sloth
Animal* Sloth_createChild(Location loc, FieldGrid* map) {
    Sloth* child = new Sloth();

    // Initialize parent Animal attributes
    child->parent.parent.loc = loc;
    child->parent.parent.energy = 5;
    child->parent.parent.movingCost = 1;
    child->parent.parent.birthThreshold = 15;
    child->parent.parent.birthCost = 5;
    child->parent.parent.energyValue = 5;
    child->parent.parent.viewRange = 1;
    child->parent.parent.map = map;

    // Child sloth should act on its first turn (turn after birth)
    child->shouldActThisTurn = true;

    // Allocate viewArray
    int viewSize = 2 * child->parent.parent.viewRange + 1;
    child->parent.parent.viewArray = new int* [viewSize];
    for (int i = 0; i < viewSize; i++) {
        child->parent.parent.viewArray[i] = new int[viewSize];
    }

    // Set function pointers
    child->parent.parent.observe = Sloth_observe;
    child->parent.parent.move = Sloth_move;
    child->parent.parent.giveBirth = Sloth_giveBirth;

    return &(child->parent.parent);
}

// Sloth-specific giveBirth function
Animal* Sloth_giveBirth(Animal* self) {
    Sloth* sloth = getSloth(self);

    // If not acting this turn, cannot give birth
    if (!sloth->shouldActThisTurn) {
        return nullptr;
    }

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
    Animal* child = Sloth_createChild(childLoc, self->map);

    // Deduct birth cost from parent
    self->energy -= self->birthCost;

    return child;
}

// Function to initialize a Sloth
Sloth* Sloth_init() {
    Sloth* sloth = new Sloth();

    // Initialize parent Animal attributes
    sloth->parent.parent.energy = 5;
    sloth->parent.parent.movingCost = 1;
    sloth->parent.parent.birthThreshold = 15;
    sloth->parent.parent.birthCost = 5;
    sloth->parent.parent.energyValue = 5;
    sloth->parent.parent.viewRange = 1;

    // Sloth acts on first turn
    sloth->shouldActThisTurn = true;

    // Allocate viewArray
    int viewSize = 2 * sloth->parent.parent.viewRange + 1;
    sloth->parent.parent.viewArray = new int* [viewSize];
    for (int i = 0; i < viewSize; i++) {
        sloth->parent.parent.viewArray[i] = new int[viewSize];
    }

    // Set function pointers
    sloth->parent.parent.observe = Sloth_observe;
    sloth->parent.parent.move = Sloth_move;
    sloth->parent.parent.giveBirth = Sloth_giveBirth;

    return sloth;
}