#pragma once
const char* rutaJugador = "Gamemode 1v1/player.dat";

char spriteList[9] = { '-', 'n', 'o', 'X', 'P', 'A', 'D', 'F', 'S' };

string celdaList[4] = {
	"Vacio",
	"Nave",
	"Fallo",
	"Golpe",
};

string listaNaves[5] = {
	"Portaaviones",
	"Acorazado",
	"Destructor",
	"Fragata",
	"Submarino"
};

class Fecha {
private:
	int dia, mes, anio;
	time_t t = time(0);
	struct tm* timeStruct = localtime(&t);
public:
	//Getters
	int getDia() { return dia; }
	int getMes() { return mes; }
	int getAnio() { return anio; }
	//Setters
	void setDia(int d) { dia = d; }
	void setMes(int m) { mes = m; }
	void setAnio(int a) { anio = a; }
	//Constructor
	Fecha();
};

Fecha::Fecha() {
	dia = timeStruct->tm_mday;
	mes = timeStruct->tm_mon + 1;
	anio = timeStruct->tm_year + 1900;
}

class Jugador {
private:
	string nombre;
	int puntuaje;
	Fecha fecha;
public:
	//Getters
	string getNombre() { return nombre; }
	int getPuntuaje() { return puntuaje;}
	//Setters
	void setNombre(string n) { nombre = n; }
	void setPuntuaje(int p) { puntuaje = p; }
	//Constructor
	Jugador();
	//Metodos
	void mostrarFecha() {
		cout << setw(2) << setfill('0') << (fecha.getDia())
			<< '-' << setw(2) << setfill('0') << (fecha.getMes())
			<< '-' << (fecha.getAnio()) << endl;
	}
	bool Grabar();
	bool Leer(int pos);
	int ContarRegistros();

};

Jugador::Jugador() {
	nombre = "Nombre de jugador";
	puntuaje = 99;
}

bool Jugador::Grabar() {
	FILE* p;
	bool escritura;
	p = fopen(rutaJugador, "ab");
	escritura = fwrite(this, sizeof(Jugador), 1, p);
	fclose(p);
	return escritura;
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

class Nave {
private:
	int tamanio;
	int salud;
	char orientacion;
	int id;
public:
	//Getters
	int getTamanio() { return tamanio; }
	int getSalud() { return salud; }
	char getOrientacion() { return orientacion; }
	int getId() { return id; }
	//Setters
	void setTamanio(int tamanio) { this->tamanio = tamanio; }
	void setSalud(int salud) { this->salud = salud; }
	void setOrientacion(char orientacion) { this->orientacion = orientacion; }
	//Tipo-> 0-Portaaviones, 1-Acorazado, 2-Destructor, 3-Fragata, 4-Submarino.
	void setId(int id) { this->id = id; }
	//Orientacion-> 'h' - Horizontal, 'v' - Vertical
	void CrearNave(char orientacion, int id);
};
const int cantidad = 5;
Nave shipJugador[cantidad];
Nave shipIA[cantidad];
void Nave::CrearNave(char orientacion, int id) {
	switch (id) {
	case 0:
		this->tamanio = 5;
		salud = 5;
		break;
	case 1:
		this->tamanio = 4;
		salud = 4;
		break;
	case 2:
		this->tamanio = 3;
		salud = 3;
		break;
	case 3:
		this->tamanio = 3;
		salud = 3;
		break;
	case 4:
		this->tamanio = 2;
		salud = 2;
		break;
	default:
		break;
	}
	this->id = id;
	this->orientacion = orientacion;
}
class Elemento {
private:
	char sprite;
	string celda;
	Nave nave;
public:
	//Getters
	char getSprite() { return sprite; }
	string getCelda() { return celda; }
	Nave getNave() { return nave; }
	//Setters
	void SetSprite(int id) { this->sprite = spriteList[id]; }
	void SetCelda(int id) { this->celda = celdaList[id]; }
	void SetNave(Nave nave) { this->nave = nave; }
};

class Matriz {
private:
	int filas;
	int columnas;
	Elemento** arr;
public:
	//Getters
	int getFilas() { return filas; }
	int getColumnas() { return columnas; }
	//Setters
	void setFilas(int filas) { this->filas = filas; }
	void setColumnas(int columnas) { this->columnas = columnas; }
	//Constructor
	Matriz(int filas, int columnas) {
		this->filas = filas;
		this->columnas = columnas;
		arr = new Elemento* [filas];
		if (arr) {
			for (int i = 0; i < filas; i++) {
				arr[i] = new Elemento[columnas];
				assert(arr[i]);
			}
		}
	}
	//Metodos
	//Crea una tabla y setea todas las celdas en "Vacio"
	void IniciarTabla();
	//Muestra la tabla
	void DibujarTabla();
	void DibujarTabla(int, int);
	//Colocar la nave en el tablero dada una posicion en X e Y
	int ColocarNave(Nave nave, Matriz tablero, int posY, int posX);
	//La nave es colocada horizontalmente
	void ColocarNaveHorizontal(int posY, int posX, int size, Nave nave, int spriteId);
	//La nave es colocada verticalmente
	void ColocarNaveVertical(int posY, int posX, int size, Nave nave, int spriteId);
	//Valida celdas, horizontalmente, si es posible colocar una nave
	int ValidarHorizontal(Matriz tablero, int posY, int posX, int size);
	//Valida celdas, horizontalmente, si es posible colocar una nave
	int ValidarVertical(Matriz tablero, int posY, int posX, int size);
	//Ataque en la posicion. Si se produce un golpe, debe reducir el tamanio (salud) de la nave golpeada. Si el tamanio se reduce a 0, se debe eliminar el barco.
	int Atacar(int posY, int posX, bool esJugador);
};
void Matriz::IniciarTabla(){
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			arr[i][j].SetCelda(0);
			arr[i][j].SetSprite(0);
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
int Matriz::ColocarNave(Nave nave, Matriz tablero, int posY, int posX) {
	int id = nave.getId();
	int validacion;
	char r = nave.getOrientacion();
	if (r == 'h' or r == 'H') {
		validacion = ValidarHorizontal(tablero, posY, posX, nave.getTamanio());
		if (validacion == 1) {
			ColocarNaveHorizontal(posY, posX, nave.getTamanio(), nave, id);
			return 1;
		}
		else if (validacion == -1) return -1;
	}
	else if (r == 'v' or r == 'V') {
		validacion = ValidarVertical(tablero, posY, posX, nave.getTamanio());
		if (validacion == 1) {
			ColocarNaveVertical(posY, posX, nave.getTamanio(), nave, id);
			return 1;
		}
		else if (validacion == -1) return -1;
	}
	else return 0;
}
void Matriz::ColocarNaveHorizontal(int posY, int posX, int size, Nave nave, int spriteId) {
	for (int i = 0; i < size; i++) {
		arr[posY][posX].SetCelda(1);
		arr[posY][posX].SetNave(nave);
		arr[posY][posX].SetSprite(spriteId + 4);
		posX++;
	}
}
void Matriz::ColocarNaveVertical(int posY, int posX, int size, Nave nave, int spriteId) {
	for (int i = 0; i < size; i++) {
		arr[posY][posX].SetCelda(1);
		arr[posY][posX].SetNave(nave);
		arr[posY][posX].SetSprite(spriteId + 4);
		posY++;
	}
}

int Matriz::ValidarHorizontal(Matriz tablero, int posY, int posX, int size) {
	for (int i = 0; i < size; i++) {
		//Si los indices estan fuera de los limites de la matriz, la accion no es valida
		if (posY >= tablero.getFilas() || posX >= tablero.getColumnas()) {
			return -1;
		}
		//Si en la celda hay una nave, la accion no es valida
		if (arr[posY][posX].getCelda() == "Nave") return 0;
		posX++;
	}
	//La accion es valida
	return 1;
}
int Matriz::ValidarVertical(Matriz tablero, int posY, int posX, int size) {
	for (int i = 0; i < size; i++) {
		//Si los indices estan fuera de los limites de la matriz, la accion no es valida
		if (posY >= tablero.getFilas() || posX >= tablero.getColumnas()) {
			return -1;
		}
		//Si en la celda hay una nave, la accion no es valida
		if (arr[posY][posX].getCelda() == "Nave") return 0;
		posY++;
	}
	return 1;
}
int Matriz::Atacar(int posY, int posX, bool esJugador) {
	Elemento elemento = arr[posY][posX];
	//Obtengo el tipo de celda en las coordenadas
	string celda = elemento.getCelda();
	//Si la celda es de una embarcacion, instrucciones...
	if (celda == "Nave") {
		//Obtener info de la nave golpeada
		Nave nave = elemento.getNave();
		//Obtener obtener salud de la nave
		int salud;
		if(esJugador == true) salud = shipJugador[nave.getId()].getSalud();
		else salud = shipIA[nave.getId()].getSalud();
		salud--;
		//Le resto la salud en 1
		int id = nave.getId();
		if (esJugador == true) shipJugador[id].setSalud(salud);
		else shipIA[id].setSalud(salud);
		//Guardo la nueva info de la nave
		//Guardo el nuevo estado de la celda. No se podra acceder a la info de la nave desde esta coordenadas
		arr[posY][posX].SetCelda(3);
		arr[posY][posX].SetSprite(3);
		return 1;
	}
	//Si la celda fue atacada
	else if (celda == "Fallo" or celda == "Golpe") return -1;
	else {
		//Si la celda esta vacia
		arr[posY][posX].SetCelda(2);
		arr[posY][posX].SetSprite(2);
		return 0;
	}
}