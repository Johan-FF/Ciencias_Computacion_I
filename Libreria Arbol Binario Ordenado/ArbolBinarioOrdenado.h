#ifndef ARBOLBINARIOORDENADO_H
#define ARBOLBINARIOORDENADO_H

#include <iostream>
#include <cstddef>

using namespace std;

struct nodo{
    int clave, izq, der;
};

class ArbolBinarioOrdenado{
    private:
        nodo *arbol;

    public:
        ArbolBinarioOrdenado(int tam);
        void insertar(int valor);
        void eliminar(int valor);
        void imprimir_inorden(int i);
        void imprimir_preorden(int i);
        void imprimir_posorden(int i);
};

ArbolBinarioOrdenado::ArbolBinarioOrdenado(int tam_){
    this->arbol = new nodo[tam_+1];
    for(int i=0; i<=tam_; i++){
        this->arbol[i].clave = 0;
        this->arbol[i].der = i+1;
        this->arbol[i].izq = 0;
    }
    this->arbol[tam_].der = this->arbol[tam_].izq = 0;
    this->imprimir_inorden(0);
    cout<<endl;
    this->imprimir_preorden(0);
    cout<<endl;
    this->imprimir_posorden(0);
    cout<<endl;
}

void ArbolBinarioOrdenado::insertar(int valor){
    if( this->arbol[0].izq==0 ){
        int campo_vacio = this->arbol->der;
        this->arbol[campo_vacio].clave = valor;
        this->arbol[0].der = this->arbol[campo_vacio].der;
        this->arbol[campo_vacio].der = 0;
        this->arbol[0].izq = campo_vacio;
    } else {
        int posicion_padre, posicion_hijo = this->arbol->izq;
        while( posicion_hijo!=0 ){
            posicion_padre = posicion_hijo;
            posicion_hijo = this->arbol[posicion_hijo].clave>valor ? this->arbol[posicion_hijo].der : this->arbol[posicion_hijo].izq;
        }
        int campo_vacio = this->arbol->der;
        if( this->arbol[campo_vacio].der==0 )
            this->arbol->der = 0;
        else{
            this->arbol->der = this->arbol[campo_vacio].der;
            this->arbol[campo_vacio].clave = valor;
            this->arbol[campo_vacio].der = this->arbol[campo_vacio].izq = 0;
            this->arbol[posicion_padre].clave>valor ? this->arbol[posicion_padre].der=campo_vacio : this->arbol[posicion_padre].izq=campo_vacio;
        }
    }
}

void ArbolBinarioOrdenado::eliminar(int valor){
    if( this->arbol[0].izq!=0 ){
        int posicion_padre, posicion_hijo = this->arbol->izq;
        while( posicion_hijo!=0 ){
            posicion_padre = posicion_hijo;
            if( this->arbol[posicion_hijo].clave==valor ) 
                break;
            posicion_hijo = this->arbol[posicion_hijo].clave>valor ? this->arbol[posicion_hijo].der : this->arbol[posicion_hijo].izq;
        }

        if( this->arbol[posicion_hijo].der==0 && this->arbol[posicion_hijo].izq==0 ){
            int campo_vacio = this->arbol[0].der;
            if( campo_vacio!=0 )
                this->arbol[posicion_hijo].der = this->arbol[campo_vacio].der;
            this->arbol[posicion_hijo].clave = 0;
            this->arbol[0].der = posicion_hijo;
            posicion_hijo==this->arbol[posicion_padre].der ? this->arbol[posicion_padre].der = 0 : this->arbol[posicion_padre].izq = 0;
        } else if( this->arbol[posicion_hijo].der!=0 || this->arbol[posicion_hijo].izq!=0 ){
            if( this->arbol[posicion_hijo].der!=0 ){
                posicion_hijo==this->arbol[posicion_padre].der ? this->arbol[posicion_padre].der = this->arbol[posicion_hijo].der : this->arbol[posicion_padre].izq = this->arbol[posicion_hijo].der;
            } else {
                posicion_hijo==this->arbol[posicion_padre].der ? this->arbol[posicion_padre].der = this->arbol[posicion_hijo].izq : this->arbol[posicion_padre].izq = this->arbol[posicion_hijo].izq;
            }

            int campo_vacio = this->arbol[0].der;
            if( campo_vacio!=0 )
                this->arbol[posicion_hijo].der = this->arbol[campo_vacio].der;
            this->arbol[posicion_hijo].clave = 0;
            this->arbol[posicion_hijo].izq = 0;
            this->arbol[0].der = posicion_hijo;
        } else if( this->arbol[posicion_hijo].der!=0 && this->arbol[posicion_hijo].izq!=0 ){
            int posicion_padre_aux, posicion_aux = this->arbol[posicion_hijo].der;
            while( this->arbol[posicion_aux].izq!=0 )
                posicion_padre_aux = posicion_aux;
                posicion_aux = this->arbol[posicion_aux].izq;

            this->arbol[posicion_padre_aux].izq = this->arbol[posicion_aux].der!=0 ? this->arbol[posicion_aux].der : 0;

            posicion_hijo==this->arbol[posicion_padre].der ? this->arbol[posicion_padre].der = posicion_aux : this->arbol[posicion_padre].izq = posicion_aux;

            this->arbol[posicion_aux].der = this->arbol[posicion_hijo].der;
            this->arbol[posicion_aux].izq = this->arbol[posicion_hijo].izq;

            int campo_vacio = this->arbol[0].der;
            if( campo_vacio!=0 )
                this->arbol[posicion_hijo].der = this->arbol[campo_vacio].der;
            this->arbol[posicion_hijo].clave = 0;
            this->arbol[posicion_hijo].izq = 0;
            this->arbol[0].der = posicion_hijo;
        }
    }
    cout<<"Eliminando: "<<valor;
    cout<<endl;
    cout<<"inorden: ";
    this->imprimir_inorden(1);
    cout<<endl;
    cout<<"preorden: ";
    this->imprimir_preorden(1);
    cout<<endl;
    cout<<"posorden: ";
    this->imprimir_posorden(1);
    cout<<endl;
}

void ArbolBinarioOrdenado::imprimir_inorden(int i){
    if(this->arbol[i].izq!=0) imprimir_inorden(this->arbol[i].izq);
    cout<<this->arbol[i].clave<<",";
    cout<<this->arbol[i].izq<<",";
    cout<<this->arbol[i].der<<"  ";
    if(this->arbol[i].der!=0) imprimir_inorden(this->arbol[i].der);
}

void ArbolBinarioOrdenado::imprimir_preorden(int i){
    cout<<this->arbol[i].clave<<",";
    cout<<this->arbol[i].izq<<",";
    cout<<this->arbol[i].der<<"  ";
    if(this->arbol[i].izq!=0) imprimir_preorden(this->arbol[i].izq);
    if(this->arbol[i].der!=0) imprimir_preorden(this->arbol[i].der);
}

void ArbolBinarioOrdenado::imprimir_posorden(int i){
    if(this->arbol[i].izq!=0) imprimir_posorden(this->arbol[i].izq);
    if(this->arbol[i].der!=0) imprimir_posorden(this->arbol[i].der);
    cout<<this->arbol[i].clave<<",";
    cout<<this->arbol[i].izq<<",";
    cout<<this->arbol[i].der<<"  ";
}

#endif