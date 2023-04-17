#include <cstddef>
#include "Estructura.h"

#ifndef LISTA_H
#define LISTA_H

template <typename Tipo, typename acceso>
class Lista {
    private:
        cabecera<Tipo, acceso> *cab, *cen;
        int tam, max;

        bool posicion_valida(acceso posicion);
        cabecera<Tipo, acceso>* encontrar_posicion(Tipo dato);
        cabecera<Tipo, acceso>* encontrar_posicion(acceso posicion);
    public:
        Lista() {cen=cab=NULL; tam=0;};
        cabecera<Tipo, acceso>* getCab() {return cab;};
        int getTam() {return tam;};
        void setMax(int max) {max=max;};
        void insertar_final(cabecera<Tipo, acceso> dato);
        cabecera<Tipo, acceso>* buscar(Tipo dato);
        cabecera<Tipo, acceso>* buscar(acceso poscion);
};

template <typename Tipo, typename acceso>
void Lista<Tipo, acceso>::insertar_final(cabecera<Tipo, acceso> dato) {
    if( this->max>this->tam ){
        // Crear un nuevo elemento
        cabecera<Tipo, acceso> *nuevo;
        nuevo = new cabecera<Tipo, acceso>;
        nuevo->dato = dato.dato;
        nuevo->ubicacion = dato.ubicacion;
        nuevo->sig = NULL;
        // Enlazarlo al centinela
        cen->sig = nuevo;
        // Actualizar el valor de centinela
        cen = nuevo;
        // Aumentar el numero de elementos
        this->tam+=1;
    }
};

template <typename Tipo, typename acceso>
cabecera<Tipo, acceso>* Lista<Tipo, acceso>::encontrar_posicion(Tipo dato) {
    // Recorrer la lista para encontrar la posicion 
    cabecera<Tipo, acceso> *siguiente = this->cab->sig;
    while( siguiente->dato!=dato && siguiente->sig!=nullptr ){
        siguiente = siguiente->sig;
    }
    return siguiente;
};

template <typename Tipo, typename acceso>
cabecera<Tipo, acceso>* Lista<Tipo, acceso>::encontrar_posicion(acceso posicion) {
    // Recorrer la lista para encontrar la posicion 
    cabecera<Tipo, acceso> *siguiente = this->cab->sig;
    for (int i=0; i<posicion-1; i++) {
        siguiente = siguiente->sig;
    }
    return siguiente;
};

template <typename Tipo, typename acceso>
cabecera<Tipo, acceso>* Lista<Tipo, acceso>::buscar(Tipo dato) {
    // Recorrer la lista para encontrar la posicion
    cabecera<Tipo, acceso> *siguiente = this->encontrar_posicion(dato);
    // Retornamos la informacion
    return siguiente;
};

template <typename Tipo, typename acceso>
bool Lista<Tipo, acceso>::posicion_valida(acceso posicion) {
    // Se verifica que la posicion no sea negativa ni mayor al tamaño de la lista
    if(posicion<0 || posicion>this->tam || posicion>this->max) return false;
    return true;
}

template <typename Tipo, typename acceso>
cabecera<Tipo, acceso>* Lista<Tipo, acceso>::buscar(acceso posicion) {
    if( this->posicion_valida(posicion) ) {
        // Recorrer la lista para encontrar la posicion
        cabecera<Tipo, acceso> *siguiente = this->encontrar_posicion(posicion);
        siguiente = siguiente->sig;
        // Retornamos la informacion
        return siguiente;
    }
    cabecera<Tipo, acceso> *aux;
    return aux;
};

#endif