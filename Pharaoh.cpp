//
//  Pharaoh.cpp
//  Dungeon_Game
//
//  Created by Roberto Ockerse on 16/03/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#include "Pharaoh.hpp"
//pharaoh contructor intitiate the variables withing the class and the character constructor
Pharaoh::Pharaoh()
{
    Character();
    shoot = false;
}
//pharaos movement which the pharao dosent move he just stays in place
void Pharaoh::move(double frameTimeDelta){
    
}
//reset the pharao timer and is variable that check if is time to shoot
void Pharaoh::resetTimer()
{
    Character::resetTimer();
    shoot = false;
}

//check if it is time to shoot
bool Pharaoh::timeToShoot(){
    //if shoot is false we check if the timer has run out
    if(!shoot)
    {
        std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();
        
        std::chrono::duration<double> timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(time - start);
        if(timeSpan.count() >= timer )
        {
            //if the tiemr has run out make shoot true
            shoot = true;
        }
        

    }
    
    
    return shoot;
}
