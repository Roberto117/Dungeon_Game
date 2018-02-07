//
//  Mummy.hpp
//  Dungeon_Game
//
//  Created by Roberto Ockerse on 16/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#ifndef Mummy_hpp
#define Mummy_hpp

#include "Character.hpp"
#include <chrono>

//this class is used to create and uses a mummy object it inherists from the Character class
class Mummy : public Character
{
public:
    //mummy constructor
    Mummy();
	void move(double) override;

	//sudo move function to check for imminent stopping
	bool sudoMove(double);
    //set the target the mummy will move to returns false till target is reached
    void setTarget(GLfloat, GLfloat);
    //check if is time for the mummy to move
    bool isMoving();
	
	
	bool checkIfJustStartedMoving();

	GLfloat getTargetY();
	GLfloat getTargetX();
	//get left or right direction
	bool getDirectionX();
	//get up or down direction
	bool getDirectionY();

	void copyMoves(Mummy &);
	
    
    //reset the timer for the mummy
   virtual void resetTimer();
    
private:
    
    //variable that will be used to check if the mummy is moving
    bool moving;
	bool justStartedMoving;
    

    //this will be used to know where the mummy should stop
    GLfloat targetX;
    GLfloat targetY;
    
    //this boolean values will be used to check what direction the the mummy should move
    bool down;
    bool right;
    
};

#endif /* Mummy_hpp */
