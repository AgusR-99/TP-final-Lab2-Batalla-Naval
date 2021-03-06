#pragma once
#include "Jugador.h"
#include "Nave.h"
#include "Matriz.h"
#include "Elemento.h"
#include "Constantes.h"
#include "rlutil.h"
#include "SharedFuncs.h"

int setFreq(FrecuenciaSnd value);

int setDuration(DuracionAnim value);

int setMod(Estado value);

bool AjustarVentana(int Ancho, int Alto);

//Muestra el menu de pausa ingame
OpcionMenuPausa mostrarInterfazPausa(int offsetX, int offsetY, TipoCheat& cmdCheat);

void mostrarConsola(TipoCheat& cmdCheat);

//Muestra la interfaz de ingreso de naves
void mostrarInterfazIngreso(int i, char r, int offsetX, int offsetY, bool bInstant);

//Muestra mensaje de comienzo rapido
OpcionMenuComienzo mostrarInterfazComienzoRapido(int offsetX, int offsetY);

//Muestra una breve historia del juego
void mostrarLore();

//Muestra los turnos en la interfaz
void mostrarInterfazTurnos(int, int, int);

//Muestra las acciones en la interfaz
void mostrarInterfazAcciones(Estado est0, Estado est1, int res0, int res1, int turn, int x, int y,
	int xJug, int yJug, int xIA, int yIA, int score, int oldScore, float mult, bool* flagVictoria, bool* flagDerrota);

//Muestra en la interfaz las naves restantes
void mostrarInterfazNavesRestantes(int, int, int, int);

//Muestra el resultado de la partida en la interfaz
void mostrarInterfazCondicion(std::string condicion);

//Muestra un mensaje de error de respuesta invalida
void mostrarInterfazRespuestaInvalida(int offsetX, int offsetY);

//Mostrar interfaz de leaderboard
void mostrarInterfazLeaderboard();

//Mediante las fechas direccionales, navegar por el tablero
OpcionNavegacion navegarEnTablero(int& x, int& y, Matriz tablero, int offsetX, int offsetY);

//Intercambiar elementos de un vector
void intercambiar(Jugador*, Jugador*);

void mostrarSplashScreen(int offsetX, int offsetY);

//Se valida y muestra errores de colocacion de naves
void validacionesFlags(Error& validacion, bool& flag0, bool& flag1, bool& flag2, Input cmd);

//Muestra el resultado de un ataque
void mostrarResultadoAccion(Estado estado, FrecuenciaSnd freq);
//Muestra ambos tableros
void mostrarTableros(Matriz, Matriz);

//Sin esto, no funciona la funcion de rlutil para guardar el color
void setearColorDefault();

//Muestra coordenadas ingresadas en el turno
void mostrarCoordenadas(int, int, FrecuenciaSnd);
//Muestra una nave con los sprites
void mostrarNave(int id, int length, Elemento);

bool esDigitos(const std::string& str);

char strToOrientacion(std::string c);

char strToRespuesta(std::string input);

void desplazarCursor(int& x, int& y);

Input leerListaDeComandos(std::string input, TipoCheat& cmdCheat);

//Pide coordenadas X e Y, asi como una orientacion
Input ingresarDatos(int&, int&, char&, int, int, TipoCheat& cmdCheat);

//Pide coordenadas X e Y
Input ingresarDatos(int&, int&, int, int, TipoCheat& cmdCheat);

//Pide un char
Input ingresarDatos(char&, int offsetX, int offsetY);

// Mostrar texto animado
void mostrarTextoAnimado(std::string texto, DuracionAnim sleepDuration);

//Mostrar texto animado con sonidos
void mostrarTextoAnimado(std::string texto, DuracionAnim beepDuration, FrecuenciaSnd beepFreq);

//Muestra el cambio en puntuaje mediante una animacion
void rollearPuntuaje(int inicio, int objetivo, int offsetX, int offsetY);

std::string setearCondicion(Resultados);