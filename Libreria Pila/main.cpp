#include <iostream>
#include "Pila.h"

using namespace std;

int main(){
	
	Pila<int> pilaInt(10);
    pilaInt.meter(1);
    pilaInt.meter(2);
    pilaInt.meter(3);
    cout << pilaInt.sacar() << endl;
    cout << pilaInt.sacar() << endl;
    cout << pilaInt.sacar() << endl;
    
    
    Pila<char> pilaChar(10);
    pilaChar.meter('A');
    pilaChar.meter('B');
    pilaChar.meter('C');
    cout << pilaChar.sacar() << endl;
    cout << pilaChar.sacar() << endl;
    cout << pilaChar.sacar() << endl;
    
	return 0;
}
