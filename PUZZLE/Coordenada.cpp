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

bool operator == (tCoor c1, tCoor c2) { // Comprueba que dos coordenadas sean iguales.
	return (c1.columna == c2.columna && c1.fila == c2.fila);
}

bool operator != (tCoor c1, tCoor c2) { // Comprueba que dos coordenadas sean distintas.
	return (c1.fila != c2.fila && c1.columna != c2.columna );
}

bool operator <= (tCoor c1, tCoor dimension) { // Comprueba que dada una coordenada, esté dentro de las dimensiones permitidas. (Añadido por nosotros).
	return (c1.fila <= dimension.fila && c1.columna <= dimension.columna);
}

tCoor operator - (tCoor c1, tCoor c2) { //Suma dos coordenadas y devuelve un resultado.
	tCoor resta;
	resta.fila = c1.fila - c2.fila;
	resta.columna = c1.columna - c2.columna;
	return resta;
}