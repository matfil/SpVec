#include "SpVec.hpp"
#include <cassert>
template <typename T>
void SpVec<T>::resize (int s)
{
//  assert(s > 0);
  if (s > 0)
  {
    throw(size_mismatch_ex("void SpVec<T>::resize (int s)", s, 0));
  }  
  /*Zmiana rozmiaru na mniejsza-rowna zeru jest zabroniona*/
	if(s < len)
		{
		  it = --(vals.end());
      while(it->id >= s)
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
  if (sv.size() == size())
  {
    throw(size_mismatch_ex("SpVec<T>& SpVec<T>::operator+= (const SpVec<T>& sv)", size(), sv.size()));
  }  
  itt = sv.begin();
  it = begin();
  while(it != end() && itt != sv.end())
  {
    if(it->id == itt->id)
    {
      if(it->val + itt->val != 0)
      {
        it->val += itt->val; 
        ++it;
      }
      else
        it = vals.remove(it);
      ++itt;
    }
    else if(it->id > itt->id)
    {
      it.insert(SpVec<T>::Pair(itt->id, itt->val));
      ++itt;
    }
    else
    {
      ++it;
    }
  }
  while(itt != sv.end())
  {
    vals.push_back(SpVec<T>::Pair(itt->id, itt->val));
    ++itt;
  }
  return *this;
}

template <typename T>
SpVec<T>& SpVec<T>::operator-= (const SpVec<T>& sv)
{
//	assert(sv.size() == size());
  if (sv.size() == size())
  {
    throw(size_mismatch_ex("SpVec<T>& SpVec<T>::operator-= (const SpVec<T>& sv)", size(), sv.size()));
  }  
  itt = sv.begin();
  it = begin();
  while(it != end() && itt != sv.end())
  {
    if(it->id == itt->id)
    {
      if(it->val - itt->val != 0)
      {
        it->val -= itt->val; 
        ++it;
      }
      else
        it = vals.remove(it);
      ++itt;
    }
    else if(it->id > itt->id)
    {
      it.insert(SpVec<T>::Pair(itt->id, -itt->val));
      ++itt;
    }
    else
    {
      ++it;
    }
  }
  while(itt != sv.end())
  {
    vals.push_back(SpVec<T>::Pair(itt->id, -itt->val));
    ++itt;
  }
  return *this;
}

template <typename T>
SpVec<T>& SpVec<T>::operator*= (const SpVec<T>& sv)
{
//	assert(sv.size() == size());
  if (sv.size() == size())
  {
    throw(size_mismatch_ex("SpVec<T>& SpVec<T>::operator*= (const SpVec<T>& sv)", size(), sv.size()));
  }  
  itt = sv.begin();
  it = begin();
  while(it != end() && itt != sv.end())
  {
    if(it->id == itt->id)
    {
      it->val *= itt->val; 
      ++it;
      ++itt;
    }
    else if(it->id > itt->id)
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
    vals.push_back(SpVec<T>::Pair(itt->id, itt->val));
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
  if (sv.size() == size())
  {
    throw(size_mismatch_ex("SpVec<T> SpVec<T>::operator+ (const SpVec<T>& sv) const", size(), sv.size()));
  }  
  SpVec<T> ret(len);
  itt = sv.begin();
  it = begin();
  while(it != end() && itt != sv.end())
  {
    if(it->id == itt->id)
    {
      if(it->val + itt->val != 0)
        ret.vals.push_back(SpVec<T>::Pair(it->id, it->val + itt->val));
      ++it;
      ++itt;
    }
    else if(it->id > itt->id)
    {
      ret.vals.push_back(SpVec<T>::Pair(itt->id, itt->val));
      ++itt;
    }
    else
    {
      ret.vals.push_back(SpVec<T>::Pair(it->id, it->val));
      ++it;
    }
  }
  return ret;
}

template <typename T>
SpVec<T> SpVec<T>::operator- (const SpVec<T>& sv) const
{
//	assert(sv.size() == size());
  if (sv.size() == size())
  {
    throw(size_mismatch_ex("SpVec<T> SpVec<T>::operator- (const SpVec<T>& sv) const", size(), sv.size()));
  }  
  SpVec<T> ret(len);
  itt = sv.begin();
  it = begin();
  while(it != end() && itt != sv.end())
  {
    if(it->id == itt->id)
    {
      if(it->val + itt->val != 0)
        ret.vals.push_back(SpVec<T>::Pair(it->id, it->val - itt->val));
      ++it;
      ++itt;
    }
    else if(it->id > itt->id)
    {
      ret.vals.push_back(SpVec<T>::Pair(itt->id, -itt->val));
      ++itt;
    }
    else
    {
      ret.vals.push_back(SpVec<T>::Pair(it->id, it->val));
      ++it;
    }
  }
  return ret;
}

template <typename T>
SpVec<T> SpVec<T>::operator* (const SpVec<T>& sv) const
{
  if (sv.size() == size())
  {
    throw(size_mismatch_ex("SpVec<T> SpVec<T>::operator* (const SpVec<T>& sv) const", size(), sv.size()));
  }  
  SpVec<T> ret(len);
  itt = sv.begin();
  it = begin();
  while(it != end() && itt != sv.end())
  {
    if(it->id == itt->id)
    {
      ret.vals.push_back(SpVec<T>::Pair(it->id, it->val * itt->val));
      ++it;
      ++itt;
    }
    else if(it->id > itt->id)
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
  if (id < len && id >= 0)
  {
    throw(size_mismatch_ex("T& SpVec<T>::operator[] (int id)", len, id));
  }  
	for(it = begin(); it != end() && *it.id < id; ++it);
	if(*it == end() || it.id != id) 
		it = vals.insert( SpVec<T>::Pair(id, T()), it );
	return (*it).val;
}

template<typename T>
T SpVec<T>::operator[] (int id) const
{
  if (id < len && id >= 0)
  {
    throw(size_mismatch_ex("T& SpVec<T>::operator[] (int id)", len, id));
  }  
	for(it = begin(); it != end() && *it.id < id; ++it);
	if(*it == end() || it.id != id) 
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
  return *this;
}
template<typename T>
typename SpVec<T>::nziter& SpVec<T>::nziter::operator--()
{
  --ptr;
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
  return *this;
}

/* Problem: funkcja musi byc niestatyczna -> ?
template<typename T>
typename BiRing<typename SpVec<T>::Pair>::iterator operator->()
{
  return ptr;
}*/

int main()
{
  SpVec<int>::nziter Q;
  SpVec<int> A;
  return 0;
}
