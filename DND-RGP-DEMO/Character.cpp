#include <iostream>  
#include <algorithm> 
#include <vector>
#include "Character.h"
#include "Location.h"
#include "Item.h"
using namespace std;



// Define overloaded operator
std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "Player current info:" << std::endl
        << "HP: " << player.getHitPoints() << "  Score: " << player.getScore() << std::endl;
       
    return os;
}
// Setters and getters for Character and Player classes
void Character::setName(const string& newName) { name = newName; }

string Character::getName() const { return name; }

void Character::setHitPoints(int hp) { hitPoints = hp; }

int Character::getHitPoints() const { return hitPoints; }

void Player::setScore(int newScore) { score = newScore; }

int Player::getScore() const { return score; }

void Player::setCurrentLocation(Location& location) { currentLocation = &location; }

Location& Player::getCurrentLocation() const { return *currentLocation; }




// Collect items from a location
void Player::collectItems(const vector<shared_ptr<Item>>& itemsFromLocation) {
    for (auto& item : itemsFromLocation) {    // Iterate over all items at the location
        if (auto potion = dynamic_pointer_cast<Potion>(item)) {  // Check the type of the item and add it to the appropriate player's item container vector based on its type
            potions.push_back(potion);

            cout << "Collected potion: " << potion->getName() << endl; // Output the name of the collected potion
        }
        else if (auto weapon = dynamic_pointer_cast<Weapon>(item)) {  // If possible, cast the current iterated item to a pointer of type Weapon
            
            weapons.insert(weapon);
            cout << "Collected weapon: " << weapon->getName() << endl; // Output the name of the collected weapon
        }
        else if (auto treasure = dynamic_pointer_cast<Treasure>(item)) { // If possible, cast the current iterated item to a pointer of type Treasure
            treasures.push_back(treasure);

            addScore(treasure->getValue());
            cout << "Collected treasure: " << treasure->getName() << endl; // Output the name of the collected treasure
        }
		else if (auto armour = dynamic_pointer_cast<Armour>(item)) { // If possible, cast the current iterated item to a pointer of type Treasure
        			Armours.push_back(armour);
        
        			cout << "Collected Armour: " << armour->getName() << endl; // Output the name of the collected treasure
        		}
    }
}



   

    // Print information about the current equipment
template <typename T>
void displayItems(const string& classification, const T& items) {

    // Print the category information
    cout << classification << ":" << endl;

    // Create a new vector to store item names with their values
    vector<string> itemNamesWithValues;

    // Iterate through the passed pointer vector
    for (const auto& item : items) {
        // Get the name of the item
        string itemName = (*item).getName();

        // Check the type of the item
        // If it's a Potion, append its strength to the name
        if (dynamic_cast<Potion*>(item.get())) {
            const Potion* potionPtr = dynamic_cast<Potion*>(item.get());
            itemName += " (+" + to_string((*potionPtr).getStrength()) + " Strength)";
        }
        // If it's a Weapon, append its power to the name
        else if (dynamic_cast<Weapon*>(item.get())) {
            const Weapon* weaponPtr = dynamic_cast<Weapon*>(item.get());
            itemName += " (+" + to_string((*weaponPtr).getPower()) + " Power)";
        }
        // If it's a Treasure, append its value to the name
        else if (dynamic_cast<Treasure*>(item.get())) {
            const Treasure* treasurePtr = dynamic_cast<Treasure*>(item.get());
            itemName += " (+" + to_string((*treasurePtr).getValue()) + " Value)";
        }
        else if (dynamic_cast<Armour*>(item.get())) {
            const Armour* ArmourPtr = dynamic_cast<Armour*>(item.get());
            itemName += " (+" + to_string((*ArmourPtr). getProtection()) + " Protection)";
        }

        // Add the modified item name to the vector
        itemNamesWithValues.push_back(itemName);
    }





    // Sort the item names in alphabetical order
    sort(itemNamesWithValues.begin(), itemNamesWithValues.end());

    // Print the sorted item names with their values
    for (const auto& name : itemNamesWithValues) {
        cout << "  " << name << endl;
    }
}






// Show player's inventory ,healthPoint and  score
void Player::showInventory() const {
    std::cout << *this << std::endl;
    cout << "Your current inventory:" << endl;

    // Display various items
    displayItems("Potions",potions);
    displayItems("Treasures",treasures);
    displayItems("Weapons",weapons);
    displayItems("Armour", Armours);
}



// Drink all potions in the inventory
void Player::drinkPotions() {
    for (auto& item : potions) {
        auto potion = dynamic_pointer_cast<Potion>(item);
        if (potion) {
            setHitPoints(getHitPoints() + potion->getStrength()); 
        }
    }
    potions.clear();  // Clear all potions in the inventory after drinking
}

// Engage in combat with an opponent, such as a monster or BOSS
void Player::engageCombat(Character& opponent, bool isBoss) {
   
    int round = 0;    // Initialize round counter
    std::cout << "You engage in combat with " << opponent.getName() << "!" << std::endl;

    while (this->getHitPoints() > 0 && opponent.getHitPoints() > 0) {
        round++;  
        std::cout << "Round " << round << ":" << std::endl;

        std::cout  << std::endl;
        std::cout << std::endl;

        // Display player and opponent's health points
        std::cout << "Your health points: " << this->getHitPoints() << std::endl;
        std::cout << opponent.getName() << "'s health points: " << opponent.getHitPoints() << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        // Calculate the attack value blocked by the armour
        int maxArmourProtection = 0;
        for (const auto& item : Armours) {
            auto armour = std::dynamic_pointer_cast<Armour>(item);
            if (armour && armour->getProtection() > maxArmourProtection) {
                maxArmourProtection = armour->getProtection();
            }
        }
        int armourBlock = std::rand() % (maxArmourProtection + 1);  
        std::cout << "Armour blocks " << armourBlock << " damage" << std::endl;

        
        // Opponent attacks
        int damage = opponent.rollDice() * 2- armourBlock;
        this->takeHit(damage);
        std::cout << opponent.getName() << " attacks you for " << damage << " damage!" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        if (this->getHitPoints() <= 0) {
            std::cout << "You have been defeated by " << opponent.getName() << "!" << std::endl;
            break;
        }

        // Player attacks back
        int playerDamage = rollDice() * 2;
        // Find the weapon with the highest power
        int maxWeaponPower = 0;
        for (const auto& item : weapons) {
            auto weapon = std::dynamic_pointer_cast<Weapon>(item);
            if (weapon && weapon->getPower() > maxWeaponPower) {
                maxWeaponPower = weapon->getPower();
            }
        }


        playerDamage += maxWeaponPower;
        std::cout << "Your weapon deals " << maxWeaponPower << " damage" << std::endl;
        opponent.takeHit(playerDamage);
        std::cout << "You attack " << opponent.getName() << " for " << playerDamage << " damage!" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        if (opponent.getHitPoints() <= 0) {
            std::cout << "You have defeated " << opponent.getName() << "!" << std::endl;
            if (isBoss) {
                addScore(SCORE_BOSS_WIN);   // If the opponent is defeated, add score
            }
            else {
                addScore(opponent.getInitialHitPoints());
            }
            break;
        }
    }
 }

// Combat with a monster
   void Player::combat(Monster & monster) {

        engageCombat(monster, false);

    }
   // Combat with a boss
    void  Player::combatBoss(Player & opponent) {
        engageCombat(opponent, true);
    }


Monster::~Monster() {
    
}


 
