//
//  LShaderProgram.hpp
//  Dungeon_Game
//
//  Created by Roberto Ockerse on 28/01/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#ifndef LShaderProgram_hpp
#define LShaderProgram_hpp

#include "LOpenGL.h"
#include <string>

class LShaderProgram
{
public:
    
    //constructor for the class, initializes the variables
    LShaderProgram();
    
    //destructor to free the shader program from the GPU
    virtual ~LShaderProgram();
    
    //we Load the shader program here any clas that inherits from LShaderProgram must override this command if program was created the programId will be saved to mProgramID if not the funtion will return false
    virtual bool loadProgram( std::string glvsPath, std::string glfsPath) = 0;
    
    
    //function that frees the shader program from the GPU;
    virtual void freeprogram();
    
    //our shader program gets bind the current shaderprogram
    bool bind();
    //binds a null shader program
    void unbind();
    
    //get the program ID of this shader progra,m
    GLuint getProgramID();
    
    
protected:
    
    
    //prints the prorgram log reports an Error if the program is not a shader program
    void printProgramLog(GLuint program);
    
    void printShaderLog(GLuint shader);
    //prints the sahder log reports an error if the program is not a shader
    
    
    //loads the shader from the file dicated from the path if the file is found and succesfully compiled it return the Program ID which is the location of the shader program in the GPU otherwise will return an error the console
    GLuint loadShaderFromFile(std::string path, GLenum shaderType);
    
    
    //Program Id
    GLuint mProgramID;
    
    
    
    
};

#endif /* LShaderProgram_hpp */
