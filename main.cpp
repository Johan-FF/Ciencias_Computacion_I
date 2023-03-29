#include <iostream>
#include "Lista.h"

using namespace std;

struct Estudiante{
    string nombre;
    int codigo;	
};
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void imprimir_menu();
void ejecutar_funcionamiento(void **listas, int opcion);
void imprimir_submenu();
void ejecutar_metodo(Lista<int>* lista, int opcion);
void ejecutar_metodo(Lista<float>* lista, int opcion);
void ejecutar_metodo(Lista<char>* lista, int opcion);
void ejecutar_metodo(Lista<Estudiante>* lista, int opcion);

int main() {
    Lista<int> enteros;
	Lista<float> flotantes;
	Lista<char> chars;
	Lista<Estudiante> estudiantes;

    void **listas;
    listas = new void*[4];
    listas[0] = &enteros;
    listas[1] = &flotantes;
    listas[2] = &chars;
    listas[3] = &estudiantes;  

    int opcion = 0;
    std::cout<<"Bienvenid@ al sistema de listas"<<endl;
    while(opcion!=5){
        imprimir_menu();
        std::cin>>opcion;
        if(opcion>=1 && opcion<=4) {
            ejecutar_funcionamiento(listas, opcion);
        } else if (opcion!=5) {
            std::cout<<"Introduzca una opcion valida."<<endl;
        }
    }
	return 0;
}

void imprimir_menu(){
    std::cout<<"Seleccione una lista:"<<endl;
    std::cout<<"1. Enteros"<<endl;
    std::cout<<"2. Flotantes"<<endl;
    std::cout<<"3. Chars"<<endl;
    std::cout<<"4. Estudiantes"<<endl;
    std::cout<<"5. SALIR"<<endl;
}

void ejecutar_funcionamiento(void **listas, int opcion){
    switch(opcion){
        case 1:
            Lista<int>* lista_enteros;
            lista_enteros = static_cast<Lista<int>*>(listas[0]);
            imprimir_submenu();
            std::cin>>opcion;
            if(opcion>=1 && opcion<=7) {
                ejecutar_metodo(lista_enteros, opcion);
            }
            break;
        case 2:
            Lista<float>* lista_flotantes;
            lista_flotantes = static_cast<Lista<float>*>(listas[1]);
            imprimir_submenu();
            std::cin>>opcion;
            if(opcion>=1 && opcion<=7) {
                ejecutar_metodo(lista_flotantes, opcion);
            }
            break;
        case 3:
            Lista<char>* lista_chars;
            lista_chars = static_cast<Lista<char>*>(listas[2]);
            imprimir_submenu();
            std::cin>>opcion;
            if(opcion>=1 && opcion<=7) {
                ejecutar_metodo(lista_chars, opcion);
            }
            break;
        case 4:
            Lista<Estudiante>* lista_estudiantes;
            lista_estudiantes = static_cast<Lista<Estudiante>*>(listas[3]);
            imprimir_submenu();
            std::cin>>opcion;
            if(opcion>=1 && opcion<=7) {
                ejecutar_metodo(lista_estudiantes, opcion);
            }
            break;
        default:
            break;
    }
}

void imprimir_submenu(){
    std::cout<<"Seleccione una funcion:"<<endl;
    std::cout<<"1. Lista vacia"<<endl;
    std::cout<<"2. Insertar"<<endl;
    std::cout<<"3. Insertar al inicio"<<endl;
    std::cout<<"4. Insertar al final"<<endl;
    std::cout<<"5. Borrar"<<endl;
    std::cout<<"6. Buscar"<<endl;
    std::cout<<"7. Modificar"<<endl;
}

void ejecutar_metodo(Lista<int>* lista, int opcion){
    int dato;
    int posicion;
    switch(opcion) {
        case 1:
            std::cout<<"Lista vacia: "<<lista->lista_vacia()<<endl;
            break;
        case 2:
            std::cout<<"Ingrese el numero:"<<endl;
            std::cin>>dato;
            std::cout<<"Ingrese la posicion:"<<endl;
            std::cin>>posicion;
            lista->insertar(dato, posicion);
            std::cout<<"Elemento insertado"<<endl;
            break;
        case 3:
            std::cout<<"Ingrese el numero:"<<endl;
            std::cin>>dato;
            lista->insertar_inicio(dato);
            std::cout<<"Elemento insertado"<<endl;
            break;
        case 4:
            std::cout<<"Ingrese el numero:"<<endl;
            std::cin>>dato;
            lista->insertar_final(dato);
            std::cout<<"Elemento insertado"<<endl;
            break;
        case 5:
            std::cout<<"Ingrese la posicion del elemento a eliminar:"<<endl;
            std::cin>>posicion;
            bool eliminado;
            eliminado = lista->borrar(posicion);
            std::cout<<"Elemento eliminado: "<<eliminado<<endl;
            break;
        case 6:
            std::cout<<"Ingrese la posicion del elemento a buscar:"<<endl;
            std::cin>>posicion;
            int elemento;
            elemento = lista->buscar(posicion);
            std::cout<<"Elemento: "<<elemento<<endl;
            break;
        case 7:
            std::cout<<"Ingrese el nuevo numero:"<<endl;
            std::cin>>dato;
            std::cout<<"Ingrese la posicion del elemento a cambiar:"<<endl;
            std::cin>>posicion;
            bool cambiado;
            cambiado = lista->modificar(dato, posicion);
            std::cout<<"Elemento cambiado: "<<cambiado<<endl;
            break;
        default:
            break;
    }
}

void ejecutar_metodo(Lista<float>* lista, int opcion){
    float dato;
    int posicion;
    switch(opcion) {
        case 1:
            std::cout<<"Lista vacia: "<<lista->lista_vacia()<<endl;
            break;
        case 2:
            std::cout<<"Ingrese el numero flotante:"<<endl;
            std::cin>>dato;
            std::cout<<"Ingrese la posicion:"<<endl;
            std::cin>>posicion;
            lista->insertar(dato, posicion);
            std::cout<<"Elemento insertado"<<endl;
            break;
        case 3:
            std::cout<<"Ingrese el numero flotante:"<<endl;
            std::cin>>dato;
            lista->insertar_inicio(dato);
            std::cout<<"Elemento insertado"<<endl;
            break;
        case 4:
            std::cout<<"Ingrese el numero flotante:"<<endl;
            std::cin>>dato;
            lista->insertar_final(dato);
            std::cout<<"Elemento insertado"<<endl;
            break;
        case 5:
            std::cout<<"Ingrese la posicion del elemento a eliminar:"<<endl;
            std::cin>>posicion;
            bool eliminado;
            eliminado = lista->borrar(posicion);
            std::cout<<"Elemento eliminado: "<<eliminado<<endl;
            break;
        case 6:
            std::cout<<"Ingrese la posicion del elemento a buscar:"<<endl;
            std::cin>>posicion;
            float elemento;
            elemento = lista->buscar(posicion);
            std::cout<<"Elemento: "<<elemento<<endl;
            break;
        case 7:
            std::cout<<"Ingrese el nuevo numero flotante:"<<endl;
            std::cin>>dato;
            std::cout<<"Ingrese la posicion del elemento a cambiar:"<<endl;
            std::cin>>posicion;
            bool cambiado;
            cambiado = lista->modificar(dato, posicion);
            std::cout<<"Elemento cambiado: "<<cambiado<<endl;
            break;
        default:
            break;
    }
}

void ejecutar_metodo(Lista<char>* lista, int opcion){
    char dato;
    int posicion;
    switch(opcion) {
        case 1:
            std::cout<<"Lista vacia: "<<lista->lista_vacia()<<endl;
            break;
        case 2:
            std::cout<<"Ingrese el caracter:"<<endl;
            std::cin>>dato;
            std::cout<<"Ingrese la posicion:"<<endl;
            std::cin>>posicion;
            lista->insertar(dato, posicion);
            std::cout<<"Elemento insertado"<<endl;
            break;
        case 3:
            std::cout<<"Ingrese el caracter:"<<endl;
            std::cin>>dato;
            lista->insertar_inicio(dato);
            std::cout<<"Elemento insertado"<<endl;
            break;
        case 4:
            std::cout<<"Ingrese el caracter:"<<endl;
            std::cin>>dato;
            lista->insertar_final(dato);
            std::cout<<"Elemento insertado"<<endl;
            break;
        case 5:
            std::cout<<"Ingrese la posicion del elemento a eliminar:"<<endl;
            std::cin>>posicion;
            bool eliminado;
            eliminado = lista->borrar(posicion);
            std::cout<<"Elemento eliminado: "<<eliminado<<endl;
            break;
        case 6:
            std::cout<<"Ingrese la posicion del elemento a buscar:"<<endl;
            std::cin>>posicion;
            char elemento;
            elemento = lista->buscar(posicion);
            std::cout<<"Elemento: "<<elemento<<endl;
            break;
        case 7:
            std::cout<<"Ingrese el nuevo caracter:"<<endl;
            std::cin>>dato;
            std::cout<<"Ingrese la posicion del elemento a cambiar:"<<endl;
            std::cin>>posicion;
            bool cambiado;
            cambiado = lista->modificar(dato, posicion);
            std::cout<<"Elemento cambiado: "<<cambiado<<endl;
            break;
        default:
            break;
    }
}

void ejecutar_metodo(Lista<Estudiante>* lista, int opcion){
    Estudiante estudiante;
    int posicion;
    switch(opcion) {
        case 1:{
            std::cout<<"Lista vacia: "<<lista->lista_vacia()<<endl;
            break;
        }
        case 2:{
            std::cout<<"Ingrese el nombre del estudiante:"<<endl;
            std::cin>>estudiante.nombre;
            std::cout<<"Ingrese el codigo del estudiante:"<<endl;
            std::cin>>estudiante.codigo;
            std::cout<<"Ingrese la posicion:"<<endl;
            std::cin>>posicion;
            lista->insertar(estudiante, posicion);
            std::cout<<"Elemento insertado"<<endl;
            break;
        }
        case 3:{
            std::cout<<"Ingrese el nombre del estudiante:"<<endl;
            std::cin>>estudiante.nombre;
            std::cout<<"Ingrese el codigo del estudiante:"<<endl;
            std::cin>>estudiante.codigo;
            lista->insertar_inicio(estudiante);
            std::cout<<"Elemento insertado"<<endl;
            break;
        }
        case 4:{
            std::cout<<"Ingrese el nombre del estudiante:"<<endl;
            std::cin>>estudiante.nombre;
            std::cout<<"Ingrese el codigo del estudiante:"<<endl;
            std::cin>>estudiante.codigo;
            lista->insertar_final(estudiante);
            std::cout<<"Elemento insertado"<<endl;
            break;
        }
        case 5:{
            std::cout<<"Ingrese la posicion del elemento a eliminar:"<<endl;
            std::cin>>posicion;
            bool eliminado;
            eliminado = lista->borrar(posicion);
            std::cout<<"Elemento eliminado: "<<eliminado<<endl;
            break;
        }
        case 6:{
            std::cout<<"Ingrese la posicion del elemento a buscar:"<<endl;
            std::cin>>posicion;
            Estudiante elemento;
            elemento = lista->buscar(posicion);
            std::cout<<"Elemento: "<<elemento.nombre<<" "<<elemento.codigo<<endl;
            break;
        }
        case 7:{
            std::cout<<"Ingrese el nombre del nuevo estudiante:"<<endl;
            std::cin>>estudiante.nombre;
            std::cout<<"Ingrese el codigo del nuevo estudiante:"<<endl;
            std::cin>>estudiante.codigo;
            std::cout<<"Ingrese la posicion del elemento a cambiar:"<<endl;
            std::cin>>posicion;
            bool cambiado;
            cambiado = lista->modificar(estudiante, posicion);
            std::cout<<"Elemento cambiado: "<<cambiado<<endl;
            break;
        }
        default:
            break;
    }
}