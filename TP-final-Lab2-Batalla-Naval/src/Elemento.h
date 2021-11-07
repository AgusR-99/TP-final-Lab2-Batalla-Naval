#pragma once
#include "Nave.h"
#include <string>
class Elemento {
private:
	char sprite;
	std::string celda;
	Nave nave;
public:
	enum tipoCelda {
		VACIO,
		FALLO,
		GOLPE,
		NAVE,
	};
	enum tipoNave {
		PORTAAVIONES,
		ACORAZADO,
		DESTRUCTOR,
		FRAGATA,
		SUBMARINO
	};
	//Obtener sprite en posicion
	char getSprite();
	//Obtener nombre del elemento en posicion
	std::string getCelda();
	Nave getNave();
	//Setters
	void SetSprite(const int value);
	void setSpriteNave(int id);
	void SetCelda(const int value);
	void SetNave(Nave nave);
	//Constructor
	Elemento();
};