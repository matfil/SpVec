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
		
	class nziter
	{
	};
};
#endif
