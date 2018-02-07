//
//  Slime.hpp
//  Dungeon_Game
//
//  Created by Roberto Ockerse on 23/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#ifndef Slime_hpp
#define Slime_hpp

#include "LOpenGL.h"
#include "Character.hpp"

//this class will inherit from the charater class
class Slime : public Character
{
public:
    //constructor for the slime class
    Slime();
    //override the move class in object
	void move(double) override;
    
    //check if the slime should move
    bool isMoving();
    
    //reset the timer on the slime
    void resetTimer();
    //set the range on the slime
    void setRange( int );
    
    //check if is time to drop goo
    bool dropGoo();
    //check if slime has stopped
    bool hasStoped();
    
    //get the range of the slime
    GLfloat getRange();
    
private:
    /*variables for the slime movement
     -range is for how far the slime should move
     -target is the target cordiantes the slime should move
     -move is how far the slime has moved
     -stoped is to check if the slime has stopped
     -DIRECTIONS is used for what direction should the slime move
     -direction will stored the direction the slime is currently moving
     */
    GLfloat range;
    GLfloat target;
    GLfloat moved;
    bool stoped;
    bool moving;
    enum DIRECTIONS {UP = 0, DOWN, RIGHT, LEFT };
    int direction;
};

#endif /* Slime_hpp */
