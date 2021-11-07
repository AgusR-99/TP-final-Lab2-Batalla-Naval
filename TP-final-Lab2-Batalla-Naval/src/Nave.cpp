#include "Nave.h"
//Getters
int Nave::getTamanio() { return tamanio; }
int Nave::getSalud() { return salud; }
char Nave::getOrientacion() { return orientacion; }
std::string Nave::getNombre() { return nombre; }
Nave::Designacion Nave::getDesignacion() { return des; }
int Nave::getId() { return id; }
//Setters
void Nave::setTamanio(int tamanio) { this->tamanio = tamanio; }
void Nave::setSalud(int salud) { this->salud = salud; }
void Nave::setOrientacion(char orientacion) { this->orientacion = orientacion; }
void Nave::setNombre(std::string nombre) { this->nombre = nombre; }
void Nave::setDesignacion(Designacion des) { this->des = des; }
void Nave::setId(int id) { this->id = id; }
//Funcs
void Nave::CrearNave(int id) {
	switch (id) {
	case 0:
		this->tamanio = 5;
		salud = 5;
		nombre = "Portaaviones";
		des = Designacion::PORTAAVIONES;
		break;
	case 1:
		this->tamanio = 4;
		salud = 4;
		nombre = "Acorazado";
		des = Designacion::ACORAZADO;
		break;
	case 2:
		this->tamanio = 3;
		salud = 3;
		nombre = "Destructor";
		des = Designacion::DESTRUCTOR;
		break;
	case 3:
		this->tamanio = 3;
		salud = 3;
		nombre = "Fragata";
		des = Designacion::FRAGATA;
		break;
	case 4:
		this->tamanio = 2;
		salud = 2;
		nombre = "Submarino";
		des = Designacion::SUBMARINO;
		break;
	default:
		break;
	}
	this->id = id;
	this->orientacion = orientacion;
}
void Nave::DaniarNave() {
	//Le resto la salud en 1
	salud--;
}