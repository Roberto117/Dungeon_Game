//
//  LUtil.hpp
//  Dungeon_Game
//
//  Created by Roberto Ockerse on 06/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//


#include "LOpenGL.h"
#include "Object.hpp"
#include "Sprites.h"
#include "Dungeon.hpp"
#include "DungeonArea.h"
#include <vector>




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



//create a new dungeon, it will need a int which will store its postion in the dungeon graph array.
bool createDungeons();

void createDungeon(Dungeon *, int);

void initializeDungeonStruct();


void initilizeDungeon(Dungeon&);

