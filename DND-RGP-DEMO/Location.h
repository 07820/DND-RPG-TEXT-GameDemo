#ifndef LOCATION_H
#define LOCATION_H
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <algorithm>
#include "Item.h"
#include <set> 

class Monster;
class Player;

class Location {

private:
    // The name of the location 
    std::string name;

    // A description of the location  
    std::string description;

    // A mapping of exits from this location, where the key is the direction and the value is the destination Location
    std::map<std::string, Location*> exits;


    // A list of items present at this location, managed with smart pointers 
    std::vector<std::shared_ptr<Item>> items;


    // A list of monsters present at this location
    std::vector<Monster> monsters;
    Player* boss;  // BOSS
    

public:
    
    void setBoss(Player* newBoss) { boss = newBoss; }
    Player* getBoss() const { return boss; }

    // Sets the name of the location
    void setName(const std::string& newName);

    // Retrieves the name of the location 
    std::string getName() const;


    // Sets the description of the location  
    void setDescription(const std::string& newDescription);

    // Retrieves the description of the location  
    std::string getDescription() const;


    // Adds an exit to the specified direction  
    void addExit(const std::string& direction, Location& location);

    // Retrieves all exits from this location
    std::map<std::string, Location*>& getExits();


    // Template function to add an item of any type derived from Item  
    template <typename T>

    void addItem(const std::shared_ptr<T>& item) {

        items.push_back(std::static_pointer_cast<Item>(item));

    }

    // Retrieves all items present at this location 
    std::vector<std::shared_ptr<Item>> getItems() const; 

    // Clears all items from this location
    void clearItems(); 

    // Adds a monster to the location  
    void addMonster(Monster& m);



    // Retrieves the strongest monster at this location (based on  health)  
     Monster* getStrongestMonster();
    // Removes defeated monsters from the location
    void removeDefeatedMonsters();




   
    // Constructor for the Location class, initializes the name, description, and an empty list of monsters  
    Location(const std::string& newName, const std::string& newDescription)

        : name(newName), description(newDescription), monsters() { } 



};



#endif