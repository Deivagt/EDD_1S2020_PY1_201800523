#pragma once
#include <iostream>
#include "nodoFicha.h"
using namespace std;

class colaFichas
{


public:
   
    colaFichas();
    void insertarPrimero(nodoFicha* n);
    nodoFicha* sacarUltimo();

    void ordenar();
    void imprimir();

    void graficar();

    nodoFicha* primero;
    nodoFicha* ultimo;
};

