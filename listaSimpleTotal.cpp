#include "listaSimpleTotal.h"
#include "nodoPuntos.h"
#include <iostream>
#include <fstream>
#include<string>

listaSimpleTotal::listaSimpleTotal() {
    primero = new nodoPuntos();
    ultimo = new nodoPuntos();
    primero->siguiente = ultimo;
  
    ultimo->siguiente = NULL;
	tamanio = 0;
}
void listaSimpleTotal::insertarPrimero(nodoPuntos* n) {
	for (int i = 0; i < n->nombre.length(); i++) {
		n->nombre[i] = tolower(n->nombre[i]);
	}
	n->siguiente = primero->siguiente;
	primero->siguiente = n;
	tamanio++;

}
nodoPuntos* listaSimpleTotal::elementAt(int n) {
	nodoPuntos* nod = this->primero;
	int i = 0;
	while (i <= n) {
		nod = nod->siguiente;
		i++;
	}
	return nod;

}


void listaSimpleTotal::ordenar() {
	
	for (int i = 0; i < this->tamanio; i++) {
		
		for (int j = 0; j < this->tamanio - 1; j++) {
			
			if (this->elementAt(j)->puntuacion < this->elementAt(j+1)->puntuacion) {
				nodoPuntos* t1 = new nodoPuntos();
				nodoPuntos* t2= new nodoPuntos();
				nodoPuntos* t3 = new nodoPuntos();
				t1 = this->elementAt(j);
				t2 = this->elementAt(j-1);
				t3 = this->elementAt(j + 1);

				t1->siguiente = t3->siguiente;
				t3->siguiente = t1;
				t2->siguiente = t3;
				

			}
		
		}
		
	}
}
void listaSimpleTotal::imprimir() {
    nodoPuntos* aux = new nodoPuntos();
    aux = primero->siguiente;
    if (aux->siguiente == NULL) {
        cout << "La lista esta vacia" << endl;
    }
    else {

        while (aux != ultimo) {
            cout << aux->nombre<<" "<<aux->puntuacion <<endl;
            aux = aux->siguiente;
        }
    }
}


void listaSimpleTotal::graficar() {

	string encabezado = " digraph G {";


	this->ordenar();


	nodoPuntos* aux = this->primero->siguiente;

	int i = 1;
	string nodos = "";
	string dir = "";

	while (aux != this->ultimo) {

		nodos = nodos + "node" + to_string(i) + "[label = \"" + aux->nombre+": "+ to_string(aux->puntuacion) + "\"];";
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

