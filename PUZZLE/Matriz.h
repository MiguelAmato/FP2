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

#include "Coordenadas.h"
#include <fstream>

using namespace std;

struct tMatrizChar { // Esta es la estructura que conforma a cada puzle, con un tCoor que guarda sus dimensiones 
	tCoor dimension;
	char casilla[DIM_MAX][DIM_MAX]; // y una matriz bidimensional de caracteres que forma los colores.
};

//Prototipos de las funciones necesarias.

bool cargar(tMatrizChar& matriz, ifstream& entrada);

bool operator == (tMatrizChar const& matriz1, tMatrizChar const& matriz2);

bool swap(tMatrizChar& matriz, tCoor pos1, tCoor pos2);

bool swapF(tMatrizChar& matriz, short int f1, short int f2);

bool swapC(tMatrizChar& matriz, short int c1, short int c2);

bool swapD(tMatrizChar& matriz, short int d);

bool voltearF(tMatrizChar& matriz, short int f);

bool voltearC(tMatrizChar& matriz, short int c);

bool voltearD(tMatrizChar& matriz, short int d);

void voltearV(tMatrizChar& matriz);

void voltearH(tMatrizChar& matriz);

bool voltearID(tMatrizChar& matriz, bool accionDirecta);

void rotarD(tMatrizChar& matriz);

bool swapAdy(tMatrizChar& matriz, tCoor pos1, tCoor pos2);