#pragma once
#include <string>
class Nave {
public:
	enum Designacion {
		PORTAAVIONES,
		ACORAZADO,
		DESTRUCTOR,
		FRAGATA,
		SUBMARINO
	};
	//Getters
	int getTamanio();
	int getSalud();
	char getOrientacion();
	std::string getNombre();
	Designacion getDesignacion();
	int getId();
	//Setters
	void setTamanio(int tamanio);
	void setSalud(int salud);
	void setOrientacion(char orientacion);
	void setNombre(std::string nombre);
	void setDesignacion(Designacion des);
	//Tipo-> 0-Portaaviones, 1-Acorazado, 2-Destructor, 3-Fragata, 4-Submarino.
	void setId(int id);
	void CrearNave(int id);
	//Reduce la salud en 1
	void DaniarNave();
private:
	int tamanio;
	int salud;
	char orientacion;
	std::string nombre;
	int id;
	Designacion des;
};