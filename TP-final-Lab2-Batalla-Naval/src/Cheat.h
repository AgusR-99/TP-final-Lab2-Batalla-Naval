#pragma once
class Cheat {
private:
	std::string nombre;
	TipoCheat tipo;
public:
	Cheat(std::string n, TipoCheat t);
	std::string getNombre();
	TipoCheat getTipo();
};

extern Cheat listaCheats[];
extern const size_t listaCheats_size;