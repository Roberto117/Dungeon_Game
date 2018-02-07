//
//  Consumable.hpp
//  Tomb Raider
//
//  Created by Roberto Ockerse on 17/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#ifndef Consumable_hpp
#define Consumable_hpp

#include "Object.hpp"
#include "Player.hpp"
//consumable class that inherits from the object class
class Consumable: public Object
{
public:
    
   
    //constructor
    Consumable();
    //function to set the type of consumable
    void setType(int = -1);
    
    //function to consume the item
    void consume(Player &);
    //set the consume value
    void setConsumeValue( int);
    //get the type the consumable is
    int getType( );
    //get the consume value
    int getConsumeValue();
    
    
private:
    //-enum is used for the types of consumable the item can be
    enum types  {HEALTH_BOX = 0, AMMO_BOX};
    
    //int type stores the type the object is
    int type;
    //store the ammpount the item will heal or add or whatever
    int consumeValue;
};

#endif /* Consumable_hpp */
