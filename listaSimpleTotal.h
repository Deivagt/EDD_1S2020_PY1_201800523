#pragma once
#include <iostream>
#include "nodoPuntos.h"
using namespace std;

class listaSimpleTotal
{

    


public:
    int tamanio;
    nodoPuntos* primero;
    nodoPuntos* ultimo;
    listaSimpleTotal();
    void insertarPrimero(nodoPuntos* n);
    void ordenar();
    void imprimir();
    void graficar();
    nodoPuntos* elementAt(int n);
};

