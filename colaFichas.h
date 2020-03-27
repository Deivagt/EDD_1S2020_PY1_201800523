#pragma once
#include <iostream>
#include "nodoFicha.h"
using namespace std;

class colaFichas
{
private:
    nodoFicha* primero;
    nodoFicha* ultimo;


public:
    colaFichas();
    void insertarPrimero(nodoFicha* n);
    nodoFicha* sacarUltimo();
    nodoFicha* obtenerficha(int id);
    void ordenar();
    void imprimir();
};

