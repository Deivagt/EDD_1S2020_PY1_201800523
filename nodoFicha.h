#pragma once
#include <iostream>
#include "listaD.h"
using namespace std;

class nodoFicha
{
public:
	int puntuacion;
	char letra;
	int cantidad;
	
	nodoFicha* siguiente;
	
	friend class colaFichas;
	

	

};

