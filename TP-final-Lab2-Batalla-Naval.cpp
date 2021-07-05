#include <iostream>
#include <Windows.h>
#include <assert.h>
#include <string>
#include <sstream>
using namespace std;
#include "rlutil.h"
using namespace rlutil;
stringstream buffer;

enum{
	HIGH,
	MEDIUM,
	LOW,
	INSTANT,
	FAST,
	NORMAL,
	SLOW
};

int setFreq(const int value) {
	switch (value) {
		case HIGH  : return 2000;
		case MEDIUM: return 1000;
		case LOW   : return 500;
	}
}

int setDuration(const int value) {
	switch (value) {
	case INSTANT: return 0;
	case FAST   : return 5;
	case NORMAL : return 15;
	case SLOW   : return 30;
	}
}

int PHIGH = 1200;
int PMEDIUM = 800;
int PLOW = 500;

int DNORMAL = 15;
int DSHORT = 5;
int DLONG = 30;
const int ANCHO_VENTANA = 80;
const int ALTO_VENTANA = 40;
const int POSICION_MATRIX_X = 20;
const int POSICION_MATRIX_Y = 1;

#include "Clases.h"
#include "ComportamientoIA.h"
#include "Funcs.h"

bool AjustarVentana(int Ancho, int Alto);

int main(){
	srand((unsigned)time(0));
	setlocale(LC_ALL, "spanish");
    AjustarVentana(ANCHO_VENTANA, ALTO_VENTANA);
	setColor(WHITE);
	setBackgroundColor(BLACK);
	saveDefaultColor();
    iniciarJuego();
    return 0;
}

bool AjustarVentana(int Ancho, int Alto) {
	_COORD Coordenada;
	Coordenada.X = Ancho;
	Coordenada.Y = Alto;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Right = Ancho - 1;
	Rect.Bottom = Alto - 1;

	// Obtener el handle de la consola
	HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);

	// Ajustar el buffer al nuevo tamaño
	SetConsoleScreenBufferSize(hConsola, Coordenada);

	// Cambiar tamaño de consola a lo especificado en el buffer
	SetConsoleWindowInfo(hConsola, TRUE, &Rect);
	return TRUE;
}