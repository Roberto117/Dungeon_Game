//
//  Mummy.cpp
//  Dungeon_Game
//
//  Created by Roberto Ockerse on 16/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#include "Mummy.hpp"
#include "LOpenGL.h"
#include <ctime>
#include <math.h>
#include <algorithm>

//initilize the mummmy class and its variables
Mummy::Mummy()
{

    moving = right = down = false;
    
    targetX = targetY =0;
    
    

    Character();
}

//move the mummy object
void Mummy::move(double frameTimeDelta)
{
	GLfloat currentSpeed = speed * frameTimeDelta;
    //we check to what direction is moving the mummy will move to that direction at the angel especified before it starts moving we reset the timer on the mummy wants it has reached its target position and wait for the mummy to mvoe again
    if(right && down)
    {
        if( posY <= targetY && posX <= targetX )
        {
			posY += (sin(rotation) * currentSpeed);
            posX += ( cos(rotation)  * currentSpeed );
        }
        else resetTimer();
    }
    
    else if(!right && down)
    {
        if( posY <= targetY && posX >= targetX )
        {
            posY += ( sin(rotation) * currentSpeed );
            posX += ( cos(rotation)  * currentSpeed );
        }
        else resetTimer();
    }
    
    else if(right && !down)
    {
        if( posY >= targetY && posX <= targetX )
        {
             posY += ( sin(rotation) * currentSpeed );
			 posX += (cos(rotation)  * currentSpeed);
        }
        else resetTimer();
    }
    
    
    if(!right && !down)
    {
        if( posY >= targetY && posX >= targetX )
        {
            posY += ( sin(rotation) * currentSpeed );
            posX += ( cos(rotation)  * currentSpeed );
        }
        else resetTimer();
    }
    

}

bool Mummy::sudoMove(double frameTimeDelta)
{
	GLfloat currentSpeed = speed * frameTimeDelta;
	//we check to what direction is moving the mummy will move to that direction at the angel especified before it starts moving we reset the timer on the mummy wants it has reached its target position and wait for the mummy to mvoe again
	if (right && down)
	{
		if (posY <= targetY && posX <= targetX)
		{
			posY += (sin(rotation) * currentSpeed);
			posX += (cos(rotation)  * currentSpeed);
			return false;
		}
		else
		{
			resetTimer();
			return true;
		}
	}

	else if (!right && down)
	{
		if (posY <= targetY && posX >= targetX)
		{
			posY += (sin(rotation) * currentSpeed);
			posX += (cos(rotation)  * currentSpeed);

			return false;
		}
		else {

			resetTimer();
			return true;
		}
	}

	else if (right && !down)
	{
		if (posY >= targetY && posX <= targetX)
		{
			posY += (sin(rotation) * currentSpeed);
			posX += (cos(rotation)  * currentSpeed);
			return false;
		}
		else
		{
			resetTimer();
			return true;
		}
	}


	else if (!right && !down)
	{
		if (posY >= targetY && posX >= targetX)
		{
			posY += (sin(rotation) * currentSpeed);
			posX += (cos(rotation)  * currentSpeed);
			return false;
		}
		else
		{
			resetTimer();
			return true;
		}
	}


}


//set the target that the mummy will move in to
void Mummy::setTarget(GLfloat x, GLfloat y)
{
    targetX = x;
    targetY = y;
}

//check if it is time for the mummy to move
bool Mummy::isMoving()
{
    //if is not moving check if is time to move by comparing the time the timer started and time now and check if enough time has passed for it to move
    if(!moving)
    {

        std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();
        
        std::chrono::duration<double> timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(time - start);
        if(timeSpan.count() >= timer )
        {
            //if it is time to move we check the direction the mummy should moved to based on the target position
            if(posX < targetX ) right = true;
            else right = false;
            
            if(posY < targetY) down = true;
            
            else down = false;
            moving = true;
			justStartedMoving= true;
        }
    }
    return moving;
}


//reset the timer on the mummy and we make that moving is false now
void Mummy::resetTimer()
{
 
    Character::resetTimer();
    moving = false;
}

GLfloat Mummy::getTargetX()
{
	return targetX;

}

GLfloat Mummy::getTargetY()
{
	return targetY;

}


void Mummy::copyMoves(Mummy & m)
{
	this->targetX = m.getTargetX();
	this->targetY = m.getTargetY();

	this->moving = true;

	this->right = m.getDirectionX();

	this->down = m.getDirectionY();

	Object::copyMoves(m);
}

bool Mummy::checkIfJustStartedMoving()
{
	if (justStartedMoving)
	{
		justStartedMoving = false;

		return true;
	}

	else return false;
}

bool Mummy::getDirectionX()
{
	return right;

}

bool Mummy::getDirectionY()
{
	return down;
}