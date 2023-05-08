#include "ArbolRojinegro.h"

int main() {
	ArbolRojoNegro arbol;
	arbol.insertar(3);
	arbol.insertar(1);
	arbol.insertar(2);
	arbol.insertar(5);
	arbol.insertar(4);
	arbol.insertar(6);
	arbol.inorder(arbol.get_raiz());
	if(arbol.eliminar_valor(2))
		arbol.inorder(arbol.get_raiz());
	return 0;
}
