//
//  Object.cpp
//  Tomb Raider
//
//  Created by Roberto Ockerse on 09/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#include "Object.hpp"

//object constructor we initilize its values
Object::Object()
{
    posX = posY = rotation = VAO = vertices = width = height = speed = damage = 0;
}

//set teh object VAO for later use when rendering
void Object::setVAO(GLint VAOID)
{
    VAO = VAOID;
}
//set the objects X cordinate in the program
void Object::setCoordX(GLfloat x)
{
    posX = x;
}

//set the objects Y cordinate in the program
void Object::setCoordY(GLfloat y )
{
    posY = y;
}

//set the angle of the object this could be used to rotate the angle or calculate at what direction should the object travel
void Object::setRotation(float angle)
{
    rotation = angle;
}

//the number of vertice point the object has
void Object::setNumVertice(int numVertices)
{
    vertices = numVertices;
}

//this 4 functions are used to get the X , Y  cordinates , the angle  and the VAO of the object respectively.
GLfloat Object::getX()
{
    return posX;
}

GLfloat Object::getY()
{
    return posY;
}

float Object::getRotation()
{
    return rotation;
}

GLint Object::getVAO()
{
    return VAO;
}


//draw the object with the stored VAO
void Object::drawObject()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLE_FAN, vertices, GL_UNSIGNED_INT, NULL);
}


//return the number of vertice the object has
int Object::getNumVertices()
{
    return vertices;
}

//set the obkects with (I am actually setting the width and the height  to half the object width and hieght for easier use)
void Object::setObjectWidth(GLfloat widthValue)
{
    width = widthValue;
}

void Object::setObjectHeight(GLfloat heightValue)
{
    height = heightValue;
}
//get teh width and the height
GLfloat Object::getWidth()
{
    return width;
}

GLfloat Object::getHeight()
{
    return height;
}



//set the speed the object will travel
void Object::setSpeed(GLfloat speedValue)
{
    speed = speedValue;
}


//set the damage the object will give to another object
void Object::setDamage(int damageValue)
{
    damage = damageValue;
}

//get teh speed of the objet
GLfloat Object::getSpeed()
{
    return speed;
}
//get the damage of the object
int Object::getDamage()
{
    return damage;
}

//this is a virtual function that will be used by other sprites higher in the hierarchy we store it here for easier use betwen functions.
void Object::move(double frameTimeDelta)
{
    
}


void Object::copyMoves(Object  & o)
{
	this->posX = o.getX();
	this->posY = o.getY();
	this->rotation = o.getRotation();
}