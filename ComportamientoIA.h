#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>

void colocarNaveIA(Matriz, int i);
void generarCoordenadas(int&, int&);
void generarOrientacion(char&);
void colocarNaveIA(Matriz tablero, int i){
	srand((unsigned)time(0));
	int x, y, validacion;
	char r;
	do {
		generarCoordenadas(x, y);
		generarOrientacion(r);
		shipIA[i].CrearNave(r, i);
		validacion = tablero.ColocarNave(shipIA[i], tablero, y, x);
		//Si no se cumple la validacion, se crean nuevos valores
	} while (validacion == -1 or validacion == 0);
}

void generarCoordenadas(int& x, int& y) {
	//0 hasta 10
	x = (rand() % 10);
	//0 hasta 10
	y = (rand() % 10);
}
void generarOrientacion(char& r) {
	//0 o 1 - v / h
	int rInt = (rand() % 2);
	if (rInt == 0) r = 'v';
	else r = 'h';
}