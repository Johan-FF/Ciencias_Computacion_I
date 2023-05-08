#ifndef ARBOLROJINEGRO_H
#define ARBOLROJINEGRO_H

#define BLACK 1
#define RED 0

#include <iostream>

using namespace std;


struct Nodo {
    int valor;
    bool color;
    Nodo *subArbolIzquierdo, *subArbolDerecho, *padre;

    // Constructor por defecto
    Nodo() : valor(0), color(RED), subArbolIzquierdo(nullptr), subArbolDerecho(nullptr), padre(nullptr) { } 

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
        if(padre == abuelo()->subArbolDerecho)
            return abuelo()->subArbolIzquierdo;
        else
            return abuelo()->subArbolDerecho;
    }

    // M�todo que devuelve el hermano del nodo
    Nodo* hermano() {
        if(padre->subArbolIzquierdo == this)
            return padre->subArbolDerecho;
        else
            return padre->subArbolIzquierdo;
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
        raiz = nullptr;
    }

    // Destructor del �rbol binario de b�squeda
    ~ArbolRojoNegro() {
        destruir(raiz);
        delete NIL;
    }

	void destruir(Nodo *p) {
	    if (p != nullptr && p != NIL) {
	        destruir(p->subArbolIzquierdo);
	        destruir(p->subArbolDerecho);
	        p->subArbolIzquierdo = nullptr;
	        p->subArbolDerecho = nullptr;
	        if (p->padre != nullptr) {
	            if (p->padre->subArbolIzquierdo == p) {
	                p->padre->subArbolIzquierdo = nullptr;
	            } else {
	                p->padre->subArbolDerecho = nullptr;
	            }
	        }
	        delete p;
	    }
	}

	// M�todo para recorrido inorden del �rbol
	void inorder() {
	    if(raiz == nullptr)
	        return;
	    inorder (raiz);
	    cout << endl;
	}

	    // Realiza una rotaci�n a la derecha en el nodo p
	void rotar_derecha(Nodo *p){
	    // Obtiene el abuelo, padre e hijo derecho del nodo p
	    Nodo *gp = p->abuelo();
	    Nodo *fa = p->padre;
	    Nodo *y = p->subArbolIzquierdo;
	 
	    // Realiza la rotaci�n a la derecha
	    fa->subArbolDerecho = y;
	    if(y != NIL)
	        y->padre = fa;
	 
	    p->subArbolIzquierdo = fa;
	    fa->padre = p;
	 
	    if(raiz == fa)
	        raiz = p;
	 
	    p->padre = gp;
	    if(gp != nullptr){
	        if(gp->subArbolDerecho == fa)
	            gp->subArbolDerecho = p;
	        else
	            gp->subArbolIzquierdo = p;
	    }
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
	    Nodo *y = p->subArbolDerecho;
	
	    // Realiza la rotaci�n a la izquierda
	    fa->subArbolIzquierdo = y;
	    if(y != NIL)
	        y->padre = fa;
	 
	    p->subArbolDerecho = fa;
	    fa->padre = p;
	 
	    if(raiz == fa)
	        raiz = p;
	    p->padre = gp;
	    
	    if(gp != NULL){
	        if(gp->subArbolDerecho == fa)
	            gp->subArbolDerecho = p;
	        else
	            gp->subArbolIzquierdo = p;
	    }
	}
	
		// M�todo para insertar un nuevo nodo al �rbol rojo-negro
	void insertar(int x) {
	    // Si el �rbol est� vac�o, se crea el nodo ra�z
	    if (raiz == nullptr) {
	        raiz = new Nodo();
	        raiz->valor = x;
	        raiz->color = BLACK; // El primer nodo siempre es negro
	        raiz->padre = NIL;
	        raiz->subArbolIzquierdo = NIL;
	        raiz->subArbolDerecho = NIL;
	        return;
	    }
	
	    // Se busca la posici�n adecuada para el nuevo nodo
	    Nodo *p = raiz;
	    Nodo *q = NIL; // Nodo padre del nodo actual "p"
	    while (p != NIL) {
	        q = p;
	        if (x < p->valor)
	            p = p->subArbolIzquierdo;
	        else
	            p = p->subArbolDerecho;
	    }
	
	    // Se crea el nuevo nodo y se establecen sus propiedades
	    Nodo *nuevo = new Nodo();
	    nuevo->valor = x;
	    nuevo->color = RED;
	    nuevo->padre = q;
	    nuevo->subArbolIzquierdo = NIL;
	    nuevo->subArbolDerecho = NIL;
	
	    // Se inserta el nuevo nodo como hijo del nodo padre q
	    if (x < q->valor)
	        q->subArbolIzquierdo = nuevo;
	    else
	        q->subArbolDerecho = nuevo;
	
	    // Se corrige el �rbol para mantener las propiedades del �rbol rojo-negro
	    insertarCorregir(nuevo);
	}

	void insertarCorregir(Nodo *n) {
	    // Si el padre del nodo actual es negro, no hay violaciones de las propiedades
	    while (n->padre->color == RED) {
	        // Si el padre es hijo izquierdo del abuelo
	        if (n->padre == n->padre->padre->subArbolIzquierdo) {
	            Nodo *y = n->padre->padre->subArbolDerecho; // T�o del nodo actual
	            // Caso 1: el t�o es rojo
	            if (y->color == RED) {
	                n->padre->color = BLACK;
	                y->color = BLACK;
	                n->padre->padre->color = RED;
	                n = n->padre->padre;
	            } else {
	                // Caso 2: el t�o es negro y el nodo actual es hijo derecho
	                if (n == n->padre->subArbolDerecho) {
	                    n = n->padre;
	                    rotar_izquierda(n);
	                }
	                // Caso 3: el t�o es negro y el nodo actual es hijo izquierdo
	                n->padre->color = BLACK;
	                n->padre->padre->color = RED;
	                rotar_derecha(n->padre->padre);
	            }
	        } else { // El padre es hijo derecho del abuelo
	            Nodo *y = n->padre->padre->subArbolIzquierdo; // T�o del nodo actual
	            // Caso 1: el t�o es rojo
	            if (y->color == RED) {
	                n->padre->color = BLACK;
	                y->color = BLACK;
	                n->padre->padre->color = RED;
	                n = n->padre->padre;
	            } else {
	                // Caso 2: el t�o es negro y el nodo actual es hijo izquierdo
	                if (n == n->padre->subArbolIzquierdo) {
	                    n = n->padre;
	                    rotar_derecha(n);
	                }
	                // Caso 3: el t�o es negro y el nodo actual es hijo derecho
	                n->padre->color = BLACK;
	                n->padre->padre->color = RED;
	                rotar_izquierda(n->padre->padre);
	            }
	        }
	    }
	    // La ra�z debe ser negra
	    raiz->color = BLACK;
	}

    void inorder(Nodo *p){
        if(p == NIL)
            return;

        if(p->subArbolDerecho)
            inorder(p->subArbolIzquierdo);

        cout << p->valor << " ";
                
        if(p->subArbolIzquierdo)
            inorder(p->subArbolDerecho);
    }

	Nodo* get_raiz() {
        return raiz;
    }  
};

#endif