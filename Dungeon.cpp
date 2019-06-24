//
//  Dungeon.cpp
//  Dungeon_Game
//
//  Created by Roberto Ockerse on 21/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#include "Dungeon.hpp"

//intilize the dungeon and its variables
Dungeon::Dungeon()
{
    numMummys = numCrates = numConsumables =0;
    
}
//set the mummys in the dungeon with a given list full of mummys
void Dungeon::setMummys(DLList<Mummy *>&mummyList)
{
     Mummy *currentMummy;
    //set teh local list to teh start
    mummys.setStart();
    
    //remove all the mummys in the local list
    while(mummys.remove(currentMummy));
    
  //set the given list to teh start
    mummyList.setStart();
    //append every item on the given list to the local liks
    while(mummyList.remove(currentMummy))
    {
        mummys.append(currentMummy);
    }
    //delete the pointer
   currentMummy = nullptr;
    
    delete currentMummy;
}
//set the slime on the local list
void Dungeon::setSlimes(DLList<Slime * > &slimeList)
{
    Slime *currentSlime;
    
    slimes.setStart();
    
    while(slimes.remove(currentSlime));
    
    slimeList.setStart();
    
    while(slimeList.remove(currentSlime))
    {
        slimes.append(currentSlime);
    }
}
//set the pharos on the local list
void Dungeon::setPharaohs(DLList<Pharaoh * > & pharaohList)
{
    Pharaoh * currentPharaoh;
    pharaohs.setStart();
    while(pharaohs.remove(currentPharaoh));
    
    pharaohList.setStart();
    while(pharaohList.remove(currentPharaoh))
    {
        pharaohs.append(currentPharaoh);
    }
}
//set the crates on the local list
void Dungeon::setCrates(DLList<Crate *> &crateList)
{
    
    Crate *currentCrate;
    
    crates.setStart();
    
    while(crates.remove(currentCrate));
    
    
    crateList.setStart();
    
    while(crateList.remove(currentCrate))
    {
        crates.append(currentCrate);
    }
    
    currentCrate = nullptr;
    
    delete currentCrate;
    
}

//set the consumables on the local list
void Dungeon::setConsumables(DLList<Consumable *>  &consumableList)
{
    
    Consumable *currentConsumable;
    
    
    while(consumables.remove(currentConsumable));
    
    consumableList.setStart();
    
    while(consumableList.remove(currentConsumable))
    {
        consumables.append(currentConsumable);
    }
        
    
    currentConsumable = nullptr;
    
    delete currentConsumable;
}
//set the traps on the local list
void Dungeon::setTraps(DLList<Trap *> &trapList)
{
    Trap * currenTrap;
    while(traps.remove(currenTrap));
    trapList.setStart();
    
    while(trapList.remove(currenTrap))
    {
        traps.append(currenTrap);
    }
    
    currenTrap = nullptr;
    delete currenTrap;
}

void Dungeon::setPillars(DLList<Object * >& pillarsList)
{
    Object * currentPillar;
    while(pillars.remove(currentPillar));
    pillarsList.setStart();
    while(pillarsList.remove(currentPillar))
    {
        pillars.append(currentPillar);
    }
}
//get the crates from the local list to the given list

void Dungeon::getCrates(DLList<Crate * > &crateList)
{
    Crate *currentCrate;
    crateList.setStart();
    //set the local list to the start
    crates.setStart();
    //append the local crates to teh given list till we reach an end to the list
    for(int i = 0; i < crates.totalLenght(); i ++)
    {
        crates.getValue(currentCrate);
        crateList.append(currentCrate);
        crates.next();
    }
    //delete the pointer
    currentCrate = nullptr;
    delete currentCrate;
}
//get the mummys from the local list
void Dungeon::getMummys(DLList<Mummy * > &mummyList)
{
    Mummy *currentMummy;
    
    mummyList.setStart();
    mummys.setStart();
    for(int i = 0; i < mummys.totalLenght(); i ++)
    {
        mummys.getValue(currentMummy);
        mummyList.append(currentMummy);
        mummys.next();
    }
    
    currentMummy = nullptr;
    delete currentMummy;
}
//get the slimes from the local list
void Dungeon::getSlimes(DLList<Slime * > &slimeList)
{
    Slime *currentSlime;
    
    slimeList.setStart();
    slimes.setStart();
    for(int i = 0; i < slimes.totalLenght(); i++)
    {
        slimes.getValue(currentSlime);
        slimeList.append(currentSlime);
        slimes.next();
    }
}
//get the pharos from the local list
void Dungeon::getPharaohs(DLList<Pharaoh *> & pharaohsList)
{
    Pharaoh *currentPharaoh;
    
    pharaohsList.setStart();
    pharaohs.setStart();
    for(int i = 0; i < pharaohs.totalLenght(); i++)
    {
        pharaohs.getValue(currentPharaoh);
        pharaohsList.append(currentPharaoh);
        pharaohs.next();
    }
}


//get the consumables from the local list
void Dungeon::getConsumables(DLList<Consumable * > &consumableList)
{
    Consumable *currentConsumable;
    
    consumableList.setStart();
    consumables.setStart();
    for(int i = 0; i < consumables.totalLenght(); i ++)
    {
        consumables.getValue(currentConsumable);
        consumableList.append(currentConsumable);
        consumables.next();
    }
    
    currentConsumable = nullptr;
    delete currentConsumable;
}
//get the traps from the local list
void Dungeon::getTraps(DLList<Trap * > &trapList)
{
    Trap * currentTrap;
    trapList.setStart();
    traps.setStart();
    for(int i = 0; i < traps.totalLenght(); i++)
    {
        traps.getValue(currentTrap);
        trapList.append(currentTrap);
        traps.next();
    }
    
    currentTrap = nullptr;
    delete currentTrap;
    
}

void Dungeon::getPillars(DLList<Object *> &pillarsList)
{
    Object* currentPillar;
    pillarsList.setStart();
    pillars.setStart();
    for(int i = 0; i < pillars.totalLenght(); i++)
    {
        pillars.getValue(currentPillar);
        pillarsList.append(currentPillar);
        pillars.next();
    }
    
}





