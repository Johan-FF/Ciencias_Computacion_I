#ifndef MULTILISTA_H
#define MULTILISTA_H

#include "Estructura.h"
#include "Lista.h"
#include <algorithm>
#include <string>

using namespace std;

class Multilista{
    private:
        nodo *multi, *cab, *cen;;
        Lista *k;
        int fin, max;

        void agregar_codigo( nodo* elemento, int codigo);
        void agregar_nombre( nodo* elemento, string nombre);
        void agregar_carrera( nodo* elemento, string carrera);
        void agregar_actividad( nodo* elemento, string actividad);
    public:
        Multilista(int num_elementos, int num_cabeceras);
        int getMax(){return max;};
        void agregar_cabecera(cabecera *cabecera);
        void insertar(nodo *elemento);
        bool multilista_vacia();
};

Multilista::Multilista(int num_elementos, int num_cabeceras){
    this->multi=this->cab=this->cen=NULL;
    this->fin=0;
    this->max = num_elementos;
    this->k = new Lista;
    this->k->setMax(num_cabeceras);
};

void Multilista::agregar_cabecera(cabecera *cabecera){
    this->k->insertar_final( (*cabecera) );
};

bool Multilista::multilista_vacia(){
    return this->fin==0;
};

void Multilista::insertar(nodo *elemento){
    if( this->multilista_vacia() ){
        this->multi = new nodo;
        this->multi->codigo = elemento->codigo;
        this->multi->nombre = elemento->nombre;
        this->multi->carrera = elemento->carrera;
        this->multi->actividad = elemento->actividad;
        this->multi->sig = NULL;
        this->multi->sig_nodo = new nodoSig;
        this->multi->sig_nodo->sig_codigo = 0;
        this->multi->sig_nodo->sig_nombre = 0;
        this->multi->sig_nodo->sig_carrera = 0;
        this->multi->sig_nodo->sig_actividad = 0;
        this->cab= this->multi;
        this->cen= this->multi;
    } else if ( this->max > this->fin ){
        nodo *aux;
        aux = new nodo;
        aux->codigo = elemento->codigo;
        aux->nombre = elemento->nombre;
        aux->carrera = elemento->carrera;
        aux->actividad = elemento->actividad;
        aux->sig_nodo = new nodoSig;

        this->agregar_codigo( aux, elemento->codigo );
        this->agregar_nombre( aux, elemento->nombre );
        this->agregar_carrera( aux, elemento->carrera );
        this->agregar_actividad( aux, elemento->actividad );
        this->cen->sig = aux;
        this->cen = aux;
    }
    this->fin++;
};

void Multilista::agregar_codigo(  nodo* elemento, int codigo){
    int posicion = (*this->k->buscar("Codigo")).ubicacion;
    nodo *ant, *sig;
    do{
        ant = this->multi;
        sig = this->multi->sig;
        for(int j=0; j<posicion-1; j++){
            ant = ant->sig;
            sig = sig->sig;
        }
        posicion = ant->sig_nodo->sig_codigo;
    } while( posicion!=0 && !(ant->codigo>codigo && sig->codigo<codigo) );
    elemento->sig_nodo->sig_codigo = ant->sig_nodo->sig_codigo;
    ant->sig_nodo->sig_codigo = this->fin;
};

void Multilista::agregar_nombre( nodo* elemento, string nombre){
    int posicion = (*this->k->buscar("Nombre")).ubicacion;
    nodo *ant, *sig;
    string nombres[3];
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
        nombres[1] = sig->nombre;
        nombres[2] = ant->nombre;
        int n = sizeof(nombres)/sizeof(nombres[0]); // Obtenemos el tamaño del array
        sort(nombres, nombres + n);
        if(nombres[1]==nombre)
            posicion_nombre = 2;
    } while( posicion!=0 && posicion_nombre!=2 );
    elemento->sig_nodo->sig_nombre = ant->sig_nodo->sig_nombre;
    ant->sig_nodo->sig_nombre = this->fin;
}

void Multilista::agregar_carrera( nodo* elemento, string carrera){
    int posicion = (*this->k->buscar(carrera)).ubicacion;
    nodo *ant, *sig;
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

void Multilista::agregar_actividad( nodo* elemento, string actividad){
    cabecera *cabAux = this->k->buscar(actividad);
    elemento->sig_nodo->sig_actividad = cabAux->ubicacion;
    cabAux->ubicacion = this->fin;
}

#endif