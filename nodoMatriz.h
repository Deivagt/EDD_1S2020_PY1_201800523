#pragma once
#include <iostream>

using namespace std;

class nodoMatriz
{


public:
	nodoMatriz* arriba;
	nodoMatriz* abajo;
	nodoMatriz* izquierda;
	nodoMatriz* derecha;

	string letra;
	int multiplicador;

	int x;
	int y;

};

