
#ifndef List_H
#define List_H


template <class Elem> 
class List {
		//insert a new item into the list the item will be inserte at the fence next pointervoid insert(const Elem&);
public:
	//insert a new item into the list the item will be inserte at the fence next pointer
	virtual void insert(const Elem&)= 0;
	//remove the fence next item
	virtual bool remove(Elem &) = 0;
	//set the postion on the list
	virtual bool setPos(int) = 0;
	//get the objecet value
	virtual bool getValue(Elem &) const = 0;
	//append an item to the end of the list
	virtual void append(const Elem &) = 0;
	//set the postion to the start of the list
	virtual void setStart() = 0;
	//set the position to the end of the list
	virtual void setEnd()= 0;
	//move to the previous item
	virtual bool prev()= 0;
	//move to the next item
	virtual bool next()= 0;
	// void print();

	 //get the right lenght
	virtual int rightLenght()const = 0;
	//get the left lenght
	virtual int leftLenght()const = 0;
	//get the total lengh of the list
	virtual int totalLenght()const = 0;
};
#endif