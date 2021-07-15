#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>

void colocarNaveIA(Matriz, int i);
void generarCoordenadas(int&, int&);
void generarOrientacion(char&);
void cazarNave(int& x, int& y, const int direccion);
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

void cazarNave(int& x, int& y, const int direccion) {
	switch (direccion){
	case ARRIBA:
		//Posicionamiento en celda superior
		y--;
		break;
	case ABAJO:
		//Posicionamiento en celda inferior
		y++;
		break;
	case IZQUIERDA:
		//Posicionamiento en celda izquierda
		x--;
		break;
	case DERECHA:
		//Posicionamiento en celda derecha
		x++;
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