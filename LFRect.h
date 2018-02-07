//
//  LFRect.h
//  Tomb Raider
//
//  Created by Roberto Ockerse on 09/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#ifndef LFRect_h
#define LFRect_h

#include "LVertexPos.h"
//this struc is used for rendering a rectangle
struct LFRect {
    
    LVertexPos x;
    LVertexPos y;
    LVertexPos w;
    LVertexPos h;
};

#endif /* LFRect_h */
