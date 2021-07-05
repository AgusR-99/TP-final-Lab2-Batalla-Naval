#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>

void colocarNaveIA(Matriz, int i);
void generarCoordenadas(int&, int&);
void generarOrientacion(char&);
void cazarNave(Matriz, int, int, int intento, int estado);
void colocarNaveIA(Matriz tablero, int i){
	
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

void cazarNave(Matriz tablero, int& x, int& y, int intento, int estado) {
	switch (intento){
	case 1:
		if (estado == -2 or estado == -3) x--;
		else x++;
		break;
	case 2:
		if (estado == -2 or estado == -3)
		break;
	case 3:

		break;
	case 4:

		break;
	case 5:

		break;
	case 6:

		break;
	default:
		break;
	}
}

void generarCoordenadas(int& x, int& y) {
	//0 a 9
	x = (rand() % 10);
	//0 a 9
	y = (rand() % 10);
}
void generarOrientacion(char& r) {
	//0 o 1 - v / h
	int rInt = (rand() % 2);
	if (rInt == 0) r = 'v';
	else r = 'h';
}