

#include "curses.h";
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <json.hpp>


/*------------------------Estructuras-----------------------*/
#include "arbolBinario.h";
#include "colaFichas.h";
#include "listaD.h";
#include "listaDobleCircular.h";
#include "listaSimpleFichas.h";
#include "listaSimplePJugador.h";
#include "listaSimpleTotal.h";
#include "matrizDispersa.h";

arbolBinario* arbol;
colaFichas* cola;
listaD* listaFichasJ1;
listaD* listaFichasJ2;
listaDobleCircular* listaPalabras;
listaSimpleFichas* fichasTmp;
listaSimplePJugador* listaPuntosJugador;//Busco por jugador
listaSimpleTotal* listaScore;//Historial
matrizDispersa* tablero;




/*--------------------Metodos Declarados--------------------*/
void menuPrincipal();
void reportes();
void precargar();


/*--------------------Metodos Reportes--------------------*/
void reportePalabras();
void reporteCola();

void reporteArbol();
void reportePreOrder();
void reporteInOrder();
void reportePostOrder();

void reportePuntosJ(string nombre);
void reporteScoreboard();

void actualizarMatriz();


/*Objetos escenciales*/
WINDOW* win;
using namespace std;
using json = nlohmann::json;

int dimension;


/*int main() {
	precargar();
	
}*/


int main()
{
	initscr();
	refresh();
	cbreak();
	raw();

	srand(time(NULL));

	constexpr int str_length = 11;

	constexpr int min_width = 13;
	constexpr int min_height = 3;
	constexpr int min_x = 0;
	constexpr int min_y = 0;

	int xMax, yMax;

	getmaxyx(stdscr, yMax, xMax);

	box(stdscr, 0, 0);

	int x = 0;
	int y = 0;

	win = newwin(yMax - 3, xMax - 3, 1, 1);

	refresh();
	wrefresh(win);

	keypad(win, true);

	menuPrincipal();

	endwin();

	return 0;




}

void menuPrincipal() {

	wclear(win);
	refresh();


	mvwprintw(win, 5, 8, "SCRABBLE++");

	mvwprintw(win, 7, 8, "MENU");
	mvwprintw(win, 8, 8, "1. Jugar");
	mvwprintw(win, 9, 8, "2. Cargar Configuracion");
	mvwprintw(win, 10, 8, "2. Scoreboard");
	mvwprintw(win, 11, 8, "3. Scoreboard (Por jugador)");
	mvwprintw(win, 12, 8, "5. Reportes");
	mvwprintw(win, 13, 8, "6. Salir");
	mvwprintw(win, 15, 8, "7. Precargar");

	wrefresh(win);

	while (true) {
		int c = wgetch(win);

		/*wprintw(win, "%i", c);*/
		if (c == 49) {


			break;
		}
		else if (c == 50) {



			break;
		}
		else if (c == 51) {


			break;
		}
		else if (c == 52) {

			break;
		}
		else if (c == 53) {
			reportes();
			break;
		}
		else if (c == 54) {
			exit(0);
			break;
		}
		else if (c == 55) {
			precargar();
			menuPrincipal();
			break;
		}
	}
}

void reportes() {
	wclear(win);
	refresh();


	mvwprintw(win, 4, 8, "Reportes");

	mvwprintw(win, 6, 8, "1. Lista de palabras (Lista Doble)");
	mvwprintw(win, 7, 8, "2. Cola actual de fichas (cola)");
	mvwprintw(win, 8, 8, "3. Nombres de usuario (arbol)");
	mvwprintw(win, 9, 8, "	4. Arbol preOrden");
	mvwprintw(win, 10, 8, "	5. Arbol inOrden");
	mvwprintw(win, 11, 8, "	6. Arbol postOrden");

	mvwprintw(win, 13, 8, "7. Regresar");


	wrefresh(win);

	while (true) {
		int c = wgetch(win);

		/*wprintw(win, "%i", c);*/
		if (c == 49) {
			listaPalabras->graficar();
			menuPrincipal();
			break;
		}
		else if (c == 50) {
			cola->graficar();
			menuPrincipal();
			break;
		}
		else if (c == 51) {
			arbol->graficar();
			menuPrincipal();
			break;
		}
		else if (c == 52) {
			
			arbol->graficarPre();
			menuPrincipal();
			break;
		}
		else if (c == 53) {
			arbol->graficarIn();
			menuPrincipal();
			break;
		}
		else if (c == 54) {
			arbol->graficarPos();
			menuPrincipal();
			break;
		}
		else if (c == 55) {
			menuPrincipal();
			break;
		}
	}
}


void precargar() {

	arbol = new arbolBinario();;
	cola = new colaFichas();
	listaFichasJ1 = new listaD();
	listaFichasJ2 = new listaD();
	listaPalabras = new listaDobleCircular();
	fichasTmp = new listaSimpleFichas();
	listaPuntosJugador = new listaSimplePJugador();//Busco por jugador
	listaScore = new listaSimpleTotal();//Historial
	tablero = new matrizDispersa();


	std::ifstream in("./entrada.json");
	json file = json::parse(in);


	dimension = file["dimension"];



	int contador = 0;



	while (file["diccionario"][contador] != nullptr) {
		string temp = file["diccionario"][contador]["palabra"];
		nodoPalabra* nuevo = new nodoPalabra();
		nuevo->palabra = temp;
		listaPalabras->insertarPrimero(nuevo);

		contador++;
	}
	contador = 0;

	while (file["casillas"]["dobles"][contador] != nullptr) {

		int xTemp = file["casillas"]["dobles"][contador]["x"];
		int yTemp = file["casillas"]["dobles"][contador]["y"];
		nodoMatriz* aux = new nodoMatriz();
		aux->x = xTemp;
		aux->y = yTemp;
		aux->letra = 'D';

		tablero->insertar(aux);

		contador++;
	}
	contador = 0;

	while (file["casillas"]["triples"][contador] != nullptr) {

		int xTemp = file["casillas"]["triples"][contador]["x"];
		int yTemp = file["casillas"]["triples"][contador]["y"];
		nodoMatriz* aux = new nodoMatriz();
		aux->x = xTemp;
		aux->y = yTemp;
		aux->letra = 'D';

		tablero->insertar(aux);

		contador++;
	}
	contador = 0;

	/*MEZCALR FICHAS*/
	int num;
	int maxAct = 25;
	srand(time(NULL));
	nodoFicha* auxi;
	nodoFicha* tmp;
	while (fichasTmp->tamano != 0) {


		num = rand() % (maxAct);
		if (num == 0) {
			num = 1;
		}
		auxi = fichasTmp->primero;
		tmp = new nodoFicha();

		for (int i = 1; i <= num; i++) {

			tmp = auxi;
			auxi = auxi->siguiente;


		}

		nodoFicha* novo = new nodoFicha();
		novo->letra = auxi->letra;
		novo->puntuacion = auxi->puntuacion;
		cola->insertarPrimero(novo);
		auxi->cantidad--;


		if (auxi->cantidad == 0) {
			tmp->siguiente = auxi->siguiente;
			auxi->siguiente = NULL;
			fichasTmp->tamano--;
			maxAct--;
		}


	}



	nodoArbol* n1 = new nodoArbol();
	n1->nombre = "pepe";
	nodoArbol* n2 = new nodoArbol();
	n2->nombre = "alberto";
	nodoArbol* n3 = new nodoArbol();
	n3->nombre = "susy";
	nodoArbol* n4 = new nodoArbol();
	n4->nombre = "felicia";
	nodoArbol* n5 = new nodoArbol();
	n5->nombre = "xarnold";

	arbol->insertar(n1);
	arbol->insertar(n2);
	arbol->insertar(n3);
	arbol->insertar(n4);
	arbol->insertar(n5);

}


/* std::ifstream in("./entrada.json");
	json file = json::parse(in);



	int contador = 0;

   while (file["casillas"]["dobles"][contador] != nullptr){
		cout << file["casillas"]["dobles"][contador]["x"] << endl;
		contador++;
	}*/

	/*Prueba cola de fichas*/
	/* colaFichas* prueba = new colaFichas();

		nodoFicha* letraA = new nodoFicha();
		letraA->letra = "a";
		letraA->id = 1;


		nodoFicha* letraB = new nodoFicha();
		letraB->letra = "b";
		letraB->id = 2;

		nodoFicha* letraC = new nodoFicha();
		letraC->letra = "c";
		letraC->id = 3;



		prueba->insertarPrimero(letraA);
		prueba->insertarPrimero(letraB);
		prueba->insertarPrimero(letraC);

		nodoFicha* retorno = prueba->obtenerficha(3);
		if (retorno->letra == "") {
			cout << "no";
		}
		else {
			cout << retorno->id;
		}


		prueba->imprimir();*/


