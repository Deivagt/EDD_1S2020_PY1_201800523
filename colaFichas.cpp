#include "colaFichas.h"
#include "nodoFicha.h"

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

nodoFicha* colaFichas::obtenerficha(int id) {

	nodoFicha* aux = primero;


	while (aux != ultimo  )
	{
		if (aux->id == id) {
			break;
		}
		else {
			aux = aux->siguiente;
		}
		
	}
	
		return aux;
	
	


}