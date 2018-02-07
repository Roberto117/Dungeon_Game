//
//  Bullet.hpp
//  Dungeon_Game
//
//  Created by Roberto Ockerse on 07/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include "LOpenGL.h"
#include "Object.hpp"
// a bullet class that is used to store a buller objects data in inherits from the Object class
class Bullet: public Object
{
public:
    Bullet();
    //overt ride the move function in the object class
    void move(double) override;

    
private:
    
};

#endif /* Bullet_hpp */
