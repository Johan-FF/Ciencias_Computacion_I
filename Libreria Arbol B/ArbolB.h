#ifndef ARBOLB_H
#define ARBOLB_H

#include <cstdlib>

struct nodo
{
    int *claves;
    nodo **hijos;
    int Nclaves;
    bool hoja;
};

class arbolB
{
    nodo *raiz;
    int d;

public:
    arbolB(int ord)
    {
        d = ord;
        raiz = crear_nodo();
        raiz->Nclaves = 0;
        raiz->hoja = true;
    }
    void mostrar();
    void inorden(nodo* actual);
    nodo *crear_nodo();
    int dividir_nodo(nodo *actual, nodo **hermano);
    void insertar(int clave);
    bool buscar(int clave);
    nodo *buscar_nodo(int clave, nodo **Actual);
    int InsertarNodoNormal(int clave, nodo *Actual);
    void InsertarNodoLleno(int clave, nodo *Actual, nodo *padre);
    bool borrar(int clave);
    int buscar_clave(int clave, nodo **actual, nodo **padre);
    int borrarEn_hoja(int clave, int pos, nodo *actual, nodo *padre);
    void ajustar_nodo(int pos, nodo *actual);
    int buscar_lugarEntreHnos(int clave, nodo *padre);
    bool ayuda_hnoDer(nodo *padre, int posActual);
    bool ayuda_hnoIzq(nodo *padre, int posActual);
    void juntar(nodo *padre, int pos, int posActual);
    void reemplazar_der(nodo *actual, nodo *padre, int posActual);
    void reemplazar_izq(nodo *actual, nodo *padre, int posActual);
    void unir_hno_der(nodo *padre, int posClave, int posActual);
    void unir_hno_izq(nodo *padre, int posClave, int posActual);
    int encontrar_predecesor(nodo *actual);
    nodo* encontrar_padre(nodo *nodo_actual, nodo *nodo_buscado);
    int encontrar_sucesor(nodo *actual);
    void ajustarNivelPadre(nodo *actual, int posClave);
    int borrarEn_Ninterno(int pos, nodo *actual);
};

void arbolB::mostrar() {
    inorden(raiz);
}

void arbolB::inorden(nodo* actual) {
    if (actual != nullptr) {
        int i;
        for (i = 0; i < actual->Nclaves; i++) {
            if (!actual->hoja)
                inorden(actual->hijos[i]);
            std::cout << actual->claves[i] << " ";
        }

        if (!actual->hoja)
            inorden(actual->hijos[i]);
    }
}

nodo *arbolB::crear_nodo()
{
    nodo *nuevo_nodo = new nodo;
    nuevo_nodo->claves = new int[2 * d];
    nuevo_nodo->hijos = new nodo *[2 * d + 1];
    nuevo_nodo->Nclaves = 0;
    nuevo_nodo->hoja = true;
    return nuevo_nodo;
}

int arbolB::dividir_nodo(nodo *actual, nodo **hermano)
{
    int medio = actual->Nclaves / 2;
    *hermano = crear_nodo();

    (*hermano)->hoja = actual->hoja;
    (*hermano)->Nclaves = actual->Nclaves - medio - 1;

    for (int i = 0; i < medio + 1; i++)
        (*hermano)->hijos[i] = actual->hijos[i + medio + 1];

    if (!actual->hoja)
    {
        for (int i = 0; i < medio; i++)
            (*hermano)->claves[i] = actual->claves[i + medio + 1];
    }
    else
    {
        for (int i = 0; i < medio; i++)
            (*hermano)->claves[i] = actual->claves[i + medio];
    }

    actual->Nclaves = medio;

    return actual->claves[medio];
}

void arbolB::insertar(int clave)
{
    nodo *nodo_actual = raiz;
    if (nodo_actual->Nclaves == 2 * d - 1)
    {
        nodo *nuevo_nodo = crear_nodo();
        nuevo_nodo->hijos[0] = raiz;
        raiz = nuevo_nodo;

        dividir_nodo(nodo_actual, &nuevo_nodo);
        InsertarNodoNormal(clave, nuevo_nodo);
    }
    else
    {
        InsertarNodoNormal(clave, nodo_actual);
    }
}

bool arbolB::buscar(int clave){
    return buscar_nodo(clave, &raiz)==nullptr;
}

nodo *arbolB::buscar_nodo(int clave, nodo **actual)
{
    int i = 0;
    while (i < (*actual)->Nclaves && clave > (*actual)->claves[i])
        i++;
    if ((*actual)->hoja && (*actual)->claves[i] == clave)
        return *actual;

    if ((*actual)->hoja)
        return NULL;

    return buscar_nodo(clave, &((*actual)->hijos[i]));
}

int arbolB::InsertarNodoNormal(int clave, nodo *actual)
{
    int i = actual->Nclaves - 1;
    if (actual->hoja)
    {
        while (i >= 0 && clave < actual->claves[i])
        {
            actual->claves[i + 1] = actual->claves[i];
            i--;
        }

        actual->claves[i + 1] = clave;
        actual->Nclaves++;
        return 0;
    }

    while (i >= 0 && clave < actual->claves[i])
        i--;

    i++;

    if (actual->hijos[i]->Nclaves == 2 * d - 1)
    {
        nodo *nuevo_nodo = crear_nodo();
        dividir_nodo(actual->hijos[i], &nuevo_nodo);

        if (clave > actual->claves[i])
            i++;

        InsertarNodoNormal(clave, nuevo_nodo);
    }
    else
    {
        InsertarNodoNormal(clave, actual->hijos[i]);
    }

    return 0;
}

void arbolB::InsertarNodoLleno(int clave, nodo *actual, nodo *padre)
{
    if (actual == raiz)
    {
        nodo *nuevo_nodo = crear_nodo();
        raiz = nuevo_nodo;
        nuevo_nodo->hijos[0] = actual;
        dividir_nodo(actual, &(nuevo_nodo->hijos[1]));
        InsertarNodoNormal(clave, nuevo_nodo);
    }
    else
    {
        nodo *nuevo_nodo = crear_nodo();
        dividir_nodo(actual, &nuevo_nodo);
        int pos = buscar_lugarEntreHnos(clave, padre);

        if (pos == padre->Nclaves)
            padre->hijos[pos + 1] = nuevo_nodo;
        else
            reemplazar_der(nuevo_nodo, padre, pos);
        InsertarNodoNormal(clave, padre->hijos[pos]);
    }
}

bool arbolB::borrar(int clave)
{
    nodo *actual = raiz;
    nodo *padre = NULL;
    int posActual = -1;
    while (true)
    {
        posActual = buscar_clave(clave, &actual, &padre);

        if (posActual != -1)
            break;

        if (actual->hoja)
            return false;

        if (actual->Nclaves >= d)
            actual = actual->hijos[posActual];
        else
        {
            if (ayuda_hnoDer(padre, posActual))
                ajustar_nodo(posActual, actual);
            else if (ayuda_hnoIzq(padre, posActual))
                ajustar_nodo(posActual - 1, actual);
            else
            {
                if (posActual < padre->Nclaves)
                    juntar(padre, posActual, posActual + 1);
                else
                    juntar(padre, posActual - 1, posActual);
            }
        }
    }
    if (actual->hoja)
    {
        borrarEn_hoja(clave, posActual, actual, padre);
    }
    else
    {
        int posSigClave = posActual + 1;
        nodo *nodo_sig_clave = actual->hijos[posSigClave];

        while (!nodo_sig_clave->hoja)
        {
            padre = actual;
            actual = nodo_sig_clave;
            posSigClave = 0;
            nodo_sig_clave = actual->hijos[posSigClave];
        }

        actual->claves[posActual] = nodo_sig_clave->claves[0];
        borrarEn_hoja(actual->claves[posActual], posSigClave, actual, padre);
    }

    return true;
}

int arbolB::buscar_clave(int clave, nodo **actual, nodo **padre)
{
    int posActual = -1;
    int i = 0;
    while (i < (*actual)->Nclaves && clave > (*actual)->claves[i])
    {
        i++;
    }

    if ((*actual)->hoja && (*actual)->claves[i] == clave)
    {
        return i;
    }

    if ((*actual)->hoja)
    {
        return -1;
    }

    *padre = *actual;
    *actual = (*actual)->hijos[i];

    return posActual;
}

int arbolB::borrarEn_hoja(int clave, int pos, nodo *actual, nodo *padre)
{
    for (int i = pos; i < actual->Nclaves - 1; i++)
    {
        actual->claves[i] = actual->claves[i + 1];
    }
    actual->Nclaves--;

    if (actual == raiz && actual->Nclaves == 0)
    {
        delete actual;
        raiz = NULL;
    }

    if (actual->Nclaves < d - 1 && actual != raiz)
    {
        if (ayuda_hnoDer(padre, pos))
            ajustar_nodo(pos, actual);
        else if (ayuda_hnoIzq(padre, pos))
            ajustar_nodo(pos - 1, actual);
        else
        {
            if (pos < padre->Nclaves)
                juntar(padre, pos, pos + 1);
            else
                juntar(padre, pos - 1, pos);
        }
    }

    return 0;
}

void arbolB::ajustar_nodo(int pos, nodo *actual)
{
    if (pos >= 0 && actual->hijos[pos + 1]->Nclaves > d - 1)
    {
        reemplazar_der(actual->hijos[pos + 1], actual, pos);
    }
    else if (pos >= 0 && actual->hijos[pos - 1]->Nclaves > d - 1)
    {
        reemplazar_izq(actual->hijos[pos - 1], actual, pos);
    }
    else if (pos >= 0)
    {
        unir_hno_der

            (actual, pos, pos + 1);
    }
    else
    {
        unir_hno_izq(actual, pos, pos + 1);
    }
}

int arbolB::buscar_lugarEntreHnos(int clave, nodo *padre)
{
    int pos = 0;
    while (pos < padre->Nclaves && clave > padre->claves[pos])
    {
        pos++;
    }

    return pos;
}

bool arbolB::ayuda_hnoDer(nodo *padre, int posActual)
{
    return (posActual + 1 < padre->Nclaves &&
            padre->hijos[posActual + 1]->Nclaves > d - 1);
}

bool arbolB::ayuda_hnoIzq(nodo *padre, int posActual)
{
    return (posActual > 0 && padre->hijos[posActual - 1]->Nclaves > d - 1);
}

void arbolB::juntar(nodo *padre, int pos, int posActual)
{
    nodo *actual = padre->hijos[posActual];
    nodo *hermano = padre->hijos[pos];
    if (pos < posActual)
    {
        int temp = pos;
        pos = posActual;
        posActual = temp;

        nodo *temp_nodo = actual;
        actual = hermano;
        hermano = temp_nodo;
    }

    hermano->claves[d - 1] = padre->claves[posActual];
    hermano->Nclaves++;

    for (int i = 0; i < actual->Nclaves; i++)
    {
        hermano->claves[d + i] = actual->claves[i];
        hermano->Nclaves++;
    }

    if (!actual->hoja)
    {
        for (int i = 0; i <= actual->Nclaves; i++)
        {
            hermano->hijos[d + i] = actual->hijos[i];
        }
    }

    delete actual;

    for (int i = posActual; i < padre->Nclaves - 1; i++)
    {
        padre->claves[i] = padre->claves[i + 1];
        padre->hijos[i + 1] = padre->hijos[i + 2];
    }

    padre->Nclaves--;

    if (padre->Nclaves == 0 && padre == raiz)
    {
        delete padre;
        raiz = hermano;
    }
}

void arbolB::reemplazar_der(nodo *actual, nodo *padre, int posActual)
{
    nodo *hijo_der = actual->hijos[0];
    int clave = padre->claves[posActual];
    padre->claves[posActual] = actual->claves[0];

    for (int i = 0; i < actual->Nclaves - 1; i++)
    {
        actual->claves[i] = actual->claves[i + 1];
    }

    actual->claves[actual->Nclaves - 1] = clave;

    for (int i = 0; i < actual->Nclaves; i++)
    {
        actual->hijos[i] = actual->hijos[i + 1];
    }

    actual->hijos[actual->Nclaves] = hijo_der;

    actual->Nclaves--;

    if (hijo_der->Nclaves < d - 1)
    {
        ajustar_nodo(0, actual);
    }
}

void arbolB::reemplazar_izq(nodo *actual, nodo *padre, int posActual)
{
    nodo *hijo_izq = actual->hijos[actual->Nclaves];
    int clave = padre->claves[posActual - 1];
    padre->claves[posActual - 1] = actual->claves[actual->Nclaves - 1];

    actual->claves[actual->Nclaves - 1] = clave;

    for (int i = actual->Nclaves; i > 0; i--)
    {
        actual->claves[i] = actual->claves[i - 1];
    }

    actual->claves[0] = clave;

    for (int i = actual->Nclaves; i >= 0; i--)
    {
        actual->hijos[i + 1] = actual->hijos[i];
    }

    actual->hijos[0] = hijo_izq;

    actual->Nclaves--;

    if (hijo_izq->Nclaves < d - 1)
    {
        ajustar_nodo(actual->Nclaves, actual);
    }
}

void arbolB::unir_hno_der(nodo *padre, int posClave, int posActual)
{
    nodo *actual = padre->hijos[posActual];
    nodo *hermano = padre->hijos[posActual + 1];
    actual->claves[d - 1] = padre->claves[posClave];
    actual->Nclaves++;

    for (int i = 0; i < hermano->Nclaves; i++)
    {
        actual->claves[d + i] = hermano->claves[i];
        actual->Nclaves++;
    }

    if (!actual->hoja)
    {
        for (int i = 0; i <= hermano->Nclaves; i++)
        {
            actual->hijos[d + i] = hermano->hijos[i];
        }
    }

    delete hermano;

    for (int i = posClave; i < padre->Nclaves - 1; i++)
    {
        padre->claves[i] = padre->claves[i + 1];
        padre->hijos[i + 1] = padre->hijos[i + 2];
    }

    padre->Nclaves--;

    if (padre->Nclaves == 0 && padre == raiz)
    {
        delete padre;
        raiz = actual;
    }
}

void arbolB::unir_hno_izq(nodo *padre, int posClave, int posActual)
{
    nodo *actual = padre->hijos[posActual];
    nodo *hermano = padre->hijos[posActual - 1];
    hermano->claves[d - 1] = padre->claves[posClave - 1];
    hermano->Nclaves++;

    for (int i = 0; i < actual->Nclaves; i++)
    {
        hermano->claves[d + i] = actual->claves[i];
        hermano->Nclaves++;
    }

    if (!actual->hoja)
    {
        for (int i = 0; i <= actual->Nclaves; i++)
        {
            hermano->hijos[d + i] = actual->hijos[i];
        }
    }

    delete actual;

    for (int i = posClave - 1; i < padre->Nclaves - 1; i++)
    {
        padre->claves[i] = padre->claves[i + 1];
        padre->hijos[i + 1] = padre->hijos[i + 2];
    }
    padre->Nclaves--;

    if (padre->Nclaves == 0 && padre == raiz)
    {
        delete padre;
        raiz = hermano;
    }
}

int arbolB::encontrar_predecesor(nodo *actual) {
    if (actual->hoja) {
        return actual->claves[actual->Nclaves - 1];
    } else {
        return encontrar_predecesor(actual->hijos[actual->Nclaves]);
    }
}

int arbolB::encontrar_sucesor(nodo *actual) {
    if (actual->hoja) {
        return actual->claves[0];
    } else {
        return encontrar_sucesor(actual->hijos[0]);
    }
}

nodo *arbolB::encontrar_padre(nodo *nodo_actual, nodo *nodo_buscado) {
    if (nodo_actual->hoja) {
        return nullptr; // No se encontró el padre
    }

    for (int i = 0; i <= nodo_actual->Nclaves; i++) {
        if (nodo_actual->hijos[i] == nodo_buscado) {
            return nodo_actual;
        }

        nodo *resultado = encontrar_padre(nodo_actual->hijos[i], nodo_buscado);
        if (resultado != nullptr) {
            return resultado;
        }
    }

    return nullptr; // No se encontró el padre
}

void arbolB::ajustarNivelPadre(nodo *actual, int posClave)
{
    if (actual == raiz && actual->Nclaves == 0)
    {
        nodo *nueva_raiz = actual->hijos[0];
        delete actual;
        raiz = nueva_raiz;
    }
    if (actual->Nclaves < d - 1 && actual != raiz)
    {
        nodo *padre = encontrar_padre(raiz, actual);
        int posActual = buscar_lugarEntreHnos(actual->claves[0], padre);

        if (ayuda_hnoDer(padre, posActual))
            ajustar_nodo(posActual, actual);
        else if (ayuda_hnoIzq(padre, posActual))
            ajustar_nodo(posActual - 1, actual);
        else
        {
            if (posActual < padre->Nclaves)
                juntar(padre, posActual, posActual + 1);
            else
                juntar(padre, posActual - 1, posActual);
        }
    }
}

int arbolB::borrarEn_Ninterno(int pos, nodo *actual)
{
    nodo *hijo_izq = actual->hijos[pos];
    nodo *hijo_der = actual->hijos[pos + 1];
    if (hijo_izq->Nclaves >= d)
    {
        int predecesor = encontrar_predecesor(hijo_izq);
        actual->claves[pos] = predecesor;
        borrar(predecesor);
    }
    else if (hijo_der->Nclaves >= d)
    {
        int sucesor = encontrar_sucesor(hijo_der);
        actual->claves[pos] = sucesor;
        borrar(sucesor);
    }
    else
    {
        juntar(hijo_izq, pos, pos + 1);
        borrar(actual->claves[pos]);
    }

    return 0;
}

#endif