#include "listaDobleCircular.h"

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

void listaDobleCircular::imprimirDesdeInicio() {
	nodoPalabra* aux = primero->siguiente;
	
	while (aux != ultimo) {
		cout << aux->palabra<<endl;
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