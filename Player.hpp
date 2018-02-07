//
//  Player.hpp
//  Tomb Raider
//
//  Created by Roberto Ockerse on 16/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "Character.hpp"
//this is the player class that the user will be able to controll it inherists from the character class
class Player: public Character
{
public:
    //variables that will be used for movement
    bool moveLeft, moveRight, moveUp, moveDown,pushedDown,pushedRight, pushed;

    
    Player();
    
    //set the ammo on the player
    void setAmmo(int);
    //override the move function in the object class
	void move(double) override;
    
    //activaes teh afffect of being pushed on the player class
    void gotPushed(int , int);
    
    //get the state of the different variables in teh class
    int getAmmo();
    void addAmmo(int);
    bool isImmune();

	void setImmune(bool);
    
    void copyMoves(Player &);
    
    //check if is time to remove the effect
    void removeEffect();
private:
    /*variables that indicate:
     -ammo the amount of ammo the player has
     -boolean value to cehck if the player is being pushed
     -ranged pushed will be how far the player has been pushed
     -speedPushed is how far the player need to be pused in order to stop and give controll once again to the player
     */
    int ammo;
	double immuneTimer;
   
    int rangePushed;
    
    int speedPushed;

	std::chrono::high_resolution_clock::time_point immuneStart;
};

#endif /* Player_hpp */
