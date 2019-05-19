#include "pch.h"
#include "List.h"


List::List()
{
	head = NULL;
}

void List::addTail(int k)
{
	node* p = new node;
	if (p == NULL)
		return;
	p->data = k;
	p->pNext = NULL;
	if (head == NULL)
		head = p;
	else
	{
		node* cur = head;
		while (cur->pNext)
			cur = cur->pNext;
		cur->pNext = p;
	}
}
void List::print()
{
	node* cur = head;
	while (cur)
	{
		std::cout << cur->data << " ";
		cur = cur->pNext;
	}
	std::cout << std::endl;
}
List::~List()
{
	node* cur;
	while (head)
	{
		cur = head;
		head = head->pNext;
		std::cout << "free node\n";
		free(cur);
	}
}
bool List::isEmpty()
{
	if (head == NULL)
		return true;
	return false;
}
