#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H

template <typename Tipo, typename acceso>
struct cabecera {
    Tipo dato;
    acceso ubicacion;
    cabecera<Tipo, acceso> *sig;
};

template <typename T>
struct dato{
    T dato;
};

template <typename acceso>
struct nodoSig{
    acceso sig_codigo;
    acceso sig_nombre;
    acceso sig_carrera;
    acceso sig_actividad;
};

template <typename dato_1, typename dato_2, typename acceso>
struct nodo{
    dato_1 codigo;
    dato_2 nombre;
    dato_2 carrera;
    dato_2 actividad;
    nodoSig<acceso> *sig_nodo;
    nodo *sig;
};


#endif