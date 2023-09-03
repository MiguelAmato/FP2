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

#include "Puzzle.h"

using namespace std;

const short int MAX_PUZZLES = 100;

typedef tPuzzle* tPuntPuzzles;

struct tListaPuzzles {
	tPuntPuzzles puzzle[MAX_PUZZLES] = {};
	short int cont = 0;
};

typedef tListaPuzzles tPuzzlesReunidos[2];

// Funciones del modulo ListaPuzzle;

void inicializar(tPuzzlesReunidos& jr);

bool cargar(tPuzzlesReunidos& jr);

void guardar(const tPuzzlesReunidos& listas);

void ordenar(tPuzzlesReunidos& jr, bool& orden, short int k);

void antiPasta(tPuzzle*& puntero1, tPuzzle*& puntero2);

short int elegirPuzzle(tListaPuzzles& lp);

bool insertarOrdenado(tListaPuzzles& l, tPuzzle *p);

void agregarPuzzle(tPuzzlesReunidos& jr);

short int buscar(const tListaPuzzles& lista, tPuzzle* puzzle);

