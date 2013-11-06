#include <iostream>
using namespace std;

template <class T> 
class BiRing 
{
private:
	struct Node
	{
		T val;
		Node *next, *prev;

		Node(T v=0, Node *n=0, Node *p=0) : 
		val(v), next(n), prev(p) 
		{ }
	};

	Node head;
	int nElem;

public: 
	class iterator
	{
	private:
		Node *ptr;
	public:
		iterator() : ptr(nullptr) {}
		iterator(Node *n) : ptr(n) {}
		iterator& operator++()
			{
				this->ptr = this->ptr->next;
				return *this;
			}
		iterator& operator--()
			{
				this->ptr = this->ptr->prev;
				return *this;
			}
		T& operator*()
			{
				return ptr->val;
			}
		bool operator!=(iterator it)
				{return it.ptr != ptr;}
		bool operator==(iterator it)
				{return it.ptr == ptr;}
		Node* operator->()
				{return ptr;}
		bool operator==(Node *wsk)
				{return ptr == wsk;}
		iterator operator=(Node *wsk)
			{
				ptr = wsk;
				return *this;
			}
	friend class BiRing;
	};

	BiRing(T init_val=0) : head( Node(init_val, &head, &head) ), nElem(0) { }
	~BiRing() { clear(); }
	int Size()
		{return nElem;}

	iterator remove(iterator to_remove)
	{
		if (to_remove == nullptr || to_remove == &head)
		{
			throw("invalid pointer in remove function");
		}
		to_remove -> prev -> next = to_remove -> next;
		to_remove -> next -> prev = to_remove -> prev;
		--nElem;
		
		iterator ret_val = iterator(to_remove->next);
		delete to_remove.ptr;
		return ret_val;
	}

	void clear()
	{
		Node *to_rm = head.next->next;
		while(nElem != 0)
		{	
			delete to_rm->prev;;
			--nElem;
		}
		head.next = head.prev = &head;
	}

	iterator insert(T value, iterator where)
	{
		++nElem;
		return iterator(where.ptr->next = where.ptr->next->prev = new Node(value, where.ptr->next, where.ptr));
	}
	void push_back(T value)
	{
		head.prev = head.prev->next = new Node(value, &head, head.prev);
		++nElem;
	}
	iterator begin()
		{return iterator(head.next);}
	iterator end()
		{return iterator(&head);}

};
