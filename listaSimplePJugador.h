#pragma once
#include <iostream>
#include "nodoPuntos.h"
using namespace std;

class listaSimplePJugador
{
private:
    nodoPuntos* primero;
    nodoPuntos* ultimo;


public:
    listaSimplePJugador();
    void insertarPrimero(nodoPuntos* n);
    void ordenar();
    void imprimir();
};

