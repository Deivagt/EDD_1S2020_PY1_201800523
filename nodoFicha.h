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
	int id;
	
	nodoFicha* siguiente;
	
	
	friend class colaFichas;
	

	

};

