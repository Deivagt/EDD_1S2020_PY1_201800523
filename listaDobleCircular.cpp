#include "listaDobleCircular.h"
#include <iostream>
#include <fstream>
#include<string>

listaDobleCircular::listaDobleCircular() {
	primero = new nodoPalabra();
	ultimo = new nodoPalabra();

	primero->siguiente = ultimo;
	primero->anterior = ultimo;
	ultimo->siguiente = primero;
	ultimo->anterior = primero;
}

void listaDobleCircular::insertarPrimero(nodoPalabra* n) {
	nodoPalabra* aux = new nodoPalabra();
	aux = primero;

	n->siguiente = aux->siguiente;
	aux->siguiente->anterior = n;

	aux->siguiente = n;
	n->anterior = aux;

}
nodoPalabra* listaDobleCircular::getPrimero() {
	return primero;
}
nodoPalabra* listaDobleCircular::getUltimo() {
	return ultimo;
}
nodoPalabra* listaDobleCircular::buscar(string palabra) {
	nodoPalabra* aux = new nodoPalabra();
	aux = primero;

	while (aux->siguiente != primero) {
		aux = aux->siguiente;
		if (aux->palabra.compare(palabra) != 0) {

			break;
		}

	}
	return aux;
}
bool listaDobleCircular::buscarYconfirmar(string palabra) {
	nodoPalabra* aux = new nodoPalabra();
	aux = primero;

	while (aux->siguiente != primero) {
		aux = aux->siguiente;
		if (aux->palabra.compare(palabra) == 0) {
			return true;
			
		}

	}
	return false;
}

void listaDobleCircular::imprimirDesdeInicio() {
	nodoPalabra* aux = primero->siguiente;

	while (aux != ultimo) {
		cout << aux->palabra << endl;
		aux = aux->siguiente;
	}

}

void listaDobleCircular::imprimirDesdeFinal() {
	nodoPalabra* aux = ultimo->anterior;

	while (aux != primero) {
		cout << aux->palabra << endl;
		aux = aux->anterior;
	}

}

void listaDobleCircular::graficar() {
	string encabezado = " digraph G {";

	encabezado = encabezado + "rankdir=LR;";
	


	nodoPalabra* aux = this->primero->siguiente;

	int i = 1;
	string nodos = "";
	string dir = "";

	while (aux != this->ultimo) {

		nodos = nodos + "node" + to_string(i) + "[label = \"" + aux->palabra + "\"];";
		if (aux->anterior == this->primero ) {
			dir = dir + "node" + to_string(i) + " -> node" + to_string(i + 1) + ";";
		}
		else if( aux->siguiente == this->ultimo) {
			dir = dir + "node" + to_string(i) + " -> node" + to_string(i - 1) + ";";
		}
		else {
			dir = dir + "node" + to_string(i) + " -> node" + to_string(i - 1) + ";";

			dir = dir + "node" + to_string(i) + " -> node" + to_string(i + 1) + ";";
		}
		

		i = i + 1;
		aux = aux->siguiente;
	}

	dir = dir + "node" + to_string(i-1) + " -> node" + to_string(1) + ";";
	dir = dir + "node" + to_string(1) + " -> node" + to_string(i-1) + ";";
	//nodos = nodos + "node" + to_string(i) + "[label = \"null\",width=0.5];";
	//string fi = "node1 ->node0;";
	string fin = "}";
	encabezado = encabezado + nodos + dir + fin;

	ofstream file;
	file.open("listaPalabras.txt", ios::out);

	file << encabezado;
	file.close();

	string s1 = "dot -Tpng listaPalabras.txt -o D:/grafos/listaPalabras.png";

	system(s1.c_str());
	system("start D:/grafos/listaPalabras.png");



}