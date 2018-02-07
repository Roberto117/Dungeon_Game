//
//  Queue.h
//  Dungeon_Game
//
//  Created by Roberto Ockerse on 28/03/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#ifndef Queue_h
#define Queue_h
//a Queue List which will be used to for a breath firs search in the groah
template<class Elem>
class Queue
{
public:
    //intialization with a given max size
    Queue(int size)
    {
        maxSize = size + 1;
        
        rear = 0;
        front = 1;
        
        listArray = new Elem[size];
    }
    
    ~Queue(){ delete [] listArray; }
    
    //functions to add end remove items on the list
    bool dequeue(Elem& it);
    bool enqueue(Elem& it);
    //reset the list
    void reset();
    //get the lenght of the list
    int lenght();
private:
    /*variables used on the list
     -maxSize is the maxium amount of number allowed on the list
     -front is the current position the list
     -rear is the very back of the list
     */
    int maxSize;
    int front;
    int rear;
    
    Elem *listArray;
    
};

#endif /* Queue_h */
//returns the lenght of the list
template<class Elem>
int Queue<Elem>::lenght()
{
    return rear - (front - 1);
}

//removes an item from teh front of the list
template <class Elem>
bool Queue<Elem>::dequeue(Elem &item)
{
    if(lenght() == 0) return false;
    item = listArray[front];
    
    front++;
    
    return true;
}
//inserts an item at the back of the list
template <class Elem>
bool Queue<Elem>::enqueue(Elem& item)
{
    if(rear == maxSize) return  false;
    
    rear++;
    listArray[rear]= item;
    
    return true;

}

//reser the list to the start
template <class Elem>
void Queue<Elem>::reset()
{
    rear = 0;
    
    front = 1;
}
