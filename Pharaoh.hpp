//
//  Pharaoh.hpp
//  Tomb Raider
//
//  Created by Roberto Ockerse on 16/03/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#ifndef Pharaoh_hpp
#define Pharaoh_hpp
#include "Character.hpp"

class Pharaoh :public Character
{
public:
    
    Pharaoh();
    //override objcet funtion move
	void move(double) override;
    
    //check if is time to shoot
    bool timeToShoot();
    //reset the timer
    void resetTimer();
    
private:
    //boolean variable that checks if is time to shoot
    bool shoot;
};
#endif /* Pharaoh_hpp */
