#include <iostream>

#include "ArbolBinarioOrdenado.h"
#include<stdlib.h>
#include<time.h>

using namespace std;

int main(){
    int num_elementos=10, num_elementos_eliminar=num_elementos/4; 
    int para_eliminar[num_elementos_eliminar], posicion=0, i;
    ArbolBinarioOrdenado arbol(15);

    srand(time(NULL));
    
    arbol.insertar(8);
    arbol.insertar(3);
    arbol.insertar(10);
    arbol.insertar(1);
    arbol.insertar(6);
    arbol.insertar(4);
    arbol.insertar(7);
    arbol.insertar(14);
    arbol.insertar(13);
    
    cout<<"Iniciando:"<<endl;
    for(int i=0; i<10; i++){
        cout<<arbol.arbol[i].clave<<",";
        cout<<arbol.arbol[i].izq<<",";
        cout<<arbol.arbol[i].der<<"  ";
    }
    cout<<endl;
    
    cout<<"Recorrido inorden:"<<endl;
    arbol.inorden(1);
    cout<<"Recorrido preorden:"<<endl;
    arbol.preorden(1);
    cout<<"Recorrido postorden:"<<endl;
    arbol.postorden(1);
    

    return 0;
}
