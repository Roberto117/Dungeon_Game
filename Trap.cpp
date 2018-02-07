//
//  Trap.cpp
//  Tomb Raider
//
//  Created by Roberto Ockerse on 16/03/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#include "Trap.hpp"
//initilize the type and the object class
Trap::Trap()
{
    type = -1;
    Object();
}
//set the type of trap this trap is if given a value the trap is not that that type if not it will randmly generate a trap
void Trap::setType(int typeValue)
{
    if(typeValue -1)
    {
        type = rand ()% 3;
    }
    
    else{
        if (typeValue > FIRE) return;
        else type = typeValue;
    }
}
//active the trap and do its effect to the character object given
void Trap::activate(Character * character)
{
    switch(type)
    {
        case GOO:
            character->isSlowed();
            break;
            
        default:
            break;
    }
}
