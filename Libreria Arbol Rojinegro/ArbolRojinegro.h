
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
        raiz = nullptr;
    }

    // Destructor del �rbol binario de b�squeda
    ~ArbolRojoNegro() {
        destruir(raiz);
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
	    
	    if(gp != NULL){
	        if(gp->subarbolDerecho == fa)
	            gp->subarbolDerecho = p;
	        else
	            gp->subarbolIzquierdo = p;
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
	        raiz->subarbolIzquierdo = NIL;
	        raiz->subarbolDerecho = NIL;
	        return;
	    }
	
	    // Se busca la posici�n adecuada para el nuevo nodo
	    Nodo *p = raiz;
	    Nodo *q = NIL; // Nodo padre del nodo actual "p"
	    while (p != NIL) {
	        q = p;
	        if (x < p->valor)
	            p = p->subarbolIzquierdo;
	        else
	            p = p->subarbolDerecho;
	    }
	
	    // Se crea el nuevo nodo y se establecen sus propiedades
	    Nodo *nuevo = new Nodo();
	    nuevo->valor = x;
	    nuevo->color = RED;
	    nuevo->padre = q;
	    nuevo->subarbolIzquierdo = NIL;
	    nuevo->subarbolDerecho = NIL;
	
	    // Se inserta el nuevo nodo como hijo del nodo padre q
	    if (x < q->valor)
	        q->subarbolIzquierdo = nuevo;
	    else
	        q->subarbolDerecho = nuevo;
	
	    // Se corrige el �rbol para mantener las propiedades del �rbol rojo-negro
	    insertarCorregir(nuevo);
	}
    
	void insertarCorregir(Nodo *n) {
	    // Si el padre del nodo actual es negro, no hay violaciones de las propiedades
	    while (n->padre->color == RED) {
	        // Si el padre es hijo izquierdo del abuelo
	        if (n->padre == n->padre->padre->subarbolIzquierdo) {
	            Nodo *y = n->padre->padre->subarbolDerecho; // T�o del nodo actual
	            // Caso 1: el t�o es rojo
	            if (y->color == RED) {
	                n->padre->color = BLACK;
	                y->color = BLACK;
	                n->padre->padre->color = RED;
	                n = n->padre->padre;
	            } else {
	                // Caso 2: el t�o es negro y el nodo actual es hijo derecho
	                if (n == n->padre->subarbolDerecho) {
	                    n = n->padre;
	                    rotar_izquierda(n);
	                }
	                // Caso 3: el t�o es negro y el nodo actual es hijo izquierdo
	                n->padre->color = BLACK;
	                n->padre->padre->color = RED;
	                rotar_derecha(n->padre->padre);
	            }
	        } else { // El padre es hijo derecho del abuelo
	            Nodo *y = n->padre->padre->subarbolIzquierdo; // T�o del nodo actual
	            // Caso 1: el t�o es rojo
	            if (y->color == RED) {
	                n->padre->color = BLACK;
	                y->color = BLACK;
	                n->padre->padre->color = RED;
	                n = n->padre->padre;
	            } else {
	                // Caso 2: el t�o es negro y el nodo actual es hijo izquierdo
	                if (n == n->padre->subarbolIzquierdo) {
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



