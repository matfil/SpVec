#include "SpVec.h"

	void SpVec::resize (int s)
	{
		if(s > len)
			len = s;
		else
			{
			//USUN POZOSTALE ZDEFINIOWANE ELEMENTY
			}
	}
	int SpVec::size ()
	{
		return len;
	}
	int SpVec::nonzero ()
	{
		return vals.Size();
	}
	
	T& SpVec::operator+= (const SpVec& sv)
	{
	}
	T& SpVec::operator-= (const SpVec& sv)
	{
	}
	T& SpVec::operator*= (const SpVec& sv)
	{
	}
	T& SpVec::operator= (const SpVec& sv)
	{
	}
	T& SpVec::operator+ (const SpVec& sv)
	{
	}
	T& SpVec::operator- (const SpVec& sv)
	{
	}
	T& SpVec::operator* (const SpVec& sv)
	{
	}
	T& SpVec::operator[] (int id)
	{
		for(it = vals.begin(); it != vals.end() && *it.id < id; ++it);
		if(*it == vals.end() || it.id != id) 
			it = vals.insert( Pair(id, T()), it );
		return &((*it).val);
	}
	T SpVec::operator[] (int id) const
	{
		for(it = vals.begin(); it != vals.end() && *it.id < id; ++it);
		if(*it == vals.end() || it.id != id) 
			return T(); //default value
		else
			return (*it).val;
	}

