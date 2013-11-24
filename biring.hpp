/*
 * biring.hpp
 *
 *  Created on: 23 lis 2013
 *      Author: matfil
 */

#ifndef BIRING_HPP_
#define BIRING_HPP_

template <class T> class BiRing
{
private:
	struct Node
	{
		T val;
		Node *next, *prev;

		Node(T v=0, Node *n=0, Node *p=0) : val(v), next(n), prev(p) { }
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
		iterator& operator++();
		iterator& operator--();
		T& operator*();
		bool operator!=(iterator it);
		bool operator==(iterator it);
		Node* operator->();
		bool operator==(Node *wsk);
		iterator operator=(Node *wsk);
	friend class BiRing;
	};

	BiRing(T init_val=0) : head( Node(init_val, &head, &head) ), nElem(0) { }
	~BiRing();
	int Size();

	iterator remove(iterator to_remove);

	void clear();


	iterator insert(T value, iterator where);
	iterator push_back(T value);

	iterator begin();
	iterator end();

};
/***IMPLEMENTACJA***BiRing<T>::iterator***/

template<class T>
BiRing<T>::iterator& BiRing<T>::iterator::operator++()
			{
				this->ptr = this->ptr->next;
				return *this;
			}
template<class T>
BiRing<T>::iterator& BiRing<T>::iterator::operator--()
			{
				this->ptr = this->ptr->prev;
				return *this;
			}
template<class T>
T& BiRing<T>::iterator::operator*()
			{
				return ptr->val;
			}
template<class T>
bool BiRing<T>::iterator::operator!=(iterator it)
				{return it.ptr != ptr;}
template<class T>
bool BiRing<T>::iterator::operator==(iterator it)
				{return it.ptr == ptr;}
template<class T>
BiRing<T>::Node* BiRing<T>::iterator::operator->()
				{return ptr;}
template<class T>
bool BiRing<T>::iterator::operator==(Node *wsk)
				{return ptr == wsk;}
template<class T>
BiRing<T>::iterator BiRing<T>::iterator::operator=(Node *wsk)
			{
				ptr = wsk;
				return *this;
			}

/***IMPLEMENTACJA***BiRing***/
template<class T>
BiRing<T>::~BiRing()
{
	clear();
}

template<class T>
int BiRing<T>::Size()
{
	return nElem;
}

template<class T>
inline BiRing<T>::iterator BiRing<T>::remove(iterator to_remove)
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

template<class T>
void BiRing<T>::clear()
{
	Node *to_rm = head.next->next;
	while(nElem != 0)
	{
		delete to_rm->prev;;
		--nElem;
	}
	head.next = head.prev = &head;
}

template<class T>
BiRing<T>::iterator BiRing<T>::insert(T value,BiRing<T>::iterator where)
{
	++nElem;
		return iterator(where.ptr->next = where.ptr->next->prev = new Node(value, where.ptr->next, where.ptr));
}

template<class T>
BiRing<T>::iterator BiRing<T>::push_back(T value)
{
	head.prev = head.prev->next = new BiRing<class T>::Node(value, &head, head.prev);
	++nElem;
	return --end();
}

template<class T>
BiRing<T>::iterator BiRing<T>::begin()
{
	return iterator(head.next);
}

template<class T>
BiRing<T>::iterator BiRing<T>::end()
{
	return iterator(&head);
}

#endif /* BIRING_HPP_ */
