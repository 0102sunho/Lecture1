#include "SimulationHelper.hpp"
#include "Utils.hpp"
#include "Animal.hpp"

#include <iostream>
#include <vector>
#include <set>

/*****************************************
YOU MUST EDIT THE STUDENT ID BELOW!!!
******************************************/
std::string studentID = "2025150162";  // CHANGE THIS TO YOUR STUDENT ID
/*****************************************
YOU MUST EDIT THE STUDENT ABOVE!!!
******************************************/

const int SIMULATE_ITERATION_COUNT = 100000;

int globalMap[FIELD_SIZE][FIELD_SIZE];


/* HELPER FUNCTIONS*/
// Helper function to get marker from animal based on its attributes
int getAnimalMarker(Animal* animal) {
    // Distinguish by viewRange and movingCost combination
    if (animal->birthThreshold == 15) {  // Herbivore family
        if (animal->viewRange == 2) {
            return GIRAFFE_MARKER;  // -11
        }
        else {
            // viewRange == 1, could be Herbivore or Sloth
            // We can't easily distinguish, so default to SLOTH_MARKER
            // The simulation system will use the encoded values anyway
            return SLOTH_MARKER;  // -12 (use for both base Herbivore and Sloth)
        }
    }
    else {  // Carnivore family (birthThreshold == 40)
        if (animal->viewRange == 2) {
            return TIGER_MARKER;  // -21
        }
        else {
            return WOLF_MARKER;  // -22 (use for both base Carnivore and Wolf)
        }
    }
}

// Helper function to update map indices after animal removal
void updateMapIndices(FieldGrid map, const std::vector<Animal*>& animals) {
    // Clear all animal markers on the map
    for (int x = 0; x < FIELD_SIZE; x++) {
        for (int y = 0; y < FIELD_SIZE; y++) {
            int value = map[x][y];
            if (value < 0) {
                // There's an animal here, regrow grass
                map[x][y] = 1;
            }
        }
    }

    // Re-place all living animals with correct indices
    for (size_t i = 0; i < animals.size(); i++) {
        Animal* animal = animals[i];
        int x = animal->loc.x;
        int y = animal->loc.y;

        // Determine marker type using helper function
        int marker = getAnimalMarker(animal);

        // Encode: marker * 100000 - index
        map[x][y] = marker * 100000 - static_cast<int>(i);
    }
}

// Helper function to grow grass
void growGrass(FieldGrid map) {
    for (int x = 0; x < FIELD_SIZE; x++) {
        for (int y = 0; y < FIELD_SIZE; y++) {
            int value = map[x][y];
            // Only grow grass on empty cells (positive values)
            if (value > 0 && value < 5) {
                map[x][y] = value + 1;
            }
        }
    }
}

/* END OF HELPER FUNCTIONS*/


int main() {

    // Initialize globalMap, which represents the simulation field
    Simulation_prepare(studentID, globalMap);

    // Vector that stores pointers to all currently alive animals
    std::vector<Animal*> animals;

    // Randomly generate Giraffe, Sloth, Tiger and Wolf, and add them to the animals vector
    Simulation_spawnInitialAnimals(globalMap, animals);

    // Set the map pointer for all animals
    for (size_t i = 0; i < animals.size(); i++) {
        Animal* animal = animals[i];
        if (animal == nullptr) {
            std::cout << "ERROR: Animal at index " << i << " is null!" << std::endl;
            return 1;
        }
        animal->map = &globalMap;
    }


    // Count initial populations by marker type
    int giraffeCount = 0, slothCount = 0, tigerCount = 0, wolfCount = 0;
    for (int x = 0; x < FIELD_SIZE; x++) {
        for (int y = 0; y < FIELD_SIZE; y++) {
            int val = globalMap[x][y];
            if (val < 0) {
                // Decode the marker: val = marker * 100000 - index
                // So marker = val / 100000 (integer division of negative number)
                int marker = val / 100000;

                if (marker == GIRAFFE_MARKER) giraffeCount++;        // -11
                else if (marker == SLOTH_MARKER) slothCount++;       // -12
                else if (marker == TIGER_MARKER) tigerCount++;       // -21
                else if (marker == WOLF_MARKER) wolfCount++;         // -22
            }
        }
    }

    std::cout << "Initial population: " << giraffeCount << " giraffes, "
        << slothCount << " sloths, " << tigerCount << " tigers, "
        << wolfCount << " wolves" << std::endl;



    /*
    Main simulation loop
    */
    for (int iter = 0; iter < SIMULATE_ITERATION_COUNT; ++iter) {

        // Track which animals are dead or newly born this turn
        std::set<int> deadAnimals;  // Indices of animals that died/were eaten
        std::vector<Animal*> newborns;  // Animals born this turn

        size_t numAnimalsThisTurn = animals.size();

        // Process each animal that was alive at the start of this turn
        for (size_t i = 0; i < numAnimalsThisTurn; i++) {
            // Skip if this animal was already eaten this turn
            if (deadAnimals.find(i) != deadAnimals.end()) {
                continue;
            }

            Animal* animal = animals[i];

            // 1. Observe surroundings
            animal->observe(animal);

            // 2. Move and possibly eat
            int moveResult = animal->move(animal);

            // Check if another animal was eaten
            int eatenIndex = moveResult;
            if (moveResult < 0) {
                // This animal also died from hunger
                eatenIndex = -moveResult;
                deadAnimals.insert(i);
            }

            if (eatenIndex != 100000) {
                // An animal was eaten (mark it dead)
                deadAnimals.insert(eatenIndex);
            }

            // Update map with new position (if animal is still alive)
            if (deadAnimals.find(i) == deadAnimals.end()) {
                int marker = getAnimalMarker(animal);
                globalMap[animal->loc.x][animal->loc.y] = marker * 100000 - static_cast<int>(i);

                // 3. Attempt to give birth
                Animal* child = animal->giveBirth(animal);
                if (child != nullptr) {
                    newborns.push_back(child);

                    // Place child on map
                    int childMarker = getAnimalMarker(child);
                    // Child will be at index (animals.size() + newborns.size() - 1)
                    int childIndex = static_cast<int>(animals.size() + newborns.size() - 1);
                    globalMap[child->loc.x][child->loc.y] = childMarker * 100000 - childIndex;
                }
            }
        }

        // Clean up dead animals
        std::vector<Animal*> survivingAnimals;
        for (size_t i = 0; i < animals.size(); i++) {
            if (deadAnimals.find(i) == deadAnimals.end()) {
                survivingAnimals.push_back(animals[i]);
            }
            else {
                // Free memory for dead animal
                Animal_destroy(animals[i]);
            }
        }

        // Add newborns to the population
        for (Animal* newborn : newborns) {
            survivingAnimals.push_back(newborn);
        }

        animals = survivingAnimals;

        // Update all map indices to reflect new array positions
        updateMapIndices(globalMap, animals);

        // Grow grass on empty cells
        growGrass(globalMap);

        // Print progress every 10000 iterations
        if ((iter + 1) % 10000 == 0) {
            int herbivoreCount = 0;
            int carnivoreCount = 0;
            for (Animal* a : animals) {
                if (a->birthThreshold == 15) herbivoreCount++;
                else carnivoreCount++;
            }
            std::cout << "Iteration " << (iter + 1) << ": "
                << herbivoreCount << " herbivores, "
                << carnivoreCount << " carnivores" << std::endl;
        }
    }

    std::cout << "Simulation complete!" << std::endl;
    std::cout << "Final population: " << animals.size() << " animals" << std::endl;

    // Count final populations
    int finalHerbivores = 0, finalCarnivores = 0;
    for (Animal* a : animals) {
        if (a->birthThreshold == 15) finalHerbivores++;
        else finalCarnivores++;
    }
    std::cout << "Final: " << finalHerbivores << " herbivores, "
        << finalCarnivores << " carnivores" << std::endl;

    // Compute final answer for submission
    long long finalVal = 0;
    for (int i = 1; i < FIELD_SIZE * FIELD_SIZE; ++i) {
        int x = (i - 1) % FIELD_SIZE;
        int y = (i - 1) / FIELD_SIZE;
        finalVal += std::abs(static_cast<long long>(i) * globalMap[x][y]);
        finalVal %= 100000000;
    }

    std::cout << "Answer for submission: " << finalVal << std::endl;

    // Clean up remaining animals
    for (Animal* animal : animals) {
        Animal_destroy(animal);
    }

    return 0;
}