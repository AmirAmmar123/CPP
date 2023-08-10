
#include <cstdlib>
#include "List.h"
#include <cstring>

List::List() : head(NULL), count(0) {}

void List::insert(const char * key,int elem) {
	head = new Node(key, elem, head);
	count++;
}

void List::clear() {
	while (head) {
		Node* temp = head;
		head = head->next;
		delete temp;
	}
	count = 0;
	head = nullptr;
}

List::List(const List& other) : head(nullptr), count(0) {
	Node* temp = other.head;
	while (temp) {
		insert(temp->key,temp->serielNumber);
		temp = temp->next;
	}
}

List& List::operator=(const List& rhs) {
	if (this != &rhs) {
		clear();
		Node* temp = rhs.head;
		while (temp) {
			insert(temp->key,temp->serielNumber);
			temp = temp->next;
		}
	}
	return *this;
}

List::~List() {
	clear();
}

int& List::operator[](const char *  name) {
    Node* temp = head;
    while(temp != nullptr) {
        if(strcmp(temp->key, name) == 0) break;
        temp = temp->next;
    }
    if(temp == nullptr) { std::cerr << "Name not found";exit(1);}
    return temp->serielNumber;
}

const int& List::operator[](const char * name) const {
	Node* temp = head;
	while(temp != nullptr) {
        if(strcmp(temp->key, name) == 0) break;
		temp = temp->next;
	}
    if(temp == nullptr) { std::cerr << "Name not found";}
	return temp->serielNumber;
}

ostream& operator<<(ostream& out, const List& list) {
	List::Node* temp = list.head;
	while (temp) {
		if (temp != list.head) {
			out << ",";
		}
		out << temp->key << ":" << temp->serielNumber;
		temp = temp->next;
	}
	return out;
}

void List::remove(const char * elem) {
	if (!head) { return; }
	Node* temp = head;
	if (strcmp(temp->key, elem) == 0) {
		head = head->next;
		delete temp;
		count--;
		return;
	}
	while (temp->next && temp->next->key != elem) {
		temp = temp->next;
	}
	if (temp->next) {
		Node* victim = temp->next;
		temp->next = victim->next;
		delete victim;
		count--;
	}
}

int List::size() const {
	return count;
}

List::Node::Node(const char * key, int seriel , Node* next) : serielNumber(seriel), next(next) {
    strcpy(this->key, key);
}

void List::increment(const char * name){
    Node* temp = head;
	while(temp != nullptr) {
        if(strcmp(temp->key, name) == 0) break;
		temp = temp->next;
	}
    if(temp == nullptr) { std::cerr << "Name not found";}
    temp->serielNumber+=1;
}
