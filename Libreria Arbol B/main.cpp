
#include "ArbolB.h"

int main() {
    // Crear un �rbol B con orden 3
    arbolB arbol(3);

    // Insertar claves en el �rbol
    arbol.insertar(10);
    arbol.insertar(20);
    arbol.insertar(5);
    arbol.insertar(15);
    arbol.insertar(7);

    // Imprimir el �rbol por niveles
    arbol.imprimirArbol();

    // Eliminar una clave del �rbol
    int claveEliminar = 5;
    bool eliminado = arbol.borrar(claveEliminar);
    if (eliminado) {
        std::cout << "Clave eliminada del �rbol." << std::endl;
    } else {
        std::cout << "Clave no encontrada en el �rbol." << std::endl;
    }

    // Imprimir el �rbol actualizado por niveles
    arbol.imprimirArbol();

    return 0;
}
