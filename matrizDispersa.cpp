#include "matrizDispersa.h"


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
	nodoMatriz* temp = this->raiz->abajo;
	nodoMatriz* temp1;


	 do{
		temp1 = temp;
	//	cout << temp->letra << " " << temp->x << "," << temp->y << endl;
		 do{
			temp1 = temp1->derecha;
			cout << temp1->letra << " " << temp1->x << "," << temp1->y << endl;

			
		 } while (temp1->derecha != NULL);


		temp = temp->abajo;
	 } while (temp != NULL);



}