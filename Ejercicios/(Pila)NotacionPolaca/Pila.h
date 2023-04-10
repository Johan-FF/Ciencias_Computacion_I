#include <cstddef>
#ifndef PILA_H
#define PILA_H

template<typename tipoElemento>

class Pila{
  private:
    tipoElemento *pila;
    int p;
    
  public:
    Pila(int max=100){
      pila = new tipoElemento[max]; p=0;
    };
    ~Pila(){
      delete[] pila;
    };
    void meter(tipoElemento v){
      p++;
      pila[p]=v;
    };
    tipoElemento sacar(){
      tipoElemento a = pila[p];
      p--;
      return a;
    };
    int vacia(){
      return !p; 
    };
};

#endif