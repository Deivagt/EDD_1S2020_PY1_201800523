#pragma once
#include <iostream>
#include "nodoFicha.h"
using namespace std;

class listaSimpleFichas
{


public:
    nodoFicha* primero;
    nodoFicha* ultimo;
    int tamano;
    listaSimpleFichas();
    void insertarPrimero(nodoFicha* n);
    void ordenar();
    void imprimir();
    bool vacio();
   
    nodoFicha* buscar(int id);
};

