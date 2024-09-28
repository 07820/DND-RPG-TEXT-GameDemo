#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
protected:
    std::string name; // The name of the item

public:
    void setName(const std::string& newName) ; // Function to set the name of the item

    virtual std::string getName() const ; //   function to get the name of the item

    virtual ~Item() {} // Virtual destructor to ensure proper cleanup of derived class objects
};

class Potion : public Item {
    
    int strength; // The strength of the potion
public:
    Potion(const std::string& name, int strength) :  strength(strength) { setName(name); } // Constructor
    
    void setStrength(int newStrength); // Function to set the strength of the potion
    int getStrength() const; // Function to get the strength of the potion
};

class Weapon : public Item {
    
    int power; // The power of the weapon
public:
    Weapon(const std::string& name, int power) :  power(power) { setName(name); } // Constructor
    
    void setPower(int newPower); // Function to set the power of the weapon
    int getPower() const; // Function to get the power of the weapon
};

class Treasure : public Item {
    
    int value; // The value of the treasure
public:
    Treasure(const std::string& name, int value)  : value(value) { setName(name); } // Constructor

    
    void setValue(int newValue); // Function to set the value of the treasure
    int getValue() const; // Function to get the value of the treasure
};

class Armour : public Item {
private:
    
    int protection; // The protection provided by the armour

public:
    Armour(const std::string& name, int protection)
        :  protection(protection) {  setName(name);} // Constructor

    
    int getProtection() const { // Function to get the protection provided by the armour
        return protection;
    }
};

#endif
