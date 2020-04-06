#include "listaSimpleFichas.h"
#include "nodoFicha.h"

listaSimpleFichas::listaSimpleFichas() {
	primero = new nodoFicha();
	ultimo = new nodoFicha();
	primero->siguiente = ultimo;
	
	ultimo->siguiente = NULL;

	tamano = 0;


	nodoFicha* A = new nodoFicha();
	A->letra = 'A';
	A->puntuacion = 1;
	A->cantidad = 12;
	this->insertarPrimero(A);


	nodoFicha* E = new nodoFicha();
	E->letra = 'E';
	E->puntuacion = 1;
	E->cantidad = 12;
	this->insertarPrimero(E);

	nodoFicha* I = new nodoFicha();
	I->letra = 'I';
	I->puntuacion = 1;
	I->cantidad = 6;
	this->insertarPrimero(I);

	nodoFicha* O = new nodoFicha();
	O->letra = 'O';
	O->puntuacion = 1;
	O->cantidad = 9;
	this->insertarPrimero(O);

	nodoFicha* S = new nodoFicha();
	S->letra = 'S';
	S->puntuacion = 1;
	S->cantidad = 6;
	this->insertarPrimero(S);

	nodoFicha* N = new nodoFicha();
	N->letra = 'N';
	N->puntuacion = 1;
	N->cantidad = 5;
	this->insertarPrimero(N);

	nodoFicha* L = new nodoFicha();
	L->letra = 'L';
	L->puntuacion = 1;
	L->cantidad = 4;
	this->insertarPrimero(L);

	nodoFicha* R = new nodoFicha();
	R->letra = 'R';
	R->puntuacion = 1;
	R->cantidad = 5;
	this->insertarPrimero(R);

	nodoFicha* U = new nodoFicha();
	U->letra = 'U';
	U->puntuacion = 1;
	U->cantidad = 5;
	this->insertarPrimero(U);

	nodoFicha* T = new nodoFicha();
	T->letra = 'T';
	T->puntuacion = 1;
	T->cantidad = 4;
	this->insertarPrimero(T);

	nodoFicha* D = new nodoFicha();
	D->letra = 'D';
	D->puntuacion = 2;
	D->cantidad = 5;
	this->insertarPrimero(D);

	nodoFicha* G = new nodoFicha();
	G->letra = 'G';
	G->puntuacion = 2;
	G->cantidad = 2;
	this->insertarPrimero(G);

	nodoFicha* C = new nodoFicha();
	C->letra = 'C';
	C->puntuacion = 3;
	C->cantidad = 4;
	this->insertarPrimero(C);

	nodoFicha* B = new nodoFicha();
	B->letra = 'B';
	B->puntuacion = 3;
	B->cantidad = 2;
	this->insertarPrimero(B);

	nodoFicha* M = new nodoFicha();
	M->letra = 'M';
	M->puntuacion = 2;
	M->cantidad = 2;
	this->insertarPrimero(M);

	nodoFicha* P = new nodoFicha();
	P->letra = 'P';
	P->puntuacion = 3;
	P->cantidad = 2;
	this->insertarPrimero(P);


	nodoFicha* H = new nodoFicha();
	H->letra = 'H';
	H->puntuacion = 4;
	H->cantidad = 2;
	this->insertarPrimero(H);

	nodoFicha* F = new nodoFicha();
	F->letra = 'F';
	F->puntuacion = 4;
	F->cantidad = 1;
	this->insertarPrimero(F);
	
	nodoFicha* V = new nodoFicha();
	V->letra = 'V';
	V->puntuacion = 4;
	V->cantidad = 1;
	this->insertarPrimero(V);

	nodoFicha* Y = new nodoFicha();
	Y->letra = 'Y';
	Y->puntuacion = 4;
	Y->cantidad = 1;
	this->insertarPrimero(Y);

	nodoFicha* Q = new nodoFicha();
	Q->letra = 'Q';
	Q->puntuacion = 5;
	Q->cantidad = 1;
	this->insertarPrimero(Q);

	nodoFicha* J = new nodoFicha();
	J->letra = 'J';
	J->puntuacion = 8;
	J->cantidad = 1;
	this->insertarPrimero(J);

	/*nodoFicha* Ñ = new nodoFicha();
	Ñ->letra = 'Ñ';
	Ñ->puntuacion = 8;
	Ñ->cantidad = 1;
	this->insertarPrimero(Ñ);*/

	nodoFicha* X = new nodoFicha();
	X->letra = 'X';
	X->puntuacion = 8;
	X->cantidad = 1;
	this->insertarPrimero(X);

	nodoFicha* Z = new nodoFicha();
	Z->letra = 'Z';
	Z->puntuacion = 10;
	Z->cantidad = 1;
	this->insertarPrimero(Z);

}

void listaSimpleFichas::insertarPrimero(nodoFicha* n) {

	n->siguiente = primero->siguiente;
	primero->siguiente = n;
	tamano++;
}
void listaSimpleFichas::ordenar() {

}

nodoFicha* listaSimpleFichas::buscar(int id) {
	nodoFicha* aux = this->primero;
	if (id <= tamano) {
		return NULL;
	}
	else {
		for (int i = 0; i <= id; i++) {
			aux = aux->siguiente;
		}
		return aux;
	}
}

bool listaSimpleFichas::vacio() {
	if (this->primero->siguiente == this->ultimo) {
		return true;
	}
	else {
		return false;
	}
}
/*mientras lista de letras no vacia, generar numero y agregar*/

void listaSimpleFichas::imprimir() {
	nodoFicha* aux = new nodoFicha();
	aux = primero->siguiente;
	if (aux->siguiente == NULL) {
		cout << "La lista esta vacia" << endl;
	}
	else {

		while (aux != ultimo) {
			cout << aux->letra << " " << aux->puntuacion << endl;
			aux = aux->siguiente;
		}
	}
}

