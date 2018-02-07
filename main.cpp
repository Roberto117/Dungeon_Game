//
//  main.cpp
//  Dungeon_Game
//
//  Created by Roberto Ockerse on 28/01/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

//include the OpenGl libraries and the LUtil where the program is running at,include the glm libraries and the screen constant which contains vatriables that can be used thorugh out the program
#include "LOpenGL.h"
#include "LUtil.hpp"
#include "glm/glm.hpp"
#include "ScreenConstants.h"
#include <time.h>



std::chrono::high_resolution_clock::time_point timeNow;

std::chrono::high_resolution_clock::time_point start;

double frameTimeDelta = 0.025;



//check if the was an error while building and OpenGl window
void error_callback(int error, const char* description){
    
    printf(description, stderr);
    
}


//this is where the main loop of the program will be processed
void runMainLoop(void)
{
	timeNow = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli > timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(timeNow - start);



	
	update(frameTimeDelta);
    render();
}


int main( int argc, const char *argv[] )
{
    
    //intiliaze GLFW
    if(!glfwInit())
    {
        printf("Failed to initialize GLFW\n");
        return -1;
    }
    
    //create a window for the program
    GLFWwindow * window = nullptr;
    
    //initialize the window the FORWARD_COMPAT and OPENGL_CORE PROFILE  are needed for mac use.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //Open a window and creates its OpenGL context
    glfwSetErrorCallback(error_callback);
    
    //create teh window with the given size
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dungeon_Game", nullptr, nullptr);
    
    //check if the window has failes to build

	if(!window)
    {
        printf("Failed to open window\n", stderr);
        glfwTerminate();
        return -1;
    }
    

    // make the current context teh window we have created.
    glfwMakeContextCurrent(window);
    
    glewExperimental = true;
    
    //check if glew was able to initiliaze.
    
    if(glewInit() != GLEW_OK)
    {
        printf("failes to initialize glew\n", stderr);
        
        return -1;
    }
    
    //initialize the graphics library exit if error
    if(!initGL())
    {
        printf( "Unable to initialize graphics library!\n" );
        return 1;
    }
    
    //initilize teh shader program return if there was an error
    if(!loadGP())
    {
        printf( "Unable to load shader programs!\n" );
       
		return 1;
    }
    //initlize our media, which is the sprites and dungeon graph
    if(!loadMedia())
    {
        printf( "Unable to load media!\n" );
        return 2;
    }
  
    
    
    //set the input mode to sticky keys
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    
    //set the function that OpenGL will use to scan the keys that have been pressed
    glfwSetKeyCallback(window, handleKeys);
    
    //set the funtion taht OpenGl will use for the cursor position
    glfwSetCursorPosCallback(window, cursorPosition);
    
    //set the function that is used for handling the mouse clicking
    glfwSetMouseButtonCallback(window, mouseButtonHandler);
    
    //setting the time for OpenGL
    glfwSetTime(5.0);
    
    
    //start the main loop for the program loop will contiue while the program is not closed.
    do
    { 
		start = std::chrono::high_resolution_clock::now();
		
        //update and render the program per frame
        runMainLoop();
        //sawp the rendered matrix with the last matrix
        glfwSwapBuffers(window);
        glfwPollEvents();
  
    }
    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	
	glfwTerminate();

    return 0;
    
}
