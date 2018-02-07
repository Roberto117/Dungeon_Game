//
//  Slime.cpp
//  Tomb Raider
//
//  Created by Roberto Ockerse on 23/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#include "Slime.hpp"
#include <time.h>
#include <stdlib.h>
#include "ScreenConstants.h"
#include <iostream>

//constructor for the slime we initilize the character class and the values inside the Slime class
Slime::Slime()
{
    range =target = moved = 0;
    moving = false;
    Character();
}

//variable to check if the slime should move
void Slime::move(double frameTimeDelta)
{
    //check if is time for th slime to move
    if(isMoving())
    {
		GLfloat currentSpeed = speed * frameTimeDelta;
        //the direction value will tell us how far the slime should move
        switch (direction) {
            case UP:
                if(target >= posY || posY <= width + 20) resetTimer();
                
				else  posY -= currentSpeed;
                break;
            case DOWN:
                
                if(target <= posY || posY >= SCREEN_HEIGHT - (width + 20)) resetTimer();
                
				else  posY += currentSpeed;
                break;
            case RIGHT:
                if(target <= posX || posX >= SCREEN_WIDTH - (width + 20)) resetTimer();
                
				else  posX += currentSpeed;
                break;
            case LEFT:
                if(target >= posX || posX <= width + 20) resetTimer();
                
				else  posX -= currentSpeed;
                break;
        }
    }
 
}

//function that check if the slime should move it check the time the same way as the mummy class
bool Slime::isMoving()
{
    if(!moving)
    {
        std::chrono::high_resolution_clock::time_point timeNow = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(timeNow-start);
        
        if(timeSpan.count() >= timer)
        {
            //if is time to move randomly chooses a direction that the slime should move
            direction = rand() % 4;
            switch (direction) {
                case UP:
                    target = posY - range;
                    break;
                case DOWN:
                    target = posY + range;
                    break;
                case RIGHT:
                    target = posX + range;
                    break;
                case LEFT:
                    target = posX - range;
                    break;
            }
            //the slime is mready to move to move the slime
            moving = true;
        }
        
    }
    //return true if the slime should move if not it will return false
    return moving;
}


//set how far the slime will move
void Slime::setRange( int rangeValue)
{
    range = rangeValue;
}

//reset the timer on the slime and make the moving value to false and the stopped value to ture
void Slime::resetTimer()
{
    Character::resetTimer();
    moving = false;
    stoped = true;
}
//get the range of the slime
GLfloat Slime::getRange()
{
    return range;
}

//check if is time to drop goo
bool Slime::dropGoo()
{
    //if the slime is moving we check how far the slime has moved if the slimes has moved far enough from its size and a little bit drop some goo in order to save space and not constaly drop goo
    if(moving)
    {
        if( moved >= (Object::getWidth() *2) - 8 )
        {
            moved = 0;
            return true;
        }
        
        moved += speed;
        
        return false;
        
    }
    //if the slime has  just stopped drop some goo
    else if(hasStoped()) return true;

    return false;
}
//if the slime has stopped return true, if it has stopped make the stopped variable false since we only want to dropp good once everytime the slime stops
bool Slime::hasStoped()
{
    if(stoped)
    {
        stoped = false;
        
        return true;
    }
    
    return false;
}
