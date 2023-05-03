#ifndef ESTRUCTURA1_H     
#define ESTRUCTURA1_H 

template <typename T>
struct nodoCola {
    T dato;
    nodoCola<T> *sig;
};

#endif
