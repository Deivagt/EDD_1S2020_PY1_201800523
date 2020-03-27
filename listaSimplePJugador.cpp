#include "listaSimplePJugador.h"
#include "nodoPuntos.h"

listaSimplePJugador::listaSimplePJugador() {
    primero = new nodoPuntos();
    ultimo = new nodoPuntos();
    primero->siguiente = ultimo;
  
    ultimo->siguiente = NULL;

}

void listaSimplePJugador::insertarPrimero(nodoPuntos* n) {
    
    n->siguiente = primero->siguiente;
    primero->siguiente = n;
    
}
void listaSimplePJugador::ordenar() {

}
void listaSimplePJugador::imprimir() {
    nodoPuntos* aux = new nodoPuntos();
    aux = primero->siguiente;
    if (aux->siguiente == NULL) {
        cout << "La lista esta vacia" << endl;
    }
    else {

        while (aux != ultimo) {
            cout << aux->puntuacion<<endl;
            aux = aux->siguiente;
        }
    }
}