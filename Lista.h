#include <cstddef>
#ifndef LISTA_H
#define LISTA_H

template <typename T>
struct nodo {
    T dato;
    nodo<T> *sig;
};

template <typename T>
class Lista {
    private:
        nodo<T> *cab;
        nodo<T> *cen;
        int tam;

        bool posicion_valida(int posicion);
        nodo<T>* encontrar_posicion_anterior(int posicion);
    public:
        Lista() {cen=cab=NULL; tam=0;};
        int getTam() {return tam;};
        bool lista_vacia();
        void insertar(T dato, int posicion);
        void insertar_final(T dato);
        void insertar_inicio(T dato);
        bool borrar(int posicion);
        T buscar(int posicion);
        bool modificar(T infoNueva, int posicion);
};

// PRIVATE

template <typename T>
bool Lista<T>::posicion_valida(int posicion) {
    // Se verifica que la posicion no sea negativa ni mayor al tamaño de la lista
    if(posicion<0 || posicion>this->tam) return false;
    return true;
}

template <typename T>
nodo<T>* Lista<T>::encontrar_posicion_anterior(int posicion) {
    // Recorrer la lista para encontrar la posicion 
    nodo<T> *siguiente = this->cab->sig;
    for (int i=0; i<posicion-1; i++) {
        siguiente = siguiente->sig;
    }
    return siguiente;
}

// PUBLIC

template <typename T>
bool Lista<T>::lista_vacia() {
    if( cab==NULL )
        return true;
    return false;
}

template <typename T>
void Lista<T>::insertar(T dato, int posicion) {
    // Se verifica que no ingrese posiciones negativas
    if( this->posicion_valida(posicion) ) {
        // Recorrer la lista para encontrar la posicion 
        nodo<T> *siguiente = this->encontrar_posicion_anterior(posicion);
        // Crear un nuevo elemento
        nodo<T> *nuevo;
        nuevo = new nodo<T>;
        nuevo->dato = dato;
        // Al anterior elemento se le asigna el nuevo elemento
        siguiente = nuevo;
        // Se avanza una posición en la lista para enlazar el siguiente al nuevo
        siguiente = siguiente->sig;
        nuevo->sig = siguiente;
        // Si el siguiente es el ultimo se actualiza el valor del centinela
        if( siguiente==NULL ) {
            this->cen = nuevo;
        }
        // Aumentar el numero de elementos
        this->tam+=1;
    }
}

template <typename T>
void Lista<T>::insertar_final(T dato) {
    // Crear un nuevo elemento
    nodo<T> *nuevo;
    nuevo = new nodo<T>;
    nuevo->dato = dato;
    nuevo->sig = NULL;
    // Enlazarlo al centinela
    cen->sig = nuevo;
    // Actualizar el valor de centinela
    cen = nuevo;
    // Aumentar el numero de elementos
    this->tam+=1;    
}

template <typename T>
void Lista<T>::insertar_inicio(T dato) {
    // Crear un nuevo elemento
    nodo<T> *nuevo;
    nuevo = new nodo<T>;
    nuevo->dato = dato;
    // Enlazar al primer elemento
    if( *this->cab->sig!=0 ){
        nuevo->sig = cab->sig;
    } else {
        nuevo->sig = 0;
    }
    // Actualizar el valor de la cabecera
    this->cab->sig = nuevo;
    // Aumentar el numero de elementos
    this->tam+=1;
}

template <typename T>
bool Lista<T>::borrar(int posicion) {
    if( this->posicion_valida(posicion) ) {
        // Recorrer la lista para encontrar la posicion 
        nodo<T> *siguiente = this->encontrar_posicion_anterior(posicion);
        // Guardamos el nodo para eliminarlo
        nodo<T> *nodoAEliminar = siguiente->sig;
        // Asignamos el nuevo orden 
        siguiente->sig = siguiente->sig->sig;
        // Eliminamos el nodo
        delete nodoAEliminar;
        // Disminuimos la cantidad de elementos
        this->tam-=1;

        return true;
    }
    return false;
}

template <typename T>
T Lista<T>::buscar(int posicion) {
    if( this->posicion_valida(posicion) ) {
        // Recorrer la lista para encontrar la posicion
        nodo<T> *siguiente = this->encontrar_posicion_anterior(posicion);
        siguiente = siguiente->sig;
        // Retornamos la informacion
        return siguiente->dato;
    }
    T aux;
    return aux;
}

template <typename T>
bool Lista<T>::modificar(T infoNueva, int posicion){
    if( this->posicion_valida(posicion) ) {
        // Recorrer la lista para encontrar la posicion
        nodo<T> *siguiente = this->encontrar_posicion_anterior(posicion);
        siguiente = siguiente->sig;
        // Se modifica la informacion
        siguiente->dato = infoNueva;

        return true;
    }
    return false;
}

#endif
