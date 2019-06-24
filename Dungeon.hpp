//
//  Dungeon.hpp
//  Dungeon_Game
//
//  Created by Roberto Ockerse on 21/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#ifndef Dungeon_hpp
#define Dungeon_hpp

#include "LOpenGL.h"
#include "DLList.h"
#include "Sprites.h"

//class that will be used to store the items on a dungeon
class Dungeon 
{
public:
    
    Dungeon();
    //funtions to set the items on the local list from a given list
    void setMummys( DLList<Mummy *>&);
    void setCrates(DLList<Crate*>&);
    void setConsumables(DLList<Consumable*>&);
    void setSlimes(DLList<Slime *> &);
    void setTraps(DLList<Trap *> &);
    void setPharaohs(DLList<Pharaoh *> &);
    void setPillars(DLList<Object *> &);
    //functions to get the items from the local list to a given list
    void getMummys( DLList<Mummy*>&);
    void getCrates(DLList<Crate*>&);
    void getConsumables(DLList<Consumable*>&);
    void getSlimes(DLList<Slime * >&);
    void getTraps(DLList<Trap * > &);
    void getPharaohs(DLList<Pharaoh *> &);
    void getPillars(DLList< Object * > & );
    
    //List that will be used to store all items in the dungeon
    DLList<Crate * > crates;
    
    DLList<Mummy * > mummys;
    
    DLList<Consumable * > consumables;
    
    DLList<Slime * > slimes;
    
    DLList<Trap * > traps;
    
    DLList<Pharaoh *>pharaohs;
    
    DLList<Object * > pillars;
    
    //variables that will be used to store the number of items in the dungeon
private:
    int numMummys;
    int numCrates;
    int numConsumables;


    
};

#endif /* Dungeon_hpp */
