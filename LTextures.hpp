//
//  LTextures.hpp
//  Dungeon_Game
//
//  Created by Roberto Ockerse on 09/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#ifndef LTextures_hpp
#define LTextures_hpp
#include "LOpenGL.h"
#include "Programs.h"
#include "LFRect.h"
#include "Object.hpp"
#include "LFTri.h"



#endif /* LTextures_hpp */
//this functions will be used to upload the objects renderin data

//load the triangle VAO
GLuint loadTriangleObjectVertexArray(LTexturedTriangle &, LFTri, GLfloat , GLfloat , GLfloat, GLfloat, Object *  );



//load the rectangle VAO
GLuint loadRectangleObjectVertexArray(LTexturedRectangle &, LFRect, GLfloat, GLfloat , GLfloat, GLfloat, Object * );
//load the circle VAO
GLuint loadCircleObjectVertexArray(LTexturedCircle &, LFRect,  GLfloat, GLfloat , GLfloat, GLfloat, Object * );
