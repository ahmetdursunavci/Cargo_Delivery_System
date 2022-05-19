#ifndef ASSIGNMENT3_STACK_H
#define ASSIGNMENT3_STACK_H
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
class Stack {
	public:
	Stack() {}
	~Stack() {}
	bool isEmpty() const {
	    if(_head==NULL) {
            return true;
	    }
        return false;
	}
	int size() const {
	    ListNode *temp = _head;
	    int size=0;
	    while (temp!=NULL) {
	        size++;
	        temp=temp->next;
	    }
        return size;
	}
	
	//Push: Place item on top of the stack
	void push(const T& newItem) {
	    ListNode *package = new ListNode();
        package ->item=newItem;
        package ->next=NULL;
	    if(_head==NULL) {
                _head=package ;
	    }
	    else {
            package ->next=_head;
	        _head=package ;
	    }
	}
	//Top: Take a look at the topmost item without removing it
	void getTop(T& stackTop) const {
	        if(isEmpty()) {
                throw string("Stack is empty");
	        }
            else{
                stackTop = _head->item;
            }
	}

	//Pop: Remove item from the top of the stack
	void pop() {
	    ListNode *temp = _head;
	    if(_head->next==NULL) {
	        free(temp);
	        _head=NULL;
	    }
	    else {
	        _head=_head->next;
	        free(temp);
	    }
	}
	private:
	struct ListNode {
		T item;
		ListNode* next;
		};
	ListNode* _head=NULL;
	int _size;
};


#endif