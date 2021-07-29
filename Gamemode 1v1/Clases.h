#pragma once
const char* rutaJugador = "Gamemode 1v1/player.dat";

enum class Error {
	ORIENTACION,
	FUERA,
	COLISION,
	OK,
};

enum class EstadoAtaque {
	FUERA,
	REPETIDO,
	GOLPE,
	FALLO,
	HUNDIDO,
	OK
};

enum class Input {
	NOCMD,
	DEBUG,
	QUITAR,
	COORD,
	BAD,
	OK
};

enum class Frecuencia {
	ALTA,
	MEDIA,
	BAJA
};

enum class Duracion {
	INSTANTANEO,
	RAPIDO,
	NORMAL,
	LENTO
};

enum class Resultados {
	VICTORIA, DERROTA, SIN_TERMINAR, TRAMPOSO
};

class Jugador {
private:
	char nombre[15];
	int puntuaje;
	char resultado[15];
public:
	//Getters
	char* getNombre() { return nombre; }
	int getPuntuaje() { return puntuaje;}
	char* getResultado() { return resultado; }
	//Setters
	void setNombre(char* name) { strcpy(nombre, name); }
	void setPuntuaje(int p) { puntuaje = p; }
	void setResultado(char* res) { strcpy(resultado, res); }
	//Constructor
	Jugador();
	//Metodos
	bool Grabar();
	bool Leer(int pos);
	void Mostrar(int, int);
	int ContarRegistros();
	void VaciarArchivo();
};

Jugador::Jugador() {
	strcpy(nombre, "Nombre");
	puntuaje = 99;
	strcpy(resultado, "Sin terminar");
}

bool Jugador::Grabar() {
	FILE* p;
	bool escritura;
	p = fopen(rutaJugador, "ab");
	escritura = fwrite(this, sizeof(Jugador), 1, p);
	fclose(p);
	return escritura;
}

void Jugador::Mostrar(int offsetX, int offsetY) {
	locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
	cout << nombre;
	locate(POSICION_MATRIX_X + offsetX + 16, POSICION_MATRIX_Y + offsetY);
	cout << puntuaje;
	locate(POSICION_MATRIX_X + offsetX + 25, POSICION_MATRIX_Y + offsetY);
	cout << resultado;
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
	int getTamanio() { return tamanio; }
	int getSalud() { return salud; }
	char getOrientacion() { return orientacion; }
	string getNombre() { return nombre; }
	Designacion getDesignacion() { return des; }
	int getId() { return id; }
	//Setters
	void setTamanio(int tamanio) { this->tamanio = tamanio; }
	void setSalud(int salud) { this->salud = salud; }
	void setOrientacion(char orientacion) { this->orientacion = orientacion; }
	void setNombre(string nombre) { this->nombre = nombre; }
	void setDesignacion(Designacion des) { this->des = des; }
	//Tipo-> 0-Portaaviones, 1-Acorazado, 2-Destructor, 3-Fragata, 4-Submarino.
	void setId(int id) { this->id = id; }
	void CrearNave(int id);
	//Reduce la salud en 1
	void DaniarNave();
private:
	int tamanio;
	int salud;
	char orientacion;
	string nombre;
	int id;
	Designacion des;
};

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
class Elemento {
private:
	char sprite;
	string celda;
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
	//Getters
	//Obtener sprite en posicion
	char getSprite() { return sprite; }
	//Obtener nombre del elemento en posicion
	string getCelda() { return celda; }
	Nave getNave() { return nave; }
	//Setters
	void SetSprite(const int value);
	void setSpriteNave(int id);
	void SetCelda(const int value);
	void SetNave(Nave nave) { this->nave = nave; }
	//Constructor
	Elemento();
};

Elemento::Elemento() {
	sprite = '?';
	celda = "?";
}

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

class Matriz {
private:
	const int filas = 10;
	const int columnas = 10;
public:
	Elemento **arr;
	//Obtener cantidad de filas
	const int getFilas() { return filas; }
	//Obtener cantidad de columnas
	const int getColumnas() { return columnas; }
	//Obtener elemento
	Elemento** getElemento() { return arr; }
	//Constructor
	Matriz();
	//Muestra la tabla
	void DibujarTabla();
	void DibujarTabla(int, int);
	//Colocar la nave en el tablero dada una posicion en X e Y
	void ColocarNave(Matriz tablero, int posY, int posX, Nave);
	void ColocarNaveHorizontal(int posY, int posX, int size, Nave, int);
	//La nave es colocada verticalmente
	void ColocarNaveVertical(int posY, int posX, int size, Nave, int);
	int ObtenerIDNave(int posY, int posX);
	void DestruirCelda(int x, int y);
	void FallaCelda(int x, int y);
	void OcultarTablero();
	void RevelarTablero();
	EstadoAtaque ValidarAtaque(int x, int y);
	//Ataque en la posicion. Si se produce un golpe, debe reducir el tamanio (salud) de la nave golpeada. Si el tamanio se reduce a 0, se debe eliminar el barco.
	Estado Atacar(int x, int y);
};

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
	cout << "  ";
	locate(POSICION_MATRIX_X + 2, POSICION_MATRIX_Y);
	for (int x = 0; x < filas; x++) {
		cout << x << " ";
	}
	cout << endl;
	for (int i = 0; i < filas; i++) {
		locate(POSICION_MATRIX_X, POSICION_MATRIX_Y + i + 1);
		cout << i << " ";
		for (int j = 0; j < columnas; j++) {
			cout << arr[i][j].getSprite();
			cout << " ";
		}
		cout << endl;
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
void Matriz::DibujarTabla(int offsetX, int offsetY){
		cout << "  ";
		locate(POSICION_MATRIX_X + 2 + offsetX, POSICION_MATRIX_Y + offsetY);
		for (int x = 0; x < filas; x++) {
			cout << x << " ";
		}
		cout << endl;
		for (int i = 0; i < filas; i++) {
			locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + i + 1 + offsetY);
			cout << i << " ";
			for (int j = 0; j < columnas; j++) {
				cout << arr[i][j].getSprite();
				cout << " ";
			}
			cout << endl;
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
void Matriz::ColocarNaveHorizontal(int posY, int posX,int size, Nave nave, int id) {
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
	string celda = arr[y][x].getCelda();

	//Si la celda fue atacada
	if (celda == "Fallo" or celda == "Golpe") return EstadoAtaque::REPETIDO;
	return EstadoAtaque::OK;
}

Estado Matriz::Atacar(int x, int y) {
	//Obtengo el tipo de celda en las coordenadas
	string celda = arr[y][x].getCelda();
	//Si la celda es de una embarcacion, instrucciones...
	if (celda == "Nave") {
		return Estado::GOLPE;
	}
	else {
		//Si la celda esta vacia
		return Estado::FALLO;
	}
}