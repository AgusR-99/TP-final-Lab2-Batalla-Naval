#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Matriz.h"
#include "Enums.h"
#include "FuncsMulti.h"
#include "ComportamientoIA.h"

void colocarNaveIA(Matriz tablero, int id, Nave nave[]) {
	nave[id].CrearNave(id);
	int x, y;
	Error validacion;
	char r;
	do {
		generarOrientacion(r);
		generarCoordenadas(x, y);
		validacion = validarColocacion(tablero, y, x, nave[id].getTamanio(), r);
		//Si no se cumple la validacion, se crean nuevos valores
	} while (validacion == Error::COLISION or validacion == Error::FUERA);
	nave[id].setOrientacion(r);
	tablero.ColocarNave(tablero, y, x, nave[id]);
}

void cazarNave(int& x, int& y, const int direccion) {
	switch (direccion) {
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