//
//  Character.cpp
// Dungeon_Game
//
//  Created by Roberto Ockerse on 07/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#include "Character.hpp"

//character contructre where we initiate the variables and set the time the timer starts to now and intialize the object class

Character::Character()
{
    
    timer = 0;
    start = std::chrono::high_resolution_clock::now();
    
    immune = false;
    
    health = 0;
    
    Object();
}

//set the health that the character currently has

void Character::setHealth(int healthValue)
{
    health = healthValue;
}

// get the amount of health the character has
int Character::getHealth()
{
    return health;
}

//check if the character health has reached 0 if eys return true if not false
bool Character::killed(int damage)
{
    if(!immune)
    {
        health -= damage;
        
        if(health <= 0 ) return true;
    }
    
    return false;
}

//overri the object function move
void Character::move()
{
    
}
//function to heal the character the value integer is the amount of health the chracter will be healed for
void Character::healed(int value)
{
    health += value;
}

//get the strengh teh chatacter has (strengh is used for pushing an object)
int Character::getStrenght()
{
    return strength;
    
}
//set the strengh a character has
void Character::setStrenght(int strenghtValue)
{
    strength = strenghtValue;
}
//reset starte to the time now
void Character::resetTimer(){
      start = std::chrono::high_resolution_clock::now();
}
//set the timer in seconds
void Character::setTimer(double newTimer)
{
    timer = newTimer;
}

//get the timer in seconds
double Character::getTimer()
{
    return timer;
}
//if the charater has been slowed reset the timer and make the slowed variable true
void Character::isSlowed()
{
    resetTimer();
    slowed = true;
}


