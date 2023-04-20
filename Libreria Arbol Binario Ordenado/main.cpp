#include <iostream>

#include "ArbolBinarioOrdenado.h"
#include<stdlib.h>
#include<time.h>

using namespace std;

int main(){
    int num_elementos=10, num_elementos_eliminar=num_elementos/4; 
    int para_eliminar[num_elementos_eliminar], posicion=0, i;
    ArbolBinarioOrdenado arbol(num_elementos);
    srand(time(NULL));
    int num;
    for(i=0; i<num_elementos; i++){
        num = rand()%51;
        if( i%4==0 ) para_eliminar[posicion++] = num;
        arbol.insertar(num);
    }
    cout<<"Iniciando:"<<endl;
    for(int i=0; i<11; i++){
        cout<<arbol.arbol[i].clave<<",";
        cout<<arbol.arbol[i].izq<<",";
        cout<<arbol.arbol[i].der<<"  ";
    }
    cout<<endl;

    for(i=0; i<3; i++){
        arbol.eliminar( para_eliminar[i] );
        cout<<"Eliminando: "<<para_eliminar[i]<<endl;
    }
    cout<<"Luego de eliminar:"<<endl;
    for(int i=0; i<11; i++){
        cout<<arbol.arbol[i].clave<<",";
        cout<<arbol.arbol[i].izq<<",";
        cout<<arbol.arbol[i].der<<"  ";
    }
    cout<<endl;

    return 0;
}