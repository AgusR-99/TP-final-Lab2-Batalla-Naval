#pragma once
#include <assert.h>
#include <iostream>
#include <string>
#include "Elemento.h"
#include "Enums.h"
class Matriz {
private:
	const int filas = 10;
	const int columnas = 10;
public:
	Elemento** arr;
	//Obtener cantidad de filas
	const int getFilas();
	//Obtener cantidad de columnas
	const int getColumnas();
	//Obtener elemento
	Elemento** getElemento();
	//Constructor
	Matriz();
	//Muestra la tabla
	void DibujarTabla();
	void DibujarTabla(int, int);
	//Colocar la nave en el tablero dada una posicion en X e Y
	void ColocarNave(Matriz tablero, int posY, int posX, Nave);
	void ColocarNaveHorizontal(int posY, int posX, int size, Nave, int);
	//La nave es colocada verticalmente
	void ColocarNaveVertical(int posY, int posX, int size, Nave, int);
	int ObtenerIDNave(int posY, int posX);
	void DestruirCelda(int x, int y);
	void FallaCelda(int x, int y);
	void OcultarTablero();
	void RevelarTablero();
	EstadoAtaque ValidarAtaque(int x, int y);
	//Ataque en la posicion. Si se produce un golpe, debe reducir el tamanio (salud) de la nave golpeada. Si el tamanio se reduce a 0, se debe eliminar el barco.
	Estado Atacar(int x, int y);
};