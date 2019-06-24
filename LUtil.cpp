//
//  LUtil.cpp
//  Dungeon_Game
//
//  Created by Roberto Ockerse on 06/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#include "LUtil.hpp"
#include <IL/il.h>
#include <IL/ilu.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>



#include "ScreenConstants.h"
#include "Programs.h"
#include "Dungeon.hpp"
#include "Graph.cpp"
#include "DLList.h"

#include "LTextures.hpp"
#include "LVertexPos.h"
#include "LVertexPos.h"

#include "LFRect.h"
#include "LFTri.h"
#include "DungeonArea.h"




#include "Queue.h"

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

#include "ShaderPrograms.h"
#include "CreateObjects.h"
#include "Physics.h"
#include "Render.h"
#include "GlobalGameObjects.h"
using namespace  std;

// variables for the mouse postion
GLfloat mouseX, mouseY;

// class camera which will be used when rendering the map
Camera camera;

//double linked lists to store the objects in the curren dungeon
DLList<Bullet * > bullets;
DLList<Bullet *> pharaohBullets;
//graph to store the dungeons of the program it will be used to navigate between dungeons and to render the map
Graph<Dungeon * > *dungeons;
//model objects array that store the doors and walls of the dungeons
Object WALLS[4];

Object DOORS[4];

Object modelPillar;

//matrixes used for the program
glm::mat4 mProjection;
glm::mat4 mModelView;

//programs used to rendering the sprites
LTexturedRectangle rectangleProgram;
LTexturedTriangle triangleProgram;
LTexturedCircle circleProgram;

//different Object classes used to store a model of the object class this models these will use to create new sprites for the dungeons
Player dungeoneer;
Player sudoDungeoneer;
Mummy sudoMummy;
Object healthBar;
Consumable modelHealthBox;
Consumable modelAmmoBox;
Mummy modelMummy;
Bullet modelBullet;
Bullet modelPharaohBullet;
Crate modelCrate;
Slime modelSlime;
Trap modelGoo;
Pharaoh modelPharaoh;
DungeonArea DungeonStruct;

//boolean values that will be used to pause the game and to render the map
bool paused;
bool map;
//int to save teh current location of the dungeon
int currentLocation;


ShaderPrograms shaderPrograms;



DLList<Crate * > crates;
DLList<Mummy * > mummys;
DLList<Slime * > slimes;
DLList< Trap * > traps;
DLList<Pharaoh * >pharaohs;
DLList<Consumable * > consumables;
DLList<Object *> pillars;
// queue whic I used for the breath first search of the dungeon graph
Queue<int> *queue;
// a double linked list that I used for the breath first search
DLList<int> *lastPos = new DLList<int>;





//initiliazing OpenGL
bool initGL()
{

    
  
    
    //set the viewpost
    
    //initialze the clear color
    glClearColor(0.f, 0.f, 0.f, 1.f);
    
    //enable 2d texturing
    glEnable(GL_TEXTURE_2D);
    
    //set blending
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    ilInit();
    iluInit();
    ilClearColour(255, 255, 255, 0);
    
    ILenum ilError = ilGetError();
    if(ilError != IL_NO_ERROR)
    {
        printf("Error initializing Devil %s", iluErrorString(ilError));
        return false;
    }
    

    //set the projection view to a Ortho matrix for 2D
    mProjection = glm::ortho<GLfloat>(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);
    
    //create a new model view matrix
    mModelView = glm::mat4();
    
    //set that pause value to false and the map value
    paused = false;
    map = false;
    return true;
}

bool loadGP()
{
    //initilize the programs load theird vertex shader and theri fragments shaders return errir if it fails
    if(!triangleProgram.loadProgram (shaderPrograms.vs_BasicPoylgonProgram, shaderPrograms.fs_BasicPoylgonProgram))
    {
        printf("unable to load Triangle Program \n");
        return false;
    }
    
    if(!rectangleProgram.loadProgram(shaderPrograms.vs_BasicPoylgonProgram, shaderPrograms.fs_BasicPoylgonProgram))
    {
        printf("unable to load Rectangle Program \n");
        return false;
        
    }
    
    if(!circleProgram.loadProgram(shaderPrograms.vs_CircleProgram, shaderPrograms.fs_CircleProgram))
    {
        printf("unable to load circle Program\n");
        return false;
    }
    
    
    //bind the programs one by one and update thier matrix to the current matrix.
    triangleProgram.bind();

   
    triangleProgram.updateProjection(mProjection);
    
    triangleProgram.updateModelView(mModelView);
    
	triangleProgram.unbind();

    rectangleProgram.bind();
    
    rectangleProgram.updateModelView(mModelView);
    
    rectangleProgram.updateProjection(mProjection);
    
	rectangleProgram.unbind();

    circleProgram.bind();
    
    circleProgram.updateProjectionMatrix(mProjection);
    circleProgram.updateModelView(mModelView);
    
    //unving the program
    circleProgram.unbind();
    
    return true;
    
    
    
}

bool loadMedia()
{
    
    //VAOs
   /*
    //Dungeon place holders to render ten dungeons later on I will make the game to reandomize the dungeon for now this are manually proccesed
    Dungeon *DungeonOne = new Dungeon;
    
    Dungeon *DungeonTwo = new Dungeon;
    
    Dungeon *DungeonThree = new Dungeon;
    
    Dungeon *DungeonFour = new Dungeon;
    
    Dungeon *DungeonFive = new Dungeon;
    
    Dungeon *DungeonSix = new Dungeon;
    
    Dungeon *DungeonSeven = new Dungeon;
    
    Dungeon *DungeonEight = new Dungeon;
    
    Dungeon *DungeonNine = new Dungeon;
    
    Dungeon *DungeonTen = new Dungeon;
    
    Dungeon *DungeonEleven = new Dungeon;
    
    Dungeon *DungeonTwelve = new Dungeon;
    
    Dungeon *DungeonThirteen = new Dungeon;
    
    Dungeon *DungeonFourteen = new Dungeon;
    
    Dungeon *DungeonFiffteen = new Dungeon;
    
    Dungeon *DungeonSixteen = new Dungeon;
    
    Dungeon *DungeonSeventeen = new Dungeon;
    
    Dungeon *DungeonEightteen = new Dungeon;
    
    Dungeon *DungeonNineteen = new Dungeon;
    
    Dungeon *DungeonTwenty = new Dungeon;

    //double linked list to store different object to store on the dungeons later.
    DLList<Crate * > crates2;
    
    DLList<Mummy * > mummys2;
    
    DLList<Crate *> crates3;
    
    DLList<Crate * >crates4;
	*/

    
    //structures for the vertex of the objects
  
    LFTri dungeoneerTri {
          15,  15,
        -15,   0,
          15, -15 };
    
    LFRect bulletRect{
        -2.5,2.5,
         2.5,2.5,
         2.5,-2.5,
        -2.5,-2.5};
    

    
    LFRect crateRect{
        -10,10,
        10,10,
        10,-10,
        -10,-10
        
    };
    
    LFRect wallRectHorizontal{
        -(SCREEN_WIDTH*0.5),10,
        SCREEN_WIDTH*0.5,10,
        SCREEN_WIDTH*0.5,-10,
        -(SCREEN_WIDTH*0.5),-10
        
    };
    
    LFRect wallRectVertical{
        -10,SCREEN_HEIGHT*0.5,
        10,SCREEN_HEIGHT*0.5,
        10,-(SCREEN_HEIGHT*0.5),
        -10,-(SCREEN_HEIGHT*0.5)
        
    };

    
    
    
    LFRect doorRectHorizontal{
        -(SCREEN_WIDTH*0.10),15,
        SCREEN_WIDTH*0.10,15,
        SCREEN_WIDTH*0.10,-15,
        -(SCREEN_WIDTH*0.10),-15
        
    };
    
    LFRect doorRectVertical{
        -15,SCREEN_HEIGHT*0.10,
        15,SCREEN_HEIGHT*0.10,
        15,-(SCREEN_HEIGHT*0.10),
        -15,-(SCREEN_HEIGHT*0.10)
        
    };
    LFRect healthBarRect{
        -5,5,
        5,5,
        5,-5,
        -5,-5
        
    };
    
    
    LFRect mummyRect{
        -15,15,
        15,15,
        15,-15,
        -15,-15};
    
    LFRect pillarRect{
        -75,60,
        75,60,
        75,-60,
        -75,-60};
    
    LFRect slimeRect{
        -15,15,
        15,15,
        15,-15,
        -15,-15};
    
    
    
    //setting the vertex array object inside the OpenGl program for all model objects and return the address of the VAO to be stores ono the model objects
    GLint dungeoneerVAO = loadTriangleObjectVertexArray(triangleProgram, dungeoneerTri , 0.f, 0.f, 1.f, 1.f, &dungeoneer);
    
    GLint crateVAO = loadRectangleObjectVertexArray(rectangleProgram, crateRect , 0.7, 0.4, 0.1, 1.f, &modelCrate);
    
    GLint bulletVAO = loadRectangleObjectVertexArray(rectangleProgram, bulletRect, 1.f, 1.f, 0.f, 1.f, &modelBullet );
    
     GLint pharaoBulletVAO = loadRectangleObjectVertexArray(rectangleProgram, bulletRect, 1.f, 0.f, 0.f, 1.f, &modelPharaohBullet );
    
    GLint mummyVAO = loadRectangleObjectVertexArray(rectangleProgram, mummyRect, 1.f, 1.f, 1.f, 1.f, &modelMummy );
   
    GLint pillarVAO = loadRectangleObjectVertexArray(rectangleProgram, pillarRect,0.6f, 0.6f, 0.7f, 1.f, &modelPillar );
    
    GLint healthBarVAO = loadRectangleObjectVertexArray(rectangleProgram, healthBarRect, 1.f, 0.f, 0.f, 1.f, &healthBar);
    
    GLint healthBoxVAO = loadRectangleObjectVertexArray(rectangleProgram, healthBarRect, 0.f, 0.9f, 0.2f, 1.f, &modelHealthBox);
    
    GLint ammoBoxVAO =  loadRectangleObjectVertexArray(rectangleProgram, healthBarRect, 0.f, 0.f, 0.6f, 1.f, &modelAmmoBox);
    
    GLint horizontalWallVAO = loadRectangleObjectVertexArray(rectangleProgram, wallRectHorizontal, 0.6f, 0.6f, 0.7f, 1.f, &WALLS[0]);
    
    GLint veticalWallVAO = loadRectangleObjectVertexArray(rectangleProgram, wallRectVertical, 0.6f, 0.6f, 0.7f, 1.f, &WALLS[2]);
   
    GLint horizontalDoorVAO = loadRectangleObjectVertexArray(rectangleProgram, doorRectHorizontal, 0.f, 0.f, 0.0f, 1.f, &DOORS[0]);
    
    GLint verticalDoorVAO = loadRectangleObjectVertexArray(rectangleProgram, doorRectVertical, 0.f, 0.f, 0.f, 1.f, &DOORS[2]);
    
    GLint slimeVAO = loadCircleObjectVertexArray(circleProgram, slimeRect, 0.0f, 0.6f, 0.2f, 1.f, &modelSlime);
    
    GLint gooVAO = loadCircleObjectVertexArray(circleProgram, slimeRect, 0.4f, 0.5f, 0.3f ,1.f ,&modelGoo);
    
    GLint pharaoVAO = loadCircleObjectVertexArray(circleProgram, slimeRect, 0.6f, 0.0f, 0.0f, 1.f, &modelPharaoh);

    //set the VAO addres for all the model objects
    WALLS[0].setVAO(horizontalWallVAO);
    WALLS[1].setVAO(horizontalWallVAO);
    WALLS[2].setVAO(veticalWallVAO);
    WALLS[3].setVAO(veticalWallVAO);
    
    DOORS[0].setVAO(horizontalDoorVAO);
    DOORS[1].setVAO(horizontalDoorVAO);
    DOORS[2].setVAO(verticalDoorVAO);
    DOORS[3].setVAO(verticalDoorVAO);
    
    dungeoneer.setVAO(dungeoneerVAO);
    healthBar.setVAO(healthBarVAO);
    modelMummy.setVAO(mummyVAO);
    modelCrate.setVAO(crateVAO);
    modelBullet.setVAO(bulletVAO);
    modelHealthBox.setVAO(healthBoxVAO);
    modelAmmoBox.setVAO(ammoBoxVAO);
    modelSlime.setVAO(slimeVAO);
    modelGoo.setVAO(gooVAO);
    modelPharaoh.setVAO(pharaoVAO);
    modelPharaohBullet.setVAO(pharaoBulletVAO);
    modelPillar.setVAO(pillarVAO);
    
    
    //set the types of traps
    modelGoo.setType(0);
    
    
    //set the initilized cordinates of the walls and doors and set their with and height
    WALLS[0].setCoordX(SCREEN_WIDTH*0.5);
    WALLS[0].setCoordY(WALLS[0].getHeight());
    
    WALLS[1].setCoordX(SCREEN_WIDTH*0.5);
    WALLS[1].setCoordY( SCREEN_HEIGHT - (WALLS[0].getHeight()) );
    
    WALLS[2].setCoordX( WALLS[2].getWidth() );
    WALLS[2].setCoordY(SCREEN_HEIGHT*0.5);
    
    WALLS[3].setCoordX(SCREEN_WIDTH - (WALLS[2].getWidth()));
    WALLS[3].setCoordY(SCREEN_HEIGHT*0.5);
    
    DOORS[0].setCoordX(SCREEN_WIDTH*0.5);
    DOORS[0].setCoordY(DOORS[0].getHeight());
    
    DOORS[1].setCoordX(SCREEN_WIDTH*0.5);
    DOORS[1].setCoordY( SCREEN_HEIGHT - (DOORS[0].getHeight()) );
    DOORS[1].setObjectWidth(DOORS[0].getWidth());
    DOORS[1].setObjectHeight(DOORS[0].getHeight());
    
    DOORS[2].setCoordX( DOORS[2].getWidth() );
    DOORS[2].setCoordY(SCREEN_HEIGHT*0.5);
    
    DOORS[3].setCoordX(SCREEN_WIDTH - (DOORS[2].getWidth()));
    DOORS[3].setCoordY(SCREEN_HEIGHT*0.5);
    DOORS[3].setObjectWidth(DOORS[2].getWidth());
    DOORS[3].setObjectHeight(DOORS[2].getHeight());
    
    
    //set the sudoPlayers width and heigh
    sudoDungeoneer.setObjectWidth(dungeoneer.getWidth());
    sudoDungeoneer.setObjectHeight(dungeoneer.getHeight());

	sudoMummy.setObjectWidth(modelMummy.getWidth());
	sudoMummy.setObjectHeight(modelMummy.getHeight());

    
    //set the types for consumables be it ammo or health
    modelAmmoBox.setType(1);
    modelHealthBox.setType(0);
    modelHealthBox.setConsumeValue(2);
    modelAmmoBox.setConsumeValue(10);
    
    //set the speed of the model bullets and the damage
    modelBullet.setSpeed(17.f);
    modelBullet.setDamage(10);
    modelPharaohBullet.setSpeed(17.f);
    modelPharaohBullet.setDamage(1);
    
    //set the enemies, health, speed, damage,timer and strenght
    modelMummy.setHealth(20);
    modelMummy.setSpeed(13.f);
	sudoMummy.setSpeed(modelMummy.getSpeed());
    modelMummy.setDamage(1);
    modelMummy.setTimer(1.0);
    modelMummy.setStrenght(20);

    
    modelSlime.setHealth(30);
    modelSlime.setSpeed(3.f);
    modelSlime.setDamage(2);
    modelSlime.setStrenght(20);
    modelSlime.setTimer(0.5);
    modelSlime.setRange(modelSlime.getWidth()*6);
    
    modelPharaoh.setHealth(40);
    modelPharaoh.setDamage(2);
    modelPharaoh.setTimer(2.0);
    modelPharaoh.setStrenght(20);

    //set the players initial cordinates
    dungeoneer.setCoordY(SCREEN_HEIGHT*0.9);
    dungeoneer.setCoordX(SCREEN_WIDTH*0.5);
    

    //set the playes speed, health, ammo, and timer.
	dungeoneer.setSpeed(7.f);
    sudoDungeoneer.setSpeed(dungeoneer.getSpeed());
	dungeoneer.setHealth(10);
	dungeoneer.setAmmo(30);
	dungeoneer.setTimer(2.0);
    
    
    
    //ser the health bar cordinates
    healthBar.setCoordX(SCREEN_WIDTH * 0.9);
    healthBar.setCoordY(SCREEN_HEIGHT * 0.9 );
    
	createDungeons();
    /*
    // x y cordintaes to set the intial cordinates the enemies
    GLfloat x =  -1.f;
    GLfloat y = -1.f;
    
    // pointers to objects that will be used to create new objects.
    Mummy *newMummy;
    
    
    Crate *newCrate;
    
    Slime *newSlime;
    
    Pharaoh *newPharaoh;
    
    
    Object * newPillar;
    
    
    for(int i = 0; i <= 5; i++)
    {
       
      
        
        newPillar = new Object();
        
        if(i <= 2)
        {
            GLfloat PW = modelPillar.getWidth() *2;
            GLfloat XM = -1 + i;
            
            PW *= XM;
            createPillar(newPillar, (SCREEN_WIDTH * 0.5) + PW, SCREEN_HEIGHT *0.5, modelPillar);
             pillars.append(newPillar);
        }
        else if( i != 4)
        {
             GLfloat PH = modelPillar.getHeight() * 2;
            GLfloat YM = -1 +(i - 3);
            
            PH *= YM;
            
            createPillar(newPillar, SCREEN_WIDTH * 0.5, (SCREEN_HEIGHT * 0.5) + PH, modelPillar);
             pillars.append(newPillar);
        }
        
       
        
    }
    
     x =  0.50f;
     y = 0.23f;
    
    //loop to set the initilial postion for crates and mummys
    for(int i = 0; i < 4 ; i++)
    {
        
        newMummy = new Mummy();
        newCrate = new Crate();
        createMummy(newMummy, SCREEN_WIDTH * x, SCREEN_HEIGHT* y, modelMummy);
        createCrate(newCrate, SCREEN_WIDTH * x, SCREEN_HEIGHT * y, modelCrate);
        

        
        mummys.append(newMummy);
        crates3.append(newCrate);
        
        newCrate = new Crate();
        createCrate(newCrate,SCREEN_WIDTH * x, SCREEN_HEIGHT * y, modelCrate);
        crates4.append(newCrate);
        

        //depending on i will change the i to change the pos the next object will be stored

        if(i != 2)
        {
            if(x < 0.75f )  x += 0.25f;
            
            else x -=  0.25f;
            
            if( y <  0.75f) y += 0.27f;
            
            else y  -=0.26f;
        }
        
        else{
            x = 0.25f;
            y = 0.50f;
        }
        
    }
    
    x = 0.25;
    y = 0.25;
    
    // loop to set the intial postions for slimes, pharaohs and crates.
    for(int i = 0 ; i < 4; i ++)
    {
   
        newCrate = new Crate();
        newSlime = new Slime();
        newPharaoh = new Pharaoh();
        createCrate(newCrate,SCREEN_WIDTH * x,SCREEN_HEIGHT * y, modelCrate);
        createSlime(newSlime, SCREEN_WIDTH * x, SCREEN_HEIGHT * y, modelSlime);
        createPharao(newPharaoh, SCREEN_WIDTH * x, SCREEN_HEIGHT * y, modelPharaoh);

        crates.append(newCrate);
        slimes.append(newSlime);
        pharaohs.append(newPharaoh);
        
        
        //depending on i will change the i to change the pos the next object will be stored
        if( i == 0|| i == 2)
        {
            if ( x >  0.25f ) x = 0.25f;
            
            else x = 0.75f;
        }
        
        else
        {
            if ( y > 0.25f ) y = 0.25f;
            
            else y = 0.75f;
        }
        
        
    }
    
    
    x =  0.50f;
    y = 0.25;
    
    //loop to set the cordinates of mroe mummys and crates
    for(int i = 0; i < 4 ; i++)
    {
        
        newMummy = new Mummy();
        createMummy(newMummy, SCREEN_WIDTH * x, SCREEN_HEIGHT* y, modelMummy);
        
        
        mummys2.append(newMummy);
        
        
        
        
        if(i != 2)
        {
            if(x < 0.75f )  x += 0.25f;
            
            else x -=  0.25f;
            
            if( y < 0.75f) y += 0.25f;
            
            else y  -=0.25f;
        }
        
        else{
            x = 0.25f;
            y = 0.50f;
        }
        
    }
    
    x = 0.25;
    y = 0.25;
    
    for(int i = 0 ; i < 4; i ++)
    {
        
        newCrate = new Crate();
        createCrate(newCrate,SCREEN_WIDTH * x,SCREEN_HEIGHT * y, modelCrate);
        crates2.append(newCrate);
        
        //depending on i will change the i to change the pos the next object will be stored
        if( i == 0|| i == 2)
        {
            if ( x >  0.25f ) x = 0.25f;
            
            else x = 0.75f;
        }
        
        else
        {
            if ( y > 0.25f ) y = 0.25f;
            
            else y = 0.75f;
        }
        
        
    }
    
    
    
    
    //setting the enemies on different dungeons.
    
    DungeonOne->setMummys(mummys);
    DungeonOne->setCrates(crates);
    DungeonOne->setPillars(pillars);
    
    
    DungeonTwo->setMummys(mummys2);
    DungeonTwo->setCrates(crates2);
    
    DungeonThree->setCrates(crates3);
    DungeonThree->setSlimes(slimes);
    
    DungeonFour->setCrates(crates4);
    DungeonFour->setPharaohs(pharaohs);
    
    //create a new dungeon graph to store all the dungeons with a max size which will be the number of dungeons will have
    dungeons = new Graph<Dungeon *>(20);
    
    
    
    // this is place holder for now in the future I would like the dungeons to be randomly genereate did not have time for it will do it later for now this sets manually the edges for evey dungeon createing a double directed graph which mean you can go back and forward betwen vertices
    dungeons->movePos(0);
    
    
    dungeons->setElem(DungeonOne);
    dungeons->setEdges(1);
    
    dungeons->movePos(1);
    
    dungeons->setElem(DungeonTwo);
    dungeons->setEdges(4, 0, -1 , 2);
    
    dungeons->movePos(2);
    
    dungeons->setElem(DungeonThree);
    dungeons->setEdges(3,-1,1);
    
    dungeons->movePos(3);
    dungeons->setElem(DungeonFour);
    
    dungeons->setEdges(-1,2,4,5);
    
    dungeons->movePos(4);
    
    dungeons->setElem(DungeonFive);
    dungeons->setEdges(7,1,-1,3);
    
    dungeons->movePos(5);
    
    dungeons->setElem(DungeonSix);
    dungeons->setEdges(-1,-1,3, 6);
    
    dungeons->movePos(6);
    dungeons->setElem(DungeonSeven);
    dungeons->setEdges(-1,-1,5,13);
    
    dungeons->movePos(7);
    
    dungeons->setElem(DungeonEight);
    dungeons->setEdges(8,4);
    
    dungeons->movePos(8);
    
    dungeons->setElem(DungeonNine);
    dungeons->setEdges(-1,7,10,9);
    
    dungeons->movePos(9);
    
    dungeons->setElem(DungeonTen);
    dungeons->setEdges(-1,-1,8);
    
    dungeons->movePos(10);
    
    dungeons->setElem(DungeonEleven);
    dungeons->setEdges(11,-1,-1,8);
    
    dungeons->movePos(11);
    
    dungeons->setElem(DungeonTwelve);
    dungeons->setEdges(-1,10,12);
    
    dungeons->movePos(12);
    
    dungeons->setElem(DungeonThirteen);
    dungeons->setEdges(-1,-1,-1,11);
    
    dungeons->movePos(13);
    
    dungeons->setElem(DungeonFourteen);
    dungeons->setEdges(14,-1,6);
    
    dungeons->movePos(14);
    
    dungeons->setElem(DungeonFiffteen);
    dungeons->setEdges(-1,13,-1,15);
    
    dungeons->movePos(15);
    
    dungeons->setElem(DungeonSixteen);
    dungeons->setEdges(16,-1,14);
    
    dungeons->movePos(16);
    
    dungeons->setElem(DungeonSeventeen);
    dungeons->setEdges(17,15);
    
    dungeons->movePos(17);
    
    dungeons->setElem(DungeonEightteen);
    dungeons->setEdges(-1,16,18);
 
    
    dungeons->movePos(18);
    
    dungeons->setElem(DungeonNineteen);
    dungeons->setEdges(-1,-1,19,17);
    
    dungeons->movePos(19);
    
    dungeons->setElem(DungeonTwenty);
    dungeons->setEdges(-1,-1,-1,18);
    
    //move to the first dungeon

    
    
    //delete all the pointers
    DungeonOne = nullptr;
    DungeonTwo = nullptr;
    DungeonThree = nullptr;
    DungeonFour = nullptr;
    DungeonFive = nullptr;
    DungeonSix = nullptr;
    DungeonSeven = nullptr;
    DungeonEight = nullptr;
    DungeonNine = nullptr;
    DungeonTen = nullptr;
    DungeonEleven = nullptr;
    DungeonTwelve = nullptr;
    DungeonThirteen = nullptr;
    DungeonFourteen = nullptr;
    DungeonFiffteen = nullptr;
    DungeonSixteen = nullptr;
    DungeonSeventeen = nullptr;
    DungeonEightteen = nullptr;
    DungeonNineteen = nullptr;
    DungeonTwenty = nullptr;
    
    newCrate = nullptr;
    newMummy = nullptr;
    newSlime = nullptr;
    newPharaoh = nullptr;
    newPillar= nullptr;
    
    delete newMummy;
    delete newCrate;
    delete newSlime;
    delete newPillar;
    delete newPharaoh;
    delete DungeonOne;
    delete DungeonTwo;
    delete DungeonThree;
    delete DungeonFour;
    delete DungeonFive;
    delete DungeonSix;
    delete DungeonSeven;
    delete  DungeonEight;
    delete DungeonNine;
    delete DungeonTen;
    delete DungeonEleven;
    delete DungeonTwelve;
    delete DungeonThirteen;
    delete DungeonFourteen;
    delete DungeonFiffteen;
    delete DungeonSixteen;
    delete DungeonSeventeen;
    delete  DungeonEightteen;
    delete DungeonNineteen;
    delete DungeonTwenty;

    
    
    //return true if everything was a succes.
	*/
	dungeons->movePos(0);

	moveDungeon();
	updateDungeon();
	moveDungeon();


	//initiliae the queue
	queue = new Queue<int>(dungeons->getSize());

    
    return true;
    

}




//per frame logic for updating
void update(double frameTimeDelta)
{
    // if the game is pause none of the object will move.
    if(!paused)
    {
		Dungeon *currentDungeon = new Dungeon;
		dungeons->getValue(currentDungeon);
        updatePlayer(currentDungeon,  frameTimeDelta);
        updateMummys(currentDungeon, frameTimeDelta);
        updateSlimes(currentDungeon ,frameTimeDelta);
        updateTraps(currentDungeon);
        updatePharaoh(currentDungeon, frameTimeDelta);
        updatePharaohBullets(currentDungeon, frameTimeDelta);
        updateConsumables(currentDungeon);
        updateBullets(currentDungeon, frameTimeDelta);
        checkCollitionWithDoor();
		currentDungeon = nullptr;
		delete currentDungeon;
        
    }
    //if the map is rendeing move the camera and not the player
   else  if(map)
    {
        camera.move(frameTimeDelta);
    }
}
//render the current dungeon
void render()
{
    //clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);
    //if the map is not been render then render the current dungeon
    if(!map)
	{
		Dungeon *currentDungeon = new Dungeon;
		dungeons->getValue(currentDungeon);
		renderDungeon(currentDungeon);
		renderDungeonArea(currentDungeon);
		currentDungeon = nullptr;
		delete currentDungeon;
    }
    
    //render the map
    else{
        //render the map
        renderMap();
        //unbind the program
        rectangleProgram.unbind();
    }
    
 
}

//function to a the keys
void handleKeys(GLFWwindow * window, int key, int scanmode, int action, int mods)
{
    if(!map)
    {
        // if W,A,S,D are pressed make moving true depending on which key is pressed the player will move that way
        if(key == GLFW_KEY_W && action == GLFW_PRESS) dungeoneer.moveUp = true;
        if (key == GLFW_KEY_S && action == GLFW_PRESS) dungeoneer.moveDown = true;
        if (key == GLFW_KEY_A && action == GLFW_PRESS) dungeoneer.moveLeft = true;
        if (key == GLFW_KEY_D && action == GLFW_PRESS) dungeoneer.moveRight = true;
        
        // if W,A,S,D are realesd make moving false depening on which key is pressed
        if(key == GLFW_KEY_W && action == GLFW_RELEASE)dungeoneer. moveUp = false;
        if (key == GLFW_KEY_S && action == GLFW_RELEASE) dungeoneer.moveDown = false;
        if (key == GLFW_KEY_A && action == GLFW_RELEASE) dungeoneer.moveLeft = false;
        if (key == GLFW_KEY_D && action == GLFW_RELEASE) dungeoneer.moveRight = false;
        
    }
    
    else
    {
        // if W,A,S,D are pressed make moving true depending on which key is pressed the camera will move that way
        if(key == GLFW_KEY_W && action == GLFW_PRESS) camera.moveUp = true;
        if (key == GLFW_KEY_S && action == GLFW_PRESS) camera.moveDown = true;
        if (key == GLFW_KEY_A && action == GLFW_PRESS) camera.moveLeft = true;
        if (key == GLFW_KEY_D && action == GLFW_PRESS) camera.moveRight = true;
        
        // if W,A,S,D are realesd make moving false depening on which key is pressed
        if(key == GLFW_KEY_W && action == GLFW_RELEASE)  camera. moveUp = false;
        if (key == GLFW_KEY_S && action == GLFW_RELEASE) camera.moveDown = false;
        if (key == GLFW_KEY_A && action == GLFW_RELEASE) camera.moveLeft = false;
        if (key == GLFW_KEY_D && action == GLFW_RELEASE) camera.moveRight = false;
        
    }
    
    
    // if the P key is pressed pause the game
    if(key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        if(!paused)
        {
            paused = true;
			dungeoneer. moveUp = false;
			dungeoneer.moveDown = false;
			dungeoneer.moveLeft = false;
			dungeoneer.moveRight = false;

        }
        
        
        else paused = false;
        
        
    }
    // if the M key is pressed render the map, pause the game and make the player movement all to be false
    if(key == GLFW_KEY_M && action ==GLFW_PRESS)
    {
        if(!map)
        {
            map = true;
            paused = true;
            camera.setX(SCREEN_WIDTH * 0.5);
            camera.setY(SCREEN_HEIGHT * 0.5);
        }
        
        else
        {
            map = false;
            paused = false;
//            dungeons->movePos(currentLocation);

            
			dungeoneer. moveUp = false;
			dungeoneer.moveDown = false;
			dungeoneer.moveLeft = false;
			dungeoneer.moveRight = false;
            camera.reset();
        }
    }
}

//if the cursos moves update its position on screen
void cursorPosition(GLFWwindow *window, double xpos, double ypos)
{
    //update the mouse position
    mouseX = xpos;
    
    mouseY = ypos;
    

    

}
//handle mouse clicks
void mouseButtonHandler(GLFWwindow * window, int button, int action, int mods)
{
    //if the map is not rendering handle mouse clicks
    if(!map)
    {
        //if the left mouse button is pressed and that player still has ammo create a buller
        if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && dungeoneer.getAmmo() > 0  )
        {
            
            
            Bullet *newBullet  = new Bullet();
            
            // create a new bullet at the tip of the player sprite and set angle that it will move based on the player angle
            createBullet(newBullet, dungeoneer.getX() - (30 * cos(dungeoneer.getRotation() ) ), dungeoneer.getY() - (30 * sin(dungeoneer.getRotation())), modelBullet, dungeoneer);
            
            //append the bullet to the bullet List
            bullets.append(newBullet);
            
            //take one bullt from the players ammo
			dungeoneer.setAmmo(dungeoneer.getAmmo() - 1);
            
            
            
            //delete the bullet pointer
            newBullet= nullptr;
            
            delete newBullet;
        }
    }
}






//create a new dungeon, it will need a int which will store its postion in the dungeon graph array.
bool createDungeons()
{

	
	initializeDungeonStruct();
	int v_map[100][100];
	int vpos_x[40];
	int vpos_y[40];
	fill_n(vpos_x, size(vpos_x), -1);
	fill_n(vpos_y, size(vpos_y), -1);
	for (int i = 0; i < size(v_map); i++) fill_n(v_map[i], size(v_map[i]), -1);
	vpos_x[0] =  49;
	vpos_y[0]=  49;
	v_map[vpos_y[0]][vpos_x[0]] = 0;


	srand(time(0));
	Dungeon * newDungeon;
	dungeons = new Graph<Dungeon *>(rand() % 20 + 21);

	cout << dungeons->getSize() << endl << endl;
	int next_v = 1;
	for (int i = 0; i < dungeons->getSize(); i++)
	{
		if (vpos_x[i] == -1 or vpos_y[i] == -1)
		{
			for (int j = i -1; i <= 0; i--)
			{
				int tries = 0;
				do
				{

					int edges_pos = rand() % 4;
					switch (edges_pos)
					{
					case TOP:
						if (v_map[vpos_y[j] + 1][vpos_x[j]] == -1)
						{
							v_map[vpos_y[j] + 1][vpos_x[j]] = i;
							vpos_x[i] = vpos_x[j];
							vpos_y[i] = vpos_y[j] + 1;
							tries = 5;
						}
						else tries++;
						break;
					case BOTTOM:
						if (v_map[vpos_y[j] - 1][vpos_x[j]] == -1)
						{
							v_map[vpos_y[j] - 1][vpos_x[j]] = i;
							vpos_x[i] = vpos_x[j];
							vpos_y[i] = vpos_y[j] - 1;
							tries = 5;
						}
						else tries++;
						break;
					case LEFT:
						if (v_map[vpos_y[j]][vpos_x[j] - 1] == -1)
						{
							v_map[vpos_y[j]][vpos_x[j] - 1] = i;
							vpos_x[i] = vpos_x[j] - 1;
							vpos_y[i] = vpos_y[j];
							tries = 5;
						}
						else tries++;
						break;
					case RIGHT:
						if (v_map[vpos_y[j]][vpos_x[j] + 1] == -1)
						{
							v_map[vpos_y[j]][vpos_x[j] + 1] = i;
							vpos_x[i] = vpos_x[j] + 1;
							vpos_y[i] = vpos_y[j];
							tries = 5;
						}
						else tries++;
						break;

					default:
						break;
					}
				} while (tries < 4);

				if (vpos_x[i] != -1 && vpos_y[i] != -1) break;

			}
		}
		int num_edges = 0;
		if (v_map[vpos_y[i] +1][vpos_x[i]] != -1) num_edges++;
		if (v_map[vpos_y[i] -1][vpos_x[i]] != -1) num_edges++;
		if (v_map[vpos_y[i]][vpos_x[i] +1] != -1) num_edges++;
		if (v_map[vpos_y[i]][vpos_x[i] -1] != -1) num_edges++;
		int new_edges = rand() % 4 + 1;
		if (new_edges <= num_edges) continue;
		new_edges -= num_edges;
		while (new_edges != 0 )
		{
			int edges_pos = rand() % 4;
			switch (edges_pos)
			{
			case TOP:
				if (v_map[vpos_y[i]+1][vpos_x[i]] == -1)
				{
					v_map[vpos_y[i] + 1][vpos_x[i]] = next_v;
					vpos_x[next_v] = vpos_x[i];
					vpos_y[next_v] = vpos_y[i] + 1;
					next_v++;
					new_edges -= 1;
				}
				break;
			case BOTTOM:
				if (v_map[vpos_y[i]-1][vpos_x[i]] == -1)
				{
					v_map[vpos_y[i]-1][vpos_x[i]] = next_v;
					vpos_x[next_v] = vpos_x[i];
					vpos_y[next_v] = vpos_y[i] -1;
					next_v++;
					new_edges -= 1;
				}
				break;
			case LEFT:
				if (v_map[vpos_y[i]][vpos_x[i] -1] == -1)
				{
					v_map[vpos_y[i]][vpos_x[i] -1] = next_v;
					vpos_x[next_v] = vpos_x[i] -1;
					vpos_y[next_v] = vpos_y[i];
					next_v++;
					new_edges -= 1;
					
				}
				break;
			case RIGHT:
				if (v_map[vpos_y[i]][vpos_x[i] +1] == -1)
				{
					v_map[vpos_y[i]][vpos_x[i] +1] = next_v;
					vpos_x[next_v] = vpos_x[i]+1;
					vpos_y[next_v] = vpos_y[i];
					next_v++;
					new_edges -= 1;
				}
				break;
			
			default:
				break;
			}
			if (next_v >= dungeons->getSize()) break;
		}
		if (next_v >= dungeons->getSize()) break;
	}

	for (int i = 0; i < 100; i++)
	{

		for (int j = 0; j < 100; j++)
		{
			if(v_map[i][j] >= 0 and v_map[i][j] < 10)cout <<"0"<<  v_map[i][j] << "|";
			else cout << v_map[i][j] << "|";
		}
		cout << endl;
	}
	for (int i = 0; i < size(vpos_x); i++)
	{
		
	}


	for (int i = 0; i < dungeons->getSize(); i++)
	{
		int edges[] = { -1,-1, -1, -1, };
		if (v_map[vpos_y[i] + 1][vpos_x[i]] != -1) edges[0] = v_map[vpos_y[i] + 1][vpos_x[i]];
		if (v_map[vpos_y[i] - 1][vpos_x[i]] != -1) edges[1] = v_map[vpos_y[i] - 1][vpos_x[i]];
		if (v_map[vpos_y[i]][vpos_x[i] - 1] != -1) edges[2] = v_map[vpos_y[i]][vpos_x[i] - 1];
		if (v_map[vpos_y[i]][vpos_x[i] + 1] != -1) edges[3] = v_map[vpos_y[i]][vpos_x[i] + 1];
		dungeons->movePos(i);
		newDungeon = new Dungeon;
		createDungeon(newDungeon, i +4);
		dungeons->setElem(newDungeon);
		dungeons->setEdges(edges[0], edges[1], edges[2], edges[3]);

	}







	return true;
}

void initializeDungeonStruct()
{
	

	GLfloat x = (modelPillar.getWidth() * 2) *-2;
	GLfloat	y = (modelPillar.getHeight() * 2) *-3;

	for (int i = 0; i < size(DungeonStruct.PILLAR_POS); i++)
	{
		if (i % 5 == 0 && i != 0)
		{
			x = (modelPillar.getWidth() * 2) *-2;
			y += (modelPillar.getHeight() * 2);
		}
		else if (i != 0 ) x += (modelPillar.getWidth() * 2);
		DungeonStruct.PILLAR_POS[i].x = (SCREEN_WIDTH * 0.5) + x;
		DungeonStruct.PILLAR_POS[i].y = (SCREEN_WIDTH * 0.5) + y;

	}


	x = (modelPillar.getWidth() * 2) *-3;
	y = (modelPillar.getHeight() * 2) * -4;

	for (int i = 0; i < size(DungeonStruct.OBJECT_POS); i++)
	{
		if (i % 7 == 0 && i != 0)
		{
			x = (modelPillar.getWidth() * 2) *-3;
			y += (modelPillar.getHeight() * 2);
		}
		else if (i != 0 ) x += (modelPillar.getWidth() * 2);

		DungeonStruct.OBJECT_POS[i].x = (SCREEN_WIDTH * 0.5) + x;
		DungeonStruct.OBJECT_POS[i].y = (SCREEN_WIDTH * 0.5) + y;

	}
}

void createDungeon(Dungeon * d,int dif)
{

	Object* newPillar;
	Crate* newCrate;
	Mummy * newMummy;
	Pharaoh* newPharao;
	Slime * newSlime;
	int no_object[] = { 3,14,20,21,27,38 };
	/*
	for (int i = 0; i < size(DungeonStruct.OBJECT_POS); i++)
	{
		if (find(std::begin(no_object), end(no_object), i) == end(no_object))
		{
			newPharao = new Pharaoh();
			createPharao(newPharao, DungeonStruct.OBJECT_POS[i].x, DungeonStruct.OBJECT_POS[i].y, modelPharaoh);
			d->pharaohs.append(newPharao);
		}
	}
	for (int i = 0; i < size(DungeonStruct.PILLAR_POS); i++)
	{
		newPillar = new Object();
		createPillar(newPillar, DungeonStruct.PILLAR_POS[i].x, DungeonStruct.PILLAR_POS[i].y, modelPillar);
		d->pillars.append(newPillar);
	}
	


	newPillar = nullptr;
	newCrate = nullptr;
	newMummy = nullptr;
	newPharao = nullptr;
	newSlime = nullptr;
	delete newPillar;
	delete newCrate;
	delete newMummy;
	delete newPharao;
	delete newSlime;
	return;
	*/
	bool used[size(DungeonStruct.OBJECT_POS)];
	fill_n(used, size(used), false);

	int num_objs = 0;
	if (dif > size(DungeonStruct.OBJECT_POS) -1) num_objs = rand() % 36;
	else num_objs = rand() % dif + 1;

	for (int i =  0; i <= num_objs; i++)
	{
		int objct_type = 0;
		if(dif > size(DungeonStruct.OBJECT_POS) )objct_type =  rand() % 100;
		else objct_type = rand() % (75 + dif);
		int pos = 0;
		if (objct_type >= 31 and objct_type <= 60)
		{
			do
			{
				pos = rand() % size(DungeonStruct.PILLAR_POS);
			} while (used[pos+8]);
			used[pos + 8] = true;

			newPillar = new Object();
			createPillar(newPillar, DungeonStruct.PILLAR_POS[pos].x , DungeonStruct.PILLAR_POS[pos].y , modelPillar);
			d->pillars.append(newPillar);
			continue;
		}

		do
		{
			pos = rand() % size(DungeonStruct.OBJECT_POS);
		} while (used[pos] && find(std::begin(no_object), end(no_object), pos) == end(no_object));
		used[pos] = true;
		if(objct_type <= 30)
		{
			newCrate = new Crate();
			createCrate(newCrate, DungeonStruct.OBJECT_POS[pos].x, DungeonStruct.OBJECT_POS[pos].y, modelCrate);
			d->crates.append(newCrate);

		}
		else if (objct_type <= 75)
		{
			newSlime = new Slime();
			createSlime(newSlime, DungeonStruct.OBJECT_POS[pos].x, DungeonStruct.OBJECT_POS[pos].y, modelSlime);
			d->slimes.append(newSlime);
		}
		else if (objct_type <= 85)
		{
			newMummy = new Mummy();
			createMummy(newMummy, DungeonStruct.OBJECT_POS[pos].x, DungeonStruct.OBJECT_POS[pos].y, modelMummy);
			d->mummys.append(newMummy);
		}
		else
		{
			newPharao = new Pharaoh();
			createPharao(newPharao, DungeonStruct.OBJECT_POS[pos].x, DungeonStruct.OBJECT_POS[pos].y, modelPharaoh);
			d->pharaohs.append(newPharao);

		}


	}

	newPillar =  nullptr;
	newCrate = nullptr;
	newMummy = nullptr;
	newPharao =  nullptr;
	newSlime = nullptr;
	delete newPillar;
	delete newCrate;
	delete newMummy;
	delete newPharao;
	delete newSlime;
}


bool checkIfDoor(int pos)
{
	switch (pos) {
	case TOP:
		return dungeons->topIsEdge();
	case BOTTOM:
		return dungeons->bottomIsEdge();
	case LEFT:
		return dungeons->leftIsEdge();
	case RIGHT:
		return dungeons->rightIsEdge();
	default:
		return false;
	}
}