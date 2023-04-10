#ifndef PILA1_H     
#define PILA1_H    
#include "Estructura.h"

template <typename T>
class Pila{
    private:
        nodo<T> *cab;
    public: 
        Pila(){cab= new nodo<T>; cab->dato=' '; cab->sig=NULL;}
        void push( T v);
        T pop();
        bool pilaVacia();
        ~Pila();
};

template <typename T>
void Pila<T>::push(T v){
    nodo<T> *t = new nodo<T>;
    t->dato=v; 
    t->sig=cab->sig;
    cab->sig= t;
}

template <typename T>
T Pila<T>::pop(){
    T x;
    nodo<T> *t= cab->sig;
    cab->sig= t->sig; 
    x=t->dato;
    delete t;
    return x;
}

template <typename T>
bool Pila<T>::pilaVacia(){
    return cab->sig== NULL;
}

template <typename T>
Pila<T>::~Pila(){
    nodo<T> *t=cab;
    while(t!=NULL){
        cab=t;
        t=t->sig;
        delete cab;
    }
}

#endif