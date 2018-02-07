//
//  Graph.h
//  Tomb Raider
//
//  Created by Roberto Ockerse on 21/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#ifndef Graph_h
#define Graph_h

#include "Vertex.h"
#include <vector>

// a graph that will be used to move trhough the dungeon and render the map

template <class Elem>
class Graph: public Vertex
{
public:
    
    
    //constructor that need the max size of teh graph
    Graph( int size);
    ~Graph()
    {
        delete [] elementList;
        
        delete[] edges;
    }
    
    //get tha value of teh curren item pointing at
    bool getValue(Elem &item);
    //get the total size of the list
    int getSize();
    //get the current position in the graph
    int getPos();
    //set the edges connected to the vertice, a vertice can have a maximum of 4 edges (TOP,BOTTOM,LEFT,RIGHT)
    bool setEdges(int topValue = -1, int bottomValue = -1, int leftValue = -1, int rightValue = -1);
    //set the eleme to the curren position on the graph
    bool setElem(Elem&);
    //move to a given vertice
    bool movePos(int pos);
    //move to the bottom edge
    bool moveBottom();
    //move to the top edge
    bool moveTop();
    //move to the right edge
    bool moveRight();
    //move to the left edge
    bool moveLeft();
    
    //check what edges currently exist on the vertice
    void edgesLocations(int pos, bool &top, bool &bottom, bool &left, bool &right );
    //returns what location a single edge is in reference to a vertice
    int edgeLocation(int pos, int posNext);
    
    //returns the number of edges a vertive has
    int numberOfEdges(int pos);
    //returns teh first edge of a vertice
    int first(int pos);
    //returns the last edge of a vertice
    int last(int pos);
    //returns the next edge of a vertice
    int next(int pos, int posNext);
    

   //get the mark of a vertice
    int getMark(int pos);
    //set the mark on a vertice
    bool setMark( int pos, int mark);
    //reset the marks on all vertices
    void resetMarks();
    
    //this functions chech of there exist an edge on a vertice on an especified location
    bool topIsEdge();
    bool bottomIsEdge();
    bool leftIsEdge();
    bool rightIsEdge();
private:
    //the max size of the graph
    int maxSize;
    //current position
    int fence;
    
    //this will store a list the size of teh groahs this will be used to check if a vertice has been visitied or not
    int *marks;
    //the types of marks we will use
    enum MARK { UNVISITED = 0, VISITED = 1};
    //this will store the item on the list
    Elem* elementList;
    //this will store a vertice node each vertice node will store the address of another vertice withing this array
    Vertex* vertices;
    
    //initilize the graph
    void initialize( int size)
    {
    
        maxSize = size;
        fence = 0;
        //create 3 arrays all the size of the maxSize to store the the vertices information
        elementList = new Elem[maxSize];
        
        vertices = new Vertex[maxSize];
        
        marks = new int[maxSize];
        //set all marks to unvisited
        for(int i = 0; i < maxSize; i++)
        {
            marks[i]= UNVISITED;
        }
        
    }
    
};

#endif /* Graph_h */

//returns the number of edges a vertice has
template<class Elem>
int Graph<Elem>::numberOfEdges(int pos)
{
    int n;
    if(bottomIsEdge()) n++;
    
    if(topIsEdge()) n++;
    
    if(leftIsEdge()) n++;
    
    if(rightIsEdge()) n++;
    
    return n;
}
//initlized the graph
template <class Elem>
Graph<Elem>::Graph(int size)
{
    initialize(size);
}

//get the size of the graph
template<class Elem>
int  Graph<Elem>::getSize() 
{
    return maxSize;
}


//move to the bottom edge
template <class Elem>
bool Graph<Elem>::moveBottom() {
    
    if(vertices[fence].edges[BOTTOM]== -1) return false;
    
    else fence = vertices[fence].edges[BOTTOM];
    
    return true;

}

//move to the top edge
template <class Elem>
bool Graph<Elem>::moveTop() {
    
    if(vertices[fence].edges[TOP] == -1) return false;
    
    else fence = vertices[fence].edges[TOP];

    return  true;
}
//move to the left edge
template <class Elem>
bool Graph<Elem>::moveLeft() {
    
    if(vertices[fence].edges[LEFT] == -1) return false;
    
    else fence = vertices[fence].edges[LEFT];
    
    return true;
    
}
//move to the right edge
template <class Elem>
bool Graph<Elem>::moveRight() {
    
    if(vertices[fence].edges[RIGHT] == -1) return false;
    
    else fence = vertices[fence].edges[RIGHT];
    return true;
}

//move to a given position in the graph
template<class Elem >
bool Graph<Elem>::movePos(int pos)
{
    if(pos >=maxSize) return false;
    
    else fence = pos;
    return  true;
}

//set the value on the curren position
template<class Elem>
bool Graph<Elem>::setElem( Elem& elementValue)
{

    elementList[fence] = elementValue;

    return true;
}

//get the value on the current position
template<class Elem>
bool Graph<Elem>::getValue(Elem& item)
{
    if(elementList[fence] == nullptr) return false;
    item = elementList[fence];
    
    return true;
    
}
//set the edges on the current vertice
template <class Elem >
bool Graph<Elem>::setEdges(int topValue, int bottomValue, int leftValue, int rightvalue)
{
    if(elementList[fence] == nullptr) return false;
    
    vertices[fence].edges[TOP] = topValue;
    vertices[fence].edges[BOTTOM] = bottomValue;
    vertices[fence].edges[LEFT] = leftValue;
    vertices[fence].edges[RIGHT] = rightvalue;
    
    return true;
    
}

//check if the there exist a top edge
template <class Elem>
bool Graph<Elem>::topIsEdge()
{
    if(vertices[fence].edges[TOP] == -1 ) return false;
    
    else return true;
}
//check if the there exist a bottom edge
template <class Elem>
bool Graph<Elem>::bottomIsEdge()
{
    if(vertices[fence].edges[BOTTOM] == -1 ) return false;
    
    else return true;
}//check if the there exist a left edge
template <class Elem>
bool Graph<Elem>::leftIsEdge()
{
    if(vertices[fence].edges[LEFT]== -1 ) return false;
    
    else return true;
}
//check if the there exist a right edge
template <class Elem>
bool Graph<Elem>::rightIsEdge()
{
    if(vertices[fence].edges[RIGHT] == -1 ) return false;
    
    else return true;
}

//get the curren position on the graph
template<class Elem>
int Graph<Elem>::getPos()
{
    return fence;
}


//move to the next edge in a vertice this will return the next edge after the given edges is found
template<class Elem>
int Graph<Elem>::next(int pos, int posNext)
{
    if(pos > maxSize || posNext > maxSize ) return -1;
    int result;
    
    for(result = 0; result < 3; result++)
    {
        if( vertices[pos].edges[result] == posNext) break;

    }
    
    for(result++; result <= 3; result++)
    {
        if( vertices[pos].edges[result] != -1) break;
        
    }
    if(result >3) result = -1;
    
    else result = vertices[pos].edges[result];
    
    
    return result;
}
//return the first edge of a vertice
template<class Elem>
int Graph<Elem>::first(int pos)
{
    if(pos > maxSize) return -1;
    

    
    int result;
    int e;
    for(e = 0; e < 3 ; e++)
    {
        if( vertices[pos].edges[e] != -1) break;
    }
    result = vertices[pos].edges[e];
    return result;
}
//set the mark on a vertice
template<class Elem>
bool Graph<Elem>::setMark(int pos, int mark)
{
    if(mark >VISITED) return false;
    if(pos > maxSize) return false;
    
    marks[pos] = mark;
    
    return true;
}
//get the mark on a vertice
template<class Elem>
int Graph<Elem>::getMark(int pos)
{
    if(pos > maxSize) return -1;
    
    return marks[pos];
}
//reset all the marks in the graph
template <class Elem>
void Graph<Elem>::resetMarks()
{
    for(int i = 0; i < maxSize ; i++)
    {
        marks[i]= UNVISITED;
    }
}
//check what edges a given position has
template <class Elem>
void Graph<Elem>::edgesLocations(int pos,bool &top, bool &bottom, bool &left, bool &right )
{
    if(vertices[pos].edges[TOP] == -1) top = false;
    else top = true;
        
    if(vertices[pos].edges[BOTTOM] == -1) bottom = false;
    else bottom = true;
    
    if(vertices[pos].edges[LEFT] == -1) left = false;
    else left = true;
    
    if(vertices[pos].edges[RIGHT] == -1) right = false;
    else right = true;
    
}
//return the edge position on a given vertice
template <class Elem>
int Graph<Elem>::edgeLocation(int pos, int edge)
{
    int result = -1;
    if(vertices[pos].edges[TOP] == edge) result = TOP ;
    else if(vertices[pos].edges[BOTTOM] == edge) result= BOTTOM;
    else if(vertices[pos].edges[LEFT] == edge) result = LEFT;
    else if(vertices[pos].edges[RIGHT] == edge) result = RIGHT;
    
    return result;
}
//returns the last edge on a vertic
template <class Elem>
int Graph<Elem>::last(int pos)
{
    if(pos> maxSize) return -1;
    int i;
    for(i = 3 ; i >= 0 ; i-- )
    {
        if(vertices[pos].edges[i] != -1) break;
    }
    
    return vertices[pos].edges[i];
}
