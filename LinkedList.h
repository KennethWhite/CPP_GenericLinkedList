/*
Kenneth White
CSCD 305 8:00 Spring 18
Assignment 4 - Putting it all together

Shortcomings:
	None that I know of

Compilation details :
	Compile using g++ *.cpp

	I used Microsoft Visual C++ compiler via Visual Studio 2017
	I also used g++ version 7.2.0 via MinGW64
*/

#ifndef LinkedList_h
#define LinkedList_h

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

//This is a circular doubly linked list with a dummy head

template <class T>
class LinkedList{
private:
    class Node{
    public:

		//CTORs
        Node(T& data, Node* next, Node* prev){
            this->data = data;
            this->next = next;
            this->prev = prev;
        }

        Node(T& data){
            this->data = data;
            this->next = nullptr;
            this->prev = nullptr;
        }

        Node(){
            this->next = nullptr;
            this->prev = nullptr;
        }

		//Node Attributes
        T data;
        Node* next;
        Node* prev;
    };



	// LL Attributes
    Node* head;
    int size = 0;

public:
	
//Iterator


	class Iterator {
	private:
		Node* cur;
		Node* head;
	public:
		Iterator(Node* cur) {
			this->cur = cur;
			this->head = cur->prev;
		}

		~Iterator() = default;

		T& operator*() const {
			return this->cur->data;
		}

		bool operator==(const Iterator& other) const {
			return this->cur == other.cur;
		}

		bool operator !=(const Iterator& other) const {
			return this->cur != other.cur;
		}

		Iterator& operator++() {
			if (this->cur != this->head) {
				this->cur = cur->next;
			}
			return *this;
		}
	
	};

	Iterator begin() {
		return Iterator(this->head->next);
	}

	Iterator end() {
		return Iterator(this->head);
	}

	//Allocates dummy head
    LinkedList(){
        this->head = new Node(); 
        this->head->next = this->head;
        this->head->prev = this->head;
        this->size = 0;
    }

	~LinkedList() {
		if (this->head!= nullptr) {
			Node* cur = this->head->next;
			Node* prev = this->head;
			while (cur != this->head && cur != nullptr) {
				prev = cur;
				cur = cur->next;
				delete prev;
			}
			this->size = 0;
		//prevents head from being freed twice when exiting the scope of a method
			delete head;
			head = nullptr;
		}
	}
	
	//Copy CTOR
    LinkedList(const LinkedList& cpy) { 
		//Clean up any resources in the current list
		if (this->size != 0) {
			this->~LinkedList();
		}

		//create dummy
		this->head = new Node();
		this->head->next = this->head;
		this->head->prev = this->head;


		Node* cur = cpy.head->next;
		while (cur != cpy.head) {
			this->add(cur->data);
			cur = cur->next;
		}
    }

	
	//MOVE
	

	// Move CTOR
    LinkedList(LinkedList<T>&& cpy) {
		//cpy old data
		this->head = new Node();
		this->head->next = cpy.head->next;
		this->head->next->prev = this->head;
		this->head->prev = cpy.head->prev;
		this->head->prev->next = this->head;
		this->size = cpy.getSize();
		
		//return cpy to empty state
		cpy.size = 0;
		cpy.head->next = nullptr;
		cpy.head->prev = nullptr;
    }

	 //Move Assignment
	void operator=( LinkedList<T>&& original) { 
			
			//clear resources of this
			this->size = 0;
			this->~LinkedList();

			//Move resources from original
			this->head = new Node();
			this->size = original.getSize();
			this->head->next = original.head->next;
			this->head->next->prev = this->head;
			this->head->prev = original.head->prev;
			this->head->prev->next = this->head;

			//reset original
			original.size = 0;
			original.head->next = original.head;
			original.head->prev = original.head;
	}

	//ACCESSORS


	int getSize() const {
		return this->size;
	}


	//OPERATORS


	// Assignment operator
    LinkedList& operator=(const LinkedList &old) { 
		if (this->size != 0) {
			this->~LinkedList();
		}

		//create dummy
		this->head = new Node();
		this->head->next = this->head;
		this->head->prev = this->head;


        Node* cur = old.head->next;
        while(cur != old.head){
            this->add(cur->data);
			cur = cur->next;
        }
		return *this;
    }

	
   //Allows accessing by index via LL[x]
    const T& operator [](int index) const{
        if(index < 0 || index > this->size){
            throw std::out_of_range("Index out of bounds on call to [] operator.");
        }

        Node* cur = this->head->next;
        int i = 0;

        while(i != index){
            i++;
            cur = cur->next;
        }

        return cur->data;
    }

	//Overloaded to allow non-const use
    T& operator [](int index){
        if(index < 0 || index > this->size){
            throw std::out_of_range("Index out of bounds on call to [] operator.");
        }

        Node* cur = this->head->next;
        int i = 0;

        while(i != index){
            i++;
            cur = cur->next;
        }

        return cur->data;
    }

    //Uses an order based check
    bool operator==(const LinkedList<T>& other){
        if(this->size != other.size){
            return false;
        }

        Node* thisNode = this->head->next;
        Node* otherNode = other.head->next;

        while(thisNode != this->head && otherNode != other.head){
            if(thisNode->data != otherNode->data){
                return false;
            }
            thisNode = thisNode->next;
            otherNode = otherNode->next;
        }
        return true;
    }

	bool operator!=(const LinkedList<T>& other) {
		return !(this == other);
	}

    //Appends rhs after lhs, returns new list
    LinkedList<T> operator+(LinkedList<T> const &rhs) {
        LinkedList<T> ret = LinkedList<T>();
		if (rhs.getSize() == 0 && this->size == 0) {
			return ret;
		}

        //Adds data from this
        Node* cur = this->head->next;
        while(cur != this->head){
            ret.add(cur->data);
            cur = cur->next;
        }

        //Data from rhs
        cur = rhs.head->next;
        while(cur != rhs.head){
            ret.add(cur->data);
            cur = cur->next;
        }

        return ret;
    }


	//MUTATORS


    void add(T& data){
        this->add(this->size, data);
    }

	//Allows adding primitives more easily
    void add(T&& data){
        this->add(data);
    }

    void add(int index, T& data){
        if(index < 0 || index > this->size){
            throw std::out_of_range("Index out of bounds on call to add.");
        }

        Node *cur = this->head->next;
        Node *prev = this->head;
        Node *nn = new Node(data);
        int i = 0;

		//Walk to index
        while ((cur != this->head) && (i != index)) {
            i++;
            prev = cur;
            cur = cur->next;
        }
		//insert into list
        prev->next = nn;
        cur->prev = nn;
		//connect nn
        nn->prev = prev;
        nn->next = cur;

        this->size++;
    }

    bool remove(T& data){
        Node* cur = this->head->next;
        int i = 0;

        while(cur != this->head){
            if(cur->data == data){
                break;
            }
            i++;
            cur = cur->next;
        }

		//check base case
        if(cur != this->head){
			//alter links
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			delete cur;
			this->size--;
			return true;
        }

        return false;
    }

    T removeIndex(int index){
        if(index < 0 || index > this->size){
            throw std::out_of_range("Index out of bounds on call to removeIndex.");
        }

        Node* cur = this->head->next;
        Node* prev = this->head;

        int i = 0;
        while(i != index){
            i++;
            prev = cur;
            cur = cur->next;
        }

        T ret = cur->data;
        
		//Break links
        prev->next = cur->next;
        cur->next = prev;
        delete cur;
        this->size--;

        return ret;
    }

	//Remove all occurrences
    bool removeAll(T data){
        bool removed = false;
		if (this->size == 0 || this->head == nullptr || this->head->next == nullptr) {
			return false;
		}

        Node* cur = this->head->next;
        Node* prev = this->head;
        int i = 0;

        while(cur != this->head && cur!= nullptr){
            if(cur->data == data){
				cur->prev->next = cur->next;
				cur->next->prev = cur->prev;
				this->size--;
				Node * temp = cur;
				cur = cur->next;
				delete temp;
                removed = true;
            }
			else {
				i++;
				prev = cur;
				cur = cur->next;
			}
           
        }

        return removed;
    }

    //Uses selection sort
    void sort() { 
		Node* cur = this->head->next;
		Node * walker = cur->next;
		Node* smallest;
		T temp;

		while (cur != this->head) {
			smallest = cur;
			walker = cur->next;
			while (walker != this->head) {
				if (walker->data < smallest->data) {
					smallest = walker;
				}
				walker = walker->next;
			}
			temp = cur->data;
			cur->data = smallest->data;
			smallest->data = temp;
			cur = cur->next;
		}


    }

    std::string toString() const{
        if(this->size == 0){
            return "[Empty List]";
        }else{
            std::stringstream ss;
            Node* cur = this->head->next;
			ss << "[";
            while(cur != this->head){
                ss << cur->data;
                cur = cur->next;
				if (cur != this->head) {
					ss << ", ";
				}
            }
			ss << "]";
            return ss.str();
        }
    }
};

//Output operator
template <class T>
std::ostream& operator <<(std::ostream &strm, const LinkedList<T>& rhs) {
	std::string toReturn = rhs.toString();
	return strm << toReturn;
}




#endif /* LinkedList_h */
