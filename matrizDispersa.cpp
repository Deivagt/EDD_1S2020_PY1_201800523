#include "matrizDispersa.h"
#include <iostream>
#include <fstream>
#include<string>

matrizDispersa::matrizDispersa() {
	raiz = new nodoMatriz();
	raiz->x = -1;
	raiz->y = -1;
	raiz->letra = '-';
}

void matrizDispersa::insertar(nodoMatriz* n) {
	/*cout << n->y;
	cout << n->x;*/
	nodoMatriz* nodoCol = buscarColumna(n->x);
	nodoMatriz* nodoFila =  buscarFila(n->y);


	//Fila = no Columna = no
	if (nodoFila == NULL && nodoCol == NULL) {
		//cout << "caso 1" << endl;
		nodoCol = crearColumna(n->x);
		nodoFila = crearFila(n->y);

		n = insertarColumna(n, nodoFila);
		n = insertarFila(n, nodoCol);
		return;

	}
	//Fila = si Columna = no
	else if (nodoCol == NULL && nodoFila != NULL  ) {
		//cout << "caso 2" << endl;
		nodoCol = crearColumna(n->x);
		n = insertarColumna(n, nodoFila);
		n = insertarFila(n, nodoCol);
		return;
	}
	//Fila = no Columna = si
	else if (nodoCol != NULL && nodoFila == NULL) {
		//cout << "caso 3" << endl;
		nodoFila = crearFila(n->y);
		n = insertarColumna(n, nodoFila);
		n = insertarFila(n, nodoCol);
		return;
	}
	// Fila = si Columna = si
	else if (nodoFila != NULL && nodoCol != NULL) {
		//cout << "caso 4" << endl;
		n = insertarColumna(n, nodoFila);
		n = insertarFila(n, nodoCol);
		return;
	}
}



nodoMatriz* matrizDispersa::buscarFila(int y) {
	nodoMatriz* temp = this->raiz;

	while (temp != NULL) {
		if (temp->y == y) {
			return temp;
		}
		temp = temp->abajo;
	}
	return NULL;
}
nodoMatriz* matrizDispersa::buscarColumna(int x) {
	nodoMatriz* temp = this->raiz;

	while (temp != NULL) {
		if (temp->x == x) {
			return temp;
		}
		temp = temp->derecha;
	}
	return NULL;
}


nodoMatriz* matrizDispersa::crearFila(int y) {
	nodoMatriz* encabezadoFila = this->raiz;
	nodoMatriz* nuevaFila = new nodoMatriz();
	nuevaFila->x = -1;
	nuevaFila->y = y;
	nuevaFila->letra = 'F';

	nodoMatriz* nuFi = insertarFila(nuevaFila, encabezadoFila);
	return nuFi;
}
nodoMatriz* matrizDispersa::crearColumna(int x) {
	nodoMatriz* encabezadoColumna = this->raiz;
	nodoMatriz* nuevaCol = new nodoMatriz();
	nuevaCol->x = x;
	nuevaCol->y = -1;
	nuevaCol->letra = 'C';

	nodoMatriz* nuCo = insertarColumna(nuevaCol, encabezadoColumna);
	return nuCo;

}

nodoMatriz* matrizDispersa::insertarFila(nodoMatriz* n, nodoMatriz* encabezadoFila) { // y
	nodoMatriz* temp = encabezadoFila;
	bool control = false;

	while (true) {
		if (temp->y == n->y) {
			temp->x = n->x;
			temp->letra = n->letra;
			return temp;
		}
		else if (temp->y > n->y) {
			control = true;
			break;
		}
		if (temp->abajo != NULL) {
			temp = temp->abajo;
		}
		else {
			break;
		}
	}
	if (control == true) {
		n->abajo = temp;
		temp->arriba->abajo = n;
		n->arriba = temp->arriba;
		temp->arriba = n;

	}
	else {
		temp->abajo = n;
		n->arriba = temp;
	}
	return n;
}
nodoMatriz* matrizDispersa::insertarColumna(nodoMatriz* n, nodoMatriz* encabezadoColumna) { // x
	nodoMatriz* temp = encabezadoColumna;
	bool control = false;

	while (true) {
		if (temp->x == n->x) {
			temp->y = n->y;
			temp->letra = n->letra;
			return temp;
		}
		else if (temp->x > n->x) {
			control = true;
			break;
		}

		if (temp->derecha != NULL) {
			temp = temp->derecha;
		}
		else {
			break;
		}
	}

	if (control == true) {
		n->derecha = temp;
		temp->izquierda->derecha = n;
		n->izquierda = temp->izquierda;
		temp->izquierda = n;

	}
	else {
		temp->derecha = n;
		n->izquierda = temp;
	}
	return n;
}


void matrizDispersa::imprimir() {
	nodoMatriz* temp = this->raiz;
	nodoMatriz* temp1;

	while (temp != NULL) {
		temp1 = temp;
		while (temp1 != NULL) {
			cout << temp1->letra << "|" << temp1->x << "," << temp1->y << "	";
			temp1 = temp1->derecha;
		}
		temp = temp->abajo;
		cout << endl;
	}




}
void matrizDispersa::graficar() {
	string encabezado = " digraph G {";

	nodoMatriz* auxiliar1 = this->raiz;
	nodoMatriz* auxiliar2 = this->raiz;





	string nodos = "";
	string dir = "";
	string rank = "";

	while (auxiliar1 != NULL) {
		auxiliar2 = auxiliar1;
		rank = rank + "{rank = same;";
		while (auxiliar2 != NULL)
		{
			

			if (auxiliar2->x < 0 && auxiliar2->y < 0) {

				rank = rank + nodos + "nodo" + "raiz" + ";";

				nodos = nodos + "nodo" + "raiz" +
					+"[label = \"" + auxiliar2->letra + "\"];\n";

				dir = dir + "nodo" + "raiz" + "->" +
					"nodo" + "x" + to_string(auxiliar2->derecha->x) +
					" [dir=\"both\",constraint = true];\n";

				dir = dir  +"nodo" + "raiz" + "->" +
					"nodo" + "y" + to_string(auxiliar2->abajo->y) +
					" [dir=\"both\"];\n";

			}
			else if (auxiliar2->x < 0) {
				rank = rank + "nodo" + "y" + to_string(auxiliar2->y) + ";";

				nodos = nodos + "nodo" + "y" + to_string(auxiliar2->y) +
					+"[label = \"" + auxiliar2->letra + "\"];\n";

				dir = dir + "nodo"+"y" + to_string(auxiliar2->y) + "->" +
					"nodo" + "x" + to_string(auxiliar2->derecha->x) + "y" + to_string(auxiliar2->derecha->y) +
					" [dir=\"both\",constraint = true];\n";

				if (auxiliar2->abajo != NULL) {
					dir = dir +"nodo"+ "y" + to_string(auxiliar2->y) + "->" +
						 "y" + to_string(auxiliar2->abajo->y) +
						" [dir=\"both\"];\n";
				}
			}
			else if (auxiliar2->y < 0) {
				rank = rank + "nodo" + "x" + to_string(auxiliar2->x) + ";";

				nodos = nodos + "nodo" + "x" + to_string(auxiliar2->x) +
					+"[label = \"" + auxiliar2->letra + "\"];\n";

				if (auxiliar2->derecha != NULL) {
					dir = dir + "nodo" + "x" + to_string(auxiliar2->x) + "->" +
						"nodo" + "x" + to_string(auxiliar2->derecha->x)  +
						" [dir=\"both\",constraint = true];\n";
				}
					dir = dir + "nodo" + "x" + to_string(auxiliar2->x) + "->" +
						"nodo" + "x" + to_string(auxiliar2->abajo->x) + "y" + to_string(auxiliar2->abajo->y) +
						" [dir=\"both\"];\n";
				
			}
			else {
				rank = rank + "nodo" + "x" + to_string(auxiliar2->x) + "y" + to_string(auxiliar2->y) + ";";
				nodos = nodos + "nodo" + "x" + to_string(auxiliar2->x) + "y" + to_string(auxiliar2->y) +
					+"[label = \"" + auxiliar2->letra + "\"];\n";
				if (auxiliar2->derecha != NULL) {
					dir = dir + "nodo" + "x" + to_string(auxiliar2->x) + "y" + to_string(auxiliar2->y) + "->" +
						"nodo" + "x" + to_string(auxiliar2->derecha->x) + "y" + to_string(auxiliar2->derecha->y) +
						" [dir=\"both\",constraint = true];\n";
				}
				if (auxiliar2->abajo != NULL) {
					dir = dir + "nodo" + "x" + to_string(auxiliar2->x) + "y" + to_string(auxiliar2->y) + "->" +
						"nodo" + "x" + to_string(auxiliar2->abajo->x) + "y" + to_string(auxiliar2->abajo->y) +
						" [dir=\"both\"];\n";
				}
			}
			
			auxiliar2 = auxiliar2->derecha;
		}
		rank = rank + "}";
		auxiliar1 = auxiliar1->abajo;
	}
	
	string fin = "}";
	encabezado = encabezado + nodos + dir+rank + fin;

	ofstream file;
	file.open("matriz.txt", ios::out);

	file << encabezado;
	file.close();

	string s1 = "dot -Tpng matriz.txt -o D:/grafos/matriz.png";

	system(s1.c_str());
	system("start D:/grafos/matriz.png");


}