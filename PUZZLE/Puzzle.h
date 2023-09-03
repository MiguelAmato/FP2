/*
-- Universidad Complutense de Madrid
-- Facultad de Inform�tica
-- Fundamentos de la programaci�n 2
--
-- Pr�ctica 2
--
-- Hecha por:
-- Ignacio S�nchez Santatecla (Ingenier�a de Computadores)
-- Miguel Antonio Amato Hermo (Ingenier�a de Software)
*/

#include "Matriz.h"

using namespace std;

struct tPuzzle { // Contiene la informaci�n perteneciente a un puzzle:
	tMatrizChar matriz{};			// La matriz desaf�o
	tMatrizChar matrizResuelta{};	// La matriz objetivo
	string fichero;					// El fichero con el que estamos jugando
	string nombre;					// El nombre del puzzle
	short int numMovimientos = 0;	// El n�mero de movimientos restantes
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
