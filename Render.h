#include "Sprites.h"
#include "Dungeon.hpp"


//render all bullet objects.
void renderBullets();

//render the player.
void renderPlayer(GLfloat scale = 1.f);

//render all mummy objects.
void renderMummys(Dungeon *);

//render all slime objects
void renderSlimes(Dungeon *);

//render all pharaoh objects.
void renderPharaoh(Dungeon *);

//render all pharoh bullet objects.
void renderPharaohBullets();

//rendet all crates.
void renderCrates(Dungeon *);

//render all consumables.
void renderConsumables(Dungeon *);
//render all traps.
void renderTraps(Dungeon *);

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
void renderDungeon(Dungeon * dungeon, GLfloat scale = 1.f);

void renderDungeonArea(Dungeon * dungeon);

//render the map using a breath first search of the dungeons graph.
void renderMap();

//render the pillars
void renderPillars(Dungeon *);

//rotate the model view matrix
void rotateModelView(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

//translate to position on the modelview matrix
void translateModelView(GLfloat x, GLfloat y, GLfloat z);

void scaleModelView(GLfloat x, GLfloat y, GLfloat z);

void scaleProjection(GLfloat x, GLfloat y, GLfloat z);

