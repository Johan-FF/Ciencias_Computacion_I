#ifndef ARBOLBINARIOORDENADO_H
#define ARBOLBINARIOORDENADO_H

#include <cstddef>
#include <iostream>

#include "PilaDinamica.h"
#include "Cola.h"

class ArbolBinarioOrdenado{
    private:
		struct nodo{
		    int clave, izq, der, padre, fb;
		    nodo() : clave(0), izq(0), der(0), padre(0) {}
		};

    	Cola<int> *colaInorden;
    	Cola<int> *colaPreorden;
    	Cola<int> *colaPostorden;

    	int tam;

        int obtener_altura(int posicion_nodo);
        int obtener_factor_balance(int posicion_nodo);
        void ajustar_factores_balance(int posicion_nodo);
        void rotar_simple(char tipo, int posicion_nodo);
        void rotar_doble(char tipo, int posicion_nodo);

        void eliminar_raiz(int posicion_hijo);
        void eliminar_nodo(int posicion_hijo, int posicion_padre);
        void eliminar_nodo_1hijo(int posicion_hijo, int posicion_padre);
        void eliminar_nodo_2hijo(int posicion_hijo, int posicion_padre);
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
        this->arbol[i].padre = 0;
        this->arbol[i].fb = 0;
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
    return -1; // Si no se encontr� ning�n campo vac�o
}

void ArbolBinarioOrdenado::insertar(int valor){
    if( this->arbol[0].izq==0 ){
        int campo_vacio = buscarCampoVacio();
        this->arbol[campo_vacio].clave = valor;
        this->arbol[0].der = this->arbol[campo_vacio].der;
        this->arbol[campo_vacio].der = 0;
        this->arbol[campo_vacio].padre = 0;
        this->arbol[campo_vacio].fb = 0;
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
        this->arbol[campo_vacio].padre = posicion_padre;
        this->arbol[campo_vacio].fb = 0;
        this->arbol[campo_vacio].der = this->arbol[campo_vacio].izq = 0;
        this->arbol[posicion_padre].clave>valor ? this->arbol[posicion_padre].izq=campo_vacio : this->arbol[posicion_padre].der=campo_vacio;
        this->ajustar_factores_balance(posicion_padre);
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
            this->eliminar_raiz(posicion_hijo);
        } else if( this->arbol[posicion_hijo].der==0 && this->arbol[posicion_hijo].izq==0 ){
            this->eliminar_nodo(posicion_hijo, posicion_padre);
        } else if( this->arbol[posicion_hijo].der!=0 && this->arbol[posicion_hijo].izq!=0 ){
            this->eliminar_nodo_2hijo(posicion_hijo, posicion_padre);
        } else if( this->arbol[posicion_hijo].der!=0 || this->arbol[posicion_hijo].izq!=0 ){
            this->eliminar_nodo_1hijo(posicion_hijo, posicion_padre);
        }
    }
}

void ArbolBinarioOrdenado::eliminar_raiz(int posicion_hijo){
    int posicion_padre_aux, posicion_aux = this->arbol[posicion_hijo].der;
    posicion_padre_aux = posicion_aux;
    while( this->arbol[posicion_aux].izq!=0 ){
        posicion_padre_aux = posicion_aux;
        posicion_aux = this->arbol[posicion_aux].izq;
    }

    this->arbol[posicion_padre_aux].izq = this->arbol[posicion_aux].der;
    this->arbol[this->arbol[posicion_aux].der].padre = posicion_padre_aux;

    this->arbol[0].izq = posicion_aux;
    this->arbol[this->arbol[1].der].padre = posicion_aux;
    this->arbol[this->arbol[1].izq].padre = posicion_aux;
    this->arbol[posicion_aux].der = this->arbol[1].der;
    this->arbol[posicion_aux].izq = this->arbol[1].izq;
    this->arbol[posicion_aux].padre = 0;

    int campo_vacio = this->arbol[0].der;
    this->arbol[posicion_hijo].der = campo_vacio!=0 ? this->arbol[campo_vacio].der : 0;
    this->arbol[posicion_hijo].clave = 0;
    this->arbol[posicion_hijo].izq = 0;
    this->arbol[0].der = posicion_hijo;

    this->ajustar_factores_balance(posicion_padre_aux);
}

void ArbolBinarioOrdenado::eliminar_nodo(int posicion_hijo, int posicion_padre){
    int campo_vacio = this->arbol[0].der;
    if( campo_vacio!=0 )
        this->arbol[posicion_hijo].der = campo_vacio;
    this->arbol[posicion_hijo].clave = 0;
    this->arbol[0].der = posicion_hijo;
    posicion_hijo==this->arbol[posicion_padre].der ? this->arbol[posicion_padre].der = 0 : this->arbol[posicion_padre].izq = 0;

    this->ajustar_factores_balance(posicion_padre);
}

void ArbolBinarioOrdenado::eliminar_nodo_2hijo(int posicion_hijo, int posicion_padre){
    int posicion_padre_aux, posicion_aux = this->arbol[posicion_hijo].der;
    while( this->arbol[posicion_aux].izq!=0 ){
        posicion_padre_aux = posicion_aux;
        posicion_aux = this->arbol[posicion_aux].izq;
    }

    this->arbol[posicion_padre_aux].izq = this->arbol[posicion_aux].der;
    this->arbol[this->arbol[posicion_aux].der].padre = posicion_padre_aux;

    posicion_hijo==this->arbol[posicion_padre].der ? this->arbol[posicion_padre].der = posicion_aux : this->arbol[posicion_padre].izq = posicion_aux;

    this->arbol[posicion_aux].padre = posicion_padre;
    this->arbol[posicion_aux].der = this->arbol[posicion_hijo].der;
    this->arbol[posicion_aux].izq = this->arbol[posicion_hijo].izq;

    int campo_vacio = this->arbol[0].der;
    if( campo_vacio!=0 )
        this->arbol[posicion_hijo].der = this->arbol[campo_vacio].der;
    this->arbol[posicion_hijo].clave = 0;
    this->arbol[posicion_hijo].izq = 0;
    this->arbol[0].der = posicion_hijo;

    this->ajustar_factores_balance(posicion_padre_aux);
}

void ArbolBinarioOrdenado::eliminar_nodo_1hijo(int posicion_hijo, int posicion_padre){
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

    this->ajustar_factores_balance(posicion_padre);
}

void ArbolBinarioOrdenado::ajustar_factores_balance(int posicion_nodo){
    if( !posicion_nodo==0 ){
        this->arbol[posicion_nodo].fb = this->obtener_factor_balance(posicion_nodo);
        if( this->arbol[posicion_nodo].fb<-1 ){
            this->arbol[ this->arbol[posicion_nodo].izq ].fb<0 ?
                this->rotar_simple('d', posicion_nodo):
                this->rotar_doble('i', posicion_nodo);
        } else if( this->arbol[posicion_nodo].fb>1 ){
            this->arbol[ this->arbol[posicion_nodo].der ].fb>0 ?
                this->rotar_simple('i', posicion_nodo):
                this->rotar_doble('d', posicion_nodo);
        } else {
            this->ajustar_factores_balance(this->arbol[posicion_nodo].padre);
        }
    }
}

int ArbolBinarioOrdenado::obtener_altura(int posicion_nodo) {
    if (posicion_nodo == 0)
        return 0;
    int altura_izq = obtener_altura(this->arbol[posicion_nodo].izq);
    int altura_der = obtener_altura(this->arbol[posicion_nodo].der);
    return 1 + max(altura_izq, altura_der);
}

int ArbolBinarioOrdenado::obtener_factor_balance(int posicion_nodo) {
    if (posicion_nodo == 0)
        return 0;
    int altura_izq = obtener_altura(this->arbol[posicion_nodo].izq);
    int altura_der = obtener_altura(this->arbol[posicion_nodo].der);
    return altura_der - altura_izq;
}

void ArbolBinarioOrdenado::rotar_simple(char tipo, int posicion_nodo){
    int padre = this->arbol[posicion_nodo].padre;
    if( tipo=='i' ){
        int hijo = tipo == 'i' ? this->arbol[posicion_nodo].der : this->arbol[posicion_nodo].izq;
        int nieto = tipo == 'i' ? this->arbol[hijo].izq : this->arbol[hijo].der;
        if(padre==0){
            this->arbol[0].izq = hijo;
            this->arbol[hijo].padre = 0;
        } else {
            this->arbol[padre].der == posicion_nodo ? this->arbol[padre].der = hijo : this->arbol[padre].izq = hijo;
            this->arbol[hijo].padre = padre;
            
        }
        this->arbol[hijo].izq = posicion_nodo;
        this->arbol[posicion_nodo].der = nieto;
        this->arbol[posicion_nodo].padre = hijo;
        if(nieto=!0)
            this->arbol[nieto].padre = posicion_nodo;
        this->ajustar_factores_balance(nieto);
        this->ajustar_factores_balance(posicion_nodo);
    } else if( tipo=='d' ){
        int hijo = tipo == 'd' ? this->arbol[posicion_nodo].izq : this->arbol[posicion_nodo].der;
        int nieto = tipo == 'd' ? this->arbol[hijo].der : this->arbol[hijo].izq;
        if(padre==0){
            this->arbol[0].izq = hijo;
            this->arbol[hijo].padre = 0;
        } else {
            this->arbol[padre].der == posicion_nodo ? this->arbol[padre].der = hijo : this->arbol[padre].izq = hijo;
            this->arbol[hijo].padre = padre;
        }
        this->arbol[hijo].der = posicion_nodo;
        this->arbol[posicion_nodo].izq = nieto;
        this->arbol[posicion_nodo].padre = hijo;
        if(nieto!=0)
            this->arbol[nieto].padre = posicion_nodo;
        this->ajustar_factores_balance(nieto);
        this->ajustar_factores_balance(posicion_nodo);
    }
}

void ArbolBinarioOrdenado::rotar_doble(char tipo, int posicion_nodo){
    int padre = this->arbol[posicion_nodo].padre;
    if( tipo=='i' ){
        int hijo = tipo == 'i' ? this->arbol[posicion_nodo].izq : this->arbol[posicion_nodo].der;
        int nieto = tipo == 'i' ? this->arbol[hijo].der : this->arbol[hijo].izq;
        if(padre==0){
            this->arbol[0].izq = nieto;
            this->arbol[nieto].padre = 0;
        } else {
            this->arbol[padre].der == posicion_nodo ? this->arbol[padre].der = nieto : this->arbol[padre].izq = nieto;
            this->arbol[nieto].padre = padre;
        }
        this->arbol[posicion_nodo].izq = this->arbol[nieto].der;
        if(this->arbol[nieto].der!=0)
            this->arbol[ this->arbol[nieto].der ].padre = posicion_nodo;
        this->arbol[hijo].der = this->arbol[nieto].izq;
        if(this->arbol[nieto].izq!=0)
            this->arbol[ this->arbol[nieto].izq ].padre = hijo;
        this->arbol[nieto].der = posicion_nodo;
        this->arbol[posicion_nodo].padre = nieto;
        this->arbol[nieto].izq = hijo;
        this->arbol[hijo].padre = nieto;
        this->ajustar_factores_balance(hijo);
        this->ajustar_factores_balance(posicion_nodo);
        this->ajustar_factores_balance(this->arbol[posicion_nodo].der);
    } else if( tipo=='d' ){
        int hijo = tipo == 'd' ? this->arbol[posicion_nodo].der : this->arbol[posicion_nodo].izq;
        int nieto = tipo == 'd' ? this->arbol[hijo].izq : this->arbol[hijo].der;
        if(padre==0){
            this->arbol[0].izq = nieto;
            this->arbol[nieto].padre = 0;
        } else {
            this->arbol[padre].der == posicion_nodo ? this->arbol[padre].der = nieto : this->arbol[padre].izq = nieto;
            this->arbol[nieto].padre = padre;
        }
        this->arbol[posicion_nodo].der = this->arbol[nieto].izq;
        if(this->arbol[nieto].izq!=0)
            this->arbol[ this->arbol[nieto].izq ].padre = posicion_nodo;
        this->arbol[hijo].izq = this->arbol[nieto].der;
        if(this->arbol[nieto].der!=0)
            this->arbol[ this->arbol[nieto].der ].padre = hijo;
        this->arbol[nieto].izq = posicion_nodo;
        this->arbol[posicion_nodo].padre = nieto;
        this->arbol[nieto].der = hijo;
        this->arbol[hijo].padre = nieto;
        this->ajustar_factores_balance(hijo);
        this->ajustar_factores_balance(posicion_nodo);
        this->ajustar_factores_balance(this->arbol[posicion_nodo].izq);
    }
}

void ArbolBinarioOrdenado::inorden(int inicio){
    Pila<int> pila; // Se crea una pila para almacenar los nodos que se visitar�n
    int nodo_actual = inicio; // Se inicia el recorrido desde el nodo de inicio

    // Se recorre el �rbol mientras el nodo actual no sea nulo o la pila no est� vac�a
    while (nodo_actual != 0 || !pila.vacia()) {
        if (nodo_actual != 0) { // Si el nodo actual no es nulo
            pila.meter(nodo_actual); // Se agrega el nodo actual a la pila
            nodo_actual = this->arbol[nodo_actual].izq; // Se cambia al nodo izquierdo del actual
        } else { // Si el nodo actual es nulo
            if (!pila.vacia()) { // Si la pila no est� vac�a
                nodo_actual = pila.sacar(); // Se saca el �ltimo nodo de la pila y se asigna como actual
                this->colaInorden->insCola( this->arbol[nodo_actual].clave);
                nodo_actual = this->arbol[nodo_actual].der; // Se cambia al nodo derecho del actual
            }
        }
    }
    this->colaInorden->imprimirCola();
    std::cout<<std::endl; 
 }

void ArbolBinarioOrdenado::preorden(int inicio){
    Pila<int> pila; // Se crea una pila para almacenar los nodos que se visitar�n
    pila.meter(inicio); // Se agrega el nodo de inicio a la pila

    // Se recorre el �rbol mientras la pila no est� vac�a
    while(!pila.vacia()){
        int nodo_actual = pila.sacar(); // Se saca el �ltimo nodo agregado a la pila
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