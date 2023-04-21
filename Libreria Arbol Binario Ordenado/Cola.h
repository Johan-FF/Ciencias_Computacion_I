#include <cstdlib>
#include <iostream>
#include "Estructura.h"

#ifndef COLA1_H     
#define COLA1_H 

using namespace std;

template <typename T>
class Cola{
    private:
        nodoCola<T> *cab,*fin;
    public:
        Cola(){cab=fin=NULL;}
        void insCola(T i);
        T atenderCola();
        void imprimirCola();
        bool colaVacia();
        ~Cola();
};

template <typename T>
void Cola<T>::insCola(T i){
    nodoCola<T> *nuevo;
    nuevo= new nodoCola<T>;
    nuevo->dato=i;
    nuevo->sig= NULL;
    if (cab==NULL)
        {cab=nuevo;}
    else {fin->sig = nuevo;}
    fin=nuevo;
}

template <typename T>
T Cola<T>::atenderCola(){
    T x;
    nodoCola<T> *aux = cab; 
    cab=aux->sig;
    x=aux->dato;
    delete aux;
    return x;
}

template <typename T>
void Cola<T>::imprimirCola(){
    nodoCola<T> *aux;
    aux=cab;
    while(aux!=NULL){
        cout<<aux->dato<<" ";
        aux=aux->sig;
    }    
}

template <typename T>
bool Cola<T>::colaVacia(){
    return (cab==NULL);
}

template <typename T>
Cola<T>::~Cola(){
    nodoCola<T> *aux;
    while(cab!=NULL)
    {aux= cab;
    cab=aux->sig;
    delete aux;}
    delete cab;
}

#endif
