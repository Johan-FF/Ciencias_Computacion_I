#include "Monticulo.h"

int main() {
    monticulo heap(10);

    heap.insertar(60);
    heap.insertar(80);
    heap.insertar(20);
    heap.insertar(90);
    heap.insertar(50);
    heap.insertar(40);
    heap.insertar(30);
    heap.insertar(70);
    heap.insertar(55);
    heap.insertar(45);

    cout << "Elementos del monticulo: ";
    heap.imprimirArreglo();

    cout << "Atendemos: "  <<  heap.atender() << endl;

    cout << "Elementos del monticulo: ";
    heap.imprimirArreglo();

    cout << "Atendemos: "  <<  heap.atender() << endl;

    cout << "Elementos del monticulo: ";
    heap.imprimirArreglo();

    return 0;
}
