//
//  LUtil.hpp
//  Tomb Raider
//
//  Created by Roberto Ockerse on 06/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#ifndef LUtil_hpp
#define LUtil_hpp

#include "LOpenGL.h"
#include "Object.hpp"
#include "Sprites.h"



//intialize glew Devil, sets the viewPort Clear color is set to black Set Devil clear to color to white, texturin is enable reports if there was an error
bool initGL();

//loads the graphics program
bool loadGP();

//Load the Media to be used in the program
bool loadMedia();


//load the triangle VAO
GLuint loadTriangleVertexArray(GLuint VAOID);

//load the triangle VBOs
void loadTriangleVBOs();

//load the rectangle VAO
GLuint loadRectangleVertexArray( GLuint VAOID);

void loadRectangleVBOs();


//rotate the model view matrix
void rotateModelView(GLfloat angle , GLfloat x, GLfloat y, GLfloat z);

//translate to position on the modelview matrix
void translateModelView(GLfloat x,GLfloat y, GLfloat z);

void scaleModelView(GLfloat x,GLfloat y, GLfloat z);

void scaleProjection(GLfloat x,GLfloat y, GLfloat z);


//does per frame logic
void update(double frameTimeDelta);

//renders the scene
void render();

//key handler
void handleKeys(GLFWwindow *window, int key, int scancode, int action, int mods);

//cursor postion handler
void cursorPosition(GLFWwindow *window, double xpos, double ypos);

//mouse clicks handler
void mouseButtonHandler(GLFWwindow *window, int button, int action, int mods);

//function to chech weather 2 objects have collided
bool checkCollision(Object a, Object b );

/*function to check weather 2 object have collided will return a postion that will move an object out of the other object areae
 and two boolean values that will indicate where the object should be pushes to the direction returned will be the opposite of the other object position
*/
bool checkCollision(Object a, Object b , GLfloat&, GLfloat&, bool&, bool&);
 

//check player pillar collison
bool checkPlayerPillarCollision();

//check object pillar collision
bool checkPillarCollision(Object &a);
//create a bullet object which will need a pointer to and addres of a bullet object and the x ,y position where it will be created, it will use the modelBullet object to create it
void createBullet(Bullet *bullet, GLfloat x , GLfloat y);
//create a pharaoBullet object  will need a pointer to and addres of a bullet object and the x ,y position where it will be created, it will use the modelPharaoh bullet object ot create it
void createPharaohBullet(Bullet *bullet,GLfloat x, GLfloat y, float angle);

//create a mummy object, it will need the pointer to and address of a mummy object and the x y cordinate where it will creates, it will sue the modelMummy object to create the mummy.
void createMummy(Mummy *mummy, GLfloat x , GLfloat y);
//create a crate object, it will need a pointer to and addres of the object and the x y cordinates where it will creates it will will use  a model of the object to create it.
void createCrate( Crate *crate, GLfloat x , GLfloat y );
//create a crate pillar, it will need a pointer to and addres of the object and the x y cordinates where it will creates it will will use  a model of the object to create it.
void createPillar( Object * pillar, GLfloat x , GLfloat y );
//create a Consumable object , it will need a pointer to and addres of the object and the x y cordinates where it will creates it will will use  a model of the object to create it.
void createConsumable(Consumable * consumable, GLfloat x , GLfloat y);

//create a slime object , it will need a pointer to and addres of the object and the x y cordinates where it will creates it will will use  a model of the object to create it.
void createSlime(Slime * slime, GLfloat x , GLfloat y );

//create a goo object, , it will need a pointer to and addres of the object and the x y cordinates where it will creates it will will use  a model of the object to create it.
void createdGoo(Trap * trap, GLfloat x, GLfloat y);

//crate a pharaoh object, it will need a pointer to and addres of the object and the x y cordinates where it will creates it will will use  a model of the object to create it.
void createPharao( Pharaoh *pharaoh, GLfloat x, GLfloat y);

//aftert moving to the desired edget this function will get the objects stored in this dungeon and reset the timer for object that need a timer reset.
void moveDungeon();

//before moving to a desired dungeon this function will update the objects of the current dungeon storing their new health and position.
void updateDungeon();

//delete all bullet object.
void deleteBullets();
// reset the timer for all mummys
void resetMummyTimer();
//resets the timer for all slimes.
void resetSlimeTimer();

//reset the timer for all pharaohs
void resetPharaohTimer();

//render all bullet objects.
void renderBullets();

//render the player.
void renderPlayer();

//render all mummy objects.
void renderMummys();

//render all slime objects
void renderSlimes();

//render all pharaoh objects.
void renderPharaoh();

//render all pharoh bullet objects.
void renderPharaohBullets();

//rendet all crates.
void renderCrates();

//render all consumables.
void renderConsumables();
//render all traps.
void renderTraps();

//rende =r the walls of the dungeon.
void renderWalls(GLfloat x = 0, GLfloat y = 0, GLfloat scale = 1.f);
//render the doors of the dungeon it will render a door dependin if the dungeon has an edge at the top,bottom, left and or right.
void renderDoors();
//render the doors of a dungeon this fucntion will be used when rendering the doors of a dungeon that is not the current dungeon, this function is only used when rendering the map.
void renderDoors(bool top, bool bottom, bool left, bool right, GLfloat x = 0, GLfloat y = 0, GLfloat scale = 1.f);
//render the amount of ammo current on the player.
void renderAmmoCount();
//render the playes current health
void renderHealth();
//render the current dungeon.
void renderDungeon();

//render the map using a breath first search of the dungeons graph.
void renderMap();

//render the pillars
void renderPillars();

//create a new dungeon, it will need a int which will store its postion in the dungeon graph array.
bool createDungeon(int pos);


void updateBullets(double frameTimeDelta);

//update the player.
void updatePlayer(double frameTimeDelta);

//update all mummy objects.
void updateMummys(double frameTimeDelta);

//updateall slime objects
void updateSlimes(double frameTimeDelta);

//update all pharaoh objects.
void updatePharaoh(double frameTimeDelta);

//update all pharoh bullet objects.
void updatePharaohBullets(double frameTimeDelta);

//update all crates.
void updateCrates(double frameTimeDelta);

//update all consumables.
void updateConsumables();
//update all traps.
void updateTraps();

//check if there is collision with door if yes move to that dungeon
void checkCollitionWithDoor();


#endif /* LUtil_hpp */
