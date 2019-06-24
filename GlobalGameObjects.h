
#include "DLList.h"
#include "Sprites.h"
#include "Graph.hpp"
#include "Dungeon.hpp"
#include "Queue.h"

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "LTextures.hpp"
#include "DungeonArea.h"


// variables for the mouse postion
extern GLfloat mouseX, mouseY;

// class camera which will be used when rendering the map
extern Camera camera;

//double linked lists to store the objects in the curren dungeon
extern DLList<Bullet * > bullets;
extern DLList<Bullet *> pharaohBullets;
//graph to store the dungeons of the program it will be used to navigate between dungeons and to render the map
extern Graph<Dungeon * > *dungeons;
//model objects array that store the doors and walls of the dungeons
extern Object WALLS[4];

extern Object DOORS[4];

extern Object modelPillar;

//matrixes used for the program
extern glm::mat4 mProjection;
extern glm::mat4 mModelView;

//programs used to rendering the sprites
extern LTexturedRectangle rectangleProgram;
extern LTexturedTriangle triangleProgram;
extern LTexturedCircle circleProgram;

//different Object classes used to store a model of the object class this models these will use to create new sprites for the dungeons
extern Player dungeoneer;
extern Player sudoDungeoneer;
extern Mummy sudoMummy;
extern Object healthBar;
extern Consumable modelHealthBox;
extern Consumable modelAmmoBox;
extern Mummy modelMummy;
extern Bullet modelBullet;
extern Bullet modelPharaohBullet;
extern Crate modelCrate;
extern Slime modelSlime;
extern Trap modelGoo;
extern Pharaoh modelPharaoh;

//boolean values that will be used to pause the game and to render the map
extern bool paused;
extern bool map;
//int to save teh current location of the dungeon
extern int currentLocation;


// queue whic I used for the breath first search of the dungeon graph
extern Queue<int> *queue;
// a double linked list that I used for the breath first search
extern DLList<int> *lastPos;
extern DungeonArea DungeonStruct;

