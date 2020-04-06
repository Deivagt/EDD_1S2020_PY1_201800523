#pragma once
#include <iostream>

using namespace std;

class nodoFicha
{
public:
	int puntuacion;
	string letra;
	int cantidad;
	
	nodoFicha* siguiente;
	
	friend class colaFichas;
	
};

