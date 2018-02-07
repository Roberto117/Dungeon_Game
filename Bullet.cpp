//
//  Bullet.cpp
// Dungeon_Game
//
//  Created by Roberto Ockerse on 07/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#include "Bullet.hpp"
#include <math.h>

//initilize the object variables
Bullet::Bullet()
{
    Object();
    setNumVertice(4);
}

//move the buller
void Bullet::move(double frameDeltaTime)
{
	GLfloat currentSpeed = speed * frameDeltaTime;
    //the bullet moves at the speed it has beein give at an angle defined when is created.
    posY += -( sin(rotation) * currentSpeed );
    posX +=  -( cos(rotation)  * currentSpeed );
}
