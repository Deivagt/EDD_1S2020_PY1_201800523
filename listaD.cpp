#include "listaD.h"


listaD::listaD() {
    indice = 0;
    primero = new nodoFichaActual();
    ultimo = new nodoFichaActual();
    primero->siguiente = ultimo;
    primero->anterior = NULL;

    ultimo->anterior = primero;
    ultimo->siguiente = NULL;



}
void listaD::insertar(char c,nodoFichaActual* temp) {
    nodoFichaActual* aux = new nodoFichaActual();
    aux->letra = c;
    aux->id = indice;
    indice++;

    aux->siguiente = temp->siguiente;
    aux->anterior = temp;

    
    temp->siguiente->anterior = aux;
    temp->siguiente = aux;
}


void listaD::insertarUltimo(char c)
{
    nodoFichaActual* aux = new nodoFichaActual();
    aux->letra = c;
    aux->id = indice;
    indice++;
    aux->siguiente = ultimo;
    aux->anterior = ultimo->anterior;
    

    ultimo->anterior->siguiente = aux;
    ultimo->anterior = aux;

}

void listaD::eliminarUltimo() {
    nodoFichaActual* aux = new nodoFichaActual();

    if (!(primero->siguiente == ultimo && ultimo->anterior == primero)) {
        aux = ultimo->anterior;

        aux->anterior->siguiente = ultimo;
        ultimo->anterior = aux->anterior;

        aux->siguiente = NULL;
        aux->anterior = NULL;


    }
    else {
   
    }



}

void listaD::eliminar(int id) {
    nodoFichaActual* aux = new nodoFichaActual();
    
    aux = primero;
    while (aux->siguiente != ultimo) {
        aux = aux->siguiente;
   
        if (aux->id == id) {
            aux->anterior->siguiente = aux->siguiente;
            aux->siguiente->anterior = aux->anterior;
            aux->siguiente = NULL;
            aux->anterior = NULL;
            
            break;
        }
        
    }
}

nodoFichaActual* listaD::getPrimero() {
    return primero;
}
nodoFichaActual* listaD::getUltimo() {
    return ultimo;
}
void listaD::imprimir() {
    nodoFichaActual* aux = new nodoFichaActual();
    aux = primero->siguiente;
    if (aux->siguiente == NULL) {
  
    }
    else {

        while (aux != ultimo) {
            cout << aux->letra;
            aux = aux->siguiente;
        }
    }
}

void listaD::buscar(string s) {

    char buffer[100];
    int tB = 0;

    strcpy_s(buffer, s.c_str());
    
    nodoFichaActual* aux = new nodoFichaActual();
    nodoFichaActual* temp = new nodoFichaActual();
    aux = ultimo->anterior;
    bool match = false;

    if (aux->anterior == NULL) {
        cout << "La lista esta vacia" << endl;
    }
    else {

        while (aux != primero && match != true) {
            if (aux->letra == buffer[0]) {
                temp = aux;
                for (int i = 0; i < s.size(); i++) {
                    if (aux->letra == buffer[tB]) {
                        match = true;
                        tB++;
                    }
                    else {
                        match = false;
                        break;
                    }
                    aux = aux->anterior;
               }                  
                if (match != true) {
                    tB = 0;
               }               
            }            
            aux = aux->anterior;
        }
        if (match == true) {
            cout << "La primera letra es: " << temp->letra << endl;
        }
        else {
            cout << "Palabra no encontrada" << endl;
        }
    }

}

/*
int listaD::reemplazar(string b, string r) {
    char buffer[100];
    strcpy_s(buffer, b.c_str());
    char buffer1[100];
    strcpy_s(buffer1, r.c_str());
    int tB = 0;
    int cReemplazos = 0;
    bool match = false;
    nodoFichaActual* aux = new nodoFichaActual();
    nodoFichaActual* temp = new nodoFichaActual();
    aux = primero;
    if (aux->siguiente == ultimo) {
    }
    else {
        while (aux != ultimo ) {
            aux = aux->siguiente;
            if (aux->letra == buffer[0]&& (aux->anterior->letra == 32|| aux->anterior->letra == NULL)) {
                tB = 0;
                temp = aux;
                for (int i = 0; i < b.size(); i++) {
                    if (temp->letra == buffer[tB]) {
                        temp = temp->siguiente;
                        match = true;
                        tB++;
                    }
                    else if(buffer[tB] == 32) {
                    }
                    else {
                        match = false;
                    }
                }
                if (match == true && (temp->letra == 32|| temp->letra == NULL)) {
                    aux = aux->anterior;
                    temp = temp->anterior;
                    do {
                        temp = temp->anterior;
                        this->eliminar(temp->siguiente->id);
                    }while(temp != aux);
                    for (int k = 0; k <= r.size()-1; k++) {  
                        this->insertar(buffer1[k], temp);
                        temp = temp->siguiente;
                    }
                    cReemplazos++;
                }
            }
        }
    }
    return cReemplazos;
}

void listaD::reemplazar(string b, string r, int cantidad) {
    char buffer[100];
    strcpy_s(buffer, b.c_str());
    char buffer1[100];
    strcpy_s(buffer1, r.c_str());
    int tB = 0;
    int cReemplazos = 0;
    bool match = false;
    nodoFichaActual* aux = new nodoFichaActual();
    nodoFichaActual* temp = new nodoFichaActual();
    aux = primero;
    if (aux->siguiente == ultimo) {
    }
    else {
        while (aux != ultimo && cantidad > 0) {
            aux = aux->siguiente;
            if (aux->letra == buffer[0] && (aux->anterior->letra == 32 || aux->anterior->letra == NULL)) {
                tB = 0;
                temp = aux;
                for (int i = 0; i < b.size(); i++) {
                    if (temp->letra == buffer[tB]) {
                        temp = temp->siguiente;
                        match = true;
                        tB++;
                    }
                    else if (buffer[tB] == 32) {
                    }
                    else {
                        match = false;
                    }
                }
                if (match == true && (temp->letra == 32 || temp->letra == NULL)) {
                    aux = aux->anterior;
                    temp = temp->anterior;
                    do {
                        temp = temp->anterior;
                        this->eliminar(temp->siguiente->id);
                    } while (temp != aux);
                    for (int k = 0; k <= r.size() - 1; k++) {
                        this->insertar(buffer1[k], temp);
                        temp = temp->siguiente;
                    }
                    cReemplazos++;
                    cantidad--;
                }
            }
        }
    }
    
}

listaD* listaD::duplicar() {
    nodoFichaActual* temp = new nodoFichaActual();
    listaD* t = new listaD();
    temp = primero;

    while (temp != ultimo) {
        temp = temp->siguiente;
        if (temp != ultimo) {
            t->insertarUltimo(temp->letra);
        }
    }
    
    return t;
}

string listaD::texto() {
    nodoFichaActual* aux = new nodoFichaActual();
    string salida;
    aux = primero;
    while (aux != ultimo) {
        aux = aux->siguiente;
        salida = salida + aux->letra;

    }
    return salida;
}*/