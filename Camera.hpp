//
//  Camera.hpp
//  Dungeon_Game
//
//  Created by Roberto Ockerse on 29/03/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "LOpenGL.h"

//camera class that will be used to render the map
class Camera
{
public:
    Camera();
    //camera movement function
    void move(double);
    
    //bolean values that will be used for camera movement direction
    bool moveLeft, moveRight, moveUp, moveDown,pushedDown,pushedRight;
    
    
    //functions to get teh camera x y cordinates
    GLfloat getX();
    GLfloat getY();
    
    //set the position on the camera
    void setX(  GLfloat);
    void setY( GLfloat);
    
    //reset the camera positions to 0
    void reset();

private:
    
    //variables that will store the camera X Y positions
    GLfloat posX;
    GLfloat posY;
    
};
#endif /* Camera_hpp */
