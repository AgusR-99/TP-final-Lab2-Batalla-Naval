#pragma once
//Funcion principal. Contiene a las demas funciones
void iniciarJuegoMulti();
//Inicializa una nave
void ingresarNave(Nave naveJugador[], Matriz tableroJugador, Matriz tableroIA, int id, OpcionMenuComienzo& comienzoRapido, bool& bInstant, Input& comando, TipoCheat& cmdCheat);
//Desarrollo intermedio del juego
Estado atacarPosicion(Matriz tablero, int& res, int, int, Nave[], int cantidad);
//Devuelve las naves restantes (Mas adelante debera tomar como parametro una lista de naves)
int navesRestantes(Nave nave[], int cantidad);
//Si se destruyen las naves de la IA, se cumple la condicion
bool condicionVictoria(int, TipoCheat* cmdCheat);
//Si se destruyen las naves del jugador, se cumple la condicion
bool condicionDerrota(int, TipoCheat* cmdCheat);
//Evita un overflow en el buffer
EstadoAtaque validarAtaque(Matriz tablero, int x, int y);
//Evita que se inicialicen naves con valores ilegales
Error validarOrientacion(char r);
//Evita que se coloquen naves fuera del tablero
Error validarColocacion(Matriz tablero, int posY, int posX, int size, char r);
void mostrarInterfazPuntuaje(int puntuaje, char*, int, int);
//Modificar puntuaje (sumar o restar)
int modificarPuntuaje(int puntuaje, Estado mod, float mult);


