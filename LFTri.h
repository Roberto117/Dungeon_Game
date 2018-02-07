//
//  LFTri.h
//  Tomb Raider
//
//  Created by Roberto Ockerse on 09/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#ifndef LFTri_h
#define LFTri_h

#include "LVertexPos.h"
//this struc is used to render a triangles
struct LFTri
{
    LVertexPos t;
    
    LVertexPos l;
    
    LVertexPos r;
};


#endif /* LFTri_h */
