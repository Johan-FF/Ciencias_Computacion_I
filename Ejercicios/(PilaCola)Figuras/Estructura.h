#ifndef ESTRUCTURA1_H     
#define ESTRUCTURA1_H 

template <typename T>
struct nodo {
    T dato;
    nodo<T> *sig;
};

#endif
