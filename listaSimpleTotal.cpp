#include "listaSimpleTotal.h"
#include "nodoPuntos.h"

listaSimpleTotal::listaSimpleTotal() {
    primero = new nodoPuntos();
    ultimo = new nodoPuntos();
    primero->siguiente = ultimo;
  
    ultimo->siguiente = NULL;

}

void listaSimpleTotal::insertarPrimero(nodoPuntos* n) {
    
    n->siguiente = primero->siguiente;
    primero->siguiente = n;
    
}
void listaSimpleTotal::ordenar() {

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