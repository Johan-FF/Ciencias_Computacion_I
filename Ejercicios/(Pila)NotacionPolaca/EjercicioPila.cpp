#include <iostream>
#include "Pila.h"
#include <limits>

using namespace std;

void convertir_notacion_polaca() {
	char c; // Guarda el valor ingresado por el usuario
	Pila<char> guardar(50); // Pila que gestiona los operadores de la expresion ingresada en caracteres

	cout<<"Ingrese la expresión: "<<endl;
	cout<<"Al terminar de imprimir la expresion en notacion polaca oprima Ctrl+z luego, presione enter."<<endl;
	while(cin.get(c))// Lee todos los caracteres que entren por consola
	{ 
		while(c>='0' && c<='9')// Si el numero es de una o mas cifras lo imprime
		{ 
			cout.put(c); cin.get(c);
		}
		// Al trabajar operadores binarios, se guardan los operadores y al finallizar el parentesis se imprime el operador que implica a las dos cifras anteriores 
		if (c==')') cout.put(guardar.sacar());
		if (c=='+') guardar.meter(c);
		if (c=='*') guardar.meter(c);
		if (c!='(') cout << ' ';
	}

	cin.clear(); // Restablece el estado de error de la entrada estándar
	cout<< '\n';
}

void resolver_notacion_polaca() {
	int x; // Guarda el valor numerico ya sea de una operacion o un valor ingresado por el ususario
	char d; // Guarda el valor de tipo char ingresado por el usuario, ya sea un operador o numero
	Pila<int> acc(50); // Pila que gestiona los numeros y resultados de operaciones que se hacen con los mismos de tipo entero

	cout<<"Ingrese la expresión en notacion polaca: "<<endl;
	cout<<"Al finalizar oprima Ctrl+z luego, presione enter."<<endl;
	while(cin.get(d)) // Lee todos los caracteres ingresados por consola
	{
		x=0; // Se establece un valor de control
		while (d==' ') cin.get(d); // Se lee la entrada hasta encontrar un valor valido
		while(d>= '0' && d<='9') // Si el numero es de una o mas cifras de guarda en la variable x
		{
			x=10*x + (d-'0');
			cin.get(d);
		}
		if ((d=='+' || d=='*') && x!=0) acc.meter(x); // Si continuo al numero hay un operador, primero se guarda el ultimo numero ingresado y luego si se opera
		if (d == '+') x= acc.sacar() + acc.sacar(); // Operacion de suma
		if (d == '*') x= acc.sacar() * acc.sacar(); // Operacion de multiplicacion
		if (d != '\n') acc.meter(x); // Si el caracter no es un salto de linea (es decir que finalizo de leer la entrada del usuario) guarda el valor de x
	}
	cout << acc.sacar()<< '\n'; // Imprime por consola el resultado de las operaciones 
}

int main(){
	// Ejemplo de uso "( 5 * (((9 + 10) * (4 * 6)) +20))"
	convertir_notacion_polaca();
	resolver_notacion_polaca();
	system("pause");
	return 0;
}
