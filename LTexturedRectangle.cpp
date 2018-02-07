//
//  LTexturedRectangle.cpp
//  Dungeon_Game
//
//  Created by Roberto Ockerse on 07/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#include "LTexturedRectangle.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

LTexturedRectangle::LTexturedRectangle()
{
    mVertexPosLocation = mTexCoordLocation = mColorLocation = mProjectionMatrixLocation = mModelViewMatrixLocation = 0;
    
}

bool LTexturedRectangle::loadProgram(std::string glvsPath, std::string glfsPath)
{

    mProgramID = glCreateProgram();
    
    GLuint vertexShader = loadShaderFromFile(glvsPath, GL_VERTEX_SHADER) ;
    
    //return false if the vertex shader could not be compile properly delete the program
    if(vertexShader == 0 )
    {
        glDeleteProgram(mProgramID);
        mProgramID = 0;
        return  false;
    }
    
    //attach the shader to the program
    glAttachShader(mProgramID, vertexShader);
    
    //atache teh sahder used for coloring
    GLuint fragmentShader = loadShaderFromFile(glfsPath , GL_FRAGMENT_SHADER);
    
    //check if the fragment shader compiles if not deleted teh vertex shader and the program
    if(fragmentShader == 0)
    {
        glDeleteShader(vertexShader);
        glDeleteProgram(mProgramID);
        mProgramID = 0;
        return false;
    }
    
    //attach the shader
    glAttachShader(mProgramID , fragmentShader);
    
    //Link the program
    glLinkProgram(mProgramID);
    
    GLint programSucces = GL_TRUE;
    
    glGetProgramiv(mProgramID, GL_LINK_STATUS,&programSucces);
    
    if(programSucces != GL_TRUE)
    {
        printf("Error Linking the program %d \n ", mProgramID);
        printProgramLog(mProgramID);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(mProgramID);
        mProgramID = 0;
        return false;
    }
    //clean up the already linked shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    mVertexPosLocation = glGetAttribLocation(mProgramID, "LVertexPos");
    if( mVertexPosLocation == -1) {
        
        printf("LVertexPos is not a valid glsl program variable\n");
        return false;
    }
    
    mColorLocation = glGetAttribLocation(mProgramID, "LColor");
    if(mColorLocation == -1)  {
        printf("LColor is not a valid glsl program variable\n");
        return false;
    }
    
    mProjectionMatrixLocation = glGetUniformLocation(mProgramID, "LProjectionMatrix");
    if(mProjectionMatrixLocation == -1)  {
        printf("LProjectionMatrix is not a valid glsl program variable\n");
        return false;
    }
    
    mModelViewMatrixLocation = glGetUniformLocation(mProgramID, "LModelViewMatrix");
    if(mModelViewMatrixLocation == -1)  {
        printf("LModelViewMatrix is not a valid glsl program variable\n");
        return false;
    }
    
    
    return true;

    
}


void LTexturedRectangle::setVertexPointer(GLsizei stride , const GLvoid * data)
{
    glVertexAttribPointer(mVertexPosLocation, 2,GL_FLOAT,GL_FALSE, stride, data);
    
}

void LTexturedRectangle::setTextCoordPointer(GLsizei stride , const GLvoid * data)
{
    glVertexAttribPointer(mTexCoordLocation, 2, GL_FLOAT, GL_FALSE, stride, data);
}

void LTexturedRectangle::setColorPointer(GLsizei stride, const GLvoid *data)
{
    glVertexAttribPointer(mColorLocation, 4, GL_FLOAT,GL_FALSE, stride , data );
}

void LTexturedRectangle::enableDataPointers()
{
    glEnableVertexAttribArray(mVertexPosLocation);
    glEnableVertexAttribArray(mColorLocation);
}


void LTexturedRectangle::disableDataPointers()
{
    glDisableVertexAttribArray(mVertexPosLocation);
    glDisableVertexAttribArray(mColorLocation);
}

void LTexturedRectangle::enableVertexPointer()
{
    glEnableVertexAttribArray(mVertexPosLocation);
}

void LTexturedRectangle::disableVertexPointer()
{
    glDisableVertexAttribArray(mVertexPosLocation);
}

void LTexturedRectangle::enableTexCoorPointer()
{
    glEnableVertexAttribArray(mTexCoordLocation);
}

void LTexturedRectangle::disableTexCoorPointer(){
    glDisableVertexAttribArray(mTexCoordLocation);
}

void LTexturedRectangle::updateModelView(glm::mat4 matrix)
{
    glUniformMatrix4fv(mModelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void LTexturedRectangle::updateProjection(glm::mat4 matrix)
{
    glUniformMatrix4fv(mProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

/*
void LTexturedRectangle::setModelViewMatrix(glm::mat4 matrix)
{
    mModelViewMatrix = matrix;
}

void LTexturedRectangle::setProjectionMatrix(glm::mat4 matrix )
{
    mProjectionMatrix= matrix;
}

void LTexturedRectangle::leftMutiModelView(glm::mat4 matrix)
{
    mModelViewMatrix = matrix * mModelViewMatrix;
}

void LTexturedRectangle::leftMultiProjection(glm::mat4 matrix)
{
    mProjectionMatrix = matrix* mProjectionMatrix;
}
*/


