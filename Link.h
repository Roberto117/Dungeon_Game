//
//  Link.h
//  Dungeon_Game
//
//  Created by Roberto Ockerse on 08/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#ifndef Link_h
#define Link_h
//a link node that the list will use for sotring and item it contains a next value and a previous value to move thorough the list and item to be store in each node
template<class Elem>

class Link
{
public:
    

    
    Link(const Elem &elemValue, Link* nextValue = nullptr, Link *prevValue = nullptr)
    {
        element = elemValue;
        
        next = nextValue;
        
        prev = prevValue;
    }
    
    Link(Link* nextValue = nullptr, Link *prevValue = nullptr)
    {
        next = nextValue;
        prev = prevValue;
    }

    
    Link *next;
    Link *prev;
    
    Elem element;
    
};

#endif /* Link_h */
