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

const short int DIM_MAX = 64; //Definimos el tama�o m�ximo del array del puzle.
using namespace std;

struct tCoor //Estructura para manejar coordenadas como pares de elementos.
{
	short int fila, columna;
};

bool operator == (tCoor c1, tCoor c2);

bool operator != (tCoor c1, tCoor c2);

bool operator <= (tCoor c1, tCoor dimension);

tCoor operator - (tCoor c1, tCoor c2);