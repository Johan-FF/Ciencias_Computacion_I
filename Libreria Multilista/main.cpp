#include <iostream>
#include <string>
#include "Multilista.h"
#include "Estructura.h"

using namespace std;

int main(){
    string datos[]={
    "raquel",	"electrica",	"danza",	"72",
    "jaime",	"industrial",	"natacion",	"25",
    "arturo",	"electrica",	"basquet",	"45",
    "andres",	"catastral",	"danza",	"50",
    "ariana",	"sistemas",	"basquet",	"36",
    "juanny",	"industrial",	"natacion",	"56",
    "may",	"sistemas",	"danza",	"42",
    "italia",	"catastral",	"beisol",	"87",
    "mario",	"sistemas",	"basquet",	"69",
    "pilar",	"sistemas",	"beisbol",	"30"
    };
    string cabeceras[]={
    "nombre",
    "sistemas",
    "industrial",
    "electrica",
    "catastral",
    "danza",
    "natacion",
    "beisbol",
    "basquet",
    "codigo"
    };
    int elementos, listas;
    cout<<"Ingrese el numero de elementos a agregar"<<endl;
    cin>>elementos;
    cout<<"Ingrese el numero de listas a agregar"<<endl;
    cin>>listas;

    Multilista bd(elementos, listas);

    int i;
    for(i=0; i<listas; i++){
        cabecera cabAux = {cabeceras[i], 0};
        bd.agregar_cabecera(&cabAux);
    }

    nodo *elemento;
    for(i=0; i<elementos; i+=4){
        elemento = new nodo;
        elemento->codigo = stoi(datos[i+3]);
        elemento->nombre = datos[i];
        elemento->carrera = datos[i+1];
        elemento->actividad = datos[i+2];
        bd.insertar(elemento);
    }

    for(i=0;i<4;i++)
        cout<<"ok";
    system("pause");

    return 0;
}