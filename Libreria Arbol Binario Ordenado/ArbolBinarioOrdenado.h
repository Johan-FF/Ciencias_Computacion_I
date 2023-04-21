#ifndef ARBOLBINARIOORDENADO_H
#define ARBOLBINARIOORDENADO_H

#include <cstddef>
#include <iostream>

#include "PilaDinamica.h"
#include "Cola.h"


class ArbolBinarioOrdenado{
    private:
    	
		struct nodo{
		    int clave, izq, der;
		    
		    nodo() : clave(0), izq(0), der(0) {}
		};

    	Cola<int> *colaInorden;
    	Cola<int> *colaPreorden;
    	Cola<int> *colaPostorden;
    	
    	int tam;

    public:
    	
    	nodo *arbol;
    	
        ArbolBinarioOrdenado(int tam);
        void insertar(int valor);
        void eliminar(int valor);
        
        int getRaiz(){return arbol[0].izq;};
        ~ArbolBinarioOrdenado(){delete[] arbol;};
        
        int buscarCampoVacio();
        
        //Recorrido de arboles por cola
        void inorden(int inicio);
        void preorden(int inicio);
        void postorden(int inicio);
};

ArbolBinarioOrdenado::ArbolBinarioOrdenado(int tam_){
    this->arbol = new nodo[tam_+1];
    /*Inicializamos las colas para los recorridos*/
    this->colaInorden = new Cola<int>();
    this->colaPreorden = new Cola<int>();
    this->colaPostorden = new Cola<int>();
    for(int i=0; i<=tam_; i++){
        this->arbol[i].clave = 0;
        this->arbol[i].der = i+1;
        this->arbol[i].izq = 0;
    }
    this->tam = tam_;
    this->arbol[tam_].der = this->arbol[tam_].izq = 0;
}

int ArbolBinarioOrdenado::buscarCampoVacio() {
    for (int i = 1; i < this->tam; i++) {
        if (this->arbol[i].clave == 0) {
            return i;
        }
    }
    return -1; // Si no se encontró ningún campo vacío
}

void ArbolBinarioOrdenado::insertar(int valor){
    if( this->arbol[0].izq==0 ){
        int campo_vacio = buscarCampoVacio();
        this->arbol[campo_vacio].clave = valor;
        this->arbol[0].der = this->arbol[campo_vacio].der;
        this->arbol[campo_vacio].der = 0;
        this->arbol[0].izq = campo_vacio;
    } else {
        int posicion_padre, posicion_hijo = this->arbol[0].izq;
        while( posicion_hijo!=0 ){
            posicion_padre = posicion_hijo;
            posicion_hijo = this->arbol[posicion_hijo].clave>valor ? this->arbol[posicion_hijo].izq : this->arbol[posicion_hijo].der;
        }
        int campo_vacio = buscarCampoVacio();
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

void ArbolBinarioOrdenado::inorden(int inicio){
    Pila<int> pila; // Se crea una pila para almacenar los nodos que se visitarán
    int nodo_actual = inicio; // Se inicia el recorrido desde el nodo de inicio

    // Se recorre el árbol mientras el nodo actual no sea nulo o la pila no esté vacía
    while (nodo_actual != 0 || !pila.vacia()) {
        if (nodo_actual != 0) { // Si el nodo actual no es nulo
            pila.meter(nodo_actual); // Se agrega el nodo actual a la pila
            nodo_actual = this->arbol[nodo_actual].izq; // Se cambia al nodo izquierdo del actual
        } else { // Si el nodo actual es nulo
            if (!pila.vacia()) { // Si la pila no está vacía
                nodo_actual = pila.sacar(); // Se saca el último nodo de la pila y se asigna como actual
                this->colaInorden->insCola( this->arbol[nodo_actual].clave);
                nodo_actual = this->arbol[nodo_actual].der; // Se cambia al nodo derecho del actual
            }
        }
    }
    this->colaInorden->imprimirCola();
    std::cout<<std::endl; 
 }
 
void ArbolBinarioOrdenado::preorden(int inicio){
    Pila<int> pila; // Se crea una pila para almacenar los nodos que se visitarán
    pila.meter(inicio); // Se agrega el nodo de inicio a la pila

    // Se recorre el árbol mientras la pila no esté vacía
    while(!pila.vacia()){
        int nodo_actual = pila.sacar(); // Se saca el último nodo agregado a la pila
        this->colaPreorden->insCola(arbol[nodo_actual].clave); // Se imprime el valor del nodo actual

        // Si el nodo actual tiene un nodo derecho o izquierdo, se agregan a la pila
        if(this->arbol[nodo_actual].der != 0)
            pila.meter(this->arbol[nodo_actual].der);
        if(this->arbol[nodo_actual].izq != 0)
            pila.meter(this->arbol[nodo_actual].izq);
    }
    
    this->colaPreorden->imprimirCola();
    std::cout<<std::endl; 
}

void ArbolBinarioOrdenado::postorden(int inicio){
    // Creamos dos pilas, una para el recorrido y otra para almacenar los nodos visitados
    Pila<int> pila1;
    Pila<int> pila2;
    // Insertamos el nodo de inicio en la primera pila
    pila1.meter(inicio);
    // Realizamos el recorrido en preorden
    while (!pila1.vacia()) {
        // Sacamos el nodo actual de la pila
        int nodo_actual = pila1.sacar();
        // Insertamos el nodo actual en la segunda pila
        pila2.meter(nodo_actual);
        // Insertamos los nodos hijos en la pila en orden inverso para que sean visitados en el orden correcto
        if (this->arbol[nodo_actual].izq != 0) {
            pila1.meter(this->arbol[nodo_actual].izq);
        }
        if (this->arbol[nodo_actual].der != 0) {
            pila1.meter(this->arbol[nodo_actual].der);
        }
    }
    // Imprimimos los nodos visitados en la segunda pila, que corresponden al recorrido en postorden
    while (!pila2.vacia()) {
        int nodo_actual = pila2.sacar();
        this->colaPostorden->insCola(arbol[nodo_actual].clave);
    }
    
    this->colaPostorden->imprimirCola();
    std::cout<<std::endl;
}


#endif
