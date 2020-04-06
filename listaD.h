#pragma once
#include <iostream>
#include "nodoFichaActual.h"
#include "colaFichas.h"


using namespace std;

class listaD
{


public:
    nodoFichaActual* primero;
    nodoFichaActual* ultimo;
    int indice = 0;
    listaD();
    nodoFichaActual* getPrimero();
    nodoFichaActual* getUltimo();
 
    void insertarUltimo(string c,int puntos);
    void eliminarUltimo();
    void eliminar(int id);
    void buscar(string s);
   /* int reemplazar(string b, string r);
    void reemplazar(string b, string r, int cantidad);*/
    void insertar(char c, nodoFichaActual* temp);
    void imprimir();
    void llenar(colaFichas* c);
    void graficar(string nombre);
    void devolverCola(colaFichas* c);
   /* listaD* duplicar();
    string texto();*/
};
