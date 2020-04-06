

#include "curses.h";
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <json.hpp>
#include <ctype.h>


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

/*Objetos escenciales*/
WINDOW* win;
using namespace std;
using json = nlohmann::json;

int dimension;

string nj1;
string nj2;
bool cj1;
bool cj2;
int pntJ1;
int pntJ2;

/*--------------------Metodos Declarados--------------------*/
void menuPrincipal();
void reportes();
void precargar();
void abrirArchivo();
void buscarPuntos();
void guardarConfig(json file);
void iniciarEstructuras();
void menuJuego();
void crearJugador();
void errorCrear();
void iniJuego();
void errorIni();
void inGameJ1();

void inGameJ2();

bool validarInsercion(string palabra, int x, int y, bool abajo, bool derecha);
void iniciarCola();

int main() {
	//iniciarEstructuras();

	iniciarEstructuras();
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

	precargar();
	//tablero->imprimir();

	nj1 = "abc";
	nj2 = "def";

	listaFichasJ1->llenar(cola);
	listaFichasJ2->llenar(cola);

	inGameJ1();

	endwin();

	return 0;
}

/*
int main()
{
	iniciarEstructuras();
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
*/
void menuPrincipal() {

	wclear(win);
	refresh();


	mvwprintw(win, 5, 8, "SCRABBLE++");

	mvwprintw(win, 7, 8, "MENU");
	mvwprintw(win, 8, 8, "1. Jugar");
	mvwprintw(win, 9, 8, "2. Cargar Configuracion");
	mvwprintw(win, 10, 8, "3. Scoreboard");
	mvwprintw(win, 11, 8, "4. Scoreboard (Por jugador)");
	mvwprintw(win, 12, 8, "5. Reportes");
	mvwprintw(win, 13, 8, "6. Salir");
	mvwprintw(win, 15, 8, "7. Precargar");

	wrefresh(win);

	while (true) {
		int c = wgetch(win);

		/*wprintw(win, "%i", c);*/
		if (c == 49) {
			menuJuego();
			menuPrincipal();

			break;
		}
		else if (c == 50) {
			abrirArchivo();
			menuPrincipal();
			break;
		}
		else if (c == 51) {
			listaScore->graficar();
			menuPrincipal();
			break;
		}
		else if (c == 52) {
			buscarPuntos();
			menuPrincipal();
			break;
		}
		else if (c == 53) {
			reportes();
			menuPrincipal();
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

			break;
		}
		else if (c == 50) {
			cola->graficar();

			break;
		}
		else if (c == 51) {
			arbol->graficar();

			break;
		}
		else if (c == 52) {

			arbol->graficarPre();

			break;
		}
		else if (c == 53) {
			arbol->graficarIn();

			break;
		}
		else if (c == 54) {
			arbol->graficarPos();

			break;
		}
		else if (c == 55) {

			break;
		}
	}
}

void buscarPuntos() {
	wclear(win);
	refresh();
	string entrada = "";

	mvwprintw(win, 4, 8, "Busqueda de historial");
	mvwprintw(win, 8, 8, "Escribe el nombre de usuario para ver su historial de puntos: ");

	mvwprintw(win, 13, 8, "7. Regresar");

	wrefresh(win);

	wmove(win, 9, 8);

	while (true) {
		int c = wgetch(win);

		if (c == 55) {

			break;
		}
		else

			if (c == 13) {
				if (arbol->buscar(entrada) == false) {
					buscarPuntos();

				}
				else {
					listaPuntosJugador->graficar(entrada, listaScore);
				}
				break;

			}
			else {
				entrada = entrada + (char)c;
			}
	}
}

void abrirArchivo() {
	wclear(win);
	refresh();
	string entrada = "";

	mvwprintw(win, 4, 8, "ABRIR ARCHIVO");
	mvwprintw(win, 8, 8, "Escribe la ruta del archivo: ");

	mvwprintw(win, 13, 8, "7. Regresar");

	wrefresh(win);

	wmove(win, 9, 8);

	while (true) {
		int c = wgetch(win);
		if (c == 24) {
			menuPrincipal();
			break;

		}
		else if (c == 55) {

			break;
		}
		else

			if (c == 13) {
				json file;
				try {
					ifstream in(entrada);
					file = json::parse(in);
					dimension = file["dimension"];
				}
				catch (exception e) {
					break;
				}



				break;

			}
			else {
				entrada = entrada + (char)c;
			}
	}
}

void guardarConfig(json file) {
	listaPalabras = new listaDobleCircular();
	tablero = new matrizDispersa();


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
}

void iniciarEstructuras() {
	arbol = new arbolBinario();;
	cola = new colaFichas();
	listaFichasJ1 = new listaD();
	listaFichasJ2 = new listaD();

	fichasTmp = new listaSimpleFichas();
	listaPuntosJugador = new listaSimplePJugador();//Busco por jugador
	listaScore = new listaSimpleTotal();//Historial
	listaPalabras = new listaDobleCircular();
	tablero = new matrizDispersa();
	cj1 = false;
	cj2 = false;
	pntJ1 = 0;
	pntJ2 = 0;
	iniciarCola();
}

void iniciarCola() {
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
}

void menuJuego() {

	wclear(win);
	refresh();


	mvwprintw(win, 5, 8, "OPCIONES:");

	mvwprintw(win, 7, 8, "1. Iniciar Partida");
	mvwprintw(win, 8, 8, "2. Crear nuevo jugador");

	mvwprintw(win, 12, 8, "7. Regresar");
	wrefresh(win);

	while (true) {
		int c = wgetch(win);


		if (c == 49) {
			nj1 = "";
			nj2 = "";
			pntJ1 = 0;
			pntJ2 = 0;
			listaFichasJ1 = new listaD();
			listaFichasJ2 = new listaD();
			iniJuego();

			break;
		}
		else if (c == 50) {
			crearJugador();
			menuJuego();
			break;
		}
		else if (c == 55) {

			break;
		}
	}
}

void crearJugador() {
	wclear(win);
	refresh();
	string entrada = "";

	mvwprintw(win, 4, 8, "CREAR NUEVO JUGADOR");
	mvwprintw(win, 8, 8, "Ingresa el nombre del nuevo jugador: ");

	mvwprintw(win, 13, 8, "7. Regresar");

	wrefresh(win);

	wmove(win, 9, 8);

	while (true) {
		int c = wgetch(win);

		if (c == 55) {

			break;
		}
		else
			if (c == 13) {
				if (arbol->buscar(entrada) == false) { // no existe
					nodoArbol* novo = new nodoArbol();
					novo->nombre = entrada;
					arbol->insertar(novo);
				}
				else { //existe
					errorCrear();
				}
				break;

			}
			else {
				entrada = entrada + (char)c;
			}
	}
}

void errorCrear() {
	wclear(win);
	refresh();
	string entrada = "";

	mvwprintw(win, 4, 8, "CREAR NUEVO JUGADOR");
	mvwprintw(win, 6, 8, "********ESTE USUARIO YA EXISTE********");
	mvwprintw(win, 8, 8, "Ingresa el nombre del nuevo jugador: ");

	mvwprintw(win, 13, 8, "7. Regresar");

	wrefresh(win);

	wmove(win, 9, 8);

	while (true) {
		int c = wgetch(win);

		if (c == 55) {

			break;
		}
		else
			if (c == 13) {
				if (arbol->buscar(entrada) == false) { // no existe
					nodoArbol* novo = new nodoArbol();
					novo->nombre = entrada;
					arbol->insertar(novo);
				}
				else { //existe
					errorCrear();
				}
				break;
			}
			else {
				entrada = entrada + (char)c;
			}
	}
}

void iniJuego() {
	wclear(win);
	refresh();
	string entrada = "";



	mvwprintw(win, 4, 8, "Seleccion de jugador");

	mvwprintw(win, 6, 8, "Jugador 1: ");
	mvwprintw(win, 6, 19, nj1.c_str());
	mvwprintw(win, 7, 8, "Jugador 2: ");
	mvwprintw(win, 7, 19, nj2.c_str());

	mvwprintw(win, 9, 8, "Ingresa el nombre del jugador (Ya debe existir): ");

	mvwprintw(win, 13, 8, "7. Regresar");

	wrefresh(win);

	wmove(win, 10, 8);

	while (true) {
		int c = wgetch(win);

		if (c == 55) {
			menuJuego();
			break;
		}
		else
			if (c == 13) {
				if (arbol->buscar(entrada) == false) { // no existe
					errorIni();
				}
				else { //existe
					if (nj1.empty() == true) {
						nj1 = entrada;
						iniJuego();
					}
					else if (nj2.empty() == true) {
						if (entrada.compare(nj1) == 0) {
							iniJuego();
						}
						else {
							nj2 = entrada;
							int num = rand() % 3;
							if (num == 0) {
								num = 1;
							}
							if (num == 1) {
								listaFichasJ1->llenar(cola);
								listaFichasJ2->llenar(cola);
								inGameJ1();
							}
							else if (num == 2) {
								listaFichasJ1->llenar(cola);
								listaFichasJ2->llenar(cola);
								inGameJ2();
							}
						}


					}

				}
				break;

			}
			else {
				entrada = entrada + (char)c;
			}
	}
}

void errorIni() {
	wclear(win);
	refresh();
	string entrada = "";

	const char* c;
	c = nj1.c_str();

	mvwprintw(win, 4, 8, "Seleccion de jugador");

	mvwprintw(win, 6, 8, "Jugador 1: ");
	mvwprintw(win, 6, 19, nj1.c_str());
	mvwprintw(win, 7, 8, "Jugador 2: ");
	mvwprintw(win, 7, 19, nj2.c_str());
	mvwprintw(win, 8, 8, "**********ESTE USUARIO NO EXISTE**********");

	mvwprintw(win, 9, 8, "Ingresa el nombre del jugador (Ya debe existir): ");

	mvwprintw(win, 13, 8, "7. Regresar");

	wrefresh(win);

	wmove(win, 10, 8);

	while (true) {
		int c = wgetch(win);

		if (c == 55) {
			menuJuego();
			break;
		}
		else
			if (c == 13) {
				if (arbol->buscar(entrada) == false) { // no existe
					errorIni();
				}
				else { //existe
					if (nj1.empty() == true) {
						nj1 = entrada;
						iniJuego();
					}
					else if (nj2.empty() == true) {
						if (entrada.compare(nj1) == 0) {
							iniJuego();
						}
						else {
							nj2 = entrada;
						}


					}

				}
				break;

			}
			else {
				entrada = entrada + (char)c;
			}
	}
}

void inGameJ1() {
	wclear(win);
	refresh();

	string palabra = "";
	int posX;
	int posY;
	bool derecha = false;
	bool abajo = false;


	mvwprintw(win, 1, 8, "Turno de ");
	mvwprintw(win, 1, 17, nj1.c_str());
	mvwprintw(win, 1, 30, "Puntuacion actual: ");
	mvwprintw(win, 1, 49, to_string(pntJ1).c_str());



	mvwprintw(win, 3, 8, "LETRAS DISPONIBLES:");

	int posTemporal = 8;
	nodoFichaActual* fichaTemporal = listaFichasJ1->primero->siguiente;
	for (int i = 1; i <= 7; i++) {
		string tmp = to_string(i) + ". " + fichaTemporal->letra.c_str() + " | ";

		mvwprintw(win, 4, posTemporal, tmp.c_str());
		fichaTemporal = fichaTemporal->siguiente;
		posTemporal = posTemporal + 7;
	}

	mvwprintw(win, 6, 8, "Escribe la palabra que quieres formar: ");



	mvwprintw(win, 13, 8, "6. Terminar Turno");
	mvwprintw(win, 13, 30, "7. Cambiar Fichas");
	mvwprintw(win, 15, 8, "8. Rendirse");
	mvwprintw(win, 15, 23, "9. Reporte de fichas J1");


	wrefresh(win);
	wmove(win, 7, 8);


	while (true) {
		int c = wgetch(win);

		if (c == 55) {

			break;
		}
		else if (c == 8) {
			palabra = palabra.erase(palabra.length() - 1);
		}
		else if (c == 57) {//GRAFICAR FICHAS
			listaFichasJ1->graficar("fichasJ1");////////////J2
			inGameJ1();
		}
		else if (c == 55) {
			mvwprintw(win, 4, 8, "                                                                                                ");
			int posTemporal = 8;

			listaFichasJ1->devolverCola(cola);/////// J2 
			listaFichasJ1 = new listaD();
			listaFichasJ1->llenar(cola);

			nodoFichaActual* fichaTemporal = listaFichasJ1->primero->siguiente;
			for (int i = 1; i <= 7; i++) {
				string tmp = to_string(i) + ". " + fichaTemporal->letra.c_str() + " | ";

				mvwprintw(win, 4, posTemporal, tmp.c_str());
				fichaTemporal = fichaTemporal->siguiente;
				posTemporal = posTemporal + 7;
			}
			mvwprintw(win, 13, 8, "N. Terminar Turno***");
			wrefresh(win);

			while (true) {
				int c = wgetch(win);
				if (c == 110) {
					inGameJ2();///////////////////////////Volver a j1
					break;
				}
			}

			break;
		}
		else if (c == 54) {//TERMINA EL TURNO
			inGameJ1();////////////////////////////////////////////////////DEVOLVER A J2

			break;
		}
		else if (c == 13) {
			/*bool buscarPalabra = listaPalabras->buscarYconfirmar(entrada);
			cout << buscarPalabra;*/
			mvwprintw(win, 6, 8, "                                                        ");
			mvwprintw(win, 6, 8, "Quieres formar la palabra: ");
			mvwprintw(win, 7, 8, palabra.c_str());

			mvwprintw(win, 9, 8, "Posicion X: ");
			wmove(win, 9, 20);

			wrefresh(win);
			string tempX;
			string tempY;

			while (true) {
				int c = wgetch(win);
				if (c == 13) {
					posX = stoi(tempX);
					tempX = "";
					mvwprintw(win, 9, 8, "Posicion X: ");
					mvwprintw(win, 9, 20, "                                             ");
					mvwprintw(win, 9, 20, to_string(posX).c_str());


					mvwprintw(win, 10, 8, "Posicion Y: ");
					wrefresh(win);
					wmove(win, 10, 20);

					while (true) {
						int c = wgetch(win);
						if (c == 13) {
							posY = stoi(tempY);
							tempY = "";
							mvwprintw(win, 10, 8, "Posicion Y: ");
							mvwprintw(win, 10, 20, "                                             ");
							mvwprintw(win, 10, 20, to_string(posY).c_str());

							mvwprintw(win, 11, 8, "Direccion: ");
							mvwprintw(win, 12, 8, "(D: Derecha ; A: Abajo)");
							wrefresh(win);
							wmove(win, 11, 19);

							while (true) {
								int c = wgetch(win);


								if (c == 97) {//Abajo
									abajo = true;
									derecha = false;
									mvwprintw(win, 11, 19, "                       ");
									mvwprintw(win, 12, 8, "                                ");

									mvwprintw(win, 11, 19, "Abajo");
									mvwprintw(win, 13, 8, "N. Terminar Turno***");
									wrefresh(win);
									wmove(win, 112, 19);
									
										while (true) {
											int c = wgetch(win);
											if (c == 110) { ///////////VALIDAR PALABRA Y TODO
												bool validacion = validarInsercion(palabra, posX, posY, abajo, derecha);

												if (validacion == true) {
													inGameJ2();
												
												}

												
												
												palabra = "";
												posX = 0;
												posY = 0;
												abajo = false;
												derecha = false;
												break;
											}
										}
										break;
									
								}
								else if (c == 100) {//Derecha
									derecha = true;
									abajo = false;
									mvwprintw(win, 11, 19, "                       ");
									mvwprintw(win, 12, 8, "                                ");
									mvwprintw(win, 11, 19, "Derecha");
									mvwprintw(win, 13, 8, "N. Terminar Turno***");
									wrefresh(win);
									wmove(win, 112, 19);
									while (true) {
										int c = wgetch(win);
										if (c == 110) { ///////////VALIDAR PALABRA Y TODO
											bool validacion = validarInsercion(palabra, posX, posY, abajo, derecha);
											/*
											*
											*
											*
											*
											*
											*
											*/
											
											if (validacion == true) {
												inGameJ2();
											}
											

											palabra = "";
											posX = 0;
											posY = 0;
											abajo = false;
											derecha = false;
											break;
										}
									}
									break;
								}

							}
							break;

						}
						else if (c > 47 && c < 58) {
							tempY = tempY + (char)c;
						}

					}

					break;
				}
				else if (c > 47 && c < 58) {
					tempX = tempX + (char)c;
				}
				
			}

			break;
		}
		else {
			palabra = palabra + (char)c;
		}
	}
}

bool validarInsercion(string palabra, int x, int y, bool abajo, bool derecha) {
	bool esCorrecto = true;
	//bool buscarPalabra = listaPalabras->buscarYconfirmar(palabra);

	//if (buscarPalabra == true) {
	
	for (int i = 0; i < palabra.length(); i++) {
		palabra = toupper(palabra[i]);
	}
		for (int i = 0; i < palabra.length(); i++) {
			nodoFichaActual* fichaAhora = listaFichasJ1->primero;
			while (fichaAhora != NULL) {
				if ((char)fichaAhora->letra[0] ==  palabra[i]) {
					break;
				}
				fichaAhora = fichaAhora->siguiente;
			}

			if (fichaAhora == NULL) {
				esCorrecto = false;
				return esCorrecto;
			}
			
		}

		if (derecha == true && abajo && false) { //Hacia derecha
			
		}
		else if (derecha == false && abajo && true) {//Hacia abajo

		}
	//}


	return esCorrecto;
}

void inGameJ2() {
	wclear(win);
	refresh();
	string entrada = "";




	mvwprintw(win, 1, 8, "Turno de ");
	mvwprintw(win, 1, 17, nj2.c_str());

	mvwprintw(win, 3, 8, "LETRAS DISPONIBLES:");

	int posTemporal = 8;
	nodoFichaActual* fichaTemporal = listaFichasJ2->primero->siguiente;
	for (int i = 1; i <= 7; i++) {
		string tmp = to_string(i) + ". " + fichaTemporal->letra.c_str() + " | ";

		mvwprintw(win, 4, posTemporal, tmp.c_str());
		fichaTemporal = fichaTemporal->siguiente;
		posTemporal = posTemporal + 7;
	}


	mvwprintw(win, 13, 8, "N. Terminar Turno");
	mvwprintw(win, 15, 8, "8. Rendirse");
	mvwprintw(win, 15, 23, "9. Reporte de fichas J2");



	//mvwprintw(win, 13, 8, "7. Regresar");

	wrefresh(win);

	wmove(win, 10, 8);

	while (true) {
		int c = wgetch(win);

		if (c == 55) {

			break;
		}
		else if (c == 57) {//GRAFICAR FICHAS
			listaFichasJ2->graficar("fichasJ2");
			inGameJ2();
		}
		else if (c == 110) {//TERMINA EL TURNO
			inGameJ1();

			break;
		}
		else if (c == 13) {//VALIDAR PALABRA

			inGameJ1();
			break;
		}
		else {



			entrada = entrada + (char)c;



		}
	}
}
void precargar() {

	/*arbol = new arbolBinario();;
	cola = new colaFichas();
	listaFichasJ1 = new listaD();
	listaFichasJ2 = new listaD();

	fichasTmp = new listaSimpleFichas();
	listaPuntosJugador = new listaSimplePJugador();//Busco por jugador
	listaScore = new listaSimpleTotal();//Historial
	listaPalabras = new listaDobleCircular();
	tablero = new matrizDispersa();*/


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
		aux->letra = 'T';

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

	nodoPuntos* p1 = new nodoPuntos();
	p1->nombre = "pepe";
	p1->puntuacion = 60;

	nodoPuntos* p2 = new nodoPuntos();
	p2->nombre = "alberto";
	p2->puntuacion = 80;

	nodoPuntos* p3 = new nodoPuntos();
	p3->nombre = "pepe";
	p3->puntuacion = 20;

	nodoPuntos* p4 = new nodoPuntos();
	p4->nombre = "felicia";
	p4->puntuacion = 150;

	nodoPuntos* p5 = new nodoPuntos();
	p5->nombre = "alberto";
	p5->puntuacion = 95;
	nodoPuntos* p6 = new nodoPuntos();
	p6->nombre = "alberto";
	p6->puntuacion = 1;

	listaScore->insertarPrimero(p1);
	listaScore->insertarPrimero(p2);
	listaScore->insertarPrimero(p3);
	listaScore->insertarPrimero(p4);
	listaScore->insertarPrimero(p5);
	listaScore->insertarPrimero(p6);
}


