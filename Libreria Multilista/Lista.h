#ifndef LISTA_H
#define LISTA_H

#include "Estructura.h"
#include <string>

using namespace std;

class Lista {
    private:
        cabecera *cab, *cen;
        int tam, max;

        bool posicion_valida(int posicion);
        cabecera* encontrar_posicion(string dato);
        cabecera* encontrar_posicion(int posicion);
    public:
        Lista() {cen=cab=NULL; tam=0;};
        bool lista_vacia();
        cabecera* getCab() {return cab;};
        int getTam() {return tam;};
        void setMax(int cab) {max=cab;};
        void insertar_final(cabecera dato);
        cabecera* buscar(string dato);
        cabecera* buscar(int poscion);
};

bool Lista::lista_vacia() {
    return this->cab==nullptr; 
}

void Lista::insertar_final(cabecera dato) {
    if( this->max > this->tam ){
        // Crear un nuevo elemento
        cabecera *nuevo;
        nuevo = new cabecera;
        nuevo->dato = dato.dato;
        nuevo->ubicacion = dato.ubicacion;
        nuevo->sig = NULL;
        if( !this->lista_vacia() ){
            this->cen->sig = nuevo;
            this->cen = nuevo;
        } else {
            this->cab= nuevo;
            this->cen= nuevo;
        }
        this->tam+=1;
    }
};

cabecera* Lista::encontrar_posicion(string dato) {
    // Recorrer la lista para encontrar la posicion 
    cabecera *siguiente = this->cab->sig;
    while( siguiente->dato!=dato && siguiente->sig!=nullptr ){
        siguiente = siguiente->sig;
    }
    return siguiente;
};

cabecera* Lista::encontrar_posicion(int posicion) {
    // Recorrer la lista para encontrar la posicion 
    cabecera *siguiente = this->cab->sig;
    for (int i=0; i<posicion-1; i++) {
        siguiente = siguiente->sig;
    }
    return siguiente;
};

cabecera* Lista::buscar(string dato) {
    // Recorrer la lista para encontrar la posicion
    cabecera *siguiente = this->encontrar_posicion(dato);
    // Retornamos la informacion
    return siguiente;
};

bool Lista::posicion_valida(int posicion) {
    // Se verifica que la posicion no sea negativa ni mayor al tamaño de la lista
    if(posicion<0 || posicion>this->tam || posicion>this->max) return false;
    return true;
}

cabecera* Lista::buscar(int posicion) {
    if( this->posicion_valida(posicion) ) {
        // Recorrer la lista para encontrar la posicion
        cabecera *siguiente = this->encontrar_posicion(posicion);
        siguiente = siguiente->sig;
        // Retornamos la informacion
        return siguiente;
    }
    cabecera *aux;
    return aux;
};

#endif