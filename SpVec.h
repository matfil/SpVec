#ifndef SPVEC
#define SPVEC

/*
 * plik SpVec.h
 */

#include "biring.h"

template <class T>
class SpVec
{
private:
	int len;
	struct Pair
	{
		int id;
		T val;
		Pair(int ID, T VAL = 0) : id(ID), val(VAL) { }
	};
	BiRing <Pair> vals;
	BiRing <Pair>::iterator it;

public:
	SpVec(int S=0) : len(S) { }
	~SpVec()
	{
		vals.clear();
	}
	void resize (int s);
	int size ();
	int nonzero ();
	
	T& operator+= (const SpVec& sv);
	T& operator-= (const SpVec& sv);
	T& operator*= (const SpVec& sv);
	T& operator= (const SpVec& sv);
	T& operator+ (const SpVec& sv);
	T& operator- (const SpVec& sv);
	T& operator* (const SpVec& sv);
	T& operator[] (int id);
	T operator[] (int id) const;
	
	BiRing<Pair>::iterator begin()
	{
		return vals.begin();
	}
	BiRing<Pair>::iterator end()
	{
		return vals.end();
	}
	class nziter
	{
	BiRing<Pair>::iterator ptr;
public:
	nziter(BiRing<Pair>::iterator p = iterator(nullptr)) : ptr(p) {}
//TODO
	nziter& operator++()
	{ return nziter(++ptr);}
	nziter& operator--()
	{ return nziter(--ptr);}
	Pair& operator*()
	{return *ptr;}
	operator==(nziter IT)
	{return ptr == IT.ptr;}
	operator!=(nziter IT)
	{return ptr != IT.ptr;}
	};
};
#endif
