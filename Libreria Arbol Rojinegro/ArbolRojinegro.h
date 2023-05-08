#ifndef ARBOLROJINEGRO_H
#define ARBOLROJINEGRO_H

#define NEGRO 1
#define ROJO 0

#include <iostream>

using namespace std;


struct Nodo {
    int valor;
    bool color;
    Nodo *subArbolIzquierdo, *subArbolDerecho, *padre;

    // Constructor por defecto
    Nodo() : valor(0), color(ROJO), subArbolIzquierdo(nullptr), subArbolDerecho(nullptr), padre(nullptr) { } 
    Nodo(int valor) : valor(valor), color(ROJO), subArbolIzquierdo(nullptr), subArbolDerecho(nullptr), padre(nullptr) { } 

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
	    NIL->color = NEGRO;
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
	    
	    if(gp != nullptr){
	        if(gp->subArbolDerecho == fa)
	            gp->subArbolDerecho = p;
	        else
	            gp->subArbolIzquierdo = p;
	    }
	    // Actualiza el puntero "padre" del nodo y
	    fa->padre = p;
	}

	Nodo* obtener_hijo_mas_izquierdo(Nodo *p){
        if(p->subArbolIzquierdo == NIL)
            return p;
        return obtener_hijo_mas_izquierdo(p->subArbolIzquierdo);
    }

	bool eliminar_valor(int data) {
        return eliminar_hijo(raiz, data);
    }

	// Función que encuentra el nodo a eliminar
	bool eliminar_hijo(Nodo *p, int data){
		if(p->valor > data){
			if(p->subArbolIzquierdo == NIL){
				return false;
			}
			return eliminar_hijo(p->subArbolIzquierdo, data);
		} else if(p->valor < data){
			if(p->subArbolDerecho == NIL){
				return false;
			}
			return eliminar_hijo(p->subArbolDerecho, data);
		} else if(p->valor == data){ // Encuentra el nodo
			if(p->subArbolDerecho == NIL){
				eliminar_un_hijo (p); // Lo elimina
				return true;
			}
			// Hace el cambio con el derecho más a la izquierda
			Nodo *mas_peque = obtener_hijo_mas_izquierdo(p->subArbolDerecho);
			swap(p->valor, mas_peque->valor);
			// Ahora elimina el nodo que reemplaza al primer nodo que se elimina
			eliminar_un_hijo(mas_peque);

			return true;
		}else{
			return false;
		}
	}

	void eliminar_un_hijo(Nodo *p){
		Nodo *hijo = p->subArbolIzquierdo == NIL ? p->subArbolDerecho : p->subArbolIzquierdo;
		// Se elimina la raiz
		if(p->padre == NULL && p->subArbolIzquierdo == NIL && p->subArbolDerecho == NIL){
			p = NULL;
			raiz = p;
			return;
		}

		// Se elimina la raiz con un hijo
		if(p->padre == NULL){
			delete  p;
			hijo->padre = NULL;
			raiz = hijo;
			raiz->color = NEGRO;
			return;
		}

		// Se elimina un nodo cualquiera reemplazandolo por el hijo
		if(p->padre->subArbolIzquierdo == p){
			p->padre->subArbolIzquierdo = hijo;
		} else {
			p->padre->subArbolDerecho = hijo;
		}
		hijo->padre = p->padre;

		// Ajuste de colores
		if(p->color == NEGRO){
			if(hijo->color == ROJO){
				hijo->color = NEGRO;
			} else
				eliminar_casos_rojinegro(hijo); // Se ajustan colores en el arbol
		}

		delete p;
	}

	void eliminar_casos_rojinegro(Nodo *p){
		// Se ajusta negro si es la raiz
		if(p->padre == NULL){
			p->color = NEGRO;
			return;
		}

		// Caso 1: Hermano de p es rojo
		if(p->hermano()->color == ROJO) {
			p->padre->color = ROJO;
			p->hermano()->color = NEGRO;
			if(p == p->padre->subArbolIzquierdo)
				rotar_izquierda(p->hermano());
			else
				rotar_derecha(p->hermano());
		}
		// Caso 2: Hermano de p y sus hijs son negros
		if(p->padre->color == NEGRO && p->hermano()->color == NEGRO
				&& p->hermano()->subArbolIzquierdo->color == NEGRO
				&& p->hermano()->subArbolDerecho->color == NEGRO) {
			p->hermano()->color = ROJO;
			eliminar_casos_rojinegro(p->padre);
		}// Caso 3: el hijo del hermano de p, contrario a p es negro y el otro rojo
		else if(p->padre->color == ROJO && p->hermano()->color == NEGRO
					&& p->hermano()->subArbolIzquierdo->color == NEGRO
					&& p->hermano()->subArbolDerecho->color == NEGRO) {
			p->hermano()->color = ROJO;
			p->padre->color = NEGRO;
		} else { // Caso 4: Como mínimo el hijo del hermano de p es rojo
			if(p->hermano()->color == NEGRO) {
				if(p == p->padre->subArbolIzquierdo
						&& p->hermano()->subArbolIzquierdo->color == ROJO
						&& p->hermano()->subArbolDerecho->color == NEGRO) {
					p->hermano()->color = ROJO;
					p->hermano()->subArbolIzquierdo->color = NEGRO;
					rotar_derecha(p->hermano()->subArbolIzquierdo);
				} else if(p == p->padre->subArbolDerecho
							&& p->hermano()->subArbolIzquierdo->color == NEGRO
							&& p->hermano()->subArbolDerecho->color == ROJO) {
					p->hermano()->color = ROJO;
					p->hermano()->subArbolDerecho->color = NEGRO;
					rotar_izquierda(p->hermano()->subArbolDerecho);
				}
			}
			p->hermano()->color = p->padre->color;
			p->padre->color = NEGRO;
			if(p == p->padre->subArbolIzquierdo){
				p->hermano()->subArbolDerecho->color = NEGRO;
				rotar_izquierda(p->hermano());
			} else {
				p->hermano()->subArbolIzquierdo->color = NEGRO;
				rotar_derecha(p->hermano());
			}
		}
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
	            actual = actual->subArbolIzquierdo;
	        // Si el valor a insertar es mayor o igual al valor del nodo actual
	        else
	            // Movemos el puntero actual al sub�rbol derecho
	            actual = actual->subArbolDerecho;
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
	        padre->subArbolIzquierdo = nuevo_nodo;
	    // Si el valor a insertar es mayor o igual al valor del padre, insertamos el nodo en el sub�rbol derecho del padre
	    else
	        padre->subArbolDerecho = nuevo_nodo;
	
	    // Inicializamos los sub�rboles izquierdo y derecho del nuevo nodo como NIL
	    nuevo_nodo->subArbolIzquierdo = NIL;
	    nuevo_nodo->subArbolDerecho = NIL;
	    // Establecemos el color del nuevo nodo como rojo
	    nuevo_nodo->color = ROJO;
	
	    // Llamamos al m�todo arreglar_arbol para corregir cualquier violaci�n de las propiedades del �rbol rojo-negro
	    arreglar_arbol(nuevo_nodo);
	}

	void arreglar_arbol(Nodo *nodo) {
    Nodo *padre = NULL;
    Nodo *abuelo = NULL;
 
    while ((nodo != raiz) && (nodo->color != NEGRO) &&
           (nodo->padre->color == ROJO)) {
 
        padre = nodo->padre;
        abuelo = nodo->abuelo();
 
        /*  Case A:
            El padre de nodo es el hijo izquierdo del abuelo de nodo */
        if (padre == abuelo->subArbolIzquierdo) {
 
            Nodo *tio = abuelo->subArbolDerecho;
 
            /* Caso 1:
               El t�o de nodo es de color ROJO, s�lo se necesita recoloraci�n */
            if (tio != NIL && tio->color == ROJO) {
                abuelo->color = ROJO;
                padre->color = NEGRO;
                tio->color = NEGRO;
                nodo = abuelo;
            }
 
            else {
                /* Caso 2:
                   nodo es el hijo derecho de su padre, se necesita una rotaci�n a la izquierda */
                if (nodo == padre->subArbolDerecho) {
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
            Nodo *tio = abuelo->subArbolIzquierdo;
 
            /* Caso 1:
               El t�o de nodo es de color ROJO, s�lo se necesita recoloraci�n */
            if (tio != NIL && tio->color == ROJO) {
                abuelo->color = ROJO;
                padre->color = NEGRO;
                tio->color = NEGRO;
                nodo = abuelo;
            }
            else {
                /* Caso 2:
                   nodo es el hijo izquierdo de su padre, se necesita una rotaci�n a la derecha */
                if (nodo == padre->subArbolIzquierdo) {
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
 
    raiz->color = NEGRO;
}

    void inorder(Nodo *p){
        if(p == NIL){
			cout<<endl;
            return;
		}

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


