#include "Location.h"
#include "Character.h"

using namespace std;
class Monster;

void Location::setName(const string& newName) {
    name = newName;
}

string Location::getName() const {
    return name;
}

void Location::setDescription(const string& newDescription) {
    description = newDescription;
}

string Location::getDescription() const {
    return description;
}

void Location::addExit(const string& direction, Location& location) {
    exits[direction] = &location;
}



map<string, Location*>& Location::getExits() {
    return exits;
}


vector<std::shared_ptr<Item>> Location::getItems() const {
    return items;
}



void Location::clearItems() {
    items.clear();
}

// Sets the current location as the monster's location and adds the monster to the location's list of monsters  
void Location::addMonster(Monster& m) {

    m.setCurrentLocation(this);   
     monsters.push_back(m);   
   

};



// Retrieves the strongest monster at this location based on health
 Monster* Location::getStrongestMonster() {
    if (monsters.empty()) {
        return nullptr;
    }

    Monster* strongestMonster = nullptr;
    int maxHitPoints = 0;

    for (auto& monster : monsters) {
        int currentHitPoints = monster.getHitPoints();
        if (currentHitPoints > maxHitPoints) {
            maxHitPoints = currentHitPoints;
            strongestMonster = &monster;
        }
    }

    return strongestMonster;
   
}

void Location::removeDefeatedMonsters() {
    monsters.erase(
        std::remove_if(monsters.begin(), monsters.end(), [](const Monster& m) { return m.getHitPoints() <= 0; }),
        monsters.end()
    );
    
}


