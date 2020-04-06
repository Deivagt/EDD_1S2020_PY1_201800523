#include "listaSimplePJugador.h"
#include "nodoPuntos.h"
#include <iostream>
#include <fstream>
#include<string>
#include <algorithm>  

listaSimplePJugador::listaSimplePJugador() {
	primero = new nodoPuntos();
	ultimo = new nodoPuntos();
	primero->siguiente = ultimo;

	ultimo->siguiente = NULL;
	tamanio = 0;
}

void listaSimplePJugador::insertarPrimero(nodoPuntos* n) {

	n->siguiente = primero->siguiente;
	primero->siguiente = n;
	tamanio++;
}

void listaSimplePJugador::imprimir() {
	nodoPuntos* aux = new nodoPuntos();
	aux = primero->siguiente;
	if (aux->siguiente == NULL) {
		cout << "La lista esta vacia" << endl;
	}
	else {

		while (aux != ultimo) {
			cout << aux->puntuacion << endl;
			aux = aux->siguiente;
		}
	}
}

void listaSimplePJugador::graficar(string nombre, listaSimpleTotal* raices) {

	nodoPuntos* t = raices->primero->siguiente;
	string newname = "";
	
	for (int i = 0; i < nombre.length(); i++) {
		nombre[i] = tolower(nombre[i]);
	}


	while (t != raices->ultimo) {
		if (t->nombre.compare(nombre) == 0) {
			nodoPuntos* novo = new nodoPuntos();
			novo->nombre = t->nombre;
			novo->puntuacion = t->puntuacion;
			this->insertarPrimero(novo);
		}
		t = t->siguiente;
	}

	this->ordenar();

	if (this->primero->siguiente != this->ultimo) {

		string encabezado = " digraph G {";

		int i = 1;
		string nodos = "";
		string dir = "";

		nodoPuntos* aux = this->primero->siguiente;

		

		while (aux != this->ultimo) {

			nodos = nodos + "node" + to_string(i) + "[label = \"" + aux->nombre + ": " + to_string(aux->puntuacion) + "\"];";
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
		file.open("scoreboard.txt", ios::out);

		file << encabezado;
		file.close();

		string s1 = "dot -Tpng scoreboard.txt -o D:/grafos/scoreboard.png";

		system(s1.c_str());
		system("start D:/grafos/scoreboard.png");
	}
	





}

nodoPuntos* listaSimplePJugador::elementAt(int n) {
	nodoPuntos* nod = this->primero;
	int i = 0;
	while (i <= n) {
		nod = nod->siguiente;
		i++;
	}
	return nod;

}


void listaSimplePJugador::ordenar() {

	for (int i = 0; i < this->tamanio; i++) {

		for (int j = 0; j < this->tamanio - 1; j++) {

			if (this->elementAt(j)->puntuacion < this->elementAt(j + 1)->puntuacion) {
				nodoPuntos* t1 = new nodoPuntos();
				nodoPuntos* t2 = new nodoPuntos();
				nodoPuntos* t3 = new nodoPuntos();
				t1 = this->elementAt(j);
				t2 = this->elementAt(j - 1);
				t3 = this->elementAt(j + 1);

				t1->siguiente = t3->siguiente;
				t3->siguiente = t1;
				t2->siguiente = t3;


			}

		}

	}
}