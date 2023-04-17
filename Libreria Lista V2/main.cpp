#include <iostream>
#include "Lista.h"

using namespace std;

int main() {
	
    Lista<int> lista;
	
    lista.insertar_final(2);
    lista.insertar_final(3);
    lista.insertar_inicio(1);
    lista.insertar_final(4);

    cout << "Elementos en la lista: " << lista.getTam() << endl;
    cout << "Lista vacia? " << (lista.lista_vacia() ? "Si" : "No") << endl;

    cout << "Elementos en la lista: ";
    for (int i = 0; i < lista.getTam(); i++) {
        cout << lista.buscar(i) << " ";
    }
    cout << endl;

    lista.modificar(5, 2);
    lista.borrar(3);

    cout << "Elementos en la lista: ";
    for (int i = 0; i < lista.getTam(); i++) {
        cout << lista.buscar(i) << " ";
    }
    cout << endl;

    return 0;
}
