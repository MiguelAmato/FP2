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

#include <iostream>
#include <iomanip>
#include "Puzzle.h"
#include "UtilidadesSYS.h"
#include <Windows.h>

using namespace std;

void mainPuzzle(tPuzzle& puzzle) {

	// Bucle principal de la resolución del puzzle
	do {
		mostrar(puzzle);
	} while (jugar(puzzle));
	// Se repetirá hasta que el usuario se quede sin movimientos o se haya resuelto el puzle.

	// Si se elige "Y" comienza el puzzle de nuevo.
	if (final(puzzle) == 'Y') {
		mainPuzzle(puzzle);
	}
}

char final(tPuzzle& puzzle) { // (Añadida por nosotros).
	// Esta funcion se ejecutará cuando se termine el juego.

	char opcion = 'N';
	borrar();
	cout << "\n   Puzzle a resolver:\n";
	mostrar(puzzle.matriz);
	cout << "\n   Imagen objetivo:\n";
	mostrar(puzzle.matrizResuelta);

	// Si las dos matrices son iguales te da la enhorabuena.
	if (puzzle.resuelto) {
		cout << "\nENHORABUENA!!!!\nHas sido capaz de realizar el puzle, tu nivel de iq acaba de aumentar un " << puzzle.numMovimientos << "%\n";
		pausa();
	}

	else {
		cout << "\n Ohhhh... Lo siento, no has sido capaz de resolver el puzle...\n Quieres volver a intentarlo? ";

		// Pregunta si quieres volver a jugar y recoge la opción elegida.
		cout << "Y / N: ";
		cin >> opcion;
	}
	borrar();
	cargar(puzzle);

	return opcion;
}

bool cargar(tPuzzle& puzzle) {
	// Toma desde el archivo elegido del puzle y lo carga en memoria.

	ifstream archivo;
	bool cargarJPM = false;

	archivo.open(puzzle.fichero);
	if (archivo.is_open()) {
		cargar(puzzle.matriz, archivo);
		cargar(puzzle.matrizResuelta, archivo);
		archivo >> puzzle.numMovimientos;
		cargarJPM = true;
	}
	archivo.close();

	return cargarJPM;
}

void mostrar(tMatrizChar const& matriz) {
	// Se encarga de mostrar en pantalla la matriz con sus respectivos colores.
	colorCTA(15, 0);
	cout << "\n  ";
	for (short int i = 0; i < matriz.dimension.columna; i++) {
		cout << setw(2) << i;
	}
	cout << "\n";
	for (short int i = 0; i < matriz.dimension.fila; i++) {
		colorCTA(15, 0);
		cout << setw(2) << i;
		for (short int j = 0; j < matriz.dimension.columna; j++) {
			colorCTA(matriz.casilla[i][j] - '0', matriz.casilla[i][j] - '0');
			cout << setw(2) << "";
		}
		colorCTA(15, 0);
		cout << "\n";
	}
}

void mostrar(tPuzzle const& puzzle) {
	// Borra la pantalla y muestra los dos puzzles
	borrar();
	cout << "Estas jugando a: " << puzzle.nombre << "\n";
	cout << "\n   Puzzle a resolver:\n";
	mostrar(puzzle.matriz);
	cout << "\n   Imagen objetivo:\n";
	mostrar(puzzle.matrizResuelta);
	cout << "\nTienes " << puzzle.numMovimientos << " movimientos restantes!\n";
}

bool jugar(tPuzzle& puzzle) {

	bool jugar = false;
	string movimiento;

	// Pide la accion a realizar, ya sea mostrar la lista de acciones o uno de los movimientos permitidos.
	do {
		cout << "Escribe el movimiento que deseas realizar ('A' para mostrar acciones): ";
		cin >> movimiento;

		if (movimiento[0] == 'A') {
			mostrarAcciones(puzzle);
		}
		else {
			jugar = accion(puzzle, movimiento);
			if (jugar) // Controla el numero de acciones que realiza el usuario
				puzzle.numMovimientos--;
			else cout << "\nEse movimiento no se puede realizar!\n";
		}
		// Si no se ha introducido una accion permitida volverá a solicitar que la intoduzcas.
	} while (!jugar);
	puzzle.resuelto = (puzzle.matriz == puzzle.matrizResuelta);
	jugar = (puzzle.numMovimientos > 0 && !puzzle.resuelto);

	return jugar;
}

bool accion(tPuzzle& jpm, string movimiento) {
	// Ejecuta la accion pedida por el usuario
	short int a, b, c, d; // Son los enteros que el usuario mete en consola para realizar las acciones
	bool accion = false;

	// Acciones del modo de juego 1D
	if (jpm.fichero[jpm.fichero.length() - 6] == '1') {
		if (movimiento[0] == 'S') {
			if (movimiento[1] == 'F') {	// Swap Fila
				cin >> a >> b;
				if (a != b)
					accion = swapF(jpm.matriz, a, b);
			}
			else if (movimiento[1] == 'C') { // Swap Columna
				cin >> a >> b;
				accion = swapC(jpm.matriz, a, b);
			}
			else if (movimiento[1] == 'D') { // Swap Diagonal
				cin >> a;
				accion = swapD(jpm.matriz, a);
			}
		}
		else if (movimiento[0] == 'V') {
			if (movimiento[1] == 'F') {	// Voltear Fila
				cin >> a;
				accion = voltearF(jpm.matriz, a);
			}
			else if (movimiento[1] == 'C') { // Voltear Columna
				cin >> a;
				accion = voltearC(jpm.matriz, a);
			}
			else if (movimiento[1] == 'D') { // Voltear Diagonal
				cin >> a;
				accion = voltearD(jpm.matriz, a);
			}
		}
	}
	// Acciones del modo de juego 2D
	else {
		accion = true;
		if (movimiento[0] == 'V') {
			if (movimiento[1] == 'V') // Voltear respecto a la vertical
				voltearV(jpm.matriz);
			else if (movimiento[1] == 'H') // Voltear respecto a la horizontal
				voltearH(jpm.matriz);
			else if (movimiento[1] == 'D') { // Voltear respecto a la diagonal
				accion = voltearID(jpm.matriz, false);
			}
			else accion = false;
		}
		else if (movimiento == "RD") { // Rotal la imagen 90º grados a la derecha
			rotarD(jpm.matriz);
		}
		else if (movimiento == "SA") { // Cambiar las posiciones adyacentes de dos posiciones de la matriz
			cin >> a >> b >> c >> d;
			if (a != c || b != d)
				accion = swapAdy(jpm.matriz, { a , b }, { c , d });

		}
		else accion = false;
	}
	return accion;
}

void mostrarAcciones(tPuzzle const& jpm) { // (Añadida por nosotros).
	// Muestra la lista de acciones disponibles que tiene el usuario para jugar dependiendo del modo (1D o 2D). 
	cout << "\nLista de Acciones:\n";
	// Lista de acciones del modo 1D
	if (jpm.modo == 1) {
		cout << "------------------------------------------" << endl;
		cout << "Intercambiar filas: " << setw(22) << right << "SF <f1> <f2>" << endl;
		cout << "Intercambiar columnas: " << setw(19) << right << "SC <c1> <c2>" << endl;
		cout << "Intercambiar diagonales: " << setw(11) << right << "SD <d>" << endl;
		cout << "Voltear fila: " << setw(25) << right << "VF <fila>" << endl;
		cout << "Voltear columna: " << setw(25) << right << "VC <columna>" << endl;
		cout << "Voltear diagonal: " << setw(25) << right << "VD <diagonal>" << endl;
		cout << "------------------------------------------" << endl << endl;
	}
	// Lista de acciones del modo 2D
	else {
		cout << "------------------------------------------------------------------------------" << endl;
		cout << "Voltear respecto a la vertical: " << setw(27) << right << "VV" << endl;
		cout << "Voltear respecto a la horizontal: " << setw(25) << right << "VH" << endl;
		cout << "Rotar a la derecha la imagen: " << setw(29) << right << "RD" << endl;
		cout << "Intercambiar las posiciones adyacentes de dos puntos:  " "	 SA <f1> <c1> <f2> <c2>" << endl;
		cout << "Voltear respecto a la diagonal principal: " << setw(17) << right << "VD" << endl;
		cout << "------------------------------------------------------------------------------" << endl << endl;
	}
}