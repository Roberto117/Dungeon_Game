//
//  Crate.hpp
// Dungeon_Game
//
//  Created by Roberto Ockerse on 09/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#ifndef Crate_hpp
#define Crate_hpp

#include "LOpenGL.h"
#include "Object.hpp"
//class crate that inherits from the object class
class Crate : public Object
{
public:
    Crate();
    
    virtual void move(double) override;
    
private:
    

    
};

#endif /* Crate_hpp */
