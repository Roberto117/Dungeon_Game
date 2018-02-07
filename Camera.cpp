//
//  Camera.cpp
//  Dungeon_Game
//
//  Created by Roberto Ockerse on 29/03/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#include "Camera.hpp"
//camera contructor we initilize the camera values
Camera::Camera()
{
    posX = posY = 0.f;
}

//moving the camera depending on the key pressed the camera will move to that direction using the boolean values for directions
void Camera::move(double frameTimeDelta)
{
    
    if(moveUp )  posY += 2.f;
    
    if(moveDown  ) posY -= 2.f;
    
    if(moveLeft) posX += 2.f;
    
    if(moveRight) posX -= 2.f;
}

//get the camera X position
GLfloat Camera::getX()
{
    return posX;
}

//get the cameras Y position
GLfloat Camera::getY()
{
    return posY;
}

//reset the camera positions
void Camera::reset()
{
    posX = posY = 0;
}

//set the position on the camera
void Camera::setX(  GLfloat x)
{
    posX = x;
    
}
void Camera:: setY( GLfloat y)
{
    posY = y;
}
