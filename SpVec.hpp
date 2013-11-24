#ifndef SPVEC
#define SPVEC

/*
 * plik SpVec.hpp
 */

#include "BiRing.hpp"
#include <sstream>        // std::sstream
#include <exception>      // std::exception


template <typename T>
class SpVec
{
public:
  class nziter;
private:
  /*Deklaracja iteratora po niezerowych wartosciach*/
	int len;
  /*Dlugosc wektora*/
	struct Pair
	{
		int id;
		T val;
		Pair(int ID, T VAL = 0) : id(ID), val(VAL) { }
	};
  /*Atom do budowy struktury - para indeksu i wartosci*/
	BiRing <SpVec<T>::Pair> vals;
  /*Lista niezerowych wartosci wektora */
	SpVec<T>::nziter it, itt;
  /*Statyczny - Jeden egzemplarz dla wszystkich klas, zeby zbednie
   * nie alokowac/dealokowac za kazdym razem kiedy jest potrzebny
   * pomocniczy iterator
   * Problem moze wystapic przy wielowatkowosci.*/

public:
	SpVec(int S=0) : len(S), vals(BiRing<SpVec<T>::Pair>(Pair(-1))) { }
  ~SpVec()
	{
		vals.clear();
	}
	void resize (int s);
	int size ();
	int nonzero ();
	
	T& operator[] (int id);
	T operator[] (int id) const;
	SpVec<T>& operator+= (const SpVec<T>& sv);
	SpVec<T>& operator-= (const SpVec<T>& sv);
	SpVec<T>& operator*= (const SpVec<T>& sv);
	SpVec<T>& operator= (const SpVec<T>& sv);
	SpVec<T> operator+ (const SpVec<T>& sv) const;
	SpVec<T> operator- (const SpVec<T>& sv) const;
	SpVec<T> operator* (const SpVec<T>& sv) const;
	
	nziter begin();
	nziter end();
	
  class nziter
	{
    typedef typename BiRing<SpVec<T>::Pair>::iterator myiter;
	  myiter ptr;
  public:
    nziter(myiter p = myiter(nullptr)) : ptr(p) {}

	  nziter& operator++();
	  nziter& operator--();
	  Pair& operator*();
	  bool operator==(nziter IT);
	  bool operator!=(nziter IT);
    nziter& operator=(typename BiRing<SpVec<T>::Pair>::iterator P);
    operator myiter()
    {
      return ptr;
    }
  private:
    myiter operator->() // musi byc niestatyczna ! #TODO
    {
      return ptr;
    }
  };
};

struct size_mismatch_ex : std::exception {
  std::string opr;
  int size1, size2;
  const char* what() const noexcept 
  { 
    std::stringstream ss; 
    ss << "Wrong function call, size of SpVector does not match the call: (vecotr's size" << size1 << ", call " << size2 << ") in " << opr << "\n"; 
    return ss.str().c_str();  
  }
  size_mismatch_ex(std::string m, int a1, int a2) : 
    opr(m), size1(a1), size2(a2) { }
};


//#include <cassert>
#define OPTI false  

template <typename T>
void SpVec<T>::resize (int s)
{
//  assert(s > 0);
  if (s <= 0)
  {
    throw(size_mismatch_ex("void SpVec<T>::resize (int s)", s, 0));
  }  
  /*Zmiana rozmiaru na mniejsza-rowna zeru jest zabroniona*/
	if(s < len)
		{
		  it = --(vals.end());
      while((*it).id >= s)
      {
        vals.remove(it);
        it = --(vals.end());
      }
      /*maksymalny indeks wektora jest mniejszy o 1 od jego rozmiaru*/
		}
  /*Trzeba usunac zapamietane niezerowe elementy spoza rozmiaru.*/
	len = s;
}

template <typename T>
int SpVec<T>::size ()
{
	return len;
}

template <typename T>
int SpVec<T>::nonzero ()
{
	return vals.Size();
} 

template <typename T>
SpVec<T>& SpVec<T>::operator+= (const SpVec<T>& sv)
{// czy mozna lepiej?
//	assert(sv.size() == size());
  if (sv.size() != size())
  {
    throw(size_mismatch_ex("SpVec<T>& SpVec<T>::operator+= (const SpVec<T>& sv)", size(), sv.size()));
  }  
  itt = sv.begin();
  it = begin();
  while(it != end() && itt != sv.end())
  {
    if((*it).id == (*itt).id)
    {
      if((*it).val + (*itt).val != 0)
      {
        (*it).val += (*itt).val; 
        ++it;
      }
      else
        it = vals.remove(it);
      ++itt;
    }
    else if((*it).id > (*itt).id)
    {
      it.insert(SpVec<T>::Pair((*itt).id, (*itt).val));
      ++itt;
    }
    else
    {
      ++it;
    }
  }
  while(itt != sv.end())
  {
    vals.push_back(SpVec<T>::Pair((*itt).id, (*itt).val));
    ++itt;
  }
  return *this;
}

template <typename T>
SpVec<T>& SpVec<T>::operator-= (const SpVec<T>& sv)
{
//	assert(sv.size() == size());
  if (sv.size() != size())
  {
    throw(size_mismatch_ex("SpVec<T>& SpVec<T>::operator-= (const SpVec<T>& sv)", size(), sv.size()));
  }  
  itt = sv.begin();
  it = begin();
  while(it != end() && itt != sv.end())
  {
    if((*it).id == (*itt).id)
    {
      if((*it).val - (*itt).val != 0)
      {
        (*it).val -= (*itt).val; 
        ++it;
      }
      else
        it = vals.remove(it);
      ++itt;
    }
    else if((*it).id > (*itt).id)
    {
      it.insert(SpVec<T>::Pair((*itt).id, -(*itt).val));
      ++itt;
    }
    else
    {
      ++it;
    }
  }
  while(itt != sv.end())
  {
    vals.push_back(SpVec<T>::Pair((*itt).id, -(*itt).val));
    ++itt;
  }
  return *this;
}

template <typename T>
SpVec<T>& SpVec<T>::operator*= (const SpVec<T>& sv)
{
//	assert(sv.size() == size());
  if (sv.size() != size())
  {
    throw(size_mismatch_ex("SpVec<T>& SpVec<T>::operator*= (const SpVec<T>& sv)", size(), sv.size()));
  }  
  itt = sv.begin();
  it = begin();
  while(it != end() && itt != sv.end())
  {
    if((*it).id == (*itt).id)
    {
      (*it).val *= (*itt).val; 
      ++it;
      ++itt;
    }
    else if((*it).id > (*itt).id)
    {
      ++itt;
    }
    else
    {
      it = vals.remove(it);
    }
  }
  while(itt != sv.end())
  {
    vals.push_back(SpVec<T>::Pair((*itt).id, (*itt).val));
    ++itt;
  }
  return *this;
}

template <typename T>
SpVec<T>& SpVec<T>::operator= (const SpVec<T>& sv)
{
  /*Mozna to zrobic szybciej, ale tak jest czytelniej.
   * Tzn. zamiast usuwania poprzedniej listy, zmiana
   * elementow istniejacych na odpowiednie wartosci i
   * usuniecie reszty*/
  vals.clear();
  len = sv.len;
  for(it = sv.begin(); it != sv.end(); ++it)
  {
    vals.push_back(*it);
  }
  return *this;
}

template <typename T>
SpVec<T> SpVec<T>::operator+ (const SpVec<T>& sv) const
{
//	assert(sv.size() == size());
  if (sv.size() != size())
  {
    throw(size_mismatch_ex("SpVec<T> SpVec<T>::operator+ (const SpVec<T>& sv) const", size(), sv.size()));
  }  
  SpVec<T> ret(len);
  itt = sv.begin();
  it = begin();
  while(it != end() && itt != sv.end())
  {
    if((*it).id == (*itt).id)
    {
      if((*it).val + (*itt).val != 0)
        ret.vals.push_back(SpVec<T>::Pair((*it).id, (*it).val + (*itt).val));
      ++it;
      ++itt;
    }
    else if((*it).id > (*itt).id)
    {
      ret.vals.push_back(SpVec<T>::Pair((*itt).id, (*itt).val));
      ++itt;
    }
    else
    {
      ret.vals.push_back(SpVec<T>::Pair((*it).id, (*it).val));
      ++it;
    }
  }
  return ret;
}

template <typename T>
SpVec<T> SpVec<T>::operator- (const SpVec<T>& sv) const
{
//	assert(sv.size() == size());
  if (sv.size() != size())
  {
    throw(size_mismatch_ex("SpVec<T> SpVec<T>::operator- (const SpVec<T>& sv) const", size(), sv.size()));
  }  
  SpVec<T> ret(len);
  itt = sv.begin();
  it = begin();
  while(it != end() && itt != sv.end())
  {
    if((*it).id == (*itt).id)
    {
      if((*it).val + (*itt).val != 0)
        ret.vals.push_back(SpVec<T>::Pair((*it).id, (*it).val - (*itt).val));
      ++it;
      ++itt;
    }
    else if((*it).id > (*itt).id)
    {
      ret.vals.push_back(SpVec<T>::Pair((*itt).id, -(*itt).val));
      ++itt;
    }
    else
    {
      ret.vals.push_back(SpVec<T>::Pair((*it).id, (*it).val));
      ++it;
    }
  }
  return ret;
}

template <typename T>
SpVec<T> SpVec<T>::operator* (const SpVec<T>& sv) const
{
  if (sv.size() != size())
  {
    throw(size_mismatch_ex("SpVec<T> SpVec<T>::operator* (const SpVec<T>& sv) const", size(), sv.size()));
  }  
  SpVec<T> ret(len);
  itt = sv.begin();
  it = begin();
  while(it != end() && itt != sv.end())
  {
    if((*it).id == (*itt).id)
    {
      ret.vals.push_back(SpVec<T>::Pair((*it).id, (*it).val * (*itt).val));
      ++it;
      ++itt;
    }
    else if((*it).id > (*itt).id)
    {
      ++itt;
    }
    else
    {
      ++it;
    }
  }
  return ret;
}


template<typename T>
T& SpVec<T>::operator[] (int id)
{
  if (id >= len || id < 0)
  {
    throw(size_mismatch_ex("T& SpVec<T>::operator[] (int id)", len, id));
  }  
	for(it = begin(); it != end() && (*it).id < id; ++it);
	if((*it).id == id) 
    return (*it).val;
  else
  {
    Pair tmp(id, T());
	  return (*(vals.insert( tmp, it ))).val;
  }
}

template<typename T>
T SpVec<T>::operator[] (int id) const
{
  if (id >= len || id < 0)
  {
    throw(size_mismatch_ex("T SpVec<T>::operator[] (int id) const", len, id));
  }  
	for(it = begin(); it != end() && (*it).id < id; ++it);
	if(it == end() || it.id != id) 
		return T(); //default value
	else
		return (*it).val;
}

template<typename T>
typename SpVec<T>::nziter SpVec<T>::begin()
{
  return nziter(vals.begin()); 
}

template<typename T>
typename SpVec<T>::nziter SpVec<T>::end()
{	
  return nziter(vals.end());  
}

template<typename T>
typename SpVec<T>::nziter& SpVec<T>::nziter::operator++()
{

  ++ptr;
#if OPTI == true
  if ((*ptr).id != -1)
  {
    if((*ptr).val == 0)
      ptr = BiRing<T>::remove(BiRing<T>::iterator(ptr));
  }
#endif
  return *this;
}
template<typename T>
typename SpVec<T>::nziter& SpVec<T>::nziter::operator--()
{
  --ptr;
#if OPTI == true
  if ((*ptr).id != -1)
  {
    while((*ptr).val == 0)
    {
      ptr = BiRing<T>::remove(BiRing<T>::iterator(ptr));
      --ptr;
    }

  }
#endif
  return *this;
}

template<typename T>
typename SpVec<T>::Pair& SpVec<T>::nziter::operator*()
{
  return *ptr;
}

template<typename T>
bool SpVec<T>::nziter::operator==(nziter IT)
{
  return ptr == IT.ptr;
}

template<typename T>
bool SpVec<T>::nziter::operator!=(nziter IT)
{
  return ptr != IT.ptr;
}

template<typename T>
typename SpVec<T>::nziter& SpVec<T>::nziter::operator=(typename BiRing<SpVec<T>::Pair>::iterator P)
{
  ptr=P;
#if OPTI == true
  if ((*ptr).id != -1)
  {
    while((*ptr).val == 0)
      ptr = BiRing<T>::remove(BiRing<T>::iterator(ptr));
  }
#endif
  return *this;
}

/* Problem: funkcja musi byc niestatyczna -> ?
template<typename T>
typename BiRing<typename SpVec<T>::Pair>::iterator operator->()
{
  return ptr;
}*/
#undef OPTI

#endif
