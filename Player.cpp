//
//  Player.cpp
//  Dungeon_Game
//
//  Created by Roberto Ockerse on 16/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#include "Player.hpp"
#include "ScreenConstants.h"

//Player constructor it intitiat the character object and the class variables
Player::Player()
{
    Character();
    moveLeft = moveRight = moveUp = moveDown = pushed = pushedDown = pushedRight =  immune =false;


	immuneStart = std::chrono::high_resolution_clock::now();
    
    rangePushed = speedPushed = 0;
	immuneTimer = 0.75;
}
//set the amount of ammo the player has
void Player::setAmmo(int ammoValue)
{
    ammo = ammoValue;
}

//get the amount of ammo the player has
int Player::getAmmo()
{
    return ammo;
}
//move the player the direction depends on the button presses the function also check if the player has been slowed if yes then we slow the speed the character moves, if the character is beig pushed the character cannot move by itself until the range wanted is reached
void Player::move(double frameTimeDelta)
{
    if(!pushed)
    {
        
		GLfloat currentSpeed = speed * frameTimeDelta;
        if(slowed) currentSpeed -= 50 * frameTimeDelta;
        
        if(moveUp && posY - height > 20 )  posY -= currentSpeed;
        
        if(moveDown && posY + height < SCREEN_HEIGHT - 20 ) posY += currentSpeed;
        
        if(moveLeft && posX - width > 20) posX -= currentSpeed;
        
        if(moveRight && posX + width < SCREEN_WIDTH - 20) posX += currentSpeed;
    }

    
    else{
        
        if(pushedRight && posX + width < SCREEN_WIDTH -20 ) posX += speedPushed;
        
        else if( posX -width > 20 )posX -= speedPushed;
        
        
        if(pushedDown && posY+height < SCREEN_HEIGHT -20 ) posY += speedPushed;
        
        else if(posY - height > 20) posY -= speedPushed;
        
        rangePushed -= speedPushed;
        
        if(rangePushed <= 0)
        {
            pushed = false;
            immune = false;
        }
  
    }
    

}
//if the character got pushed away from something we set the how far the character got pushed, the speed is being pushed and we set that the character is immune and pushed to  true
void Player::gotPushed(int range, int speedPsh)
{
    if(!immune)
    {
        rangePushed = range;
        
        speedPushed = speedPsh;
        
        immune = true;
        pushed = true;
		immuneStart = std::chrono::high_resolution_clock::now();
    }
	
}
//return if the player is immune
bool Player::isImmune()
{
    return immune;
}
//give ammo to the player
void Player::addAmmo(int ammoValue)
{
    ammo += ammoValue;
}

//if the time runs down remove any effect the player had
void Player::removeEffect()
{
    if(slowed)
    {
        std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();
        
        std::chrono::duration<double> timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(time - start);
        
        if(timeSpan.count() >= timer) slowed = false;


    }
    
    if(immune)
    {
        if(rangePushed == 0)  immune = false;
		else
		{
			std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();

			std::chrono::duration<double> timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(time - immuneStart);
			
			if (timeSpan.count() >= immuneTimer) immune = false;
		}
    }
}


void  Player::copyMoves(Player & p)
{
    moveRight = p.moveRight;
    moveLeft = p.moveLeft;
    moveDown = p.moveDown;
    moveUp = p.moveUp;
    
	Object::copyMoves(p);
    
    if(this->pushed == false && p.pushed == true)
    {
        this->rangePushed = p.rangePushed;
        this->speedPushed = p.speedPushed;
        this->pushed = true;
		this->pushedDown = p.pushedDown;
		this->pushedRight = p.pushedRight;
        
    }
    
}


void Player::setImmune(bool b)
{
	immune = b;
}