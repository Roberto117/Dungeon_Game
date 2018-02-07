//
//  Vertice.h
// Dungeon_Game
//
//  Created by Roberto Ockerse on 21/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#ifndef Vertice_h
#define Vertice_h

//this vertice class will be used by the Graph class to move thorugh the edges and vertices
class Vertex {
public:
    //the edges of the single vertice it can have a maxium of 4 edges (TOP,BOTTOM,LEFT,RIGHT) <- in that exact order
    int edges[4];
    

    //enum for easier understading od edge postion
    enum {TOP = 0, BOTTOM, LEFT, RIGHT};
    //the ID of the vertice which will be used for positioning
    int ID;
    
    //creating a vertice and its edges(the edges can be set later)
    Vertex(int topValue = -1, int bottomValue = -1, int leftValue = -1, int rightValue = -1)
    {
        edges[BOTTOM]= bottomValue;
        edges[TOP] = topValue;
        edges[LEFT] = leftValue;
        edges[RIGHT] = rightValue;
        
    }    
    
    
};

#endif /* Vertice_h */

