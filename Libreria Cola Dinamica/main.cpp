
#include "Cola.h"

int main(){
    Cola<int> cola; 
    
    cola.insCola(5);
    cola.insCola(6);
    cola.insCola(8);
    cola.insCola(9);
    cola.insCola(2);
    
    cola.imprimirCola();
    
    
    return 0;
}
