/*
-- Universidad Complutense de Madrid
-- Facultad de Informática
-- Fundamentos de la programación 2
--
-- Práctica 2
--
-- Hecha por:
-- Ignacio Sánchez Santatecla (Ingeniería de Computadores)
-- Miguel Antonio Amato Hermo (Ingeniería de Software)
*/

#include "ListaPuzzles.h"
#include "iostream"
#include "string"
#include <iomanip>
#include "UtilidadesSYS.h"

const string archivo = "datosPuzzles.txt";

using namespace std;

void inicializar(tPuzzlesReunidos& jr) {
	for (int i = 0; i < MAX_PUZZLES; i++) {
		jr[0].puzzle[i] = NULL;
		jr[1].puzzle[i] = NULL;
	}
}

bool cargar(tPuzzlesReunidos& jr) {

	ifstream lista;
	bool basaur = false;

	lista.open(archivo);
	if (lista.is_open()) {
		for (int i = 0; i < 2; i++) {
			short int numPuzzles;

			lista >> numPuzzles;
			lista.get();
			for (int j = 0; j < numPuzzles; j++) {
				jr[i].puzzle[j] = new tPuzzle;

				getline(lista, jr[i].puzzle[j]->nombre);
				getline(lista, jr[i].puzzle[j]->fichero);
				cargar(*jr[i].puzzle[j]);
				jr[i].puzzle[j]->modo = i + 1; // Jugada magistral de Nacho

				jr[i].cont++;
			}
		}
		basaur = true;
		lista.close();
	}

	return basaur;
}

void guardar(const tPuzzlesReunidos& listas) {

	ofstream lista;

	lista.open(archivo);
	for (int i = 0; i < 2; i++) {
		lista << listas[i].cont << "\n";
		for (int j = 0; j < listas[i].cont; j++) {
			lista << listas[i].puzzle[j]->nombre << "\n";
			lista << listas[i].puzzle[j]->fichero << "\n";
		}
	}

	// Se borran 
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < listas[i].cont; j++) {
			delete listas[i].puzzle[j];
		}
	}
}

void ordenar(tPuzzlesReunidos& jr, bool& orden, short int k) {
	if (orden) {
		bool intercambio = true;
		int i = 0;
		while ((i < jr[k].cont - 1) && intercambio) {
			intercambio = false;
			for (int j = jr[k].cont - 1; j > i; j--) {
				if (jr[k].puzzle[j]->numMovimientos < jr[k].puzzle[j - 1]->numMovimientos) {
					antiPasta(jr[k].puzzle[j], jr[k].puzzle[j - 1]);
					intercambio = true;
				}
				else if (jr[k].puzzle[j]->numMovimientos == jr[k].puzzle[j - 1]->numMovimientos) {
					if (jr[k].puzzle[j]->nombre < jr[k].puzzle[j - 1]->nombre) {
						antiPasta(jr[k].puzzle[j], jr[k].puzzle[j - 1]);
						intercambio = true;
					}
				}
				if (intercambio) {
					i++;
				}
			}
		}
	}

	else {
		for (short int i = 0; i < jr[k].cont / 2; i++) {
			antiPasta(jr[k].puzzle[i], jr[k].puzzle[(jr[k].cont - 1) - i]);
		}
		orden = false;
	}
}

void antiPasta(tPuzzle*& puntero1, tPuzzle*& puntero2) {
	tPuzzle* aux;
	aux = puntero1;
	puntero1 = puntero2;
	puntero2 = aux;
}

short int elegirPuzzle(tListaPuzzles& lp) {
	short int opcion;
	do {  
		for (long long int i = 0; i < lp.cont; i++) {
			cout << " " << setw(4 - (i / 10)) << left << i + 1 << lp.puzzle[i]->nombre << " con un maximo de " << lp.puzzle[i]->numMovimientos << " movimientos\n";
		}

		cout << " 0 " "  salir\n";
		cout << "-1 " "  Ordenar la lista de mayor a menor\n";
		cout << "-2 " "  Ordenar la lista de nemor a mayor\n\n";
		cout << "Elige un reto: ";
		cin >> opcion;
	} while (opcion < -2 || opcion > lp.cont);
	return opcion;
}

bool insertarOrdenado(tListaPuzzles& l, tPuzzle* p) {
	short int pos = buscar(l, p);
	bool devolver = false;
	if (pos != -1) {
		if (l.cont < MAX_PUZZLES) {
			if (pos == l.cont) {
				l.puzzle[pos] = p;
				devolver = true;
			}
			else {
				for (int i = l.cont - 1; i >= pos; i--) {
					l.puzzle[i + 1] = l.puzzle[i];
				}
				l.puzzle[pos] = p;
				devolver = true;
			}
			l.cont++;
			
		}
	}
	return devolver;
}

void agregarPuzzle(tPuzzlesReunidos& jr) {
	for (int i = 0; i < 2; i++) {
		cout << endl << setw(28) << right << "Juegos " << i + 1 << "D\n\n";
		for (long long int j = 0; j < jr[i].cont; j++) {
			cout << " " << setw(4 - (j / 10)) << left << j + 1 << jr[i].puzzle[j]->nombre << " con un maximo de " << jr[i].puzzle[j]->numMovimientos << " movimientos\n";
		}
		cout << "\n\n";
	}
	tPuzzle* p = new tPuzzle;
	string aux;

	cout << "Escriba el nombre del puzzle: ";
	cin.get();
	getline(cin, aux);
	p->nombre = aux;
	cout << "\n";

	do {
		cout << "Escriba nombre del fichero en que se encuentra: ";
		cin >> aux;
		p->fichero = aux;
	} while (aux.substr(6, aux.length() - 1) != "1D.txt" && aux.substr(6, aux.length() - 1) != "2D.txt");

	short int modo = aux[(aux.length() - 6)] - '0';
	p->modo = modo;

	if (cargar(*p)) {
		if (insertarOrdenado(jr[modo - 1], p)) {
			cout << "\n\nTu puzzle se agrego a la lista correctamente :D\n";
		}
	}
	else {
		cout << "\n\nEl puzzle no se pudo agregar a la lista :( \n";
	}
	pausa();
	borrar();
}

short int buscar(const tListaPuzzles& lista, tPuzzle* puzzle) {
	//Aqui descansa la busqueda binaria de Nacho :c OSTIAAAAAAAAAAAAAAAAA EL .h
	short int pos, i = 0;
	bool encontrado = false;
	while (!encontrado && i < lista.cont) {
		if (puzzle->numMovimientos < lista.puzzle[i]->numMovimientos) {
			pos = i;
			encontrado = true;
		}
		else if (puzzle->numMovimientos == lista.puzzle[i]->numMovimientos) {
			if (puzzle->nombre < lista.puzzle[i]->nombre) {
				pos = i;
				encontrado = true;
			}
			else if (puzzle->nombre == lista.puzzle[i]->nombre) {
				pos = -1;
				encontrado = true;
			}
		}	
		else {
			i++;
		}
	}
	return pos;
}