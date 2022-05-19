#ifndef ASSIGNMENT3_QUEUE_H
#define ASSIGNMENT3_QUEUE_H
/*Function templates are special functions that can operate
with generic types. This allows us to create a function 
template whose functionality can be adapted to more than 
one type or class without repeating the entire code for each type.*/

/*To use this function template we use the following format for the function call:

function_name <type> (parameters);
*/
#include <iostream>
using namespace std;

template <class T>
class Queue {
	public:
	Queue(){}
	~Queue(){}
	bool isEmpty() const {
	    if(_headQ==NULL) {
            return true;
	    }
        return false;
	}
	int size() const {
	    int size = 0;
	    QueueNode *temp=_headQ;
	    while (temp!=NULL) {
	        size++;
	        temp=temp->next;
	    }
        return size;
	}
	//Enqueue: Items are added to the back of the queue
	void enqueue(const T& newItem){
	    QueueNode *truck = new QueueNode();
	    truck->item=newItem;
	    truck->next=NULL;
	    if(_headQ==NULL) {
	        _headQ=truck;
	        _lastNode=truck;
	    }
	    else {
	        _lastNode->next=truck;
	        _lastNode=truck;
	    }
	}
	//Dequeue: Items are removed from the front of the queue
	void dequeue() {
	    QueueNode *truck=_headQ;
	    if(_headQ->next==NULL) {
	        free(truck);
	        _headQ=NULL;
	        _lastNode=truck;
	    }
	    else {
	        _headQ=_headQ->next;
	        free(truck);
	    }
	}
	//Get Front: Take a look at the first item
	void getFront(T& queueTop) const {

            if(isEmpty()) {
                throw string("Queue is empty");
            }
            else {
                queueTop = _headQ->item;
            } 
   

	}
	private:
	struct QueueNode {
		T item;
		QueueNode *next;
		};
	int _size;
	/* to avoid the traversal to the last node, 
	 an additional pointer to the last node is defined*/
	QueueNode *_lastNode=NULL;
	QueueNode *_headQ=NULL;
};

#endif