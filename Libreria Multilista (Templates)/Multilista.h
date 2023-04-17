
#ifndef MULTILISTA_H
#define MULTILISTA_H

#include <cstdlib>
#include <algorithm>
#include <cstring>
#include "Estructura.h"
#include "Lista.h"

template <typename dato_1, typename dato_2, typename Tipo, typename acceso>
class Multilista{
    private:
        nodo<dato_1, dato_2, acceso> *multi;
        Lista<Tipo, acceso> *k;
        int fin, max;

        void agregar_codigo( nodo<dato_1, dato_2, acceso>* elemento, acceso codigo);
        void agregar_nombre( nodo<dato_1, dato_2, acceso>* elemento, Tipo nombre);
        void agregar_carrera( nodo<dato_1, dato_2, acceso>* elemento, Tipo carrera);
        void agregar_actividad( nodo<dato_1, dato_2, acceso>* elemento, Tipo actividad);
    public:
        Multilista(int num_elementos, int num_cabeceras);
        void agregar_cabecera(cabecera<Tipo, acceso> *elemento);
        void insertar(nodo<dato_1, dato_2, acceso> *elemento);
        bool multilista_vacia();
};

template <typename dato_1, typename dato_2, typename Tipo, typename acceso>
Multilista<dato_1, dato_2, Tipo, acceso>::Multilista(int num_elementos, int num_cabeceras){
    this->multi=NULL;
    this->fin=0;
    this->max = num_elementos;
    this->k = new Lista<Tipo, acceso>;
    this->k->setMax(num_cabeceras);
};

template <typename dato_1, typename dato_2, typename Tipo, typename acceso>
void Multilista<dato_1, dato_2, Tipo, acceso>::agregar_cabecera(cabecera<Tipo, acceso> *elemento){
    this->k->insertar_final(*elemento);
};

template <typename dato_1, typename dato_2, typename Tipo, typename acceso>
bool Multilista<dato_1, dato_2, Tipo, acceso>::multilista_vacia(){
    return this->fin==0;
};

template <typename dato_1, typename dato_2, typename Tipo, typename acceso>
void Multilista<dato_1, dato_2, Tipo, acceso>::insertar(nodo<dato_1, dato_2, acceso> *elemento){
    if( multi==nullptr ){
        this->multi->codigo.dato = elemento->codigo.dato;
        this->multi->nombre.dato = elemento->nombre.dato;
        this->multi->carrera.dato = elemento->carrera.dato;
        this->multi->actividad.dato = elemento->actividad.dato;
        this->multi->sig = NULL;
        this->multi->sig_nodo = new nodoSig<acceso>;
        this->multi->sig_nodo->sig_codigo = 0;
        this->multi->sig_nodo->sig_nombre = 0;
        this->multi->sig_nodo->sig_carrera = 0;
        this->multi->sig_nodo->sig_actividad = 0;
    } else if ( this->max>this->fin ){
        this->fin++;
        nodo<dato_1, dato_2, acceso> *aux;
        aux = new nodo<dato_1, dato_2, acceso>;
        aux->codigo.dato = elemento->codigo.dato;
        aux->nombre.dato = elemento->nombre.dato;
        aux->carrera.dato = elemento->carrera.dato;
        aux->actividad.dato = elemento->actividad.dato;
        aux->sig_nodo = new nodoSig<acceso>;

        this->agregar_codigo( aux, elemento->codigo.dato );
        this->agregar_nombre( aux, elemento->nombre.dato );
        this->agregar_carrera( aux, elemento->carrera.dato );
        this->agregar_actividad( aux, elemento->actividad.dato );
    }
};

template <typename dato_1, typename dato_2, typename Tipo, typename acceso>
void Multilista<dato_1, dato_2, Tipo, acceso>::agregar_codigo(  nodo<dato_1, dato_2, acceso>* elemento, acceso codigo){
    acceso posicion = (*this->k->buscar('Codigo')).ubicacion;
    nodo<dato_1, dato_2, acceso> *ant, *sig;
    do{
        ant = this->multi;
        sig = this->multi->sig;
        for(int j=0; j<posicion-1; j++){
            ant = ant->sig;
            sig = sig->sig;
        }
        posicion = ant->sig_nodo->sig_codigo;
    } while( posicion!=0 && !(ant->codigo.dato>codigo && sig->codigo.dato<codigo) );
    elemento->sig_nodo->sig_codigo = ant->sig_nodo->sig_codigo;
    ant->sig_nodo->sig_codigo = this->fin;
};

template <typename dato_1, typename dato_2, typename Tipo, typename acceso>
void Multilista<dato_1, dato_2, Tipo, acceso>::agregar_nombre( nodo<dato_1, dato_2, acceso>* elemento, Tipo nombre){
    acceso posicion = (*this->k->buscar('Nombre')).ubicacion;
    nodo<dato_1, dato_2, acceso> *ant, *sig;
    Tipo nombres[3];
    int posicion_nombre = -1;
    do{
        ant = this->multi;
        sig = this->multi->sig;
        for(int j=0; j<posicion-1; j++){
            ant = ant->sig;
            sig = sig->sig;
        };
        posicion = ant->sig_nodo->sig_nombre;
        nombres[0] = nombre;
        nombres[1] = sig->nombre.dato;
        nombres[2] = ant->nombre.dato;
        int n = sizeof(nombres)/sizeof(nombres[0]); // Obtenemos el tamaño del array
        sort(nombres, nombres + n, [](const char* a, const char* b) { 
            return strcmp(a, b) < 0; // Comparador para ordenar alfabéticamente
        });
        if(nombres[1]==nombre)
            posicion_nombre = 2;
    } while( posicion!=0 && posicion_nombre!=2 );
    elemento->sig_nodo->sig_nombre = ant->sig_nodo->sig_nombre;
    ant->sig_nodo->sig_nombre = this->fin;
}

template <typename dato_1, typename dato_2, typename Tipo, typename acceso>
void Multilista<dato_1, dato_2, Tipo, acceso>::agregar_carrera( nodo<dato_1, dato_2, acceso>* elemento, Tipo carrera){
    acceso posicion = (*this->k->buscar(carrera)).ubicacion;
    nodo<dato_1, dato_2, acceso> *ant, *sig;
    do{
        ant = this->multi;
        sig = this->multi->sig;
        for(int j=0; j<posicion-1; j++){
            ant = ant->sig;
            sig = sig->sig;
        }
        posicion = ant->sig_nodo->sig_carrera;
    } while( posicion!=0 );
    elemento->sig_nodo->sig_carrera = 0;
    ant->sig_nodo->sig_carrera = this->fin;
}

template <typename dato_1, typename dato_2, typename Tipo, typename acceso>
void Multilista<dato_1, dato_2, Tipo, acceso>::agregar_actividad( nodo<dato_1, dato_2, acceso>* elemento, Tipo actividad){
    cabecera<Tipo, acceso> *cabAux = this->k->buscar(actividad);
    elemento->sig_nodo->sig_actividad = cabAux->ubicacion;
    cabAux->ubicacion = this->fin;
}

#endif