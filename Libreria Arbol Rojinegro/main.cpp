#include "ArbolRojinegro.h"

int main() {
	ArbolRojoNegro arbol;
	arbol.insertar(60);
	arbol.insertar(90);
	arbol.insertar(120);
	arbol.insertar(140);
	arbol.inorder(arbol.get_raiz());

	return 0;
}
