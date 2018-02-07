//
//  LTexturedCircle.cpp
// Dungeon_Game
//
//  Created by Roberto Ockerse on 03/03/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#include "LTexturedCircle.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"



LTexturedCircle::LTexturedCircle()
{
    mVertexPosLocation= mTexCoordLocation = mColorLocation =  mModelViewMatrixLocation = mResolutionLocation = NULL;
}

bool LTexturedCircle::loadProgram(std::string glvsPath, std::string glfsPath)
{
    mProgramID = glCreateProgram();
    
    GLuint vertexShader = loadShaderFromFile(glvsPath, GL_VERTEX_SHADER);
    
    if(vertexShader == 0 )
    {
        glDeleteProgram(mProgramID);
        mProgramID = 0;
        return false;
    }
    
    glAttachShader(mProgramID, vertexShader);
    
    GLuint fragmentShader = loadShaderFromFile(glfsPath, GL_FRAGMENT_SHADER);
    
    if(fragmentShader == 0)
    {
        glDeleteShader(vertexShader);
        glDeleteProgram(mProgramID);
        return false;
    }
    
    glAttachShader(mProgramID, fragmentShader);
    
    glLinkProgram(mProgramID);
    
    GLint programSucces = GL_TRUE;
    
    glGetProgramiv(mProgramID, GL_LINK_STATUS, &programSucces);
    
    if(programSucces != GL_TRUE)
    {
        printf("Erros Linking the program %d \n" , mProgramID);
        printProgramLog(mProgramID);
        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);
        glDeleteProgram(mProgramID);
        mProgramID = 0;
        return false;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    mVertexPosLocation = glGetAttribLocation(mProgramID , "LVertexPos");
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
    

    
    mResolutionLocation = glGetUniformLocation(mProgramID , "LResolution");
    if( mResolutionLocation == -1) {
        
    
        printf("LResolution is not a valid glsl program variable\n");
        return false;
    }
    mCenterLocation = glGetUniformLocation(mProgramID, "LCenter");
    if( mCenterLocation == -1) {
        
        
        printf("LCenter is not a valid glsl program variable\n");
        return false;
    }
    return true;
}

void LTexturedCircle::setVertexPointer(GLsizei stride , const GLvoid * data)
{
    glVertexAttribPointer(mVertexPosLocation, 2,GL_FLOAT,GL_FALSE, stride, data);
    
}

void LTexturedCircle::setTextCoordPointer(GLsizei stride , const GLvoid * data)
{
    glVertexAttribPointer(mTexCoordLocation, 2, GL_FLOAT, GL_FALSE, stride, data);
}

void LTexturedCircle::setColorPointer(GLsizei stride, const GLvoid *data)
{
    glVertexAttribPointer(mColorLocation, 4, GL_FLOAT,GL_FALSE, stride , data );
}


void LTexturedCircle::setResolution(GLfloat width, GLfloat height)
{


    glUniform2f(mResolutionLocation, width, height);
    
    
    
}

void LTexturedCircle::enableDataPointers()
{
    glEnableVertexAttribArray(mVertexPosLocation);
    glEnableVertexAttribArray(mColorLocation);

}


void LTexturedCircle::disableDataPointers()
{
    glDisableVertexAttribArray(mVertexPosLocation);
    glDisableVertexAttribArray(mColorLocation);

}

void LTexturedCircle::enableVertexPointers()
{
    glEnableVertexAttribArray(mVertexPosLocation);
}

void LTexturedCircle::disableVertexPointers()
{
    glDisableVertexAttribArray(mVertexPosLocation);
}

void LTexturedCircle::enableTextCoorPonters()
{
    glEnableVertexAttribArray(mTexCoordLocation);
}

void LTexturedCircle::disableTextCoorPointer(){
    glDisableVertexAttribArray(mTexCoordLocation);
}

void LTexturedCircle::updateModelView(glm::mat4 matrix)
{
    glUniformMatrix4fv(mModelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void LTexturedCircle::updateProjectionMatrix(glm::mat4 matrix)
{
    glUniformMatrix4fv(mProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void LTexturedCircle::updateCenterPoint(GLfloat x, GLfloat y)
{
    glUniform2f(mCenterLocation, x, y);
}
















