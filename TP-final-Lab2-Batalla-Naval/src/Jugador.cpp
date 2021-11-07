#include "Jugador.h"
#include "Constantes.h"
#include "rlutil.h"
Jugador::Jugador() {
	strcpy(nombre, "Nombre");
	puntuaje = 99;
	strcpy(resultado, "Sin terminar");
}

char* Jugador::getNombre() { return nombre; }
int Jugador::getPuntuaje() { return puntuaje; }
char* Jugador::getResultado() { return resultado; }
void Jugador::setNombre(char* name) { strcpy(nombre, name); }
void Jugador::setPuntuaje(int p) { puntuaje = p; }
void Jugador::setResultado(char* res) { strcpy(resultado, res); }
bool Jugador::Grabar() {
	FILE* p;
	bool escritura;
	p = fopen(rutaJugador, "ab");
	escritura = fwrite(this, sizeof(Jugador), 1, p);
	fclose(p);
	return escritura;
}

void Jugador::Mostrar(int offsetX, int offsetY) {
	rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
	std::cout << nombre;
	rlutil::locate(POSICION_MATRIX_X + offsetX + 16, POSICION_MATRIX_Y + offsetY);
	std::cout << puntuaje;
	rlutil::locate(POSICION_MATRIX_X + offsetX + 25, POSICION_MATRIX_Y + offsetY);
	std::cout << resultado;
}

bool Jugador::Leer(int pos) {
	FILE* p;
	p = fopen(rutaJugador, "rb");
	if (p == NULL) {
		return false;
	}
	fseek(p, pos * sizeof(Jugador), 0);
	bool lectura = fread(this, sizeof(Jugador), 1, p);
	fclose(p);
	return lectura;
}
int Jugador::ContarRegistros() {
	int pos = 0;
	while (Leer(pos++)) {
	}
	return pos;
}
void Jugador::VaciarArchivo() {
	FILE* p;
	bool escritura;
	p = fopen(rutaJugador, "wb");
	fclose(p);
}