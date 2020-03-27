#pragma once
#include <iostream>
#include "listaD.h"
using namespace std;

class nodoFichaActual
{
public:
	int puntuacion;
	char letra;
	int cantidad;
	int id;
	
	nodoFichaActual* siguiente;
	nodoFichaActual* anterior;
	
	friend class listaD;
};

