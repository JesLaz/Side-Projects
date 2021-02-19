#pragma once
//#include "DoublyLinkedList.h"
template <class T>
class StackDoublyLinkedList : public DoublyLinkedList<T> {
public:
	StackDoublyLinkedList();//default constructor
	void displayStack();//display a stack
	T getTop() const;//return element at the top of a stack
};

template<class T>
inline StackDoublyLinkedList<T>::StackDoublyLinkedList() {
	DoublyLinkedList<T>::DoublyLinkedList();
}

template<class T>
inline void StackDoublyLinkedList<T>::displayStack(){
	DoublyLinkedList<T>::displayList();
}

template<class T>
inline T StackDoublyLinkedList<T>::getTop() const {
	//Check for if tail if NULL
	return DoublyLinkedList<T>::tail->data;
}
