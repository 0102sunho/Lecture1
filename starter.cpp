#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>

class Player {
protected:
    float fatigue_level = 0.0f; // 0.0 (fresh) to 1.0 (exhausted)
    std::string playerName;
    
public:
    // Base parameterized constructor
    Player(const std::string& name) : playerName(name) {
        std::cout << "\nPlayer registered: " << name << "." << std::endl;
    }
    
    // Base destructor
    virtual ~Player() {
        std::cout << "Base destructor: Player removed from system." << std::endl;
    }
    
    // Setter method for fatigue level
    void updateFatigue(float exertion_factor) {
        fatigue_level = std::min(1.0f, std::max(0.0f, fatigue_level + (exertion_factor * 0.1f)));
        
        std::cout << "--> Fatigue now: " << std::fixed << std::setprecision(1) << (fatigue_level * 100.0f) << "%" << std::endl;
    }

    // TASK 1: Implement the virtual base functions in the Player class.
    // (1) shootingSuccessRate:
    //     - Calculates the base rate using a standard formula and fatigue penalty.
    //     - Formula: 0.5 * base_skill * (1 - fatigue_level)
    //     - Return type: float
	

    // (2) tackleSuccessRate:
    //     - Calculates the base rate, applying a less severe penalty for tackling.
    //     - Formula: base_skill * (1.0f - (0.5f * fatigue_level))
    //     - Return type: float

    virtual float shootingSuccessRate(int base_skill) {
        float success_rate = 0.5f * base_skill * (1.0f - fatigue_level);

        std::cout << "Success rate -- Shooting: " << std::fixed << std::setprecision(2) << success_rate << "%" << std::endl;

        return success_rate;
    }

    virtual float tackleSuccessRate(int base_skill) {
        float success_rate = base_skill * (1.0f - (0.5f * fatigue_level));
        
        std::cout << "Success rate -- Tackle: " << std::fixed << std::setprecision(2) << success_rate << "%" << std::endl;
        
        return success_rate;
	}

    // END OF TASK 1


    
    
    // TASK 2: Implement the two overloaded checkEnergy base functions in the Player class.
    // (1) Overload for stamina (int):
    //     - Calculates the effective stamina based on the full impact of fatigue.
    //     - Formula: effective_stamina = base_stamina * (1 - fatigue_level)
    //
    // (2) Overload for hydration (float):
    //     - Calculates the effective hydration based on the reduced impact of fatigue (0.5x).
    //     - Formula: effective_hydration = base_hydration * (1.0f - (0.5f * fatigue_level))
    
  
    void checkEnergy(int base_stamina) {

        int effective_stamina = static_cast<int>(std::round(base_stamina * (1.0f - fatigue_level)));
        std::cout << "Energy check -- Stamina: " << effective_stamina << " (Fatigue: " << std::fixed << std::setprecision(1) << (fatigue_level * 100.0f) << "%)" << std::endl;
    }
    
    void checkEnergy(float base_hydration) {

		float effective_hydration = base_hydration * (1.0f - (0.5f * fatigue_level));
        std::cout << "Energy check -- Hydration: " << std::fixed << std::setprecision(2) << effective_hydration << "%" << std::endl;
    }
    
    // END OF TASK 2


    // Getter method
    const std::string& getPlayerName() const { return playerName; }
};



// TASK 3: Defender as a public derived class of Player
// - Complete the class definition to inherit publicly from Player.
// - Write the parameterized constructor that passes the name to the base class.

class Defender : public Player{ // TASK 3 - Defender as a public derived class of Player

public:
	Defender(const std::string& name) : Player(name) { // TASK 3 - Constructor
        std::cout << "Derived: Defender assigned." << std::endl;
    }
	// END OF TASK 3

    
    // TASK 4: Override virtual base functions for Defender specialization.
    // (1) shootingSuccessRate:
    //     - Applies a positional penalty for non-attacking roles.
    //     - Formula: specialized_rate = base_rate x 0.8
    //
    // (2) tackleSuccessRate:
    //     - Applies a large tactical bonus reflective of a primary defensive duty.
    //     - Formula: specialized_rate = base_rate x 1.5
    
	float shootingSuccessRate(int base_skill) override { // Override the base function

		float specialized_rate = 0.8f * (0.5f * base_skill * (1.0f - fatigue_level));
        std::cout << "Success rate -- Shooting (Defender): " << std::fixed << std::setprecision(2) << specialized_rate << "%" << std::endl;
        
        return specialized_rate;
    }
    
	float tackleSuccessRate(int base_skill) override { // Override the base function

		float specialized_rate = 1.5f * (base_skill * (1.0f - (0.5f * fatigue_level)));
        std::cout << "Success rate -- Tackle (Defender): " << std::fixed << std::setprecision(2) << specialized_rate << "%" << std::endl;
        
        return specialized_rate;
    }

	// END OF TASK 4
    

    // TASK 5: Bring the base function overloads available in the Defender class.
    /* Write down the code here */
	using Player::checkEnergy;

	// END OF TASK 5

};


// TASK 6: Striker as a public derived class of Player
// - Complete the class definition to inherit publicly from Player.
// - Write the parameterized constructor that passes the name to the base class.

class Striker : public Player { // TASK 6 - Striker as a public derived class of Player
public:
	Striker(const std::string& name) : Player(name) { // TASK 6 - Constructor
        std::cout << "Derived: Striker assigned." << std::endl;
    }

	// END OF TASK 6

    
    // TASK 7: Override virtual base functions for Striker specialization.
    // (1) shootingSuccessRate:
    //     - Applies a high positional bonus, which reflects the primary scoring duty.
    //     - Formula: specialized_rate = base_rate x 2
    //
    // (2) tackleSuccessRate:
    //     - Applies a high penalty reflective of low defensive contribution.
    //     - Formula: specialized_rate = base_rate x 0.5
    
	float shootingSuccessRate(int base_skill) override { // Override the base function

		float specialized_rate = 2.0f * (0.5f * base_skill * (1.0f - fatigue_level));
        std::cout << "Success rate -- Shooting (Striker): " << std::fixed << std::setprecision(2) << specialized_rate << "%" << std::endl;
        
        return specialized_rate;
    }
   

    float tackleSuccessRate(int base_skill) override { // Override the base function

		float specialized_rate = 0.5f * (base_skill * (1.0f - (0.5f * fatigue_level)));
        std::cout << "Success rate -- Tackle (Striker): " << std::fixed << std::setprecision(2) << specialized_rate << "%" << std::endl;
        
        return specialized_rate;
    }

	// END OF TASK 7

    
    // TASK 8: Bring the base function overloads available in the Striker class.
    /* Write down the code here */
	using Player::checkEnergy;

	// END OF TASK 8

};


int main() {
    int base_skill_value = 60;
    int base_stamina_value = 90;
    float base_hydration_value = 95.0f;
        
    // TASK 9:
    // - Create a Defender object pointer with the name "Minjae Kim" by using the 'new' keyword.
    // - Check the object's energy (stamina and hydration) based on the provided base values.
    // - Check the object's tackle success rate based on the base_skill_value.
    
	Defender* defender = new Defender("Minjae Kim");
	defender->checkEnergy(base_stamina_value);
    defender->checkEnergy(base_hydration_value);
	defender->tackleSuccessRate(base_skill_value);

    
    std::cout << "\n[Action -- Heavy run]" << std::endl;
    // TASK 10:
    // - Update fatigue level to 0.5 (using the updateFatigue method).
    // - Check the object's new energy (stamina and hydration) based on the base values.
    // - Check the new tackle success rate based on the base_skill_value (it should be lower).
    // - Finally, delete the object using the 'delete' keyword.
    
	defender->updateFatigue(0.5f);
	defender->checkEnergy(base_stamina_value);
	defender->checkEnergy(base_hydration_value);
	defender->tackleSuccessRate(base_skill_value);
	delete defender;

    
    // TASK 11:
    // - Create a Striker object pointer with the name "Heungmin Son" by using the 'new' keyword.
    // - Check the object's energy (stamina and hydration) based on the provided base values.
    // - Check the object's shooting success rate based on the base_skill_value.
    
	Striker* striker = new Striker("Heungmin Son");
	striker->checkEnergy(base_stamina_value);
	striker->checkEnergy(base_hydration_value);
	striker->shootingSuccessRate(base_skill_value);
    
    std::cout << "\n[Action -- Moderate sprint]" << std::endl;
    // TASK 12:
    // - Update fatigue level to 0.3 (using the updateFatigue method).
    // - Check the object's new energy (stamina and hydration) based on the base values.
    // - Check the new shooting success rate based on the base_skill_value (it should be lower).
    // - Finally, delete the object using the 'delete' keyword.
    
	striker->updateFatigue(0.3f);
	striker->checkEnergy(base_stamina_value);
	striker->checkEnergy(base_hydration_value);
	striker->shootingSuccessRate(base_skill_value);
	delete striker;

    
    return 0;
}
