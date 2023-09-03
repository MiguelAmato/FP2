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

const short int DIM_MAX = 64; //Definimos el tamaño máximo del array del puzle.
using namespace std;

struct tCoor //Estructura para manejar coordenadas como pares de elementos.
{
	short int fila, columna;
};

bool operator == (tCoor c1, tCoor c2);

bool operator != (tCoor c1, tCoor c2);

bool operator <= (tCoor c1, tCoor dimension);

tCoor operator - (tCoor c1, tCoor c2);