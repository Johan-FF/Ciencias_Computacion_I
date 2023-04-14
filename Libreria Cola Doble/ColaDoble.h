#include <cstdlib>
#include <iostream>

#ifndef COLADOBLE_H     
#define COLADOBLE_H 

using namespace std;

template <typename T>
struct Nodo {
    T dato;
    Nodo<T>* sig;
    Nodo<T>* ant;
};

template <typename T>
class ColaDoble {
    private:
        Nodo<T>* cab;
        Nodo<T>* fin;
    public:
        ColaDoble() : cab(nullptr), fin(nullptr) {}

        bool estaVacia() const {
            return (cab == nullptr);
        }

        void insertar(T dato, char tipo) {
            Nodo<T>* nuevo = new Nodo<T>();
            nuevo->dato = dato;
            nuevo->sig = nullptr;
            nuevo->ant = nullptr;

            if (tipo == 'I') { // insertar por izquierda
                nuevo->sig = cab;
                if (cab != nullptr) {
                    cab->ant = nuevo;
                } else {
                    fin = nuevo;
                }
                cab = nuevo;
            } else if (tipo == 'D') { // insertar por derecha
                nuevo->ant = fin;
                if (fin != nullptr) {
                    fin->sig = nuevo;
                } else {
                    cab = nuevo;
                }
                fin = nuevo;
            } else {
                throw "Error: tipo de inserción no válido.";
            }
        }

        T eliminar(char tipo) {
            if (cab == nullptr) {
                throw "Error: La cola doble está vacía.";
            }

            T dato;
            if (tipo == 'I') { // eliminar por izquierda
                dato = cab->dato;
                Nodo<T>* tmp = cab;
                cab = cab->sig;
                if (cab != nullptr) {
                    cab->ant = nullptr;
                } else {
                    fin = nullptr;
                }
                delete tmp;
            } else if (tipo == 'D') { // eliminar por derecha
                dato = fin->dato;
                Nodo<T>* tmp = fin;
                fin = fin->ant;
                if (fin != nullptr) {
                    fin->sig = nullptr;
                } else {
                    cab = nullptr;
                }
                delete tmp;
            } else {
                throw "Error: tipo de eliminación no válido.";
            }

            return dato;
        }

        void mostrar() const {
            if (cab == nullptr) {
                cout << "La cola doble está vacía." << endl;
                return;
            }

            Nodo<T>* actual = cab;
            while (actual != nullptr) {
                cout << actual->dato << " ";
                actual = actual->sig;
            }

            cout << endl;
        }
};



#endif

