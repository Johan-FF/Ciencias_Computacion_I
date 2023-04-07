#include <cstddef>
#ifndef PILADINAMICA_H
#define PILADINAMICA_H

template <typename T>
class Pila {
    private:
        struct nodo {
            T clave;
            struct nodo *siguiente;
        };
        struct nodo *cabeza, *z;
    public:
        Pila(int max) {
            cabeza = new nodo;
            z = new nodo;
            cabeza->siguiente = z;
            z->siguiente = z;
        }
        ~Pila() {
            struct nodo *t = cabeza;
            while (t != z) {
                cabeza = t;
                t = t->siguiente;
                delete cabeza;
            }
        }
        void meter(T V) {
            struct nodo *t = new nodo;
            t->clave = V;
            t->siguiente = cabeza->siguiente;
            cabeza->siguiente = t;
        }
        T sacar() {
            T x;
            struct nodo *t = cabeza->siguiente;
            cabeza->siguiente = t->siguiente;
            x = t->clave;
            delete t;
            return x;
        }
        int vacia() {
            return cabeza->siguiente == z;
        }
};

#endif
