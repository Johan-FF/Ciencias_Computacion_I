#include "Monticulo.h"

int main() {
    monticulo heap(10);

    heap.insertar(5);
    heap.insertar(10);
    heap.insertar(2);
    heap.insertar(8);
    heap.insertar(3);

    cout << "Elementos del monticulo: ";
    heap.imprimirArreglo();


    return 0;
}
