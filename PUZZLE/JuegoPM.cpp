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
#include "JuegoPM.h"
#include "UtilidadesSYS.h"
#include <Windows.h>

void mainPuzzlesReunidos() {
	tPuzzlesReunidos jr;
	short int opcion;
	bool orden = true;
	
	inicializar(jr);
	if (cargar(jr)) {
		do {
			opcion = menu() - '0';
			switch (opcion) {
			case 0: 
				break;
			case 1: resolverPuzzle(jr, opcion, orden);
				break;
			case 2: resolverPuzzle(jr, opcion, orden);
				break;
			case 3: agregarPuzzle(jr);
				break;
			default:
				break;
			}
		} while (opcion != 0);
		orden = true;
		ordenar(jr, orden, 0);
		ordenar(jr, orden, 1);
		guardar(jr);
	}
	else {
		cout << "Error al cargar el archivo\n";
	}
}

void resolverPuzzle(tPuzzlesReunidos& jr, short int& opcion, bool& orden) {

	short int lista = opcion - 1;

	opcion = elegirPuzzle(jr[lista]);
	if (opcion < 0) {
		if (opcion == -1) {
			if (orden) {
				// Si la lista está ordenada, convertimos a false el parametro orden para reordenarla de mayor a menor.
				orden = false;
				ordenar(jr, orden, lista);
			}
		}
		else {
			if (!orden) {
				// Si la lista está ordenada inversamente, convertimos a true el parámetro orden para ordenarla de menor a mayor.
				orden = true;
				ordenar(jr, orden, lista);
			}
		}
	}
	else if (opcion > 0) {
		mainPuzzle(*jr[lista].puzzle[opcion - 1]);
	}
	else {
		opcion = lista + 1;
		borrar();
	}
}

char menu() {
	// Muestra los modos de juego disponible.

	char opcion;
	do {
		cout << "Elige un modo de juego! \n\n";
		cout << "1 Para jugar en 1D\n";
		cout << "2 Para jugar en 2D\n";
		cout << "3 Para agregar un nuevo puzzle\n";
		cout << "0 Salir del programa\n";
		cout << "Modo: ";

		// Recoge la opción deseada.
		cin >> opcion;
		if (opcion < '0' || opcion > '3') {
			cout << "\nEso no se puede! Prueba otra vez\n";
			Sleep(1000);
		}
		borrar();

	} while (opcion < '0' || opcion > '3');
	return (opcion);
}