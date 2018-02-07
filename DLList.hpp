//
//  DLList.h
//  Tomb Raider
//
//  Created by Roberto Ockerse on 09/02/2017.
//  Copyright © 2017 Roberto Ockerse. All rights reserved.
//

#ifndef DLList_h
#define DLList_h

#include "Link.h"
//double linked List that I used to store all object sprites
template <class Elem>

class DLList : public Link <Elem>
{
public:
    
    explicit DLList();
    //insert a new item into the list the item will be inserte at the fence next pointer
    void insert(const Elem&);
    //remove the fence next item
    bool remove(Elem &);
    //set the postion on the list
    bool setPos(int);
    //get the objecet value
    bool getValue(Elem &) const;
    //append an item to the end of the list
    void append(const Elem &);
    //set the postion to the start of the list
    void setStart();
    //set the position to the end of the list
    void setEnd();
    //move to the previous item
    bool prev();
    //move to the next item
    bool next();
   // void print();
    
    //get the right lenght
    int rightLenght();
    //get the left lenght
    int leftLenght();
    //get the total lengh of the list
    int totalLenght();
    
    
    
    
private:
    //pointers to the place on the list
    Link <Elem>* head;
    Link <Elem>* tail;
    Link <Elem>* fence;
    
    //this will store the size of the list
    int leftCnt;
    int rightCnt;
    
    //List initiliaziation
    void initialize()
    {
        fence = tail = head = new Link<Elem>;
        leftCnt = rightCnt = 0;
    }
    
    //remove all the items from the list
    void removeAll()
    {
        while (fence != tail )
        {
            fence = head;
            
            head = head->next;
            
            delete fence;
        }
    }
    
    
};




#endif /* DLList_h */












