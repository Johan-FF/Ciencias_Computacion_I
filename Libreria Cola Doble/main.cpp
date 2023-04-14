#include <iostream>
#include "ColaDoble.h"

using namespace std;

int main(){
    ColaDoble<int> cola;

    cola.insertar(1,'D');
    cola.insertar(2,'D');
    cola.insertar(3,'I');
    cola.insertar(4,'I');

    cola.mostrar(); // deber�a imprimir: 4 3 1 2

    cout << "Eliminando " << cola.eliminar('D') << endl; // deber�a imprimir: Eliminando 1
    cout << "Eliminando " << cola.eliminar('I') << endl; // deber�a imprimir: Eliminando 4

    cola.mostrar(); // deber�a imprimir: 3 2
	
	return 0;
}
