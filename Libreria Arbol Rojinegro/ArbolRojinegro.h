#ifndef ARBOLROJINEGRO_H
#define ARBOLROJINEGRO_H

#define BLACK 1
#define RED 0

#include <iostream>

using namespace std;


struct Nodo {
    int valor;
    bool color;
    Nodo *subarbolIzquierdo, *subarbolDerecho, *padre;

    // Constructor por defecto
    Nodo() : valor(0), color(RED), subarbolIzquierdo(nullptr), subarbolDerecho(nullptr), padre(nullptr) { } 
    Nodo(int valor) : valor(valor), color(RED), subarbolIzquierdo(nullptr), subarbolDerecho(nullptr), padre(nullptr) { } 
    // M�todo que devuelve el abuelo del nodo
    Nodo* abuelo() {
        if(padre == nullptr){
            return nullptr;
        }
        return padre->padre;
    }

    // M�todo que devuelve el t�o del nodo
    Nodo* tio() {
        if(abuelo() == nullptr) {
            return nullptr;
        }
        if(padre == abuelo()->subarbolDerecho)
            return abuelo()->subarbolIzquierdo;
        else
            return abuelo()->subarbolDerecho;
    }

    // M�todo que devuelve el hermano del nodo
    Nodo* hermano() {
        if(padre->subarbolIzquierdo == this)
            return padre->subarbolDerecho;
        else
            return padre->subarbolIzquierdo;
    }
 };
 
 
class ArbolRojoNegro {
private:
	
	Nodo *raiz, *NIL;    

public:
	
    // Constructor del �rbol binario de b�squeda
	ArbolRojoNegro() {
	    NIL = new Nodo();
	    NIL->color = BLACK;
	    raiz = NIL;
	}

	// Destructor del �rbol binario de b�squeda
	~ArbolRojoNegro() {
	    destruir(raiz);
	    NIL->padre = nullptr; // Establece el puntero padre del nodo NIL a nullptr
	    delete NIL;
	}

	void destruir(Nodo *p) {
	    if (p != nullptr && p != NIL) {
	        destruir(p->subarbolIzquierdo);
	        destruir(p->subarbolDerecho);
	        p->subarbolIzquierdo = nullptr;
	        p->subarbolDerecho = nullptr;
	        if (p->padre != nullptr) {
	            if (p->padre->subarbolIzquierdo == p) {
	                p->padre->subarbolIzquierdo = nullptr;
	            } else {
	                p->padre->subarbolDerecho = nullptr;
	            }
	        }
	        delete p;
	    }
	}

	
	// M�todo para recorrido inorden del �rbol
	void inorder() {
	    if(raiz == NIL)
	        return;
	    inorder (raiz);
	    cout << endl;
	}
	
	// Realiza una rotaci�n a la derecha en el nodo p
	void rotar_derecha(Nodo *p){
	    // Obtiene el abuelo, padre e hijo derecho del nodo p
	    Nodo *gp = p->abuelo();
	    Nodo *fa = p->padre;
	    Nodo *y = p->subarbolIzquierdo;
	 
	    // Realiza la rotaci�n a la derecha
	    fa->subarbolDerecho = y;
	    if(y != NIL)
	        y->padre = fa;
	 
	    p->subarbolIzquierdo = fa;
	    fa->padre = p;
	 
	    if(raiz == fa)
	        raiz = p;
	 
	    p->padre = gp;
	    if(gp != nullptr){
	        if(gp->subarbolDerecho == fa)
	            gp->subarbolDerecho = p;
	        else
	            gp->subarbolIzquierdo = p;
	    }
	    // Actualiza el puntero "padre" del nodo fa
	    fa->padre = p;
	}
	
	// Realiza una rotaci�n a la izquierda en el nodo p
	void rotar_izquierda(Nodo *p){
	    // Si el padre es nulo, el nodo p es la ra�z
	    if(p->padre == nullptr){
	        raiz = p;
	        return;
	    }
	    
	    // Obtiene el abuelo, padre e hijo izquierdo del nodo p
	    Nodo *gp = p->abuelo();
	    Nodo *fa = p->padre;
	    Nodo *y = p->subarbolDerecho;
	 
	    // Realiza la rotaci�n a la izquierda
	    fa->subarbolIzquierdo = y;
	    if(y != NIL)
	        y->padre = fa;
	 
	    p->subarbolDerecho = fa;
	    fa->padre = p;
	 
	    if(raiz == fa)
	        raiz = p;
	    p->padre = gp;
	    
	    if(gp != nullptr){
	        if(gp->subarbolDerecho == fa)
	            gp->subarbolDerecho = p;
	        else
	            gp->subarbolIzquierdo = p;
	    }
	    // Actualiza el puntero "padre" del nodo y
	    fa->padre = p;
	}

	
	void insertar(int valor){
	    // Inicializamos los punteros padre y actual como NIL y la ra�z del �rbol, respectivamente
	    Nodo *padre = NIL;
	    Nodo *actual = raiz;
	
	    // Mientras no lleguemos al final del �rbol
	    while(actual != NIL){
	        // Movemos el puntero padre al nodo actual
	        padre = actual;
	        // Si el valor a insertar es menor al valor del nodo actual
	        if(valor < actual->valor)
	            // Movemos el puntero actual al sub�rbol izquierdo
	            actual = actual->subarbolIzquierdo;
	        // Si el valor a insertar es mayor o igual al valor del nodo actual
	        else
	            // Movemos el puntero actual al sub�rbol derecho
	            actual = actual->subarbolDerecho;
	    }
	
	    // Creamos un nuevo nodo con el valor a insertar
	    Nodo *nuevo_nodo = new Nodo(valor);
	    // Establecemos el padre del nuevo nodo como el �ltimo nodo visitado durante la b�squeda
	    nuevo_nodo->padre = padre;
	    // Si el padre es NIL, el nuevo nodo es la ra�z del �rbol
	    if(padre == NIL)
	        raiz = nuevo_nodo;
	    // Si el valor a insertar es menor al valor del padre, insertamos el nodo en el sub�rbol izquierdo del padre
	    else if(valor < padre->valor)
	        padre->subarbolIzquierdo = nuevo_nodo;
	    // Si el valor a insertar es mayor o igual al valor del padre, insertamos el nodo en el sub�rbol derecho del padre
	    else
	        padre->subarbolDerecho = nuevo_nodo;
	
	    // Inicializamos los sub�rboles izquierdo y derecho del nuevo nodo como NIL
	    nuevo_nodo->subarbolIzquierdo = NIL;
	    nuevo_nodo->subarbolDerecho = NIL;
	    // Establecemos el color del nuevo nodo como rojo
	    nuevo_nodo->color = RED;
	
	    // Llamamos al m�todo arreglar_arbol para corregir cualquier violaci�n de las propiedades del �rbol rojo-negro
	    arreglar_arbol(nuevo_nodo);
	}
	
	void arreglar_arbol(Nodo *nodo) {
		
    Nodo *padre = NULL;
    Nodo *abuelo = NULL;
 
    while ((nodo != raiz) && (nodo->color != BLACK) &&
           (nodo->padre->color == RED)) {
 
        padre = nodo->padre;
        abuelo = nodo->abuelo();
 
        /*  Case A:
            El padre de nodo es el hijo izquierdo del abuelo de nodo */
        if (padre == abuelo->subarbolIzquierdo) {
 
            Nodo *tio = abuelo->subarbolDerecho;
 
            /* Caso 1:
               El t�o de nodo es de color RED, s�lo se necesita recoloraci�n */
            if (tio != NIL && tio->color == RED) {
                abuelo->color = RED;
                padre->color = BLACK;
                tio->color = BLACK;
                nodo = abuelo;
            }
 
            else {
                /* Caso 2:
                   nodo es el hijo derecho de su padre, se necesita una rotaci�n a la izquierda */
                if (nodo == padre->subarbolDerecho) {
                    rotar_izquierda(padre);
                    nodo = padre;
                    padre = nodo->padre;
                }
 
                /* Caso 3:
                   nodo es el hijo izquierdo de su padre, se necesita una rotaci�n a la derecha */
                rotar_derecha(abuelo);
                swap(padre->color, abuelo->color);
                nodo = padre;
            }
        }
 
        /* Case B:
           El padre de nodo es el hijo derecho del abuelo de nodo */
        else {
            Nodo *tio = abuelo->subarbolIzquierdo;
 
            /* Caso 1:
               El t�o de nodo es de color RED, s�lo se necesita recoloraci�n */
            if (tio != NIL && tio->color == RED) {
                abuelo->color = RED;
                padre->color = BLACK;
                tio->color = BLACK;
                nodo = abuelo;
            }
            else {
                /* Caso 2:
                   nodo es el hijo izquierdo de su padre, se necesita una rotaci�n a la derecha */
                if (nodo == padre->subarbolIzquierdo) {
                    rotar_derecha(padre);
                    nodo = padre;
                    padre = nodo->padre;
                }
 
                /* Caso 3:
                   nodo es el hijo derecho de su padre, se necesita una rotaci�n a la izquierda */
                rotar_izquierda(abuelo);
                swap(padre->color, abuelo->color);
                nodo = padre;
            }
        }
    }
 
    raiz->color = BLACK;
}


    void inorder(Nodo *p){
        if(p == NIL)
            return;
 
        if(p->subarbolDerecho)
            inorder(p->subarbolIzquierdo);
 
        cout << p->valor << " ";
                
        if(p->subarbolIzquierdo)
            inorder(p->subarbolDerecho);
    }
	
	Nodo* get_raiz() {
        return raiz;
    }  
};

#endif



