#ifndef WOLF_HPP
#define WOLF_HPP

#include "Carnivore.hpp"

struct Wolf {
    // TODO: Add member attributes for the Wolf struct.
    
    // - Carnivore parent: embedded Carnivore struct acting as the base data.
    Carnivore parent;
    Wolf() {
        // Wolf has same attributes as base Carnivore
        // (already initialized in Carnivore constructor)
    }
    // You may add additional attributes and helper functions if needed.


};

// TODO: Implement Wolf_init_() to initialize a Wolf.
Wolf* Wolf_init();

#endif // WOLF_HPP
