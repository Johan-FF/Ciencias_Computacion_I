#include <iostream>
#include "Multilista.h"
#include "Estructura.h"

using namespace std;

int main(){
    int elementos, listas;
    cout<<"Ingrese el numero de elementos a agregar"<<endl;
    cin>>elementos;
    cout<<"Ingrese el numero de listas a agregar"<<endl;
    cin>>listas;

    Multilista<dato<int>, dato<char*>, char*, int> bd(elementos, listas);

    int i;
    char *nombre_cabecera;
    for(i=0; i<listas; i++){
        cout<<"Ingrese el nombre de la lista:"<<endl;
        cin>>nombre_cabecera;
        cabecera<char*,int> cabAux = {nombre_cabecera, 0};
        bd.agregar_cabecera(&cabAux);
    }

    int cod;
    char *contenido;
    for(i=0; i<elementos; i++){
        nodo<dato<int>,dato<char*>,int> *elemento;
        elemento = new nodo<dato<int>,dato<char*>,int>;
        cout<<"Ingrese el codigo"<<endl;
        cin>>cod; 
        elemento->codigo.dato = cod;
        cout<<"Ingrese el nombre"<<endl;
        cin>>contenido;
        elemento->nombre.dato = contenido;
        cout<<"Ingrese la carrera"<<endl;
        cin>>contenido;
        elemento->carrera.dato = contenido;
        cout<<"Ingrese la actividad"<<endl;
        cin>>contenido;
        elemento->actividad.dato = contenido;
        bd.insertar(elemento);
    }

    return 0;
}