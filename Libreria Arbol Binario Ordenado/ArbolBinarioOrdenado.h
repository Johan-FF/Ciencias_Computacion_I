#ifndef ARBOLBINARIOORDENADO_H
#define ARBOLBINARIOORDENADO_H

#include <cstddef>
#include <EstructuraABO.h>

class ArbolBinarioOrdenado{
    public:
        nodo *arbol;
        int tam;

    private:
        ArbolBinarioOrdenado(int tam);
        void insertar(int valor);
        void eliminar(int valor);
};

ArbolBinarioOrdenado::ArbolBinarioOrdenado(int tam_){
    this->tam = tam_;
    this->arbol = NULL;
}

void ArbolBinarioOrdenado::insertar(int valor){
    if( this->arbol==nullptr ){
        this->arbol = new nodo;
        this->arbol->clave = valor;
    } else {   
        nodo *aux;
        aux = arbol;
        while( aux!=nullptr )
            aux = valor>aux->clave ? aux->der : aux->izq; 
        aux->clave = valor;
    }
}

// falta 
void ArbolBinarioOrdenado::eliminar(int valor){
    if( this->arbol==nullptr ){
        this->arbol = new nodo;
        this->arbol->clave = valor;
    } else {   
        nodo *aux;
        aux = arbol;
        while( aux!=nullptr )
            aux = valor>aux->clave ? aux->der : aux->izq; 
        aux->clave = valor;
    }
}

#endif