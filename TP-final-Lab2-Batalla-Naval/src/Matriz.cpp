#include "Matriz.h"
#include "Nave.h"
#include "rlutil.h"
#include "Enums.h"
#include "Constantes.h"

const int Matriz::getFilas() { return filas; }

const int Matriz::getColumnas() { return columnas; }

Elemento** Matriz::getElemento() { return arr; }

Matriz::Matriz() {
	arr = new Elemento * [filas];
	if (arr) {
		for (int i = 0; i < filas; i++) {
			arr[i] = new Elemento[columnas];
			assert(arr[i]);
		}
	}
	for (int f = 0; f < filas; f++) {
		for (int c = 0; c < columnas; c++) {
			arr[f][c].SetCelda(Elemento::tipoCelda::VACIO);
			arr[f][c].SetSprite(Elemento::tipoCelda::VACIO);
		}
	}
}

void Matriz::DibujarTabla() {
	std::cout << "  ";
	rlutil::locate(POSICION_MATRIX_X + 2, POSICION_MATRIX_Y);
	for (int x = 0; x < filas; x++) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < filas; i++) {
		rlutil::locate(POSICION_MATRIX_X, POSICION_MATRIX_Y + i + 1);
		std::cout << i << " ";
		for (int j = 0; j < columnas; j++) {
			std::cout << arr[i][j].getSprite();
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}
void Matriz::OcultarTablero() {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			if (arr[i][j].getCelda() == "Nave") {
				arr[i][j].SetSprite(Elemento::tipoCelda::VACIO);
			}
		}
	}
}
void Matriz::RevelarTablero() {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			if (arr[i][j].getCelda() != "Golpe" && arr[i][j].getCelda() != "Vacio") {
				Nave nave = arr[i][j].getNave();
				switch (nave.getDesignacion()) {
				case Nave::PORTAAVIONES:
					arr[i][j].setSpriteNave(Elemento::tipoNave::PORTAAVIONES);
					break;

				case Nave::ACORAZADO:
					arr[i][j].setSpriteNave(Elemento::tipoNave::ACORAZADO);
					break;

				case Nave::DESTRUCTOR:
					arr[i][j].setSpriteNave(Elemento::tipoNave::DESTRUCTOR);
					break;

				case Nave::FRAGATA:
					arr[i][j].setSpriteNave(Elemento::tipoNave::FRAGATA);
					break;

				case Nave::SUBMARINO:
					arr[i][j].setSpriteNave(Elemento::tipoNave::SUBMARINO);
					break;
				}
			}
		}
	}
}
void Matriz::DibujarTabla(int offsetX, int offsetY) {
	std::cout << "  ";
	rlutil::locate(POSICION_MATRIX_X + 2 + offsetX, POSICION_MATRIX_Y + offsetY);
	for (int x = 0; x < filas; x++) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < filas; i++) {
		rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + i + 1 + offsetY);
		std::cout << i << " ";
		for (int j = 0; j < columnas; j++) {
			std::cout << arr[i][j].getSprite();
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}
void Matriz::ColocarNave(Matriz tablero, int posY, int posX, Nave nave) {
	char r = nave.getOrientacion();
	int id = nave.getId();
	if (r == 'h' or r == 'H') {
		ColocarNaveHorizontal(posY, posX, nave.getTamanio(), nave, id);
	}
	else ColocarNaveVertical(posY, posX, nave.getTamanio(), nave, id);
}
void Matriz::ColocarNaveHorizontal(int posY, int posX, int size, Nave nave, int id) {
	for (int i = 0; i < size; i++) {
		arr[posY][posX].SetCelda(Elemento::tipoCelda::NAVE);
		arr[posY][posX].SetNave(nave);
		arr[posY][posX].setSpriteNave(id);
		posX++;
	}
}
void Matriz::ColocarNaveVertical(int posY, int posX, int size, Nave nave, int id) {
	for (int i = 0; i < size; i++) {
		arr[posY][posX].SetCelda(Elemento::tipoCelda::NAVE);
		arr[posY][posX].SetNave(nave);
		arr[posY][posX].setSpriteNave(id);
		posY++;
	}
}

int Matriz::ObtenerIDNave(int posY, int posX) {
	Elemento elemento = arr[posY][posX];
	Nave nave = elemento.getNave();
	return nave.getId();
}

void Matriz::DestruirCelda(int x, int y) {
	arr[y][x].SetCelda(Elemento::tipoCelda::GOLPE);
	arr[y][x].SetSprite(Elemento::tipoCelda::GOLPE);
}

void Matriz::FallaCelda(int x, int y) {
	arr[y][x].SetCelda(Elemento::tipoCelda::FALLO);
	arr[y][x].SetSprite(Elemento::tipoCelda::FALLO);
}

EstadoAtaque Matriz::ValidarAtaque(int x, int y) {
	int limiteX = columnas;
	int limiteY = filas;
	if (x >= limiteX or y >= limiteY or x < 0 or y < 0) return EstadoAtaque::FUERA;
	//Obtengo el tipo de celda en las coordenadas
	std::string celda = arr[y][x].getCelda();

	//Si la celda fue atacada
	if (celda == "Fallo" or celda == "Golpe") return EstadoAtaque::REPETIDO;
	return EstadoAtaque::OK;
}

Estado Matriz::Atacar(int x, int y) {
	//Obtengo el tipo de celda en las coordenadas
	std::string celda = arr[y][x].getCelda();
	//Si la celda es de una embarcacion, instrucciones...
	if (celda == "Nave") {
		return Estado::GOLPE;
	}
	else {
		//Si la celda esta vacia
		return Estado::FALLO;
	}
}