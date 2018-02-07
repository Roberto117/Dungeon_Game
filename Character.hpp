//
//  Character.hpp
//  Tomb Raider
//
//  Created by Roberto Ockerse on 07/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#ifndef Character_hpp
#define Character_hpp

#include "LOpenGL.h"
#include "Object.hpp"
#include <chrono>


//character class which all enemie and the player class will inherit from, it inherits from the object class
class Character : public Object
{
public:
    
    
    Character();
    //set and get different variables stored in the character class
    void setHealth(int );
    int getHealth();
    void setStrenght(int);
    int getStrenght();
    
    //checkd if the character has been killed
    bool killed(int );
    //make the character been slowed to true
    void isSlowed();
    //heals the chracter by a given amount
    void healed(int);
    //overiide the move function in the object class
    virtual void move();
    //set the timer in seconds
    void setTimer( double);
    
    //get the timer in seconds
    double getTimer();
    //reset timer class that can be overwritten
    virtual void resetTimer();
    

    
protected:
    /*different vairbles that are used by the character class
     -slowed is used to check if the character is currently being slowed
     -timer is how long before we restart the timer in seconds
     -health is the amount of health the character has
     -strengh is the strenght the charater has
     -start is store a time which we will use to calculte the time betwen then and now to check if the tiemr has run out
     */
    
    bool immune;
    bool slowed;
    double timer;
    int health;
    int strength;
    std::chrono::high_resolution_clock::time_point start;
    
    
    
};

#endif /* Character_hpp */
