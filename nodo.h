#pragma once
#include <iostream>
using namespace std;

class nodo
{
public:

    char letra;
    int id;
    nodo* anterior;
    nodo* siguiente;
 
    friend class listaD;
};


