#pragma once
#include <iostream>
#include "nodoPuntos.h"
#include "listaSimpleTotal.h"
using namespace std;

class listaSimplePJugador
{


public:
    nodoPuntos* primero;
    nodoPuntos* ultimo;

    int tamanio;
    listaSimplePJugador();
    void insertarPrimero(nodoPuntos* n);
    
    void imprimir();
    void graficar(string nombre, listaSimpleTotal* raices);
    void ordenar();
    nodoPuntos* elementAt(int i);
};

