#include <iostream>
#include "Enums.h"
#include "Cheat.h"

std::string Cheat::getNombre() { return nombre; }

TipoCheat Cheat::getTipo() { return tipo; }

Cheat::Cheat(std::string n, TipoCheat t) {
	nombre = n;
	tipo = t;
}

Cheat listaCheats[] = {
   Cheat("thisistoohard", TipoCheat::GANAR),
   Cheat("seppuku",	   TipoCheat::PERDER),
   Cheat("xmarksthespot", TipoCheat::REVELAR)
};

const size_t listaCheats_size = sizeof(listaCheats) / sizeof(listaCheats[0]);