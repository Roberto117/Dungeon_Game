//
//  Consumable.cpp
//  Dungeon_Game
//
//  Created by Roberto Ockerse on 17/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#include "Consumable.hpp"
#include <time.h>
#include <stdlib.h>

//construcutor for the consumble class default type will be set to HEALTH_BOX = 0
Consumable::Consumable()
{
    Object();
    type = HEALTH_BOX;
}
//set the type  the consumable will be when created if a value is given then the type will be the type that has been given if not then we randomize the type
void Consumable::setType( int typeValue)
{

    if(typeValue == -1)
    {
       // srand(time(NULL));
        
        type = rand() % 2;
        
        
    }
    
    else type = typeValue;
}

//get the item type
int Consumable::getType(){
    return type;
}

//consume the consumable by th eplayer
void Consumable::consume(Player &player)
{
    //if the type is health heal the player
    if(type == HEALTH_BOX)
    {player.healed(consumeValue);}
    // if not add ammo
    else
    {
        player.addAmmo(consumeValue);
    }
}

//get the ammount the the consume item will add or subtract from the player
int Consumable::getConsumeValue()
{
    return consumeValue;
}
//set the consume value

void Consumable::setConsumeValue(int value)
{
    consumeValue = value;
}
