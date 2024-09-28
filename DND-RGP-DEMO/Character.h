#ifndef CHARACTER_H
#define CHARACTER_H

#include "Item.h"
#include "Location.h"
#include <iostream>
#include <vector>
#include <string>

#include <cstdlib>  // For std::rand and std::srand
#include <ctime>     // For std::time


// Base class for all characters in the game
class Character {
protected:
    std::string name;  // the character name
    int hitPoints;     //the  Health points

    int initialHitPoints;  // Initial health points of the character

    std::vector<std::shared_ptr<Item>> Armours;// The character's armours

    std::string sketch;  // ASCII picture of the character
public:
    // Set the ASCII sketch of the boss
    void setSketch(const std::string& newSketch) { sketch = newSketch; }
    // Get the ASCII sketch of the boss
    std::string getSketch() const { return sketch; }


    // Get the initial health points of the monster
    int getInitialHitPoints() const { return initialHitPoints; }

   
   // Reduce the character's health points by a certain amount of damage
    void takeHit(int damage) {
        hitPoints -= damage;
        if (hitPoints < 0) {
            hitPoints = 0;  // Ensure health points do not go below 0
        }
    }

    int rollDice() {
        return std::rand() % 6 + 1;  // Roll a dice and return a random number between 1 and 6
    }
    void setName(const std::string& newName); // Set character name
    std::string getName() const;              // Get character name
    void setHitPoints(int hp);                // Set health points
    int getHitPoints() const;                 // Get health points

    virtual ~Character() {} // Virtual destructor 
};


// Monster class, derived from Character
class Monster : public Character {

private:
    std::vector<std::shared_ptr<Item>> items;// The monster's items

    Location* currentLocation;// The monster's current location

    //int initialHitPoints;  // Initial health points of the monster

    std::string sketch;  // The sketch of the monster

public:
    Monster(const std::string& name, int hitPoints, const std::string& sketch)
        : sketch(sketch) {
        setName(name);
        setHitPoints(hitPoints);
        initialHitPoints = hitPoints;
    }
    // Get the sketch of the monster
    std::string getSketch() const { return sketch; }
    
    // Set the current location of the monster
    void setCurrentLocation(Location* location) {
        currentLocation = location;
    }
    // Destructor for the Monster class
    virtual~Monster();

    // Get the current location of the monster
    Location& getCurrentLocation() const;
   
    // Add an item to the monster's inventory, allows any type of Item 
    template <typename T>
    void monsterAddItem(const std::shared_ptr<T>& item) {
        items.push_back(std::static_pointer_cast<Item>(item));
    }

    // Get the monster's items
   std::vector<std::shared_ptr<Item>>& monsterGetItems() {
       std::cout << name << " has the following items:" << std::endl;
       for (const auto& item : items) {
           std::cout << item->getName() << std::endl;
       }
       return items;
   }

   
   // Clear the monster's items
    void clearItems() {
        items.clear();
    }
};




// Comparator for sorting weapons
struct CompareWeapon {
    bool operator()(const std::shared_ptr<Weapon>& a, const std::shared_ptr<Weapon>& b) const {
        return a->getPower() < b->getPower();
    }
};


// Player class, derived from Character
class Player : public Character {
    static const int SCORE_BOSS_WIN = 50;  // Score awarded to the player if they defeat the boss

    int score;                                      // Player's score
    //std::vector<std::shared_ptr<Item>> weapons;     // Player's collection of owned weapons stored as shared pointers
    std::set<std::shared_ptr<Weapon>, CompareWeapon> weapons;
    std::vector<std::shared_ptr<Item>> potions;     // Player's owned potions
    std::vector<std::shared_ptr<Item>> treasures;   // Player's owned treasures
   

    Location* currentLocation;  // Reference to the current location of the player
  


public:
    // Constructor for the Player class, without ASCII sketch
    Player(int initialScore, Location& startLocation)
        : score(initialScore),
        weapons(),   // Default initialize weapons vector to empty vector
        potions(),   // Default initialize potions vector to empty vector
        treasures(), // Default initialize treasures vector to empty vector
        currentLocation(&startLocation) {
    }

    // Constructor for the Player class, with ASCII sketch for BOSS
    Player(int initialScore, Location& startLocation, const std::string& sketch)
        : score(initialScore),
        weapons(),   // Default initialize weapons vector to empty vector
        potions(),   // Default initialize potions vector to empty vector
        treasures(), // Default initialize treasures vector to empty vector
        currentLocation(&startLocation) {
        setSketch(sketch);
    }

    friend std::ostream& operator<<(std::ostream& os, const Player& player);  // Friend function for outputting player information

    friend void displayItems(const std::string& classification, const std::vector<std::shared_ptr<Item>>& items );  // Friend function to display items in a given classification.

    void setScore(int newScore);                    // Set player's score
    void addScore(int points) {                    // Add points to player's score
        score += points;
    }
    int getScore() const;                           // Get player's score
    void setCurrentLocation(Location& location);    // Set player's current location
    Location& getCurrentLocation() const;           // Get player's current location


    void collectItems(const std::vector<std::shared_ptr<Item>>& itemsFromLocation); // Collect items from location


    void showInventory() const; // Display player's  current inventory

    void drinkPotions();  // Drink potions

    void combat(Monster& monster);  //  Engage in combat with a monster

    void combatBoss(Player& opponent);   // Engage in combat with another player (the boss)

    void engageCombat(Character& opponent, bool isBoss);
};





#endif