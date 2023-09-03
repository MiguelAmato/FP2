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

using namespace std;

struct tPuzzle { // Contiene la información perteneciente a un puzzle:
	tMatrizChar matriz{};			// La matriz desafío
	tMatrizChar matrizResuelta{};	// La matriz objetivo
	string fichero;					// El fichero con el que estamos jugando
	string nombre;					// El nombre del puzzle
	short int numMovimientos = 0;	// El número de movimientos restantes
	bool resuelto = false;			// Nos indica si se ha resuelto el puzzle o no
	short int modo;
};

// Prototipos de las funciones necesarias.
void mainPuzzle(tPuzzle& puzzle);

void mostrarAcciones(tPuzzle const& puzzle);

void mostrar(tMatrizChar const& puzzle);

void mostrar(tPuzzle const& puzzle);

char final(tPuzzle& puzzle);

bool cargar(tPuzzle& puzzle);

bool jugar(tPuzzle& puzzle);

bool accion(tPuzzle& puzzle, string funcion);
