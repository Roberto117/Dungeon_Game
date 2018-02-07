//
//  LTextures.cpp
//  Dungeon_Game
//
//  Created by Roberto Ockerse on 09/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#include "LTextures.hpp"
#include <math.h>
#include "ScreenConstants.h"



GLuint loadTriangleObjectVertexArray(LTexturedTriangle &triangleProgram, LFTri vertices, GLfloat r , GLfloat g, GLfloat b, GLfloat a, Object* object )
{
    GLuint VAOID;
    
    
    GLuint triangleVertexVBO, triangleColorVBO, triangleIBO;
    
    
    
    
    
    //VBO data
    LVertexPos triPos[3];
    LColorRGBA RGBA[3];
    GLuint indice[3];
    
    // set the triangular vertices
    triPos[0].x = vertices.t.x;
    triPos[0].y= vertices.t.y;
    
    triPos[1].x = vertices.r.x;
    triPos[1].y = vertices.r.y;
    
    triPos[2].x= vertices.l.x;
    triPos[2].y = vertices.l.y;
    
    RGBA[0].r = r;
    RGBA[0].g= g;
    RGBA[0].b = b;
    RGBA[0].a = a;
    
    RGBA[1].r = r;
    RGBA[1].g= g;
    RGBA[1].b = b;
    RGBA[1].a = a;
    
    RGBA[2].r = r;
    RGBA[2].g= g;
    RGBA[2].b = b;
    RGBA[2].a = a;
    
    //set the rendering indice
    indice[0] = 0;
    indice[1] = 1;
    indice[2] = 2;
    
    //Create VBO
    glGenBuffers(1, &triangleVertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVertexVBO);
    glBufferData(GL_ARRAY_BUFFER, 3* sizeof(LVertexPos), triPos, GL_STATIC_DRAW);
    
    glGenBuffers(1 , &triangleColorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, triangleColorVBO);
    glBufferData(GL_ARRAY_BUFFER, 3*sizeof(LColorRGBA), RGBA,GL_STATIC_DRAW);
    
    
    //create IBO
    
    glGenBuffers(1, &triangleIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), indice, GL_STATIC_DRAW);

    
    //create VAO
    glGenVertexArrays(1 , &VAOID);
    
    //bind the VAO
    glBindVertexArray(VAOID);
    
    //enabate vetex attributes
    triangleProgram.enableDataPointers();
    
    //set the vertex data
    glBindBuffer(GL_ARRAY_BUFFER, triangleVertexVBO);
    
    triangleProgram.setVertexPointer(0, NULL);
    
    glBindBuffer(GL_ARRAY_BUFFER, triangleColorVBO);
    
    triangleProgram.setColorPointer(0, NULL);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleIBO);
    
    glBindVertexArray(NULL);
    
    object->setObjectHeight (abs(triPos[0].y) );
    
    object->setObjectWidth(abs(triPos[2].x));
    //if an object was given set the number of vertie it should have
    if(object != nullptr)
    {
        
        object->setNumVertice(3);
        

    }
    
    
    return VAOID;
    
}

GLuint loadRectangleObjectVertexArray(LTexturedRectangle &rectangleProgram, LFRect vertices,  GLfloat r , GLfloat g, GLfloat b, GLfloat a, Object* object )
{
    GLuint VAOID;
    
    GLuint rectangleVertexVBO, rectangleColorVBO, rectangleIBO;
    
    
    //VBO
    LVertexPos quadPos[4];
    LColorRGBA RGBA[4];
    GLuint indice[4];
    
    //set the quad vertices
    
    
    quadPos[0].x = vertices.x.x;
    quadPos[0].y = vertices.x.y;
    
    quadPos[1].x = vertices.y.x;
    quadPos[1].y = vertices.y.y;
    
    quadPos[2].x = vertices.w.x;
    quadPos[2].y = vertices.w.y;
    
    quadPos[3].x = vertices.h.x;
    quadPos[3].y = vertices.h.y;
    
    
    RGBA[0].r = r;
    RGBA[0].g= g;
    RGBA[0].b = b;
    RGBA[0].a = a;
    
    RGBA[1].r = r;
    RGBA[1].g= g;
    RGBA[1].b = b;
    RGBA[1].a = a;
    
    RGBA[2].r = r;
    RGBA[2].g= g;
    RGBA[2].b = b;
    RGBA[2].a = a;
    
    
    RGBA[3].r =r;
    RGBA[3].g= g;
    RGBA[3].b = b;
    RGBA[3].a = a;
    
    //set the rendering indice
    indice[0] = 0;
    indice[1] = 1;
    indice[2] = 2;
    indice[3] = 3;
    
    //Create VBO
    
    glGenBuffers(1, &rectangleVertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, rectangleVertexVBO);
    glBufferData(GL_ARRAY_BUFFER, 4* sizeof(LVertexPos), quadPos, GL_STATIC_DRAW);
    
    glGenBuffers(1, &rectangleColorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, rectangleColorVBO);
    glBufferData(GL_ARRAY_BUFFER, 4*sizeof(LColorRGBA), RGBA, GL_STATIC_DRAW);
    
    //Create IBO
    
    glGenBuffers(1, &rectangleIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangleIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), indice, GL_STATIC_DRAW);
    glGenVertexArrays(1 , &VAOID);
    glBindVertexArray(VAOID);
    
    rectangleProgram.enableDataPointers();
    
    glBindBuffer(GL_ARRAY_BUFFER, rectangleVertexVBO);
    
    rectangleProgram.setVertexPointer(0, NULL);
    
    glBindBuffer(GL_ARRAY_BUFFER, rectangleColorVBO);
    
    rectangleProgram.setColorPointer(0, NULL );
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangleIBO);
    
    glBindVertexArray(NULL);
    
    object->setObjectHeight (abs(quadPos[0].y) );
    
    object->setObjectWidth(abs(quadPos[0].x));
    
    
    if(object != nullptr)
    {

        
        object->setNumVertice(4);
        
        
    }
    return VAOID;
}

GLuint loadCircleObjectVertexArray(LTexturedCircle &circleProgram, LFRect vertices,  GLfloat r, GLfloat g , GLfloat b, GLfloat a, Object *object )
{
    GLuint VAOID;
    
    GLuint rectangleVertexVBO, rectangleColorVBO, rectangleIBO, radiusVBO, resolutionVBO;
    
    
    //VBO
    LVertexPos quadPos[4];
    LColorRGBA RGBA[4];
    GLuint indice[4];
    
    //set the quad vertices
    
    
    quadPos[0].x = vertices.x.x;
    quadPos[0].y = vertices.x.y;
    
    quadPos[1].x = vertices.y.x;
    quadPos[1].y = vertices.y.y;
    
    quadPos[2].x = vertices.w.x;
    quadPos[2].y = vertices.w.y;
    
    quadPos[3].x = vertices.h.x;
    quadPos[3].y = vertices.h.y;
    
    
    RGBA[0].r = r;
    RGBA[0].g= g;
    RGBA[0].b = b;
    RGBA[0].a = a;
    
    RGBA[1].r = r;
    RGBA[1].g= g;
    RGBA[1].b = b;
    RGBA[1].a = a;
    
    RGBA[2].r = r;
    RGBA[2].g= g;
    RGBA[2].b = b;
    RGBA[2].a = a;
    
    
    RGBA[3].r =r;
    RGBA[3].g= g;
    RGBA[3].b = b;
    RGBA[3].a = a;
    
    //set the rendering indice
    indice[0] = 0;
    indice[1] = 1;
    indice[2] = 2;
    indice[3] = 3;
    
    //Create VBO
    glGenBuffers(1, &rectangleVertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, rectangleVertexVBO);
    glBufferData(GL_ARRAY_BUFFER, 4* sizeof(LVertexPos), quadPos, GL_STATIC_DRAW);
    
    glGenBuffers(1, &rectangleColorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, rectangleColorVBO);
    glBufferData(GL_ARRAY_BUFFER, 4*sizeof(LColorRGBA), RGBA, GL_STATIC_DRAW);
    

    
    //Create IBO
    
    glGenBuffers(1, &rectangleIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangleIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), indice, GL_STATIC_DRAW);
    glGenVertexArrays(1 , &VAOID);
    glBindVertexArray(VAOID);
    
    circleProgram.enableDataPointers();
    
    glBindBuffer(GL_ARRAY_BUFFER,rectangleVertexVBO);
    
    circleProgram.setVertexPointer(0, NULL);
    
    glBindBuffer(GL_ARRAY_BUFFER,rectangleColorVBO);
    
    
    circleProgram.setColorPointer(0, NULL);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangleIBO);
    
    glBindVertexArray(NULL);

    
    object->setObjectHeight (abs(quadPos[0].y) );
    
    object->setObjectWidth(abs(quadPos[0].x));
    
    
    if(object != nullptr)
    {
        
        
        object->setNumVertice(4);
        
        
    }

    circleProgram.bind();
    
    circleProgram.setResolution(SCREEN_WIDTH ,  SCREEN_HEIGHT );
    circleProgram.unbind();
    
    
    return VAOID;
}

