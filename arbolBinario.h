#pragma once
#include <iostream>
#include "nodoArbol.h"
using namespace std;

class arbolBinario
{
private:
	nodoArbol* raiz;
	nodoArbol* temp;
	int contador;
	int ct;
	string recGraf(nodoArbol* n);
	string recPre(nodoArbol* n);
	string recIn(nodoArbol* n);
	string recPos(nodoArbol* n);
	bool recorridoInsercion(nodoArbol* n1);
	void impresora(nodoArbol* n);
public:
	

	arbolBinario();
	bool insertar(nodoArbol* n);
	void imprimir();

	void graficar();
	void graficarPre();
	void graficarIn();
	void graficarPos();

};


