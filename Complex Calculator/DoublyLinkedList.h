#include "Node.h"
template <class T>
class DoublyLinkedList {
protected:
	struct Node<T> * head;//Pointer to the first node of a doubly linked list
	struct Node<T> * tail;//Pointer to the last node of a doubly linked list
	int size;//Size of the DoublyLinkedList
public:
	DoublyLinkedList();
	void addFront(T data);//Add node to the front of the DoublyLinkedList
	void popFront();//Remove node at the beginning of the DoublyLinkedList
	void addBack(T data);//Add node to the end of the DoublyLinkedList
	void popBack();//Remove node at the end of the DoublyLinkedList
	void addNode(T data, Node<T> * iter);//Add node in general
	void deleteNode(T d, Node<T> * iter);//Delete node in general
	Node<T> findNode(T data);//Find the given node and return a pointer to that node; returns false if node isn't present
	int getSize() const;//Return size of the DoublyLinkedList
	bool isEmpty() const;//Return true if the DoublyLinkedList is empty otherwise returns false
	void displayList();//Display the data of the DoublyLinkedList
};

template<class T>
inline DoublyLinkedList<T>::DoublyLinkedList() {
	size = 0;
	head = NULL;
	tail = NULL;
}

template<class T>
inline Node<T> DoublyLinkedList<T>::findNode(T data) {
	//Catch to see if there are no nodes to review
	if (head == NULL) {
		Node<T> n;
		n.data = NULL;
		return n;
	}
	//Else traverse through the DLL and compare the given data to the current node's data
	else {
		Node<T> * temp;
		temp = head;
		while (temp != NULL) {
			if (temp->data == data) {
				cout << "Data Found" << endl;
				Node<T> retrieve;
				retrieve.data = temp->data;
				retrieve.next = temp->next;
				retrieve.prev = temp->prev;
				cout << "Data of Node Retrieved: " << retrieve.data << endl;
				return retrieve;
			}
			if (temp->next != NULL) {
				temp = temp->next;
			}
			else {
				break;
			}
		}
	}
}

template<class T>
inline int DoublyLinkedList<T>::getSize() const {
	return size;
}

template<class T>
inline bool DoublyLinkedList<T>::isEmpty() const {
	if (size == 0) {
		return true;
	}
	else {
		return false;
	}
}

template<class T>
inline void DoublyLinkedList<T>::addFront(T data) {
	Node<T> * newNode = new Node<T>;
	newNode->data = data;
	newNode->next = head;
	newNode->prev = NULL;

	if (head == NULL) {
		head = newNode;
		tail = newNode;
	}
	else {
		head->prev = newNode;
		newNode->next = head;
		head = newNode;
	}
	size++;
}


template<class T>
inline void DoublyLinkedList<T>::addBack(T data) {
	Node<T> * newNode = new Node<T>;
	newNode->data = data;
	newNode->next = NULL;
	//If the head is null then both the tail and the head should be set to the newNode
	if (head == NULL) {
		newNode->prev = NULL;
		head = newNode;
		tail = newNode;
	}
	else {
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}
	size++;
}


template<class T>
inline void DoublyLinkedList<T>::popFront() {
	//Catch if there is nothing to pop
	if (head == NULL || size == 0) {
		cout << "Attempted to popFront of empty List" << endl;
		return;
	}
	else {
		T data = head->data;
		Node<T> * temp = head->next;
		if (temp != NULL) {
			temp->prev = NULL;
		}
		head->next = NULL;
		delete head;
		head = temp;
		size--;
	}
}


template<class T>
inline void DoublyLinkedList<T>::popBack() {
	//Catch if there is nothing to pop
	if (tail == nullptr || size == 0) {
		cout << "Attempted to popBack of empty List" << endl;
		return;
	}
	else if(size > 1){
		T data = tail->data;
		Node<T> * temp = tail->prev;
		if (temp != NULL) {
			temp->next = NULL;
		}
		tail->prev = NULL;
		delete tail;
		tail = temp;
		size--;
	}
	//For when the size is not greater than one
	//sets it to nullptr therefore there are no issues
	//when determining if there are values
	else {
		tail = nullptr;
		head = nullptr;
		size--;
	}
}

template<class T>
inline void DoublyLinkedList<T>::addNode(T data, Node<T>* iter) {
	Node<T> * newNode = new Node<T>;	
	newNode->data = data;
	newNode->next = iter->next;
	iter->next = newNode;
	newNode->prev = iter;

	if (newNode->next != NULL) {
		newNode->next->prev = newNode;
	}
}

template<class T>
inline void DoublyLinkedList<T>::displayList(){
	//To avoid compiler error from attempting to print empty list
	if (size == 0) {
		cout << "List is empty" << endl;
		return;
	}
	else {
		Node<T> * walker;
		walker = head;
		while (walker != NULL) {
			cout << walker->data << " ";
			walker = walker->next;
		}
		cout << endl;
	}
}
