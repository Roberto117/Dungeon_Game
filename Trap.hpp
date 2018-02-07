//
//  Trap.hpp
//  Tomb Raider
//
//  Created by Roberto Ockerse on 16/03/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#ifndef Trap_hpp
#define Trap_hpp

#include "Object.hpp"
#include "Character.hpp"
//Trap object class that inherits from the object class
class Trap : public Object
{
public:
    Trap();
    
    
    //set the type of trap the object is
    void setType (int typeValue = -1);
    //activate the trap and give its effect to the character class
    void activate(Character *);
    
private:
    //different typed of traps
    enum TYPES { GOO = 0, FIRE, SPIKE };
    //the type of the trap the object is is stored here
    int type;
};

#endif /* Trap_hpp */
