#pragma once
#include <iostream>
#include "nodoPuntos.h"
using namespace std;

class listaSimpleTotal
{
private:
    nodoPuntos* primero;
    nodoPuntos* ultimo;


public:
    listaSimpleTotal();
    void insertarPrimero(nodoPuntos* n);
    void ordenar();
    void imprimir();
};

