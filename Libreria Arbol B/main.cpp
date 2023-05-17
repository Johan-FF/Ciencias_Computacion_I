
#include "ArbolB.h"

int main() {
    // Crear un árbol B con orden 3
    arbolB arbol(3);

    // Insertar claves en el árbol
    arbol.insertar(10);
    arbol.insertar(20);
    arbol.insertar(5);
    arbol.insertar(15);
    arbol.insertar(7);

    // Imprimir el árbol por niveles
    arbol.imprimirArbol();

    // Eliminar una clave del árbol
    int claveEliminar = 5;
    bool eliminado = arbol.borrar(claveEliminar);
    if (eliminado) {
        std::cout << "Clave eliminada del árbol." << std::endl;
    } else {
        std::cout << "Clave no encontrada en el árbol." << std::endl;
    }

    // Imprimir el árbol actualizado por niveles
    arbol.imprimirArbol();

    return 0;
}
