
#pragma once
#include <iostream>
#include "nodoMatriz.h"
using namespace std;
class matrizDispersa
{
private:
	nodoMatriz* raiz;

public:
	matrizDispersa();

	nodoMatriz* buscarFila(int y);
	nodoMatriz* buscarColumna(int x);

	nodoMatriz* crearFila(int y);
	nodoMatriz* crearColumna(int x);

	nodoMatriz* insertarFila(nodoMatriz* n, nodoMatriz* encabezadoFila);
	nodoMatriz* insertarColumna(nodoMatriz* n, nodoMatriz* encabezadoColumna);

	void insertar(nodoMatriz* n);
	void graficar();
	void imprimir();

};

