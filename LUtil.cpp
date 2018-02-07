//
//  LUtil.cpp
//  Tomb Raider
//
//  Created by Roberto Ockerse on 06/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#include "LUtil.hpp"
#include <IL/il.h>
#include <IL/ilu.h>
#include <math.h>
#include <iostream>



#include "ScreenConstants.h"
#include "Programs.h"
#include "Dungeon.hpp"
#include "Graph.h"

#include "LTextures.hpp"
#include "LVertexPos.h"

#include "LFRect.h"0
#include "LFTri.h"


#include "DLList.cpp"
#include "Queue.h"

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"



using namespace  std;

// variables for the mouse postion
GLfloat mouseX, mouseY;

// class camera which will be used when rendering the map
Camera camera;

//double linked lists to store the objects in the curren dungeon
DLList<Bullet * > bullets;
DLList<Bullet *> pharaohBullets;
DLList<Crate * > crates;
DLList<Mummy * > mummys;
DLList<Slime * > slimes;
DLList< Trap * > traps;
DLList<Pharaoh * >pharaohs;
DLList<Consumable * > consumables;
DLList<Object *> pillars;

//graph to store the dungeons of the program it will be used to navigate between dungeons and to render the map
Graph<Dungeon * > *dungeons;
// queue whic I used for the breath first search of the dungeon graph
Queue<int> *queue;
// a double linked list that I used for the breath first search
DLList<int> *lastPos = new DLList<int>;

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

//boolean values that will be used to pause the game and to render the map
bool paused;
bool map;
//int to save teh current location of the dungeon
int currentLocation;

//a constant that will be used to calulate PI
const float PI = 3.14159265;

enum SHAPES{NOTHING = 0 ,CROSS, CROSS_NO_MID, TWO_VERTICAL_LINES, TWO_HORIZONTAL_LINES, TOP_BOTTOM, LEFT_RIGHT, CORNERS,MID_VERTICAL_LINE,MID_HORIZONTALL_LINE, L_SHAPE_CORNER };


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
    if(!triangleProgram.loadProgram("C:/Polygon_Programs/BasicPolygonProgram.glvs", "C:/Polygon_Programs/BasicPolygonProgram.glfs"))
    {
        printf("unable to load Triangle Program \n");
        return false;
    }
    
    if(!rectangleProgram.loadProgram("C:/Polygon_Programs/BasicPolygonProgram.glvs", "C:/Polygon_Programs/BasicPolygonProgram.glfs"))
    {
        printf("unable to load Rectangle Program \n");
        return false;
        
    }
    
    if(!circleProgram.loadProgram("C:/Polygon_Programs/CircleProgram.glvs", "C:/Dungeon_Game/Polygon_Programs/CircleProgram.glfs"))
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
    modelBullet.setSpeed(200.f);
    modelBullet.setDamage(10);
    modelPharaohBullet.setSpeed(100.f);
    modelPharaohBullet.setDamage(1);
    
    //set the enemies, health, speed, damage,timer and strenght
    modelMummy.setHealth(20);
    modelMummy.setSpeed(160.f);
	sudoMummy.setSpeed(modelMummy.getSpeed());
    modelMummy.setDamage(1);
    modelMummy.setTimer(1.0);
    modelMummy.setStrenght(20);

    
    modelSlime.setHealth(30);
    modelSlime.setSpeed(80.f);
    modelSlime.setDamage(2);
    modelSlime.setTimer(1.0);
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
	dungeoneer.setSpeed(100.f);
    sudoDungeoneer.setSpeed(dungeoneer.getSpeed());
	dungeoneer.setHealth(10);
	dungeoneer.setAmmo(30);
	dungeoneer.setTimer(2.0);
    
    
    
    //ser the health bar cordinates
    healthBar.setCoordX(SCREEN_WIDTH * 0.9);
    healthBar.setCoordY(SCREEN_HEIGHT * 0.9 );
    
    
    
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
            createPillar(newPillar, (SCREEN_WIDTH * 0.5) + PW, SCREEN_HEIGHT *0.5);
             pillars.append(newPillar);
        }
        else if( i != 4)
        {
             GLfloat PH = modelPillar.getHeight() * 2;
            GLfloat YM = -1 +(i - 3);
            
            PH *= YM;
            
            createPillar(newPillar, SCREEN_WIDTH * 0.5, (SCREEN_HEIGHT * 0.5) + PH);
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
        createMummy(newMummy, SCREEN_WIDTH * x, SCREEN_HEIGHT* y);
        createCrate(newCrate, SCREEN_WIDTH * x, SCREEN_HEIGHT * y);
        

        
        mummys.append(newMummy);
        crates3.append(newCrate);
        
        newCrate = new Crate();
        createCrate(newCrate,SCREEN_WIDTH * x, SCREEN_HEIGHT * y);
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
        createCrate(newCrate,SCREEN_WIDTH * x,SCREEN_HEIGHT * y);
        createSlime(newSlime, SCREEN_WIDTH * x, SCREEN_HEIGHT * y);
        createPharao(newPharaoh, SCREEN_WIDTH * x, SCREEN_HEIGHT * y);

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
        createMummy(newMummy, SCREEN_WIDTH * x, SCREEN_HEIGHT* y);
        
        
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
        createCrate(newCrate,SCREEN_WIDTH * x,SCREEN_HEIGHT * y);
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
    dungeons->movePos(0);

    moveDungeon();
    updateDungeon();
    moveDungeon();
    
    
    //initiliae the queue
    queue = new Queue<int>(dungeons->getSize());
    
    
    
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
    
    return true;
    

}




//per frame logic for updating
void update(double frameTimeDelta)
{
    // if the game is pause none of the object will move.
    if(!paused)
    {
        updatePlayer(frameTimeDelta);
        updateMummys(frameTimeDelta);
        updateSlimes(frameTimeDelta);
        updateTraps();
        updatePharaoh(frameTimeDelta);
        updatePharaohBullets(frameTimeDelta);
        updateConsumables();
        updateBullets(frameTimeDelta);
        checkCollitionWithDoor();
        
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
        //bind the rectangle prgram
        rectangleProgram.bind();

    
        //render the walls and doors
        renderWalls();
        renderDoors();
		
		rectangleProgram.unbind();
        //render the enemies, crates, traps, bullets and consumables
        renderDungeon();
        //render the ammo acount and health bar
		rectangleProgram.bind();

        renderAmmoCount();
        renderHealth();
        

		rectangleProgram.unbind();
  

        //unbind the program
        
        
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
            createBullet(newBullet, dungeoneer.getX() - (30 * cos(dungeoneer.getRotation() ) ), dungeoneer.getY() - (30 * sin(dungeoneer.getRotation())));
            
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



// translate the modelView
void translateModelView(GLfloat x, GLfloat y , GLfloat z)
{
    //translate the modelView to the given cordinates
    mModelView = glm::translate<GLfloat>(glm::vec3(x, y, z));
}
//rotate the model view to the given cordinates
void rotateModelView(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    mModelView = glm::rotate<GLfloat>(mModelView, angle, glm::vec3( x, y ,z));
}
//translate the projection matrix to the given cordinates
void translateProjectionView(GLfloat x, GLfloat y, GLfloat z)
{
    mProjection = glm::translate<GLfloat>(glm::vec3(x, y, z));
}
//scale the model view to the given scale
void scaleModelView(GLfloat x,GLfloat y, GLfloat z)
{
    glm::mat4 m = glm::translate(glm::vec3(camera.getX(), camera.getY(), 0.f));
    mModelView *= glm::scale<GLfloat>(m,glm::vec3(x,y,z));
}

//scale the projection view to the given scale
void scaleProjection(GLfloat x,GLfloat y, GLfloat z)
{
    glm::mat4 m = glm::translate(glm::vec3(camera.getX(), camera.getY(), 0.f));
    mProjection *= glm::scale<GLfloat>(m,glm::vec3(x,y,z));
    
}
//check the collison betwen to object we use this function if we do no need for the object to move away from each other afeter collision
bool checkCollision(Object a, Object b)
{
    
    //using Axis-Align Bounding Box to check if to objects collide if they do return true if not return false
    if(abs(a.getX() - b.getX() ) < a.getWidth() + b.getWidth() && abs(a.getY() - b.getY()) < a.getHeight() + b.getHeight())
    {

        return true;
    }
    return false;
    
}
//check collison between to object we use this function if after collision we desire for the objects not to touch eachother

bool checkCollision(Object a, Object b , GLfloat &x, GLfloat &y, bool &right, bool &down)
{
    
     //using AABB to check if to objects collide if they do return true , return and  x,y position that will not have both object colliding and return where an object should be pushed to be pushed away from the other object if not return false
    if(abs(a.getX() - b.getX() ) < a.getWidth() + b.getWidth() && abs(a.getY() - b.getY()) < a.getHeight() + b.getHeight())
    {


        //check where the object a  should move to move away from the object b
        
        // object a x cordinates is smaller than object b then the object should move to the right  else the object should move right
        
        if(a.getX() < b.getX() )
        {
            right = false;
            
            //get an x cordinate away from the other object b
            x = (b.getX() - b.getWidth()) - (a.getX() +a.getWidth());

        }
        else
        {
            right = true;
       
            x = (b.getX() + b.getWidth()) - (a.getX() -a.getWidth());
            
          
        }
        
        //if object a y cordinate is smaller than object b x cordinate then object a should move down else object a should move up
        if(a.getY() < b.getY())
        {
            down = false;
            y = (b.getY() - b.getHeight()) - (a.getY() + a.getHeight());
            
        }
        else
        {
            down = true;
            
            y = (b.getY() + b.getHeight()) - (a.getY() - a.getHeight());
        }
        
        
        
        x = a.getX() + x;
        
        y = a.getY() + y;
        
        return true;
    }
    return false;
}



//create a new bullet
void createBullet( Bullet *bullet,  GLfloat x, GLfloat y )
{
    //set the bullets cordinates
    bullet->setCoordX(x);
    bullet->setCoordY(y);
    //set the bullets width, height using the model bullet
    bullet->setObjectWidth(modelBullet.getWidth());
    bullet->setObjectHeight(modelBullet.getHeight());
    //set the bullets angle that it will move thorugh based on the players current rotation angle
    bullet->setRotation(dungeoneer.getRotation());
    //set the bullets speed based on the model bullets
    bullet->setSpeed(modelBullet.getSpeed());
    
}
// create a pharaoh buller
void createPharaohBullet( Bullet *bullet, GLfloat x , GLfloat y , float angle){
    //set the bullets x y cordinated
    bullet->setCoordX(x);
    bullet->setCoordY(y);
    //set the bulles width and heigh bases on the model pharao bullet
    bullet->setObjectWidth(modelPharaohBullet.getWidth());
    bullet->setObjectHeight(modelPharaohBullet.getHeight());
    //set the angle the bullet will move by based on the given angle
    bullet->setRotation(angle);
    //set the bullets spped based on the model buller current speed
    bullet->setSpeed(modelPharaohBullet.getSpeed());
    
}

//create a new mummy using the modelMummy Object
void createMummy( Mummy *mummy , GLfloat x, GLfloat y)
{
    mummy->setCoordX(x);
    mummy->setCoordY(y);
    mummy->setObjectWidth(modelMummy.getWidth());
    mummy->setObjectHeight(modelMummy.getHeight());
    mummy->setHealth(modelMummy.getHealth());
    mummy->setSpeed(modelMummy.getSpeed());
    mummy->setTimer(modelMummy.getTimer());
    mummy->setStrenght(modelMummy.getStrenght());
    mummy->setDamage(modelMummy.getDamage());
}

//create a new slime
void createSlime(Slime * slime, GLfloat x, GLfloat y)
{
    slime->setCoordX(x);
    slime->setCoordY(y);
    slime->setObjectWidth(modelSlime.getWidth());
    slime->setObjectHeight(modelSlime.getHeight());
    slime->setHealth(modelSlime.getHealth());
    slime->setSpeed(modelSlime.getSpeed());
    slime->setStrenght(modelSlime.getStrenght());
    slime->setDamage(modelSlime.getDamage());
    slime->setTimer(modelSlime.getTimer());
    slime->setRange(modelSlime.getRange());
    slime->setVAO(modelSlime.getVAO());
    slime->setNumVertice(4);
}
//create goo using the modelGoo object and setting the type of the trap to 0
void createdGoo(Trap * trap, GLfloat x, GLfloat y)
{
    trap->setType(0);
    trap->setObjectWidth(modelGoo.getWidth());
    trap->setObjectHeight(modelGoo.getHeight());
    trap->setCoordX(x);
    trap->setCoordY(y);
    trap->setVAO(modelGoo.getVAO());
    trap->setNumVertice(4);
    
}
//create a new crate object
void createCrate(Crate *crate, GLfloat x, GLfloat y)
{
    crate->setCoordX(x);
    crate->setCoordY(y);
    crate->setObjectHeight(modelCrate.getHeight());
    crate->setObjectWidth(modelCrate.getWidth());
    
}

void createPillar( Object * pillar, GLfloat x , GLfloat y ){
    pillar->setCoordX(x);
    pillar->setCoordY(y);
    pillar->setObjectWidth(modelPillar.getWidth());
    pillar->setObjectHeight(modelPillar.getHeight());
}

//create a consumable object it will randomize what item it could be if is a health box use the modelHealth box to model it if not use the ammo health box
void createConsumable(Consumable * consumable, GLfloat x , GLfloat y)
{
    
    consumable->setType();
    if(consumable->getType() == modelHealthBox.getType()) consumable->setConsumeValue(modelHealthBox.getConsumeValue());
    
    else consumable->setConsumeValue(modelAmmoBox.getConsumeValue());
    consumable->setCoordX(x);
    consumable->setCoordY(y);
    consumable->setObjectWidth(modelHealthBox.getWidth());
    consumable->setObjectHeight(modelHealthBox.getHeight());
    
    
}


//create a pharaoh object
void createPharao( Pharaoh * pharaoh, GLfloat x, GLfloat y)
{
    pharaoh->setCoordY(y);
    pharaoh->setCoordX(x);
    pharaoh->setObjectWidth(modelPharaoh.getWidth());
    pharaoh->setObjectHeight(modelPharaoh.getHeight());
    pharaoh->setHealth(modelPharaoh.getHealth());
    pharaoh->setStrenght(modelPharaoh.getStrenght());
    pharaoh->setTimer(modelPharaoh.getTimer());
    pharaoh->setDamage(modelPharaoh.getDamage());
    pharaoh->setVAO(modelPharaoh.getVAO());
    pharaoh->setNumVertice(4);
}

//update the dungeon before moving to the next dungeon
void updateDungeon()
{
    //reset the timer of all enemies in the dungeon
    if(mummys.totalLenght() > 0) resetMummyTimer();
    if(slimes.totalLenght() > 0) resetSlimeTimer();
    if(pharaohs.totalLenght() > 0) resetPharaohTimer();
    
    Dungeon *currentDungeon;
    
    
    dungeons->getValue(currentDungeon);
    //udpate the objects inside the dungeon to their new health and position and if they were killed or not
    currentDungeon->setMummys(mummys);
    currentDungeon->setCrates(crates);
    currentDungeon->setSlimes(slimes);
    currentDungeon->setPillars(pillars);
    currentDungeon->setConsumables(consumables);
    currentDungeon->setTraps(traps);
    currentDungeon->setPharaohs(pharaohs);
    currentDungeon = nullptr;
    
    
    
    
    delete currentDungeon;
}

//move to the next dungeon
void moveDungeon()
{
    Dungeon *nextDungeon;
    
    dungeons->getValue(nextDungeon);
    currentLocation = dungeons->getPos();
    
    //get the enemies, traps,crates, consumables from the dungeon ready to be handled
    nextDungeon->getMummys(mummys);
    nextDungeon->getCrates(crates);
    nextDungeon->getSlimes(slimes);
    nextDungeon->getPillars(pillars);
    nextDungeon->getConsumables(consumables);
    nextDungeon->getTraps(traps);
    nextDungeon->getPharaohs(pharaohs);
    nextDungeon = nullptr;
    
    delete nextDungeon;
    //reset the timer on all enemies
    if(mummys.totalLenght() > 0) resetMummyTimer();
    if(slimes.totalLenght() > 0) resetSlimeTimer();
    if(pharaohs.totalLenght() > 0) resetPharaohTimer();
}

//reset the times on all mummies on the list
void resetMummyTimer()
{
    mummys.setStart();
    
    Mummy *currentMumy;
    for(int i = 0; i < mummys.totalLenght() ; i++)
    {
        mummys.getValue(currentMumy);
        currentMumy->resetTimer();
        mummys.next();
        
    }
    
    
    currentMumy= nullptr;
    delete  currentMumy;
}
//resets the times for all slimes on the list
void resetSlimeTimer()
{
    slimes.setStart();
    
    Slime *currentSlime;
    for(int i = 0; i < slimes.totalLenght(); i++)
    {
        slimes.getValue(currentSlime);
        currentSlime->resetTimer();
        slimes.next();
    }
}

//reset all pharohs on the list
void resetPharaohTimer()
{
    pharaohs.setStart();
    Pharaoh * currentPharaoh;
    
    for(int i = 0 ; i < pharaohs.totalLenght(); i++)
    {
        pharaohs.getValue(currentPharaoh);
        currentPharaoh->resetTimer();
        pharaohs.next();
    }
}


//render the bullets on the list
void renderBullets()
{
    if((bullets.rightLenght() + bullets.leftLenght()) > 0)
    {
        Bullet *bullet;
        
        bullets.setStart();
        
        bullets.getValue(bullet);
        for(int i = 0; i < (bullets.leftLenght()+bullets.rightLenght()); i++)
        {
            //translate the model view to the bullet position update the shader program
            translateModelView(bullet->getX(), bullet->getY(), 0.f);
            
            rectangleProgram.updateModelView(mModelView);
            
            //draw the bullet
            modelBullet.drawObject();
            
            bullets.next();
            
            
            //move to the next bullet
            bullets.getValue(bullet);
            
            
        }
        
        bullet = nullptr;
        
        delete bullet;
    }
}

//render the player
void renderPlayer(){
    //move to rendering position
    translateModelView(dungeoneer.getX(), dungeoneer.getY(), 0.f);
    
    rotateModelView(dungeoneer.getRotation(), 0, 0, 1);
    
    triangleProgram.updateModelView(mModelView);
    
	dungeoneer.drawObject();
}

//render all the mummies
void renderMummys(){
    
    if(mummys.totalLenght() > 0)
    {
        Mummy *currentMummy;
        
        mummys.setStart();
        
        
        for(int i = 0; i < mummys.totalLenght(); i++ )
        {
            mummys.getValue(currentMummy);
            translateModelView(currentMummy->getX(), currentMummy->getY(), 0.f);
            rectangleProgram.updateModelView(mModelView);
            
            modelMummy.drawObject();
            
            mummys.next();
        }
        
        
        currentMummy = nullptr;
        delete currentMummy;
        
    }
    
}

//render slimes
void renderSlimes(){
    if(slimes.totalLenght() > 0)
    {
        
        
        Slime *currentSlime;
        
        slimes.setStart();
        
        for(int i = 0; i < slimes.totalLenght(); i++)
        {
            slimes.getValue(currentSlime);
            
            //update the center point of the object, translate to position and update the shader program
            circleProgram.updateCenterPoint(currentSlime->getX(), currentSlime->getY());
            translateModelView(currentSlime->getX(), currentSlime->getY(), 0.f);
            circleProgram.updateModelView(mModelView);
            
            
            //draw the object
            currentSlime->drawObject();
            //modelSlime.drawObject();
            slimes.next();
            
        }
        
        currentSlime = nullptr;
        delete currentSlime;
    }
}

//render the pharaoh object
void renderPharaoh()
{
    if(pharaohs.totalLenght() > 0)
    {
        Pharaoh * currentPharaoh;
        pharaohs.setStart();
        for(int i = 0; i < pharaohs.totalLenght(); i++)
        {
            pharaohs.getValue(currentPharaoh);
            circleProgram.updateCenterPoint(currentPharaoh->getX(), currentPharaoh->getY());
            translateModelView(currentPharaoh->getX(), currentPharaoh->getY(), 0.f);
            circleProgram.updateModelView(mModelView);
            currentPharaoh->drawObject();
            pharaohs.next();
        }
        
        currentPharaoh = nullptr;
        delete currentPharaoh;
    }
    
}

//render the pharaoh bullets
void renderPharaohBullets()
{
    
    if(pharaohBullets.totalLenght() > 0)
    {
        Bullet *bullet;
        
        pharaohBullets.setStart();
        
        pharaohBullets.getValue(bullet);
        for(int i = 0; i < pharaohBullets.totalLenght(); i++)
        {
            translateModelView(bullet->getX(), bullet->getY(), 0.f);
            
            rectangleProgram.updateModelView(mModelView);
            
            modelPharaohBullet.drawObject();
            
            pharaohBullets.next();
            
            pharaohBullets.getValue(bullet);
            
            
        }
        
        bullet = nullptr;
        
        delete bullet;
        
    }
    
}

//render the crates
void renderCrates()
{
    
    if(crates.rightLenght()+crates.leftLenght() > 0)
    {
        Crate *crate;
        
        crates.setStart();
        
        
        for( int i = 0; i < crates.rightLenght()+crates.leftLenght() ; ++i )
        {
            crates.getValue(crate);
            
            translateModelView(crate->getX(), crate->getY(), 0.f);
            
            rectangleProgram.updateModelView(mModelView);
            
            modelCrate.drawObject();
            
            crates.next();
        }
        
        crate = nullptr;
        
        delete crate;
        
    }
}

//render the consumables
void renderConsumables()
{
    
    if(consumables.totalLenght() > 0 )
    {
        Consumable *currentConsumable;
        
        consumables.setStart();
        
        for(int i = 0; i < consumables.totalLenght(); i++)
        {
            consumables.getValue(currentConsumable);
            translateModelView(currentConsumable->getX(), currentConsumable->getY(), 0.f);
            rectangleProgram.updateModelView(mModelView);
            
            if( currentConsumable->getType() == modelHealthBox.getType()) modelHealthBox.drawObject();
            
            else modelAmmoBox.drawObject();
            
            consumables.next();
        }
    }
    
}
//render traps
void renderTraps()
{
    if(traps.totalLenght() > 0)
    {
        
        Trap *currentTrap;
        traps.setStart();
        for(int i = 0; i < traps.totalLenght(); i++)
        {
            traps.getValue(currentTrap);
            circleProgram.updateCenterPoint(currentTrap->getX(), currentTrap->getY());
            translateModelView(currentTrap->getX(), currentTrap->getY(), 0.f);
            circleProgram.updateModelView(mModelView);
            
            currentTrap->drawObject();
            traps.next();
        }
        
        currentTrap = nullptr;
        delete currentTrap;
    }
}


void renderPillars()
{
    if(pillars.totalLenght() > 0)
    {
        Object * currentPillar;
        pillars.setStart();
        
        for(int i = 0; i < pillars.totalLenght(); i ++)
        {
            pillars.getValue(currentPillar);
            translateModelView(currentPillar->getX(), currentPillar->getY(), 0.f);
            rectangleProgram.updateModelView(mModelView);
            modelPillar.drawObject();
            
            pillars.next();
        }
    }
    
}

//render the walls, this functions will also be used to render the map so we use a scaling variable for when rendering the map
void renderWalls(GLfloat x, GLfloat y, GLfloat scale)
{
    for(int i = 0; i < 4 ; i++)
    {
        //translate to the model view scale the cordinates if need scaling, scale the matrix and update the shader program
        translateModelView((WALLS[i].getX() * scale )+ (x * scale), (WALLS[i].getY() * scale )+ (y * scale), 0.f);
        scaleModelView(scale, scale, 0.f);
        rectangleProgram.updateModelView(mModelView);
        
        
        // if the i index is smalle than two then we draw a vertical wall, if i index is bigger we draw a vertical door
        if(i < 2) WALLS[0].drawObject();
        
        else WALLS[2].drawObject();
        
        
    }
}

//render the doors
void renderDoors()
{
    //we check if the dungeong has an edge at the top,bottom, left and right if an edge exist we draw a door in that postion
    if(dungeons->topIsEdge())
    {
        translateModelView(DOORS[0].getX(), DOORS[0].getY(), 0.f);
        rectangleProgram.updateModelView(mModelView);
        
        DOORS[0].drawObject();
        
    }
    
    if(dungeons->bottomIsEdge())
    {
        translateModelView(DOORS[1].getX(), DOORS[1].getY(), 0.f);
        rectangleProgram.updateModelView(mModelView);
        
        DOORS[0].drawObject();
    }
    if(dungeons->leftIsEdge())
    {
        translateModelView(DOORS[2].getX(), DOORS[2].getY(), 0.f);
        rectangleProgram.updateModelView(mModelView);
        
        DOORS[2].drawObject();
    }
    if(dungeons->rightIsEdge())
    {
        translateModelView(DOORS[3].getX(), DOORS[3].getY(), 0.f);
        rectangleProgram.updateModelView(mModelView);
        
        DOORS[2].drawObject();
    }
    
    
}

//render the amoount of ammo the player has
void renderAmmoCount()
{

	GLfloat y = 0;
	GLfloat x = 0;
    
    //if the player has ammo render the amount
    for(int i = 0; i < dungeoneer.getAmmo(); i++ )
    {
      
        //start at the bottom of the screen if there is more than one bullet  slowly move to 1.5 the modelBullets with so that the objects won't touch each other, if i has reached more than 15  go up by 1.5 the model bullets width every time the bullet count goes past 15 more
        if( i   % 15  == 0)
        {
            x = SCREEN_WIDTH*0.1;
            y = SCREEN_HEIGHT*0.9 - modelBullet.getHeight()*3 * (1+  i/15) ;
        }
        translateModelView( x + modelBullet.getWidth()* 3 * (i% 15), y, 0.f);
        rectangleProgram.updateModelView(mModelView);
        
        modelBullet.drawObject();
    }
}

//render the health
void renderHealth()
{
    //render the health bar for every i index draw the next health bar 1.5 the width of a health bar away from the last bar in order that they wont touch and get confused
    for(int i = 0 ; i < dungeoneer.getHealth(); i++)
    {
        translateModelView(healthBar.getX() -(healthBar.getWidth()*3 * i), healthBar.getY(), 0.f);
        
        rectangleProgram.updateModelView(mModelView);
        
        healthBar.drawObject();
    }
}

//render the map using breath first search
void renderMap()
{
	// start variable which we will use to check which vertice we are checking it's edges a last value where we will store the edge that this vertice is connected too
	int start = currentLocation;
	int last = currentLocation;

	GLfloat scale = 0.1f;

	

	//2 arrays which we will store the postion every dungeon should be
	GLfloat* dungeonX =new GLfloat[dungeons->getSize()];
	GLfloat* dungeonY = new GLfloat[dungeons->getSize()];

    //this variable we will use to handle the edges of a vertice
    int next;
    
    // boolean variables that will return if a vertice has a top,bottom,left and right edge
    bool right, left, bottom, top;
    
    //we will save the curren vertice postion here
    GLfloat x = 0;
    GLfloat y = 0;
    
    /*location of the edge will be store here
     if 0 = TOP
     if 1 = BOTTOM
     if 2 = LEFT
     if 3 = RIGHT
     */
    int location;
    
    
    //reset the queue list
    queue->reset();
    
    //remove all the postions in th double link list lastPos
    if(lastPos->totalLenght() != 0)
    {
        lastPos->setStart();
        while(lastPos->remove(last));
        
        last = currentLocation;
    }
    
    

    //initiate the queue
    queue->enqueue(start);
    
    //mark the first dungeon visitied
    dungeons->setMark(start, VISITED);
    rectangleProgram.bind();
    renderWalls(0, 0, scale);
    //check for edges location
    dungeons->edgesLocations(start, top, bottom, left, right);
    renderDoors(top, bottom, left, right, x, y ,scale);
    
    
    //set the cordinate of the first dungeon
    dungeonX[start] = 0;
    dungeonY[start] = 0;
    
    //do while teh queue is not empty
    while(queue->lenght() != 0)
    {
        //set the list at the start
        lastPos->setStart();
        //deque the vertice to handle
        queue->dequeue(start);
        //if is the first vertice dont update position
        if(last != start)
        {
            //get the value of the last position
            lastPos->getValue(last);
            location = dungeons->edgeLocation(last, start);
            //while the last position does not match with teh current vertice do the loop to find the last position
            while(location == -1)
            {
                lastPos->next();
                lastPos->getValue(last);
                location = dungeons->edgeLocation(last, start);
            }
            
            //depending on the next location update the cordinates
            
            switch(location)
            {
                case TOP:
                    y = dungeonY[last] - SCREEN_HEIGHT;
                    x = dungeonX[last];
                    break;
                case BOTTOM:
                    y = dungeonY[last] + SCREEN_HEIGHT;
                    x = dungeonX[last];
                    break;
                case LEFT:
                    y = dungeonY[last];
                    x = dungeonX[last] - SCREEN_WIDTH;
                    break;
                case RIGHT:
                    y = dungeonY[last];
                    x = dungeonX[last] + SCREEN_WIDTH;
                    break;
            }
            
            
            //update the cordinates of this vertice
            dungeonX[start] = x;
            dungeonY[start] = y;
        }
        //get the first edge of the vertice
        next = dungeons->first(start);
        
        
        
        
        do
        {
            //vertice has been visited skip it
            if(dungeons->getMark(next) == UNVISITED)
            {
                //mark vertice as visited
                dungeons->setMark(next, VISITED);
                //enqueue teh vertice for later handling
                queue->enqueue(next);
               
                //get the edges of the vertice
                location = dungeons->edgeLocation(start, next);
                dungeons->edgesLocations(next, top, bottom, left, right);
               //render the vertice based on its position to the start vertice
                switch(location)
                {
                    case TOP:
                      
                        renderWalls(x , y - SCREEN_HEIGHT,scale);
                        renderDoors(top, bottom, left, right, x , y - SCREEN_HEIGHT ,scale);
                        break;
                    case BOTTOM:
                        renderWalls(x , y + SCREEN_HEIGHT ,scale);
                        renderDoors(top, bottom, left, right, x , y +SCREEN_HEIGHT ,scale);
                        break;
                    case LEFT:
                        renderWalls(x - SCREEN_WIDTH, y ,scale);
                        renderDoors(top, bottom, left, right, x - SCREEN_WIDTH, y ,scale);
                        break;
                    case RIGHT:
                        renderWalls(x + SCREEN_WIDTH, y ,scale);
                        renderDoors(top, bottom, left, right, x + SCREEN_WIDTH, y,scale);
                        break;
                }
            }
            //get the next edge on the vertice
            next = dungeons->next(start, next);

        }
        while(next != -1); //if next returns -1 it means there is not more edges to handles
        
        //appen the start vertice to the list
        lastPos->append(start);
    }

    //when finished rendering reset the marks on the graph
    dungeons->resetMarks();
    
}

//render the dungeon
void renderDungeon()
{
    //bind the circle program and render all circle objects
    circleProgram.bind();
    
    renderTraps();
    renderSlimes();
    renderPharaoh();
    
	circleProgram.unbind();
    //bind the rectangle program and render all rectangle objects
    rectangleProgram.bind();
    
    renderPillars();
    renderCrates();
    renderConsumables();
    renderBullets();
    renderPharaohBullets();
    renderMummys();
	renderPlayer();
	rectangleProgram.unbind();

	


}

//render the doors this dunction is used mainly when renderin the map
void renderDoors(bool top, bool bottom, bool left, bool right , GLfloat x, GLfloat y , GLfloat scale)
{

    //based on the boolean values we will render the door if a boolean value is tru we will render its door.
        if(top)
        {
            translateModelView((DOORS[0].getX() * scale) + (x * scale), (DOORS[0].getY() * scale ) + (y * scale), 0.f);
            scaleModelView(scale, scale, 0.f);

            rectangleProgram.updateModelView(mModelView);
            
            DOORS[0].drawObject();
            
        }
        
        if(bottom)
        {
            
            translateModelView((DOORS[1].getX() * scale)+ (x * scale), (DOORS[1].getY() * scale ) + (y * scale), 0.f);
            scaleModelView(scale, scale, 0.f);
            rectangleProgram.updateModelView(mModelView);
            
            DOORS[0].drawObject();
        }
        if(left)
        {
      
            translateModelView((DOORS[2].getX() * scale) +(x * scale), (DOORS[2].getY() * scale ) + (y * scale), 0.f);
            scaleModelView(scale, scale, 0.f);

            rectangleProgram.updateModelView(mModelView);
            
            DOORS[2].drawObject();
        }
        if(right)
        {
   
            translateModelView((DOORS[3].getX() * scale) +(x * scale), (DOORS[3].getY() * scale ) + (y * scale), 0.f);
            scaleModelView(scale, scale, 0.f);

            rectangleProgram.updateModelView(mModelView);
            
            DOORS[2].drawObject();
        }
}

//update the bullets
void updateBullets( double frameTimeDelta)
{
    
    
    
    //if there is player bulles in the dungeon handle them
    if((bullets.totalLenght()) > 0 )
    {
        Bullet *bullet;
        bool bulletDeleted = false;
        
        bullets.setStart();
        
        
        
        for(int i = 0; i < bullets.totalLenght(); i++)
        {
            bullets.getValue(bullet);
            
            bool bulletDeleted = false;
            // move the bullet
            bullet->move(frameTimeDelta);
            
            //if the bullet reched the edge of the screen delete it
            if((bullet->getY() <= 20 || bullet->getY() >= SCREEN_HEIGHT - 20) || (bullet->getX() <=  20 || bullet->getX() >=SCREEN_WIDTH - 20 ))
            {
                //delet the bulled
                Bullet *tempBullet = new Bullet();
                bullets.remove(tempBullet);
                
                delete tempBullet;
                bulletDeleted = true;
                
                bullets.next();
                
                
                continue;
                
            }
            
            
            //check if bullet hits a wall
            
            if(checkPillarCollision(*bullet))
            {
                Bullet *tempBullet = new Bullet();
                bullets.remove(tempBullet);
                
                delete tempBullet;
                bulletDeleted = true;
                
                bullets.next();
                
                
                continue;

            }
            
            //if there is mummy on the screen check for collision
            if(mummys.totalLenght() > 0)
            {
                Mummy *currentMummy;
                
                mummys.setStart();
                
                
                for(int i  = 0; i < mummys.totalLenght() ; i++)
                {
                    
                    mummys.getValue(currentMummy);
                    
                    if(checkCollision(*bullet, *currentMummy))
                    {
                        // if there is collision damage the mummy checked if killed
                        Bullet *tempBullet;
                        //check if the mummy is killed
                        if(currentMummy->killed(modelBullet.getDamage()))
                        {
                            //if the mummys is killed delete teh mummy
                            Mummy * tempMummy;
                            mummys.remove(tempMummy);
                            delete tempMummy;
                        }
                        
                        //remove the bullet
                        bullets.remove(tempBullet);
                        delete tempBullet;
                        //move to the next bullet on the list
                        bullets.next();
                        
                        bulletDeleted = true;
                        break;
                        
                    }
                    // move the the next mummy
                    mummys.next();
                }
                //delete mummy pointer
                currentMummy = nullptr;
                delete currentMummy;
                
            }
            if(bulletDeleted) continue;
            //if there is slimes on the screen check for collison.
            if(slimes.totalLenght() > 0 )
            {
                Slime * currentSlime;
                
                slimes.setStart();
                
                
                for(int i = 0 ; i < slimes.totalLenght(); i++)
                {
                    //if there is collison damage the slime and checked if killed
                    slimes.getValue(currentSlime);
                    if(checkCollision(*bullet, *currentSlime))
                    {
                        //
                        Bullet *tempBullet;
                        
                        //check if the slime is killed
                        if(currentSlime->killed(modelBullet.getDamage()))
                        {
                            //if killed remove it from the list.
                            Slime *tempSlime;
                            slimes.remove(tempSlime);
                            delete tempSlime;
                        }
                        // remove the buller from the list/
                        bullets.remove(tempBullet);
                        delete tempBullet;
                        //move to the next bullet
                        bullets.next();
                        
                        
                        bulletDeleted = true;
                        break;
                    }
                    //move to the next bullet
                    
                    slimes.next();
                }
                //delete the slime pointer.
                currentSlime = nullptr;
                delete currentSlime;
            }
            if(bulletDeleted) continue;
            //if there is pharos in the dungeon check for collison
            if(pharaohs.totalLenght() > 0 )
            {
                
                Pharaoh *currentPharaoh;
                pharaohs.setStart();
                
                
                for(int i  = 0; i < pharaohs.totalLenght(); i ++)
                {
                    pharaohs.getValue(currentPharaoh);
                    if(checkCollision(*bullet, *currentPharaoh))
                    {
                        //if there is collison damage the paharo and check if killed
                        Bullet *tempBullet;
                        
                        if(currentPharaoh->killed(modelBullet.getDamage()))
                        {
                            //if killed remove the pharao from the list
                            Pharaoh * tempPharaoh;
                            pharaohs.remove(tempPharaoh);
                            delete tempPharaoh;
                        }
                        
                        //remove the buller from the list
                        bullets.remove(tempBullet);
                        delete tempBullet;
                        bullets.next();
                        bulletDeleted = true;
                        break;
                    }
                    pharaohs.next();
                }
            }
            //if the bullet has been deleted continue to the next list.
            if(bulletDeleted) continue;
            
            
            // if there is crates on the screen check for collison
            if(crates.totalLenght() > 0)
            {
                
                Crate *currentCrate;
                
                crates.setStart();
                
                
                for( int j = 0; j < crates.totalLenght(); ++j )
                {
                    crates.getValue(currentCrate);
                    if( checkCollision(*bullet, *currentCrate) )
                    {
                        //if there is collison remove the create and create a new consumable
                        Bullet *tempBullet;
                        Crate *tempCrate;
                        Consumable *newConsumable = new Consumable();
                        
                        bullets.remove(tempBullet);
                        crates.remove(tempCrate);
                        
                        //create a new consumable where the crate was located
                        createConsumable(newConsumable, tempCrate->getX(), tempCrate->getY());
                        //append the consumable to the list
                        consumables.append(newConsumable);
                        
                        
                        //delete the pointer and objects
                        newConsumable = nullptr;
                        delete newConsumable;
                        delete tempCrate;
                        delete tempBullet;
                        
                        break;
                    }
                    
                    //move to the next crate on the list
                    crates.next();
                }
                //delete the pointer
                currentCrate = nullptr;
                delete currentCrate;
            }
            //move to the next bullet on the list
            bullets.next();
            
        }
        //delet the pointer
        bullet = nullptr;
        delete bullet;
    }
    

}

//update the player.
void updatePlayer(double frameTimeDelta)
{
    //check if the effect on player can be removed
    //move the player
    
    sudoDungeoneer.copyMoves(dungeoneer);
    
    sudoDungeoneer.move(frameTimeDelta);
   
	if(!checkPillarCollision(sudoDungeoneer))
    {
		dungeoneer.move(frameTimeDelta);
    }
    else if(dungeoneer.pushed)
    {
		dungeoneer.pushed = false;
		
    }
    
    //set the angel that the player is pointing at based on the mouse position
    float angle = atan2(dungeoneer.getY() - mouseY , dungeoneer.getX() - mouseX );
    
    
    //input the angle into the player class.
	dungeoneer.setRotation(angle);
    
	dungeoneer.removeEffect();

}

//update all mummy objects.
void updateMummys(double frameTimeDelta)
{
        Player *player = &dungeoneer;
    //do the loop while there is objects to handle
    if(mummys.totalLenght() > 0)
    {
        
        Mummy *currentMummy;
        
        mummys.setStart();
        
        for(int i = 0; i < mummys.totalLenght(); i++)
        {
            
            mummys.getValue(currentMummy);
            
            //check if the mummy should move if yes then move
            if(currentMummy->isMoving())
            {
				//check if there is immint impcat if there is then stop the mummy from moving and reset the timer.
				if(currentMummy->checkIfJustStartedMoving())
				{
					sudoMummy.copyMoves(*currentMummy);
		            while (!sudoMummy.sudoMove(frameTimeDelta))
					{
						if (checkPillarCollision(sudoMummy))
						{
					        currentMummy->resetTimer();
							sudoMummy.resetTimer();
							break;
						}
					}
					
					
				}
				else
				{
					currentMummy->move(frameTimeDelta);
				}
                // move the mummy
                
            }
            // if the mummy is not moving it will track the postion of the player this position is teh postion it will move to once it is time to move
            else
            {
                // get the angle pointing to the player from the current mummy
                float angle = atan2(dungeoneer.getY() - currentMummy->getY() , dungeoneer.getX() - currentMummy->getX());
                //give the angle to the mummy
                currentMummy->setRotation(angle);
                
                //give the postion of the player to the mummy the mummy wont stop movin until collison with the player or if arrive at this given postion.
                currentMummy->setTarget(dungeoneer.getX(), dungeoneer.getY());
            }
            
            // values to be used if the player collides with the current object
            
            GLfloat pushX;
            GLfloat pushY;
            
            bool right, down;
            
            if(checkCollision(*player, *currentMummy, pushX, pushY, right, down ))
            {
                // if the player collided with object, damage the player and push the player to the opposite the direction of the object the speed and range pushed is based on the objects strengh
				dungeoneer.killed(currentMummy->getDamage());
				dungeoneer.pushedDown = down;
				dungeoneer.pushedRight= right;
				dungeoneer.gotPushed(currentMummy->getStrenght()*4, currentMummy->getStrenght());
                currentMummy->resetTimer();
                
            }
            
            
            mummys.next();
            
            
        }
        //delete the mummy object
        currentMummy = nullptr;
        delete  currentMummy;
    }
    
    //delete player pointer
    player = nullptr;
    
    delete player;
    
    
}

//updateall slime objects
void updateSlimes(double frameTimeDelta){
    Player *player = &dungeoneer;
    // if ther is slimes handle them
    if(slimes.totalLenght() > 0)
    {
        //pointer used to get the addres of the current object to be handled
        
        Slime *currentSlime;
        
        //set the double linked list to the start.
        
        slimes.setStart();
        
        // values to be used if the player collides with the current object
        GLfloat pushX;
        GLfloat pushY;
        
        bool right, down;
        
        //do the loop while there is objects to handle
        for(int i = 0; i < slimes.totalLenght() ; i++)
        {
            //get the value of the next object in the list.
            slimes.getValue(currentSlime);
            
            
            //check if teh current slime should drop goo
            if(currentSlime->dropGoo())
            {
                
                //create a new trap which will be of type goo
                Trap *newTrap= new Trap();
                createdGoo(newTrap, currentSlime->getX(), currentSlime->getY());
                
                //append the trap to the list
                traps.append(newTrap);
                
                //delete the trap pointer
                newTrap = nullptr;
                delete newTrap;
                
                
                
            }
            
            //move the slime
            currentSlime->move(frameTimeDelta);
            //check if the player collides with the current object
            if(checkCollision(*player, *currentSlime, pushX, pushY, right, down))
            {
                
                // if the player collided with object, damage the player and push the player to the opposite the direction of the object the speed and range pushed is based on the objects strengh
				dungeoneer.killed(currentSlime->getDamage());
				dungeoneer.pushedDown = down;
				dungeoneer.pushedRight= right;
				dungeoneer.gotPushed(currentSlime->getStrenght()*4, currentSlime->getStrenght());
                
                //reset the slime timer
                currentSlime->resetTimer();
            }
            
            //move the the next object on the list
            slimes.next();
        }
        
        //delete teh slime pointer
        currentSlime = nullptr;
        delete currentSlime;
    }

    
    //delete player pointer
    player = nullptr;
    
    delete player;
    
    
}

//update all pharaoh objects.
void updatePharaoh(double frameTimeDelta)
{
    Player *player = &dungeoneer;
    // if there is pharaos in the curren dungeon update their movement.
    if(pharaohs.totalLenght() > 0)
    {
        //pointer that will be used to store the address of the current pharaoh that we are handling
        Pharaoh *currentPharaoh;
        //set the double linke list to the start.
        pharaohs.setStart();
        
        //do a loop while there is still pharaohs that have not been handled
        for(int i = 0; i < pharaohs.totalLenght(); i ++ )
        {
            //get the address of the next pharaoh to handle
            pharaohs.getValue(currentPharaoh);
            
            // values to be used if the player collides with a pharao
            GLfloat pushX;
            GLfloat pushY;
            bool right, down;
            //check if the player collides with a pharaoh
            if(checkCollision(*player, *currentPharaoh, pushX, pushY, right, down))
            {
                // if the player collided with object, damage the player and push the player to the opposite the direction of the object the speed and range pushed is based on the objects strengh
				dungeoneer.killed(currentPharaoh->getDamage());
				dungeoneer.pushedDown = down;
				dungeoneer.pushedRight= right;
				dungeoneer.gotPushed(currentPharaoh->getStrenght()*4, currentPharaoh->getStrenght());
                
            }
            //check if is time for the pharaoh to shoot
            if(currentPharaoh->timeToShoot())
            {
                //if is time to shoot create bullet for every 30 degrees around the pharaph
                Bullet *newBullet;
                
                float i = -180;
                while (i <=180)
                {
                    float angle = 0;
                    if(i != 0)
                    {
                        angle = i *(PI/180);
                    }
                    
                    newBullet = new Bullet();
                    createPharaohBullet(newBullet,currentPharaoh->getX(), currentPharaoh->getY(), angle);
                    pharaohBullets.append(newBullet);
                    i += 45;
                }
                
                
                //reset the timer of the pharoh so that it can wait again before shooting
                currentPharaoh->resetTimer();
                //delete the bullet pointer
                newBullet = nullptr;
                delete newBullet;
            }
            //move to the next pharoh to handle
            pharaohs.next();
            
        }
        //delete the pharaoh pointer
        currentPharaoh= nullptr;
        delete currentPharaoh;
    }
    
    
    //delete player pointer
    player = nullptr;
    
    delete player;
    
    
}

//update all pharoh bullet objects.
void updatePharaohBullets(double frameTimeDelta){
    Player *player = &dungeoneer;
    //if there is pharaoh bullets in the dungeon handle them
    if(pharaohBullets.totalLenght() > 0)
    {
        //pointer to be use to handle the current bullet
        Bullet *bullet;
        //boolean value used to check if the bulled has been deleted
        bool bulletDeleted = false;
        
        pharaohBullets.setStart();
        
        for(int i = 0; i < pharaohBullets.totalLenght(); i++)
        {
            bool bulletDeleted = false;
            pharaohBullets.getValue(bullet);
            
            // move the bullet
            bullet->move(frameTimeDelta);
            
            // if the bullet reached the edges of the screen deleted it
            if((bullet->getY() <= 20 || bullet->getY() >= SCREEN_HEIGHT - 20) || (bullet->getX() <=  20 || bullet->getX() >=SCREEN_WIDTH - 20 ))
            {
                
                //remove the bulled from the list
                Bullet *tempBullet;
                pharaohBullets.remove(tempBullet);
                
                //delete teh bullet
                delete tempBullet;
                bulletDeleted = true;
                //move to the next bullet.
                pharaohBullets.next();
                
                // do another round of the loop
                continue;
                
            }
            
            GLfloat pushX;
            GLfloat pushY;
            
            bool right, down;
            
            if(checkCollision(*player, *bullet, pushX, pushY, right, down ))
            {
                //push the player to the oppisiote direection if collision occur and damage the player.
				dungeoneer.killed(modelPharaohBullet.getDamage());
				dungeoneer.pushedDown = down;
				dungeoneer.pushedRight= right;
				dungeoneer.gotPushed(80.f, 20.f);
                
                //delte the bullet
                Bullet *tempBullet = new Bullet();
                pharaohBullets.remove(tempBullet);
                
                delete tempBullet;
                bulletDeleted = true;
                
                //move to the next buller
                pharaohBullets.next();
                
                
                continue;
            }
            //move to the next bullet
            pharaohBullets.next();
            
        }
        
        //delete the bullet pointer
        bullet = nullptr;
        delete bullet;
    }
    
    
    //delete player pointer
    player = nullptr;
    
    delete player;
    
    
}



//update all consumables.
void updateConsumables()
{
    Player *player = &dungeoneer;
    //if there are consumables on the current dungeon handle them
    if(consumables.totalLenght() > 0)
    {
        //pointer used to get the addres of the current object to be handled
        Consumable *currentConsumable;
        //set the double linked list to the start.
        consumables.setStart();
        
        
        //do the loop while there is objects to handle
        for(int i = 0; i < consumables.totalLenght(); i++)
        {
            //get the value of the next object in the list.
            consumables.getValue(currentConsumable);
            
            //check if the object collides with the player
            if(checkCollision(*player, *currentConsumable))
            {
                //creates a temp object to delete the object
                Consumable *tempConsumable;
                
                //remove the current object from the list
                consumables.remove(tempConsumable);
                
                //the player consumes the object the consumable class will handle what to do with the player depending on the type of consumable it is if is an ammo box it will add ammo if it a health box it will add health
                tempConsumable->consume(dungeoneer);
                //delete the consumable and break out of the loop
                delete tempConsumable;
                break;
            }
            //go to the next consumable.
            consumables.next();
        }
        
        //delete the pointer
        
        currentConsumable = nullptr;
        delete currentConsumable;
        
    }
    
    //delete player pointer
    player = nullptr;
    
    delete player;
    
    

}
//update all traps.
void updateTraps(){
    Player *player = &dungeoneer;
    //if there is traps handle them.
    if(traps.totalLenght() > 0)
    {
        //get the value of the next object in the list.
        
        Trap  *currentTrap;
        
        //set the double linked list to the start.
        traps.setStart();
        
        //check if the player collides with the current object
        
        for(int i = 0; i < traps.totalLenght(); i++)
        {
            traps.getValue(currentTrap);
            
            //check if the player collides with the current object
            if(checkCollision(*currentTrap, *player))
            {
                // the trap class will handle that will happen if the object collides with the player for example if is goo then the player is slowed
                currentTrap->activate(player);
                
            }
            // go the next object
            traps.next();
        }
        
    }
    
    
    //delete player pointer
    player = nullptr;
    
    delete player;
    
    

}

void checkCollitionWithDoor()
{
    //player objer that points at the player adress
   
    
    Player *player = &dungeoneer;
    
    
    
    
    
    //check if the player collides with the doors if yes then move to the desired dungeon
    
    // check collison with the top door
    if(checkCollision(*player, DOORS[0]))
    {
        //check if edge exist
        if(dungeons->topIsEdge())
        {
            //update the current dungeons enemies creates and consumables this will update their health, and position
            updateDungeon();
            //move to the top edge
            dungeons->moveTop();
            
            //get the next dungeons enemies, crates and consumables store them on Lutils lists for objects
            moveDungeon();
            //move the player to the bottom of the screen
			dungeoneer.setCoordY(SCREEN_HEIGHT - DOORS[0].getHeight() * 3);
            
        }
    }
    //check collison with bottom door
    else if(checkCollision(*player, DOORS[1]))
    {
        //check if edge exist
        if(dungeons->bottomIsEdge())
        {
            //update the current dungeons enemies creates and consumables this will update their health, and position
            updateDungeon();
            //move to the bottom edge
            dungeons->moveBottom();
            
            //get the next dungeons enemies, crates and consumables store them on Lutils lists for objects
            moveDungeon();
            
            //set the player postion to the top of the screen
			dungeoneer.setCoordY(DOORS[0].getHeight() * 3);
        }
    }
    //check collision with the ledt door
    else  if(checkCollision(*player, DOORS[2]))
    {
        //check edge exist
        if(dungeons->leftIsEdge())
        {
            //update the current dungeons enemies creates and consumables this will update their health, and position
            updateDungeon();
            // move to the left edge
            dungeons->moveLeft();
            //get the next dungeons enemies, crates and consumables store them on Lutils lists for objects
            moveDungeon();
            
            //move to the right of the screen
			dungeoneer.setCoordX(SCREEN_WIDTH - DOORS[2].getWidth() * 3);
            
        }
    }
    
    //check collison with the right door
    else  if(checkCollision(*player, DOORS[3]))
    {
        //check if edge exist
        if(dungeons->rightIsEdge())
        {
            //update the current dungeons enemies creates and consumables this will update their health, and position
            updateDungeon();
            //move to the right edge
            dungeons->moveRight();
            //get the next dungeons enemies, crates and consumables store them on Lutils lists for objects
            moveDungeon();
            
            //set the player cordinate to the left of the screen
			dungeoneer.setCoordX(DOORS[2].getWidth() * 3);
        }
    }
    
    
    
    //delete player pointer
    player = nullptr;
    
    delete player;
    
    
}

//create a new dungeon, it will need a int which will store its postion in the dungeon graph array.
bool createDungeon(int pos)
{
    Dungeon *newDungeon;
    dungeons->movePos(pos);
    dungeons->getValue(newDungeon);
    
    Object newPillar;
    
    int shape;

    shape  = rand()% 10;
    
    switch(shape)
    {
        case NOTHING:
            break;
        case CROSS:
            break;
            
            
    }
    
    return true;
}


//check if an object collides with a pillar
bool checkPlayerPillarCollision()
{
    if(pillars.totalLenght() > 0)
    {
        
        pillars.setStart();
        Object * currentPillar;
        
        Player *player = &sudoDungeoneer;
        for(int i = 0; i < pillars.totalLenght(); i++)
        {
            pillars.getValue(currentPillar);
            
            GLfloat pushX;
            GLfloat pushY;
            bool right, down;
            //check if the player collides with a pharaoh
            if(checkCollision(*player, *currentPillar, pushX, pushY, right, down))
            {
                return true;
            }
            
            pillars.next();
        }
        
        
        
        player = nullptr;
        currentPillar = nullptr;
        delete  player;
        delete currentPillar;
    }
    
    
    return false;
  
}







bool checkPillarCollision(Object &a)
{
    if(pillars.totalLenght() > 0)
    {
        
        pillars.setStart();
        Object * currentPillar;
        for(int i = 0; i < pillars.totalLenght(); i++)
        {
            pillars.getValue(currentPillar);
            
          
            //check if the object collides with a pharaoh
            if(checkCollision(a, *currentPillar))
            {
                return true;
            }
            
            pillars.next();
        }
        
        
        
      
        currentPillar = nullptr;
        delete currentPillar;
    }
    
    
    return false;
    
}

