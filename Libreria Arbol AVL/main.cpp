#include <iostream>

#include "ArbolBinarioOrdenado.h"
#include<stdlib.h>
#include<time.h>

using namespace std;

int main(){
    ArbolBinarioOrdenado arbol(15);

    arbol.insertar(8);
    arbol.insertar(3);
    arbol.insertar(10);
    arbol.insertar(2);
    arbol.insertar(6);
    arbol.insertar(4);
    arbol.insertar(7);
    arbol.insertar(14);
    arbol.insertar(13);
    arbol.insertar(1);
    arbol.insertar(0);

    cout<<"Iniciando:"<<endl;
    for(int i=0; i<12; i++){
        cout<<arbol.arbol[i].clave<<",";
        cout<<arbol.arbol[i].fb<<",";
        cout<<arbol.arbol[i].padre<<",";
        cout<<arbol.arbol[i].izq<<",";
        cout<<arbol.arbol[i].der<<"  ";
    }
    cout<<endl;

    cout<<"Recorrido inorden:"<<endl;
    arbol.inorden(arbol.getRaiz());
    cout<<"Recorrido preorden:"<<endl;
    arbol.preorden(arbol.getRaiz());
    cout<<"Recorrido postorden:"<<endl;
    arbol.postorden(arbol.getRaiz());

    return 0;
}
