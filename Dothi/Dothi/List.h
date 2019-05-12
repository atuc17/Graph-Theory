#pragma once
#include <iostream>
struct node
{
	int data;
	struct node* pNext;
};

class List
{
private:
	node* head;
public:
	List();
	~List();
	void addTail(int);
	void print();
	bool isEmpty();
	node* getHead()
	{
		return head;
	}
};

