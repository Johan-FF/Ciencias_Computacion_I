#include <iostream>

#include "ArbolBinarioOrdenado.h"
#include<stdlib.h>
#include<time.h>

using namespace std;

int main(){
    int para_eliminar[5], posicion=0, i;
    ArbolBinarioOrdenado arbol(10);
    srand(time(NULL));
    int num;
    for(i=0; i<10; i++){
        num = rand()%51;
        if( i%4==0 ) para_eliminar[posicion++] = num;
        arbol.insertar(num);
    }
    cout<<endl;
    cout<<"inorden: ";
    arbol.imprimir_inorden(1);
    cout<<endl;
    cout<<"preorden: ";
    arbol.imprimir_preorden(1);
    cout<<endl;
    cout<<"posorden: ";
    arbol.imprimir_posorden(1);
    cout<<endl;

    for(i=0; i<5; i++)
        arbol.eliminar( para_eliminar[i] );

    cout<<endl;
    cout<<"inorden: ";
    arbol.imprimir_inorden(1);
    cout<<endl;
    cout<<"preorden: ";
    arbol.imprimir_preorden(1);
    cout<<endl;
    cout<<"posorden: ";
    arbol.imprimir_posorden(1);
    cout<<endl;

    return 0;
}