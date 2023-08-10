//
// Created by Abziz on 01/12/2020.
//

#ifndef LAB6_LIST_H
#define LAB6_LIST_H

#include <iostream>

using namespace std;

class List {
public:

	/**
	 * Create an empty list of integers
	 */
	List();

	/* big three */
	List(const List& other);

	List& operator=(const List& rhs);

	~List();

	/**
	 * insert an element to the head of the list
	 * @param elem
	 */
	void insert(const char * key,int elem);

	/**
	 * remove the first occurrence of elem in the list
	 * @param elem
	 */
	void remove(const char * elem);

	/**
	 * remove all elements from the list
	 */
	void clear();

	/**
	 * return how many elements are in the list
	 */
	int size() const;

	/**
	 * access an element at a given index
	 * @param index
	 * @return
	 */
	int& operator[](const char * index);

    /*
     * Will increase the value of the serial number by one
     */
    void increment(const char * name);


	/**
	 * return an element at a given index
	 * @param index
	 * @return
	 */
	const int& operator[](const char * index) const;

	friend ostream& operator<<(ostream& out, const List& list);

private:
	struct Node {
        int serielNumber;
        char key[8]{};
		Node* next;

		Node(const char * key,int seriel, Node* next);
	};

	Node* head;
	int count;
};

ostream& operator<<(ostream& out, const List& list);

#endif //LAB6_LIST_H
