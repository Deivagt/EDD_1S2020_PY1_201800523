#include "colaFichas.h"
#include "nodoFicha.h"
#include <iostream>
#include <fstream>
#include<string>
colaFichas::colaFichas() {
	primero = new nodoFicha();
	ultimo = new nodoFicha();
	primero->siguiente = ultimo;

	ultimo->siguiente = NULL;

}

void colaFichas::insertarPrimero(nodoFicha* n) {

	n->siguiente = primero->siguiente;
	primero->siguiente = n;

}
void colaFichas::ordenar() {

}
void colaFichas::imprimir() {
	nodoFicha* aux = new nodoFicha();
	aux = primero->siguiente;
	if (aux->siguiente == NULL) {
		cout << "La Cola esta vacia";
	}
	else {

		while (aux != ultimo) {
			cout << aux->letra;
			aux = aux->siguiente;
		}
	}
}

nodoFicha* colaFichas::sacarUltimo() {
	nodoFicha* auxPrevio = new nodoFicha();
	nodoFicha* aux = primero;

	if (aux->siguiente != ultimo) {
		while (aux->siguiente != ultimo)
		{
			auxPrevio = aux;
			aux = aux->siguiente;
		}

		auxPrevio->siguiente = ultimo;
		aux->siguiente = NULL;

		return aux;
	}
}

void colaFichas::graficar() {

		string encabezado = " digraph G {";

		encabezado = encabezado + "rankdir=LR;";



		nodoFicha* aux = this->primero->siguiente;

		int i = 1;
		string nodos = "";
		string dir = "";

		while (aux != this->ultimo) {

			nodos = nodos + "node" + to_string(i) + "[label = \"" + aux->letra + "\"];";
			if (aux->siguiente == this->ultimo) {
			
			}
			else {
				

				dir = dir + "node" + to_string(i) + " -> node" + to_string(i + 1) + ";";
			}


			i = i + 1;
			aux = aux->siguiente;
		}

		//nodos = nodos + "node" + to_string(i) + "[label = \"null\",width=0.5];";
		//string fi = "node1 ->node0;";
		string fin = "}";
		encabezado = encabezado + nodos + dir + fin;

		ofstream file;
		file.open("colaLetras.txt", ios::out);

		file << encabezado;
		file.close();

		string s1 = "dot -Tpng colaLetras.txt -o D:/grafos/colaLetras.png";

		system(s1.c_str());
		system("start D:/grafos/colaLetras.png");



	}
