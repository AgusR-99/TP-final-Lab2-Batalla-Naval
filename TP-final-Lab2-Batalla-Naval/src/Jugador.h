#pragma once
#include <stdio.h>
#include <string>
class Jugador {
private:
	char nombre[15];
	int puntuaje;
	char resultado[15];
public:
	//Getters
	char* getNombre();
	int getPuntuaje();
	char* getResultado();
	//Setters
	void setNombre(char* name);
	void setPuntuaje(int p);
	void setResultado(char* res);
	//Constructor
	Jugador();
	//Metodos
	bool Grabar();
	bool Leer(int pos);
	void Mostrar(int, int);
	int ContarRegistros();
	void VaciarArchivo();
};