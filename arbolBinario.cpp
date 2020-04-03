#include "arbolBinario.h"
#include <iostream>
#include <fstream>
#include<string>

arbolBinario::arbolBinario() {
	contador = 0;

}

bool arbolBinario::insertar(nodoArbol* n) {

	if (raiz == NULL) {
		n->id = contador;
		contador++;
		this->raiz = n;
		return true;
	}
	else {
		temp = n;
		return recorridoInsercion(this->raiz);
	}

}

bool arbolBinario::recorridoInsercion(nodoArbol* n1) {

	int temporal = 0;
	if (temp->nombre.compare(n1->nombre) < 0) {
		temporal = 1;
	}
	else if (temp->nombre.compare(n1->nombre) > 0) {
		temporal = 2;
	}
	else if (temp->nombre.compare(n1->nombre) == 0) {
		temporal = 0;
	}

	if (temporal == 1) {
		if (n1->izq != NULL) {
			n1 = n1->izq;
			recorridoInsercion(n1);
		}
		else {
			temp->id = contador;
			contador++;
			n1->izq = temp;
			temp = NULL;
			return true;
		}
	}
	else if (temporal == 2) {
		if (n1->der != NULL) {
			n1 = n1->der;
			recorridoInsercion(n1);
		}
		else {
			temp->id = contador;
			contador++;
			n1->der = temp;

			temp = NULL;
			return true;
		}
	}
	else {
		cout << "el usuario ya existe";
		return false;
	}

}

void arbolBinario::imprimir() {
	impresora(this->raiz);

}
void arbolBinario::impresora(nodoArbol* n) {
	if (n == NULL) {
		return;
	}

	cout << n->nombre;
	impresora(n->izq);

	impresora(n->der);


}


void arbolBinario::graficar() {

	string encabezado = " digraph G {";

	string fin = "}";
	encabezado = encabezado + recGraf(raiz) + fin;

	ofstream file;
	file.open("arbol.txt", ios::out);

	file << encabezado;
	file.close();

	string s1 = "dot -Tpng arbol.txt -o D:/grafos/arbol.png";

	system(s1.c_str());
	system("start D:/grafos/arbol.png");




}
string arbolBinario::recGraf(nodoArbol* n) {
	string nodos;
	if (n->izq == NULL && n->der == NULL) {
		nodos = "node" + to_string(n->id) + "[label = \"" + n->nombre + "\"];";
	}
	else {
		nodos = "node" + to_string(n->id) + "[label = \"" + n->nombre + "\"];";
	}
	if (n->izq != NULL) {
		nodos = nodos + recGraf(n->izq) + "node" + to_string(n->id) + "->node" +
			to_string(n->izq->id) + "\n";
	}
	if (n->der != NULL) {
		nodos = nodos + recGraf(n->der) + "node" + to_string(n->id) + "->node" +
			to_string(n->der->id) + "\n";
	}

	nodos = nodos + "node" + to_string(raiz->id) + " [ label =\"" + raiz->nombre + "\"];\n";
	return nodos;
}


void arbolBinario::graficarPre() {
	ct = 0;
	string encabezado = " digraph G { rankdir= LR;";

	string fin = "}";
	encabezado = encabezado + recPre(raiz) ;
	string conecciones = "";
	for (int i = 0; i < ct-1; i++) {
		encabezado = encabezado + "node" + to_string(i) + "->node" +
			to_string(i+1) + "\n";
	}

	encabezado = encabezado + fin;
	ofstream file;
	file.open("pre.txt", ios::out);

	file << encabezado;
	file.close();

	string s1 = "dot -Tpng pre.txt -o D:/grafos/pre.png";

	system(s1.c_str());
	system("start D:/grafos/pre.png");
}
void arbolBinario::graficarIn() {
	ct = 0;
	string encabezado = " digraph G { rankdir= LR;";

	string fin = "}";
	encabezado = encabezado + recIn(raiz);
	string conecciones = "";
	for (int i = 0; i < ct - 1; i++) {
		encabezado = encabezado + "node" + to_string(i) + "->node" +
			to_string(i + 1) + ";\n";
	}
	encabezado = encabezado + fin;
	ofstream file;
	file.open("in.txt", ios::out);

	file << encabezado;
	file.close();

	string s1 = "dot -Tpng in.txt -o D:/grafos/in.png";

	system(s1.c_str());
	system("start D:/grafos/in.png");
}
void arbolBinario::graficarPos() {
	ct = 0;
	string encabezado = " digraph G { rankdir= LR;";

	string fin = "}";
	encabezado = encabezado + recPos(raiz);
	string conecciones = "";
	for (int i = 0; i < ct - 1; i++) {
		encabezado = encabezado + "node" + to_string(i) + "->node" +
			to_string(i + 1) + ";\n";
	}
	encabezado = encabezado + fin;
	ofstream file;
	file.open("pos.txt", ios::out);

	file << encabezado;
	file.close();

	string s1 = "dot -Tpng pos.txt -o D:/grafos/pos.png";

	system(s1.c_str());
	system("start D:/grafos/pos.png");
}

string arbolBinario::recPre(nodoArbol* n) {
	if (n == NULL) {
		return "";
	}

	string nodos;
	nodos = "node" + to_string(ct) + "[label = \"" + n->nombre + "\"];";
	ct++;

	nodos = nodos + recPre(n->izq);
	nodos = nodos + recPre(n->der);
	
	return nodos;

}
string arbolBinario::recIn(nodoArbol* n) {
	if (n == NULL) {
		return "";
	}

	string nodos;
	

	nodos = nodos + recIn(n->izq);
	nodos = nodos + "node" + to_string(ct) + "[label = \"" + n->nombre + "\"];";
	ct++;
	nodos = nodos + recIn(n->der);

	return nodos;
}
string arbolBinario::recPos(nodoArbol* n) {
	if (n == NULL) {
		return "";
	}

	string nodos;


	nodos = nodos + recPos(n->izq);
	nodos = nodos + recPos(n->der);
	nodos = nodos + "node" + to_string(ct) + "[label = \"" + n->nombre + "\"];";
	ct++;
	return nodos;
}
