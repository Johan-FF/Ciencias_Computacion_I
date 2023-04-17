#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H

#include <string>

using namespace std;

struct cabecera {
    string dato;
    int ubicacion;
    cabecera *sig;
};

struct nodoSig{
    int sig_codigo;
    int sig_nombre;
    int sig_carrera;
    int sig_actividad;
};

struct nodo{
    int codigo;
    string nombre;
    string carrera;
    string actividad;
    nodoSig *sig_nodo;
    nodo *sig;
};


#endif