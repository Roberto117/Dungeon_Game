//
//  LTexturedRectangle.hpp
//  Tomb Raider
//
//  Created by Roberto Ockerse on 07/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#ifndef LTexturedRectangle_hpp
#define LTexturedRectangle_hpp

#include "LShaderProgram.hpp"
#include "glm/glm.hpp"
#include "LColorRGBA.h"


class LTexturedRectangle: public LShaderProgram
{
public:
    
    LTexturedRectangle();
   
    //loads the shader files for the program
    bool loadProgram(std::string glvsPath, std::string glfsPath);
    
    //sets the Texture atribute pointer
    void setTextCoordPointer(GLsizei stride, const GLvoid *data);
    
    //set the Vertex positon attribute pointer
    
    void setVertexPointer(GLsizei stride, const GLvoid *data);
    
    void setColorPointer(GLsizei stride, const GLvoid *data );
    
    //enables the vertex pointer
    void enableVertexPointer();
    
    //disables usage of the vertex pointer
    void disableVertexPointer();
    
    //enable the Texture pointer
    void enableTexCoorPointer();
    
    //disable TextCoordPointer
    void disableTexCoorPointer();

    
    //updating the projection Matrix
    void updateModelView(glm::mat4 matrix);
    
    //update the projection matrix
    
    void updateProjection(glm::mat4 matrix);
    
    //enable the data pointer
    void enableDataPointers();
    
    //disable the data pointers
    void disableDataPointers();
    
    
    
    /*
     //set the projection matrix
     void setProjectionMatrix(glm::mat4  matrix);
     
     //set the modelview matrix
     void setModelViewMatrix(glm::mat4 matrix);
     
     //left multiplies the member projection matrix
     void leftMultiProjection(glm::mat4 matrix);
     
     //left multiply the memeber ModelView Matrix
     void leftMutiModelView(glm::mat4 matrix);
     
     */

private:
    //texture and vertex attribute location
    GLint mVertexPosLocation;
    GLint mTexCoordLocation;
    
    GLint mColorLocation;
    
    //Projection matrix
    GLint mProjectionMatrixLocation;
   // glm::mat4 mProjectionMatrix;
    
    //Model View matrix;
    GLint mModelViewMatrixLocation;
    //glm::mat4 mModelViewMatrix;
    
    


    
    
};

#endif /* LTexturedRectangle_hpp */
