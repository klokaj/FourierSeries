#ifndef HARMONIC_H
#define HARMONIC_H
#include <iostream>
using namespace std;

struct harmonic{
  size_t nr = 0;
  double a = 0;
  double b = 0;

  harmonic(size_t number, double a, double b ): nr(number), a(a), b(b){}
  harmonic(): harmonic(0, 0, 0) {}
  harmonic(const harmonic& har): harmonic(har.nr, har.a, har.b) {}
  friend ostream & operator<<(ostream &os, const harmonic& har) {
    return os <<"harmonic nr. "<< har.nr<< ", a = " << har.a << ", b " << har.b;

  }

  harmonic& operator=(const harmonic& har){
      nr = har.nr;
      a = har.a;
      b = har.b;
      return *this;
  }
};


#endif // HARMONIC_H
