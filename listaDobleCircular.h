

#include <iostream>
#include "nodoPalabra.h"

using namespace std;


class listaDobleCircular
{
private:
    nodoPalabra* primero;
    nodoPalabra* ultimo;


public:
    listaDobleCircular();
    void insertarPrimero(nodoPalabra* n) ;
    void imprimirDesdeInicio();
    void imprimirDesdeFinal();
    nodoPalabra* getPrimero();
    nodoPalabra* getUltimo();
    nodoPalabra* buscar(string palabra);
    void graficar();
};

