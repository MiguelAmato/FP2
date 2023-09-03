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

#include "Matriz.h"
#include <iostream>
#include <fstream>

using namespace std;

bool cargar(tMatrizChar& matriz, ifstream& entrada) { 
	// Toma las dimensiones de la matriz y sus elementos desde un archivo de texto.
	// Devuelve false si no se ha podido realizar.
	bool cargar = false;
	if (entrada.is_open()) {
		entrada >> matriz.dimension.fila;
		entrada >> matriz.dimension.columna;

		for (short int i = 0; i < matriz.dimension.fila; i++) {
			for (short int j = 0; j < matriz.dimension.columna; j++) {
				entrada >> matriz.casilla[i][j];
			}
		}
		cargar = true;
	}

	return cargar;
}

bool operator == (tMatrizChar const& matriz1, tMatrizChar const& matriz2) {
	// Comprueba que dos matrices sean iguales, es muy útil para saber cuando se ha ganado.
	bool igual = true;
	short int i = 0, j = 0;
	if (matriz1.dimension.fila == matriz2.dimension.fila && matriz1.dimension.columna == matriz2.dimension.columna) {
		while (igual && i < matriz1.dimension.columna) {
			j = 0;
			while (igual && j < matriz1.dimension.fila) {
				if (matriz1.casilla[i][j] != matriz2.casilla[i][j])
					igual = false;
				j++;
			}
			i++;
		}
	}
	else igual = false;
	return igual;
}

bool swap(tMatrizChar& matriz, tCoor pos1, tCoor pos2) {
	/* Esta es la funcion principal que va a aparecer en todo el programa,
	se encarga de intercambiar el contenido de dos casillas introducidas.*/
	bool swap = false;
	char aux;
	if (pos1 <= matriz.dimension && pos1 <= matriz.dimension && tCoor{ 0, 0 } <= pos1 && tCoor{ 0, 0 } <= pos2) {
		aux = matriz.casilla[pos1.fila][pos1.columna];
		matriz.casilla[pos1.fila][pos1.columna] = matriz.casilla[pos2.fila][pos2.columna];
		matriz.casilla[pos2.fila][pos2.columna] = aux;
		swap = true;
	}
	return swap;
}

// ACCIONES DEL MODO 1D

/* TODAS LAS ACCIONES COMPRUEBAN SIEMPRE QUE SE TRANTEN DE MOVIMIENTOS PERMITIDOS ANTES DE REALIZARSE.
En caso contrario devolverán false.*/

bool swapF(tMatrizChar& matriz, short int f1, short int f2) { 
	// Intercambia dos filas.
	bool swapF = false;
	if (f1 < matriz.dimension.fila && f2 < matriz.dimension.fila && f1 >= 0 && f2 >= 0) {
		for (short int i = 0; i < matriz.dimension.columna; i++) {
			swapF = swap(matriz, { f1, i }, { f2, i });
		}
	}
	return swapF;
}

bool swapC(tMatrizChar& matriz, short int c1, short int c2) { 
	//Intercambia dos columnas.
	bool swapC = false;

	if (c1 < matriz.dimension.columna && c2 < matriz.dimension.columna && c1 >= 0 && c2 >= 0) {
		for (short int i = 0; i < matriz.dimension.fila; i++) {
			swapC = swap(matriz, { i, c1 }, { i, c2 });
		}
	}
	return swapC;
}

bool swapD(tMatrizChar& matriz, short int d) { 
	// Intercambia dos diagonales distintas a la principal.
	bool swapD = false;

	if (d < 0)
		d = -d;

	if (matriz.dimension.fila == matriz.dimension.columna && d < matriz.dimension.columna) {
		for (short int i = 0; i < matriz.dimension.columna; i++) {
			swapD = swap(matriz, { d, i }, { i, d });
			d++;
		}
	}
	return swapD;
}

bool voltearF(tMatrizChar& matriz, short int f) { 
	// Da la vuelta a la fila introducida respecto al eje imaginario vertical que cruza el medio del puzle.
	bool voltearF = false;

	if (f < matriz.dimension.fila && f >= 0) {
		for (short int i = 0; i < matriz.dimension.columna / 2; i++) {
			voltearF = swap(matriz, { f, i }, { f, (matriz.dimension.columna - 1) - i });
		}
	}
	return voltearF;
}

bool voltearC(tMatrizChar& matriz, short int c) {
	// Da la vuelta a la columna introducida respecto al eje imaginario horizontal que cruza el medio del puzle.
	bool voltearC = false;

	if (c < matriz.dimension.columna && c >= 0) {
		for (short int i = 0; i < (matriz.dimension.fila / 2); i++) {
			voltearC = swap(matriz, { i, c }, { (matriz.dimension.fila - 1) - i, c });
		}
	}
	return voltearC;
}

bool voltearD(tMatrizChar& matriz, short int d) { 
	// Da la vuelta a la diagonal introducida respecto al eje imaginario que cruza de la esquina inferior izquierda a la opuesta.
	bool voltearD = false;

	if (matriz.dimension.fila == matriz.dimension.columna && d < matriz.dimension.columna && d > -matriz.dimension.columna && d != 0) {
		// En caso de que el usuario introduzca la diagonal final (la esquina del puzle), se le informara y no le contará como movimiento
		if (d == matriz.dimension.columna - 1 || d == (-matriz.dimension.columna + 1)) {
			cout << "\nEse movimiento es inutil! Prueba otra vez.\n";
			voltearD = false;
		}
		// Si la diagonal es positiva:
		else if (d > 0) {
			for (short int i = 0; i < ((matriz.dimension.columna - d) / 2); i++) {
				voltearD = swap(matriz, { i, d }, { (matriz.dimension.columna - 1) - d, (matriz.dimension.columna - 1) - i });
				d++;
			}
		}
		// Si la diagonal es negativa:
		else {
			d = -d;
			for (short int i = 0; i < (matriz.dimension.fila - d) / 2; i++) {
				voltearD = swap(matriz, { d, i }, { ((matriz.dimension.fila - 1) - i), ((matriz.dimension.fila - 1) - d) });
				d++;
			}

		}
	}
	return voltearD;
}

// ACCIONES DEL MODO 2D

void voltearV(tMatrizChar& matriz) {
	// Voltea todo el puzle respecto a la vertical.
	for (short int i = 0; i < matriz.dimension.fila; i++) {
		voltearF(matriz, i);
	}
}

void voltearH(tMatrizChar& matriz) {
	// Voltea todo el puzle respecto a la horizontal.
	for (short int i = 0; i < matriz.dimension.columna; i++) {
		voltearC(matriz, i);
	}
}

bool voltearID(tMatrizChar& matriz, bool accionIndirecta) {
	// Voltea todo el puzle respecto a la diagonal. (matriz traspuesta)
	bool vul = false;
	short int max;

	// En caso de que se llame a esta función desde "RotarD" se ignora la condicion de que sean iguales para que se realice la acción.
	if (matriz.dimension.fila == matriz.dimension.columna || accionIndirecta) {

		if (matriz.dimension.columna < matriz.dimension.fila)
			max = matriz.dimension.fila;
		else max = matriz.dimension.columna;

		for (short int i = 0; i < max; i++) {
			for (short int j = i; j < max; j++) {
				swap(matriz, { i, j }, { j, i });
			}
		}
		vul = true;
	}
	return vul;
}

void rotarD(tMatrizChar& matriz) { 
	// Gira el puzle 90º a la derecha.

	short int aux;
	voltearID(matriz, true);

	// Se cambian las dimensiones de la matriz para que se pueda mostrar 
	aux = matriz.dimension.fila;
	matriz.dimension.fila = matriz.dimension.columna;
	matriz.dimension.columna = aux;

	voltearV(matriz);
}

bool swapAdy(tMatrizChar& matriz, tCoor pos1, tCoor pos2) { 
	// Intercambia las casillas adyacentes a dos posiciones.

	// Comprobamos que las coordenadas introducidas estén dentro del rango permitido.
	bool swapAdy = (pos1.fila < matriz.dimension.fila - 1 && pos1.columna < matriz.dimension.columna - 1 &&
		pos2.fila < matriz.dimension.fila - 1 && pos2.columna < matriz.dimension.columna - 1 && pos1.fila > 0 && pos1.columna > 0 &&
		pos2.fila > 0 && pos2.columna > 0 && (!(tCoor { 0, 3 } <= pos1 - pos2 || tCoor{ 0, 3 } <= pos2 - pos1) || !(tCoor{ 3, 0 } <= pos1 - pos2 || tCoor{ 3, 0 } <= pos2 - pos1)));

	// Si lo están comienza la funcion.
	if (swapAdy) {
		for (short int i = 0; i < 3; i++) {
			for (short int j = 0; j < 3; j++) {
				swap(matriz, { (pos1.fila - 1) + i, (pos1.columna - 1) + j }, { (pos2.fila - 1) + i, (pos2.columna - 1) + j });
			}
		}
		swap(matriz, pos1, pos2);
	}

	return swapAdy;
}