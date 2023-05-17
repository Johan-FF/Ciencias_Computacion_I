#ifndef ARBOLB_H
#define ARBOLB_H

#include <iostream>
#include <queue>
using namespace std;

struct nodo {
    int *claves;
    nodo **hijos;
    int Nclaves;
    bool hoja;
};

class arbolB {
    nodo *raiz;
    int d;

public:
    arbolB(int ord) {
        d = ord;
        raiz = crear_nodo();
        raiz->Nclaves = 0;
        raiz->hoja = true;
    }
    nodo *crear_nodo();
    nodo *get_raiz();
    int dividir_nodo(nodo *actual, nodo **hermano);
    void insertar(int clave);
    nodo *buscar_nodo(int clave, nodo *Actual, nodo **padre);
    int InsertarNodoNormal(int clave, nodo *Actual);
    void InsertarNodoLleno(int clave, nodo *Actual, nodo *padre);
    nodo *buscar_padre(int clave, nodo *Actual, nodo *padre);
    bool borrar(int clave);
    nodo *Unir_nodos(nodo *hizq, nodo *hDer, nodo *padre);
    void rotacion_derecha(int i, nodo *actual, nodo *hermano_izq, nodo *hijo);
    void rotacion_izquierda(int i, nodo *actual, nodo *hermano_der, nodo *hijo);
    void fusionar_nodos(int i, nodo *actual, nodo *hermano, nodo *hijo);
    void imprimirArbol();
};

nodo *arbolB::crear_nodo() {
    nodo *nuevo = new nodo;
    nuevo->claves = new int[2 * d - 1];
    nuevo->hijos = new nodo *[2 * d];
    nuevo->Nclaves = 0;
    nuevo->hoja = true;
    return nuevo;
}

nodo *arbolB::get_raiz() {
    return raiz;
}

void arbolB::insertar(int clave) {
    nodo *padre = NULL, *Actual = raiz;
    Actual = buscar_nodo(clave, Actual, &padre);
    if (Actual->Nclaves < 2 * d - 1)
        InsertarNodoNormal(clave, Actual);
    else
        InsertarNodoLleno(clave, Actual, padre);
}

nodo *arbolB::buscar_nodo(int clave, nodo *Actual, nodo **padre) {
    int i = 0;
    while ((i < Actual->Nclaves) && clave > Actual->claves[i])
        i++;
    if (Actual->hoja) {
        if (Actual == raiz)
            *padre = NULL;
        return Actual;
    } else {
        *padre = Actual;
        Actual = Actual->hijos[i];
        return buscar_nodo(clave, Actual, padre);
    }
}

int arbolB::InsertarNodoNormal(int clave, nodo *Actual) {
    int i, j;
    i = Actual->Nclaves;
    while ((i - 1) >= 0 && clave < Actual->claves[i - 1]) {
        Actual->claves[i] = Actual->claves[i - 1];
        if (!Actual->hoja) // si el nodo no es una hoja
            Actual->hijos[i + 1] = Actual->hijos[i];
        i--;
    }
    Actual->claves[i] = clave;
    (Actual->Nclaves)++;
    return i;
}

void arbolB::InsertarNodoLleno(int clave, nodo *Actual, nodo *padre) {
    int pos, sube;
    nodo *nuevo, *nivelad = NULL;
    sube = dividir_nodo(Actual, &nuevo);
    if (clave < sube) {
        Actual->claves[d - 1] = clave;
        (Actual->Nclaves)++;
    } else {
        nuevo->claves[d - 1] = clave;
        (nuevo->Nclaves)++;
    }
    if (Actual != raiz && padre->Nclaves < 2 * d - 1) {
        pos = InsertarNodoNormal(sube, padre);
        padre->hijos[pos] = Actual;
        padre->hijos[pos + 1] = nuevo;
    } else {
        if (Actual == raiz) {
            nivelad = crear_nodo();
            nivelad->hoja = false;
            nivelad->Nclaves = 1;
            nivelad->hijos[0] = Actual;
            nivelad->hijos[1] = nuevo;
        } else {
            nivelad = buscar_padre(padre->claves[0], padre, nivelad);
            InsertarNodoLleno(padre->claves[d - 1], padre, nivelad);
        }
    }
}

int arbolB::dividir_nodo(nodo *actual, nodo **hermano) {
    int i;
    nodo *nuevo = crear_nodo();
    nuevo->hoja = actual->hoja;
    for (i = 0; i < d - 1; i++)
        nuevo->claves[i] = actual->claves[i + d];
    if (!actual->hoja) {
        for (i = 0; i < d; i++)
            nuevo->hijos[i] = actual->hijos[i + d];
    }
    nuevo->Nclaves = actual->Nclaves = d - 1;
    return actual->claves[d - 1];
}

nodo *arbolB::buscar_padre(int clave, nodo *Actual, nodo *padre) {
    int i = 0;
    if (clave == Actual->claves[0])
        return padre;
    else {
        while (i < Actual->Nclaves && clave > Actual->claves[i])
            i++;
        padre = Actual;
        Actual = Actual->hijos[i];
        return buscar_padre(clave, Actual, padre);
    }
}

bool arbolB::borrar(int clave) {
    if (!raiz) {
        cout << "El arbol esta vacio." << endl;
        return false;
    }
    nodo *padre = NULL;
    nodo *actual = buscar_nodo(clave, raiz, &padre);
    int i = 0;
    while (i < actual->Nclaves && clave > actual->claves[i])
        i++;
    if (i < actual->Nclaves && clave == actual->claves[i]) {
        if (actual->hoja) {
            for (int j = i; j < actual->Nclaves - 1; j++)
                actual->claves[j] = actual->claves[j + 1];
            (actual->Nclaves)--;
            if (actual == raiz && actual->Nclaves == 0) {
                delete[] actual->claves;
                delete[] actual->hijos;
                delete actual;
                raiz = NULL;
            }
        } else {
            nodo *predecesor = actual->hijos[i];
            while (!predecesor->hoja)
                predecesor = predecesor->hijos[predecesor->Nclaves];
            int pred = predecesor->claves[predecesor->Nclaves - 1];
            actual->claves[i] = pred;
            return borrar(pred);
        }
        return true;
    } else {
        if (actual->hoja)
            return false;
        nodo *hijo_izq = NULL, *hijo_der = NULL;
        if (i > 0)
            hijo_izq = padre->hijos[i - 1];
        if (i < padre->Nclaves)
            hijo_der = padre->hijos[i + 1];
        if (hijo_izq && hijo_izq->Nclaves > d - 1) {
            rotacion_derecha(i - 1, actual, hijo_izq, hijo_izq->hijos[hijo_izq->Nclaves]);
        } else if (hijo_der && hijo_der->Nclaves > d - 1) {
            rotacion_izquierda(i, actual, hijo_der, hijo_der->hijos[0]);
        } else if (hijo_izq) {
            fusionar_nodos(i - 1, actual, hijo_izq, hijo_izq->hijos[hijo_izq->Nclaves]);
            actual = hijo_izq;
        } else if (hijo_der) {
            fusionar_nodos(i, actual, hijo_der, hijo_der->hijos[0]);
        }
        return borrar(clave);
    }
}

void arbolB::rotacion_derecha(int i, nodo *actual, nodo *hermano_izq, nodo *hijo) {
    for (int j = actual->Nclaves; j > 0; j--)
        actual->claves[j] = actual->claves[j - 1];
    actual->claves[0] = hermano_izq->claves[hermano_izq->Nclaves - 1];
    if (!actual->hoja) {
        for (int j = actual->Nclaves + 1; j > 0; j--)
            actual->hijos[j] = actual->hijos[j - 1];
        actual->hijos[0] = hijo;
    }
    (actual->Nclaves)++;
    hermano_izq->Nclaves--;
    hermano_izq->claves[hermano_izq->Nclaves] = 0;
    if (!actual->hoja)
        hermano_izq->hijos[hermano_izq->Nclaves + 1] = NULL;
}

void arbolB::rotacion_izquierda(int i, nodo *actual, nodo *hermano_der, nodo *hijo) {
    actual->claves[actual->Nclaves] = hermano_der->claves[0];
    if (!actual->hoja)
        actual->hijos[actual->Nclaves + 1] = hijo;
    (actual->Nclaves)++;
    for (int j = 0; j < hermano_der->Nclaves - 1; j++)
        hermano_der->claves[j] = hermano_der->claves[j + 1];
    if (!actual->hoja) {
        for (int j = 0; j < hermano_der->Nclaves; j++)
            hermano_der->hijos[j] = hermano_der->hijos[j + 1];
        hermano_der->hijos[hermano_der->Nclaves] = NULL;
    }
    hermano_der->Nclaves--;
    hermano_der->claves[hermano_der->Nclaves] = 0;
}

void arbolB::fusionar_nodos(int i, nodo *actual, nodo *hermano, nodo *hijo) {
    hermano->claves[hermano->Nclaves] = actual->claves[i];
    for (int j = 0; j < hijo->Nclaves; j++)
        hermano->claves[hermano->Nclaves + 1 + j] = hijo->claves[j];
    if (!actual->hoja) {
        for (int j = 0; j <= hijo->Nclaves; j++)
            hermano->hijos[hermano->Nclaves + 1 + j] = hijo->hijos[j];
    }
    hermano->Nclaves += hijo->Nclaves + 1;
    for (int j = i; j < actual->Nclaves - 1; j++)
        actual->claves[j] = actual->claves[j + 1];
    if (!actual->hoja) {
        for (int j = i + 1; j < actual->Nclaves; j++)
            actual->hijos[j] = actual->hijos[j + 1];
    }
    actual->Nclaves--;
    actual->claves[actual->Nclaves] = 0;
    if (!actual->hoja)
        actual->hijos[actual->Nclaves + 1] = NULL;
}

void arbolB::imprimirArbol() {
    if (!raiz) {
        std::cout << "El árbol está vacío." << std::endl;
        return;
    }

    std::queue<nodo*> cola;
    cola.push(raiz);

    while (!cola.empty()) {
        int nivelSize = cola.size();
        for (int i = 0; i < nivelSize; i++) {
            nodo* temp = cola.front();
            cola.pop();
            for (int j = 0; j < temp->Nclaves; j++) {
                std::cout << temp->claves[j] << " ";
                if (!temp->hoja)
                    cola.push(temp->hijos[j]);
            }
            if (!temp->hoja)
                cola.push(temp->hijos[temp->Nclaves]);
        }
        std::cout << std::endl;
    }
}

#endif

