#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "Utils.hpp"

struct Animal {
    // TODO: Add member attributes for the Animal struct.
    // - Location loc: struct that stores the Animal's position on the map.
    // - int energy: current energy of the Animal.
    // - int movingCost: energy consumed when the Animal moves once.
    // - int birthThreshold: minimum energy required to be able to giveBirth.
    // - int birthCost: energy spent when giving birth.
    // - int energyValue: energy a predator gains when it eats this Animal.
    // - int viewRange: distance within which the Animal can scan the map.
    // - int** viewArray: 2D array that stores the scanned map values.
    // - int*** map: pointer to the globalMap.
	Location loc;
	int energy;
	int movingCost;
	int birthThreshold;
	int birthCost;
	int energyValue;
	int viewRange;
	int** viewArray;
	FieldGrid* map;



    // TODO: Declare function pointers for the Animal's behavior.
    // - observe: scans the map within viewRange and updates viewArray.
    // - move: moves the Animal to the position with the highest value in viewArray.
    // - giveBirth: creates a new Animal when giving birth is possible.
	void (*observe)(Animal* self);
	int (*move)(Animal* self);
	Animal* (*giveBirth)(Animal* self);

    // The actual implementations must be written in the Animal.cpp file.
    // Implement observe as an abstract function.
};

// Constructor and destructor functions
Animal* Animal_create(Location loc, int energy, int movingCost,
    int birthThreshold, int birthCost, int energyValue,
    int viewRange, FieldGrid* map);

void Animal_destroy(Animal* animal);

// Common move implementation (can be used by child classes)
int Animal_move(Animal* self);

// Common giveBirth implementation (can be called by child classes)
Animal* Animal_giveBirth(Animal* self, Animal* (*createChild)(Location, FieldGrid*));

#endif // ANIMAL_HPP
