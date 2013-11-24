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
	static SpVec<T>::nziter it, itt;
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
#endif
