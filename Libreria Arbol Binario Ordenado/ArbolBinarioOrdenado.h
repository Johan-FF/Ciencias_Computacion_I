#ifndef ARBOLBINARIOORDENADO_H
#define ARBOLBINARIOORDENADO_H

#include <cstddef>

struct nodo{
    int clave, izq, der;
};

class ArbolBinarioOrdenado{
    private:

    public:
        nodo *arbol;
        ArbolBinarioOrdenado(int tam);
        void insertar(int valor);
        void eliminar(int valor);
        int getRaiz(){return arbol[0].izq;};
        ~ArbolBinarioOrdenado(){delete arbol;};
};

ArbolBinarioOrdenado::ArbolBinarioOrdenado(int tam_){
    this->arbol = new nodo[tam_+1];
    for(int i=0; i<=tam_; i++){
        this->arbol[i].clave = 0;
        this->arbol[i].der = i+1;
        this->arbol[i].izq = 0;
    }
    this->arbol[tam_].der = this->arbol[tam_].izq = 0;
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
            posicion_hijo = this->arbol[posicion_hijo].clave>valor ? this->arbol[posicion_hijo].izq : this->arbol[posicion_hijo].der;
        }
        int campo_vacio = this->arbol->der;
        this->arbol->der = this->arbol[campo_vacio].der==0 ? 0 : this->arbol[campo_vacio].der; 
        this->arbol[campo_vacio].clave = valor;
        this->arbol[campo_vacio].der = this->arbol[campo_vacio].izq = 0;
        this->arbol[posicion_padre].clave>valor ? this->arbol[posicion_padre].izq=campo_vacio : this->arbol[posicion_padre].der=campo_vacio;
    }
}

void ArbolBinarioOrdenado::eliminar(int valor){
    if( this->arbol[0].izq!=0 ){
        int posicion_padre, posicion_hijo = this->arbol->izq;
        while( posicion_hijo!=0 ){
            if( this->arbol[posicion_hijo].clave==valor ) 
                break;
            posicion_padre = posicion_hijo;
            posicion_hijo = this->arbol[posicion_hijo].clave>valor ? this->arbol[posicion_hijo].izq : this->arbol[posicion_hijo].der;
        }

        if( posicion_hijo==this->arbol[0].izq ){
            int posicion_padre_aux, posicion_aux = this->arbol[posicion_hijo].der;
            posicion_padre_aux = posicion_aux;
            while( this->arbol[posicion_aux].izq!=0 ){
                posicion_padre_aux = posicion_aux;
                posicion_aux = this->arbol[posicion_aux].izq;
            }

            this->arbol[posicion_padre_aux].izq = this->arbol[posicion_aux].der!=0 ? this->arbol[posicion_aux].der : 0;

            this->arbol[0].izq = posicion_aux;
            this->arbol[posicion_aux].der = this->arbol[1].der;
            this->arbol[posicion_aux].izq = this->arbol[1].izq;

            int campo_vacio = this->arbol[0].der;
            this->arbol[posicion_hijo].der = campo_vacio!=0 ? this->arbol[campo_vacio].der : 0;
            this->arbol[posicion_hijo].clave = 0;
            this->arbol[posicion_hijo].izq = 0;
            this->arbol[0].der = posicion_hijo;
        } else if( this->arbol[posicion_hijo].der==0 && this->arbol[posicion_hijo].izq==0 ){
            int campo_vacio = this->arbol[0].der;
            if( campo_vacio!=0 )
                this->arbol[posicion_hijo].der = campo_vacio;
            this->arbol[posicion_hijo].clave = 0;
            this->arbol[0].der = posicion_hijo;
            posicion_hijo==this->arbol[posicion_padre].der ? this->arbol[posicion_padre].der = 0 : this->arbol[posicion_padre].izq = 0;
        } else if( this->arbol[posicion_hijo].der!=0 && this->arbol[posicion_hijo].izq!=0 ){
            int posicion_padre_aux, posicion_aux = this->arbol[posicion_hijo].der;
            while( this->arbol[posicion_aux].izq!=0 ){
                posicion_padre_aux = posicion_aux;
                posicion_aux = this->arbol[posicion_aux].izq;
            }

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
        } else if( this->arbol[posicion_hijo].der!=0 || this->arbol[posicion_hijo].izq!=0 ){
            if( this->arbol[posicion_hijo].der!=0 ){
                posicion_hijo==this->arbol[posicion_padre].der ? this->arbol[posicion_padre].der = this->arbol[posicion_hijo].der : this->arbol[posicion_padre].izq = this->arbol[posicion_hijo].der;
            } else {
                posicion_hijo==this->arbol[posicion_padre].der ? this->arbol[posicion_padre].der = this->arbol[posicion_hijo].izq : this->arbol[posicion_padre].izq = this->arbol[posicion_hijo].izq;
            }

            int campo_vacio = this->arbol[0].der;
            if( campo_vacio!=0 )
                this->arbol[posicion_hijo].der = campo_vacio;
            this->arbol[posicion_hijo].clave = 0;
            this->arbol[posicion_hijo].izq = 0;
            this->arbol[0].der = posicion_hijo;
        }
    }
}

#endif