#include "Elemento.h"


Elemento::Elemento() {
	sprite = '?';
	celda = "?";
}

char Elemento::getSprite() { return sprite; }
std::string Elemento::getCelda() { return celda; }
Nave Elemento::getNave() { return nave; }

void Elemento::SetSprite(const int value) {
	switch (value) {
	case VACIO: sprite = '-';
		break;
	case FALLO: sprite = 'o';
		break;
	case GOLPE: sprite = 'X';
		break;
	default:
		sprite = '?';
		break;
	}
}

void Elemento::setSpriteNave(int id) {
	switch (id) {
	case PORTAAVIONES: sprite = 'P';
		break;
	case ACORAZADO: sprite = 'A';
		break;
	case DESTRUCTOR: sprite = 'D';
		break;
	case FRAGATA: sprite = 'F';
		break;
	case SUBMARINO: sprite = 'S';
		break;
	}
}

void Elemento::SetCelda(const int value) {
	switch (value) {
	case VACIO: celda = "Vacio";
		break;
	case FALLO: celda = "Fallo";
		break;
	case GOLPE: celda = "Golpe";
		break;
	case NAVE: celda = "Nave";
		break;
	default:
		celda = "?";
		break;
	}
}

void Elemento::SetNave(Nave nave) { this->nave = nave; }