#include <cstddef>
#ifndef LISTA_H
#define LISTA_H

#include <iostream>

using namespace std;

// Definición de la clase Nodo
template<typename T>
class Nodo {
public:
    T valor;              
    Nodo<T>* siguiente;    

    // Constructor de la clase Nodo
    Nodo(T valor) {
        this->valor = valor;
        this->siguiente = nullptr;
    }
};

// Definición de la clase Lista
template<typename T>
class Lista {
private:
    Nodo<T>* inicio;    
    Nodo<T>* fin;       
    int tam;            

public:
    // Constructor de la clase Lista
    Lista() {
        inicio = nullptr;
        fin = nullptr;
        tam = 0;
    }

    // Destructor de la clase Lista
    ~Lista() {
        Nodo<T>* actual = inicio;
        Nodo<T>* tmp;
        // Se recorre la lista liberando la memoria de cada nodo
        while (actual != nullptr) {
            tmp = actual->siguiente;
            delete actual;
            actual = tmp;
        }
    }

    // Método para insertar un elemento al final de la lista
    void insertar_final(T valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);

        // Si la lista está vacía, el nuevo nodo será tanto el primero como el último
        if (inicio == nullptr) {
            inicio = nuevo;
            fin = nuevo;
        }
        // Si no, se agrega el nuevo nodo después del último
        else {
            fin->siguiente = nuevo;
            fin = nuevo;
        }

        // Se aumenta el tamaño de la lista
        tam++;
    }

    // Método para insertar un elemento al inicio de la lista
    void insertar_inicio(T valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);

        // Si la lista está vacía, el nuevo nodo será tanto el primero como el último
        if (inicio == nullptr) {
            inicio = nuevo;
            fin = nuevo;
        }
        // Si no, se agrega el nuevo nodo antes del primero
        else {
            nuevo->siguiente = inicio;
            inicio = nuevo;
        }

        // Se aumenta el tamaño de la lista
        tam++;
    }

    // Método para insertar un elemento en una posición específica de la lista
    void insertar(T valor, int pos) {
        // Se verifica que la posición sea válida
        if (pos > tam || pos < 0) {
            cout << "Posicion invalida" << endl;
            return;
        }

        // Si la posición es 0, se inserta al inicio de la lista
        if (pos == 0) {
            insertar_inicio(valor);
        }
        // Si la posición es igual al tamaño de la lista, se inserta al final
        else if (pos == tam) {
            insertar_final(valor);
        }
        // Si no, se busca el nodo anterior a la posición deseada y se inserta después de él
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
	    if (pos >= tam || pos < 0) { // Verificar si la posición es válida
	        cout << "Posicion invalida" << endl;
	        return;
	    }
	
	    Nodo<T>* actual = inicio;
	    for (int i = 0; i < pos; i++) { // Recorrer la lista hasta llegar a la posición indicada
	        actual = actual->siguiente;
	    }
	    actual->valor = valor; // Modificar el valor del nodo en la posición indicada
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
