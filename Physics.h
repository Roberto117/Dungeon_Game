#ifndef Physics_h
#define Physics_h
#include "Sprites.h"
#include "Dungeon.hpp"
#include "DLList.h"
#include "Graph.hpp"

void updateBullets(Dungeon *dungeon, double frameTimeDelta);

//update the player.
void updatePlayer(Dungeon *dungeon, double frameTimeDelta);

//update all mummy objects.
void updateMummys(Dungeon *dungeon,  double frameTimeDelta);

//updateall slime objects
void updateSlimes(Dungeon *dungeon, double frameTimeDelta);

//update all pharaoh objects.
void updatePharaoh(Dungeon *dungeon,  double frameTimeDelta);

//update all pharoh bullet objects.
void updatePharaohBullets(Dungeon *dungeon,  double frameTimeDelta);


//update all consumables.
void updateConsumables(Dungeon *dungeoneer);
//update all traps.
void updateTraps(Dungeon *dungeon);

//check if there is collision with door if yes move to that dungeon
void checkCollitionWithDoor();

//function to chech weather 2 objects have collided
bool checkCollision(Object a, Object b);

/*function to check weather 2 object have collided will return a postion that will move an object out of the other object areae
 and two boolean values that will indicate where the object should be pushes to the direction returned will be the opposite of the other object position
*/
bool checkCollision(Object a, Object b, GLfloat&, GLfloat&, bool&, bool&);


//check player pillar collison
bool checkPlayerPillarCollision(Dungeon *dungeon);

//check object pillar collision
bool checkPillarCollision(Dungeon *dungeon, Object &a);

//aftert moving to the desired edget this function will get the objects stored in this dungeon and reset the timer for object that need a timer reset.
void moveDungeon();

//before moving to a desired dungeon this function will update the objects of the current dungeon storing their new health and position.
void updateDungeon();
// reset the timer for all mummys
void resetMummyTimer(Dungeon *dungeon);
//resets the timer for all slimes.
void resetSlimeTimer(Dungeon *dungeon);

//reset the timer for all pharaohs
void resetPharaohTimer(Dungeon *dungeon);

//delete all bullet object.
void deleteBullets();

#endif
