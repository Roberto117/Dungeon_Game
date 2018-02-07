//
//  LShaderProgram.cpp
//  Dungeon_Game
//
//  Created by Roberto Ockerse on 28/01/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#include "LShaderProgram.hpp"
#include <fstream>

LShaderProgram::LShaderProgram()
{
    //initiliaze the Program ID
    mProgramID = NULL;
    
    
}

LShaderProgram::~LShaderProgram()
{
    //frees the program from the GPU
    freeprogram();
    
}

void LShaderProgram::freeprogram(){
    
    //frees the program from the GPU
    glDeleteProgram(mProgramID);
}

bool LShaderProgram::bind(){
    //bind this Objects program to the curremy context
    glUseProgram(mProgramID);
    
    
    //check if there was any erros binding the program
    GLenum error = glGetError();
    if(error != GL_NO_ERROR)
    {
        //tell the user there was an error
        printf("Error binding shader %s \n",gluErrorString(error));
        //get the and reason for error,print to the console and exit the function
        printProgramLog(mProgramID);
        return false;
        
    }
    
    //return true if the program bind to the context correctly
    return true;
}


void LShaderProgram::unbind()
{
    //bind a null program to the context this will unbind the current program from the context.
    glUseProgram(NULL);
}

GLuint LShaderProgram::getProgramID()
{
    // return this objects Program ID
    return mProgramID;
}

void LShaderProgram::printProgramLog(GLuint program)
{
    //make sure the program exist
    if(glIsProgram(program))
    {
        //initialize the program log lenght variables
        int infoLengh = 0;
        int maxLenght = 0;
        //get the length of the info log
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLenght);
        
        //allocate enough storage to output the log
        char* infolog = new char[maxLenght];
        
        //get the info log
        glGetProgramInfoLog(program,maxLenght,&infoLengh, infolog);
        if(infoLengh > 0 )
        {
            printf("%s\n", infolog);
            
        }
        
        //detele the string
        delete [] infolog;
    }
    
    else
    {
        printf("Name %d is not a program\n", program);
    }
}

void  LShaderProgram::printShaderLog(GLuint shader)
{
    if(glIsShader(shader))
    {
        //initiliaze the shader log variables
        int infoLogLenght = 0;
        int maxLenght = 0;
        
        //get the lenght of the info log
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLenght);
        
        //allocate enough storage to output the log
        char * infolog = new char [maxLenght];
        //get the info log
        glGetProgramInfoLog(shader, maxLenght, &infoLogLenght, infolog);
        if(infoLogLenght > 0)
        {
            printf("%s\n", infolog);
            
        }
        
        
        delete [] infolog;
    }
    
    else
    {
        printf("Name %d is not a shader \n", shader);
    }
    
    
}

GLuint LShaderProgram::loadShaderFromFile(std::string path , GLenum shadertype)
{
    GLuint shaderID = 0;
    std::string shaderString;
    std::ifstream sourcefile (path.c_str());
    
    //source file loaded
    if(sourcefile)
    {
        //get shader source code
        shaderString.assign((std::istreambuf_iterator<char>(sourcefile)), std::istreambuf_iterator<char>());
        
        //Create shadeeID
        shaderID= glCreateShader(shadertype);
        //set the shader source
        const GLchar* shaderSource = shaderString.c_str();
        glShaderSource(shaderID,1,(const GLchar**)&shaderSource, NULL);
        
        //compile the shader
        glCompileShader(shaderID);
        
        
        //check sahder for errors
        GLint shaderCompiled = GL_FALSE;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompiled);
        if(shaderCompiled != GL_TRUE)
        {
            printf( "Unable to compile shader %d!\n\nSource:\n%s\n", shaderID, shaderSource );
            printShaderLog(shaderID);
            glDeleteShader(shaderID);
            shaderID = 0;
        }
        
    }
    else
    {
         printf( "Unable to open file %s\n", path.c_str() );
        
    }
    
    return shaderID;
}


