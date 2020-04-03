#pragma once
#include <iostream>
using namespace std;


class nodoArbol
{
public:
	string nombre;
	nodoArbol* izq;
	nodoArbol* der;
	int id;
	friend class arbolBinario;


};

