//
//  Object.hpp
//  Tomb Raider
//
//  Created by Roberto Ockerse on 09/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include "LOpenGL.h"

class Object
{
public:
    Object();
    
    //draw the object to the screen
    void drawObject();
    
    //functions to set the objects variables
    void setCoordX(GLfloat );
    void setCoordY(GLfloat );
    void setVAO(GLint);
    void setRotation(float);
    void setNumVertice(int);
    void setObjectWidth(GLfloat);
    void setObjectHeight(GLfloat);
    void setSpeed(GLfloat);
    void setDamage( int );
	virtual void move(double);

    
    
    //functions to get the objects variables
    GLfloat getSpeed();
    int getDamage();
    int getNumVertices();
    GLfloat getX();
    GLfloat getY();
    GLfloat getWidth();
    GLfloat getHeight();
    GLint getVAO();
    float getRotation();
	void copyMoves(Object &);
    
protected:
    //variables to maybe be uses by classes higher in the hirarchy
    int vertices;
    GLfloat posX;
    GLfloat posY; 
    GLint VAO;
    float rotation;
    
    GLfloat width;
    GLfloat height;
    
    GLfloat speed;
    int damage;
    
};

#endif /* Object_hpp */
