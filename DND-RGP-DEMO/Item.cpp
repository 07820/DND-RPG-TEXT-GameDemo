#include "Item.h"
using namespace std;

void Item::setName(const std::string& newName) { name = newName; } // Function to set the name of the item

string Item::getName() const { return name; } // Function to get the name of the item

void Potion::setStrength(int newStrength) { strength = newStrength; } // Function to set the strength of the potion

int Potion::getStrength() const { return strength; } // Function to get the strength of the potion

void Weapon::setPower(int newPower) { power = newPower; } // Function to set the power of the weapon

int Weapon::getPower() const { return power; } // Function to get the power of the weapon

void Treasure::setValue(int newValue) { value = newValue; } // Function to set the value of the treasure

int Treasure::getValue() const { return value; } // Function to get the value of the treasure
