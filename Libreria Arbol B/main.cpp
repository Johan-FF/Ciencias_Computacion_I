#include <iostream>
#include "ArbolB.h"

using namespace std;

int main() {
    // Crea un árbol B con un orden de 3
    arbolB miArbol(3);

    // Inserta algunas claves en el árbol
    miArbol.insertar(10);
    miArbol.insertar(5);
    miArbol.insertar(20);
    miArbol.insertar(30);
    miArbol.insertar(15);

    miArbol.mostrar();

    // Realiza algunas operaciones en el árbol
    bool encontrado = miArbol.buscar(25);
    cout<<endl<<"Clave 25 encontrada? "<<(encontrado ? "Si" : "No")<<endl;

    bool borrado = miArbol.borrar(20);
    cout<<endl<<"Clave 20 borrada? "<<(borrado ? "Si" : "No")<<endl;

    miArbol.mostrar();
    return 0;
}
