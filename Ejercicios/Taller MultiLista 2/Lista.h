#include <cstddef>
#ifndef LISTA_H
#define LISTA_H

#include <iostream>

using namespace std;

template<typename T>
class Nodo {
public:
    T valor;
    Nodo<T>* siguiente;

    Nodo(T valor) {
        this->valor = valor;
        this->siguiente = nullptr;
    }
};

template<typename T>
class Lista {
private:
    Nodo<T>* inicio;
    Nodo<T>* fin;
    int tam;

public:
    Lista() {
        inicio = nullptr;
        fin = nullptr;
        tam = 0;
    }

    ~Lista() {
        Nodo<T>* actual = inicio;
        Nodo<T>* tmp;
        while (actual != nullptr) {
            tmp = actual->siguiente;
            delete actual;
            actual = tmp;
        }
    }

    void insertar_final(T valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);

        if (inicio == nullptr) {
            inicio = nuevo;
            fin = nuevo;
        }
        else {
            fin->siguiente = nuevo;
            fin = nuevo;
        }

        tam++;
    }

    void insertar_inicio(T valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);

        if (inicio == nullptr) {
            inicio = nuevo;
            fin = nuevo;
        }
        else {
            nuevo->siguiente = inicio;
            inicio = nuevo;
        }

        tam++;
    }

    void insertar(T valor, int pos) {
        if (pos > tam || pos < 0) {
            cout << "Posicion invalida" << endl;
            return;
        }

        if (pos == 0) {
            insertar_inicio(valor);
        }
        else if (pos == tam) {
            insertar_final(valor);
        }
        else {
            Nodo<T>* nuevo = new Nodo<T>(valor);
            Nodo<T>* actual = inicio;
            for (int i = 0; i < pos - 1; i++) {
                actual = actual->siguiente;
            }
            nuevo->siguiente = actual->siguiente;
            actual->siguiente = nuevo;
            tam++;
        }
    }

    void modificar(T valor, int pos) {
        if (pos >= tam || pos < 0) {
            cout << "Posicion invalida" << endl;
            return;
        }

        Nodo<T>* actual = inicio;
        for (int i = 0; i < pos; i++) {
            actual = actual->siguiente;
        }
        actual->valor = valor;
    }

    void borrar(int pos) {
        if (pos >= tam || pos < 0) {
            cout << "Posicion invalida" << endl;
            return;
        }

        Nodo<T>* actual = inicio;
        Nodo<T>* tmp;
        if (pos == 0) {
            inicio = actual->siguiente;
            if (inicio == nullptr) {
                fin = nullptr;
            }
            delete actual;
        }
        else {
            for (int i = 0; i < pos - 1; i++) {
                actual = actual->siguiente;
            }
            tmp = actual->siguiente;
            actual->siguiente = tmp->siguiente;
            if (actual->siguiente == nullptr) {
                fin = actual;
            }
            delete tmp;
        }

        tam--;
    }

    int getTam() {
        return tam;
    }

    bool lista_vacia() {
        return (tam == 0);
    }

    T buscar(int pos) {
        if (pos < 0 || pos >= tam) {
	        cout<<"Posición invalida"<<endl;
	    }
	
	    Nodo<T> *actual = inicio;
	    for (int i = 0; i < pos; i++) {
	        actual = actual->siguiente;
	    }
	
	    return actual->valor;
    }
    
};

#endif
