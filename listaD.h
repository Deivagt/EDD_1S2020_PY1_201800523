#pragma once
#include <iostream>
#include "nodoFichaActual.h"
using namespace std;


class listaD
{
private:
    nodoFichaActual* primero;
    nodoFichaActual* ultimo;
    int indice = 0;

public:
    listaD();
    nodoFichaActual* getPrimero();
    nodoFichaActual* getUltimo();
 
    void insertarUltimo(char c);
    void eliminarUltimo();
    void eliminar(int id);
    void buscar(string s);
    int reemplazar(string b, string r);
    void reemplazar(string b, string r, int cantidad);
    void insertar(char c, nodoFichaActual* temp);
    void imprimir();
    listaD* duplicar();
    string texto();
};
