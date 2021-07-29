#pragma once

#include <assert.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <vector>
stringstream buffer;

enum class Estado {
    ESPERA,
    HUNDIDA,
    REPETIDO,
    FUERA,
    FALLO,
    GOLPE,
    DEBUG,
    DEBUGOFF,
    INVALIDO
};

enum {
    ARRIBA,
    ABAJO,
    IZQUIERDA,
    DERECHA
};

const int ANCHO_VENTANA = 80;
const int ALTO_VENTANA = 25;
const int POSICION_MATRIX_X = 20;
const int POSICION_MATRIX_Y = 1;


//Se valida si la respuesta esperada es la correcta "(Y/N)"
int validarRespuesta(char value);

#include "Clases.h"
#include "UI.h"


//Funcion principal. Contiene a las demas funciones
void iniciarJuegoMulti();
//Inicializa una nave
void ingresarNave(Nave naveJugador[], Matriz tableroJugador, Matriz tableroIA, int id, int& comienzoRapido, bool& bInstant, Input&);
//Desarrollo intermedio del juego
Estado atacarPosicion(Matriz tablero, int& res, int, int, Nave[], int cantidad);
//Devuelve las naves restantes (Mas adelante debera tomar como parametro una lista de naves)
int navesRestantes(Nave nave[], int cantidad);
//Si se destruyen las naves de la IA, se cumple la condicion
bool condicionVictoria(int);
//Si se destruyen las naves del jugador, se cumple la condicion
bool condicionDerrota(int);
//Evita un overflow en el buffer
EstadoAtaque validarAtaque(Matriz tablero, int x, int y);
//Evita que se inicialicen naves con valores ilegales
Error validarOrientacion(char r);
//Evita que se coloquen naves fuera del tablero
Error validarColocacion(Matriz tablero, int posY, int posX, int size, char r);

void mostrarInterfazPuntuaje(int puntuaje, char*, int, int);

#include "ComportamientoIA.h"

// Setear condicion

//Modificar puntuaje (sumar o restar)
int modificarPuntuaje(int puntuaje, Estado mod, float mult);
void iniciarJuegoMulti() {
    PlaySound(TEXT("music/placement.wav"), NULL, SND_ASYNC | SND_LOOP);
    AjustarVentana(ANCHO_VENTANA, ALTO_VENTANA);
    const int cantidad = 5;
    Nave naveJugador[cantidad];
    Nave naveIA[cantidad];
    int comienzoRapido = -2;
    Estado estadoJugador = Estado::ESPERA;
    Estado estadoIA = Estado::ESPERA;
    int estadoCaza = false;
    int origenX, origenY, lindanteX, lindanteY;
    int direccion = ARRIBA;
    int turno = 0;
    int x, y, tempXJugador = -1, tempYJugador = -1, tempXIA = -1, tempYIA = -1;
    bool condicionV = false;
    bool condicionD = false;
    bool bInstant = false;
    int puntuaje = 0, puntuajeOld = 0;
    float multiplicador = 1.0;
    string condicion;
    Matriz tableroJugador;
    Matriz tableroIA;
    Input comando = Input::OK;
    bool toggleDebug = false, tramposo = false;
    bool musica = false;

    for (int i = 0; i < cantidad; i++) {
        do {
            ingresarNave(naveJugador, tableroJugador, tableroIA, i, comienzoRapido, bInstant, comando);
            if (comando == Input::DEBUG) {
                if (toggleDebug == true) {
                    Beep(2000, 250);
                    Beep(1000, 250);
                    toggleDebug = false;
                    tableroIA.OcultarTablero();
                }
                else {
                    tramposo = true;
                    Beep(1000, 250);
                    Beep(2000, 250);
                    toggleDebug = true;
                    tableroIA.RevelarTablero();
                }
            }
        } while (comando == Input::DEBUG);
        if (comando == Input::QUITAR) return;
        colocarNaveIA(tableroIA, i, naveIA);
        if (toggleDebug == false) tableroIA.OcultarTablero();
        else tableroIA.RevelarTablero();
    }
    hidecursor();
    system("cls");
    mostrarTableros(tableroJugador, tableroIA);
    locate(POSICION_MATRIX_X - 8, POSICION_MATRIX_Y + 16);
    resetColor();
    cout << ":q";
    setColor(LIGHTBLUE);
    cout << "<Enter>";
    resetColor();
    cout << " para salir - :d";
    setColor(LIGHTBLUE);
    cout << "<Enter>";
    resetColor();
    cout << " para togglear debug mode";
    locate(POSICION_MATRIX_X + 12, POSICION_MATRIX_Y + 13);
    setColor(YELLOW);
    mostrarTextoAnimado("Naves colocadas!", Duracion::NORMAL, Frecuencia::MEDIA);
    int restantesJugador = navesRestantes(naveJugador, cantidad);
    int restantesIA = navesRestantes(naveIA, cantidad);
    locate(POSICION_MATRIX_X - 1, POSICION_MATRIX_Y + 14);
    mostrarTextoAnimado("Presione cualquier tecla para continuar. . . ", Duracion::NORMAL, Frecuencia::MEDIA);
    getch();
    resetColor();
    EstadoAtaque validacion;
    //Comienzo del juego
    PlaySound(TEXT("music/battle.wav"), NULL, SND_ASYNC | SND_LOOP);
    while (condicionV == false and condicionD == false) {
        turno++; //Avanza de turno una vez que ambas partes realicen la accion
        showcursor();
        do { //Turno jugador
            if ((restantesIA <= 2 or restantesJugador <= 2) && musica == false) {
                PlaySound(TEXT("music/climax.wav"), NULL, SND_ASYNC | SND_LOOP);
                musica = true;
            }
            do {
                system("cls");
                mostrarTableros(tableroJugador, tableroIA);
                mostrarInterfazAcciones(estadoJugador, estadoIA, restantesJugador, restantesIA,
                    turno, 0, 12, tempXJugador, tempYJugador, tempXIA, tempYIA, puntuaje,
                    puntuajeOld, multiplicador);
                puntuajeOld = puntuaje;
                comando = ingresarDatos(x, y, 17, 11);
                if (comando == Input::DEBUG) {
                    if (toggleDebug == true) {
                        Beep(2000, 250);
                        Beep(1000, 250);
                        toggleDebug = false;
                        tableroIA.OcultarTablero();
                        estadoJugador = Estado::DEBUGOFF;
                    }
                    else {
                        tramposo = true;
                        Beep(1000, 250);
                        Beep(2000, 250);
                        toggleDebug = true;
                        estadoJugador = Estado::DEBUG;
                        tableroIA.RevelarTablero();
                    }
                }
            } while (comando == Input::DEBUG);
            if (comando == Input::QUITAR) return;
            if (comando == Input::BAD) estadoJugador = Estado::INVALIDO;
            else {
                validacion = tableroIA.ValidarAtaque(x, y);
                if (validacion == EstadoAtaque::FUERA) estadoJugador = Estado::FUERA;
                else if (validacion == EstadoAtaque::REPETIDO) estadoJugador = Estado::REPETIDO;
                else estadoJugador = atacarPosicion(tableroIA, restantesIA, x, y, naveIA, cantidad);
            }
            //Movimiento invalido
            if (estadoJugador == Estado::REPETIDO or estadoJugador == Estado::FUERA or estadoJugador == Estado::INVALIDO) {
                estadoIA = Estado::ESPERA;
                Beep(200, 250);
            }

            //Mientras se intente hacer un movimiento invalido, no pasara de turno
        } while (estadoJugador == Estado::REPETIDO or estadoJugador == Estado::FUERA or comando == Input::BAD);
        hidecursor();
        if (estadoJugador == Estado::FALLO) { //FALLO
            //Multiplicador se revierte
            multiplicador = 1.0;
            //Puntuaje disminuye
            puntuaje = modificarPuntuaje(puntuaje, Estado::FALLO, multiplicador);
        }
        else if (estadoJugador == Estado::GOLPE) { //GOLPE
         //Puntuaje aumenta
            puntuaje = modificarPuntuaje(puntuaje, Estado::GOLPE, multiplicador);
            //Multiplicador aumenta
            if (multiplicador < 1.5) multiplicador = multiplicador + 0.1;
        }
        else if (estadoJugador == Estado::HUNDIDA) { //NAVE HUNDIDA
         //Puntuaje aumenta
            puntuaje = modificarPuntuaje(puntuaje, Estado::HUNDIDA, multiplicador);
            //Multiplicador aumenta
            if (multiplicador < 1.5) multiplicador = multiplicador + 0.1;
        }
        //Se guardan las coordenadas validadas para ser mostradas al finalizar el turno
        tempXJugador = x;
        tempYJugador = y;
        //Si el puntuaje es negativo, setear a 0. Si el puntuaje es mayor a 9999, setear a 9999
        if (puntuaje < 0) puntuaje = 0;
        else if (puntuaje > 9999) puntuaje = 9999;
        do { //Turno IA
            if (estadoCaza == true) { //Cosas de caza de nave
                if (estadoIA == Estado::FUERA or estadoIA == Estado::FALLO) {
                    //Cambiar de direccion de ataque al presentarse las condiciones anteriores
                    direccion++;
                    //Se retorna a las coordenadas originales
                    lindanteX = origenX;
                    lindanteY = origenY;
                }
                cazarNave(lindanteX, lindanteY, direccion);
                x = lindanteX;
                y = lindanteY;
            }
            else generarCoordenadas(x, y); //Genera coordenadas si no esta cazando
            validacion = tableroJugador.ValidarAtaque(x, y); //Se valida si es valido atacar antes de hacerlo
            if (validacion == EstadoAtaque::FUERA) estadoIA = Estado::FUERA;
            else {
                if (validacion == EstadoAtaque::REPETIDO) estadoIA = Estado::REPETIDO;
                else {
                    estadoIA = atacarPosicion(tableroJugador, restantesJugador, x, y, naveJugador, cantidad);
                    if (estadoIA == Estado::GOLPE && estadoCaza == false) {
                        estadoCaza = true;
                        origenX = x;
                        origenY = y;
                        lindanteX = x;
                        lindanteY = y;
                    }
                    else {
                        if (estadoIA == Estado::HUNDIDA) {
                            estadoCaza = false;
                            direccion = ARRIBA;
                        }
                    }
                }
            }

        } while (estadoIA == Estado::REPETIDO or estadoIA == Estado::FUERA); //Mientras se intente hacer un movimiento invalido, no pasara de turno
        //Se guardan las coordenadas validadas para ser mostradas al finalizar el turno
        tempXIA = x;
        tempYIA = y;
        //Se analizan condiciones de victoria y derrota
        condicionV = condicionVictoria(restantesIA);
        condicionD = condicionDerrota(restantesJugador);
    }
    tableroIA.RevelarTablero();
    char resultado[15];
    if (tramposo == true) {
        condicion = setearCondicion(Resultados::TRAMPOSO);
        strcpy(resultado, "Tramposo");
        PlaySound(TEXT("music/cheater.wav"), NULL, SND_ASYNC);
    }
    else {
        if (condicionV == true) {
            condicion = setearCondicion(Resultados::VICTORIA);
            PlaySound(TEXT("music/victory.wav"), NULL, SND_ASYNC);
            strcpy(resultado, "Victoria");
        }
        else {
            condicion = setearCondicion(Resultados::DERROTA);
            PlaySound(TEXT("music/defeat.wav"), NULL, SND_ASYNC);
            strcpy(resultado, "Derrota");
        }
    }

    system("cls");
    mostrarTableros(tableroJugador, tableroIA);
    mostrarInterfazCondicion(condicion);
    mostrarInterfazPuntuaje(puntuaje, resultado, 0, 0);
}

//Game stuff
void ingresarNave(Nave naveJugador[], Matriz tableroJugador, Matriz tableroIA, int id,
    int& comienzoRapido, bool& bInstant, Input &comando) {
    int x, y;
    char r = 'v';
    Error validacion = Error::FUERA;
    bool flag0 = false;
    bool flag1 = false;
    bool flag2 = false;
    naveJugador[id].CrearNave(id);
    while (validacion == Error::ORIENTACION or
           validacion == Error::FUERA       or 
           validacion == Error::COLISION)      {
        while (comienzoRapido == -2 or comando == Input::BAD) {
            //Dependiendo lo que se haya validado, se mostrara o no un mensaje de error
            system("cls");
            mostrarTableros(tableroJugador, tableroIA);
            mostrarInterfazComienzoRapido(1, 13);
            if (comienzoRapido == -1 or comando == Input::BAD) mostrarInterfazRespuestaInvalida(8, 15);
            showcursor();
            comando = ingresarDatos(r, 40, 13);
            hidecursor;
            if (comando == Input::QUITAR) return;
            if (comando == Input::DEBUG) return;
            comienzoRapido = validarRespuesta(r);
        }
        if (comienzoRapido == 0) {
            do {
                    hidecursor();
                    system("cls");
                    validacionesFlags(validacion, flag0, flag1, flag2, comando);
                    mostrarTableros(tableroJugador, tableroIA);
                    mostrarInterfazIngreso(id, r, 6, 13, bInstant);
                    if (bInstant == false) bInstant = true;
                    showcursor();
                    comando = ingresarDatos(x, y, r, 14, 19);
                    hidecursor();
                    if (comando == Input::QUITAR) return;
                    if (comando == Input::DEBUG) return;
                //Se valida si el input es el esperado
                validacion = validarOrientacion(r);
                //Se verifica si es posible colocar la nave en el tablero
                if (validacion != Error::ORIENTACION) {
                    validacion = validarColocacion(tableroJugador, y, x, naveJugador[id].getTamanio(), r);
                }
                //Flags de validaciones
                if (validacion == Error::COLISION) flag0 = true;
                else if (validacion == Error::FUERA) flag1 = true;
                else if (validacion == Error::ORIENTACION) flag2 = true;
                if (flag0 == true or flag1 == true or flag2 == true) Beep(200, 250);
            } while (comando == Input::BAD);
            
        }
        else {
            generarOrientacion(r);
            generarCoordenadas(x, y);
            validacion = validarColocacion(tableroJugador, y, x, naveJugador[id].getTamanio(), r);
            //Si no se cumple la validacion, se crean nuevos valores
        }
    }
    naveJugador[id].setOrientacion(r);
    tableroJugador.ColocarNave(tableroJugador, y, x, naveJugador[id]);
}
Estado atacarPosicion(Matriz tablero, int& res, int x, int y, Nave nave[], int cantidad) {
    Estado ataque = tablero.Atacar(x, y);
    if (ataque == Estado::GOLPE) {
        int id = tablero.ObtenerIDNave(y, x);
        nave[id].DaniarNave();
        tablero.DestruirCelda(x, y);
        int restantesNuevo;
        restantesNuevo = navesRestantes(nave, cantidad);
        //Si se hunde una nave
        if (restantesNuevo < res) {
            ataque = Estado::HUNDIDA;
            res = restantesNuevo;
        }
    }
    else if (ataque == Estado::FALLO) {
        tablero.FallaCelda(x, y);
    }
    return ataque;
}
//Validaciones
Error validarOrientacion(char r) {
    if (r != 'v' and r != 'V' and r != 'h' and r != 'H') {
        return Error::ORIENTACION;
    }
    return Error::OK;
}

Error validarColocacion(Matriz tablero, int posY, int posX, int size, char r) {
    string foo;
    if (r == 'v' or r == 'V') {
        for (int i = 0; i < size; i++) {
            //Si los indices estan fuera de los limites de la matriz, la accion no es valida
            if (posY >= tablero.getFilas() or posX >= tablero.getColumnas()) {
                return Error::FUERA;
            }
            //Si en la celda hay una nave, la accion no es valida
            foo = tablero.getElemento()[posY][posX].getCelda();
            if (foo == "Nave") return Error::COLISION;
            posY++;
        }
    }
    else {
        for (int i = 0; i < size; i++) {
            //Si los indices estan fuera de los limites de la matriz, la accion no es valida
            if (posY >= tablero.getFilas() or posX >= tablero.getColumnas()) {
                return Error::FUERA;
            }
            //Si en la celda hay una nave, la accion no es valida
            foo = tablero.getElemento()[posY][posX].getCelda();
            if (foo == "Nave") return Error::COLISION;
            posX++;
        }
    }
    return Error::OK;
}

int validarRespuesta(char value) {
    if (value != 'y' and value != 'Y' and value != 'n' and value != 'N') {
        Beep(200, 250);
        return -1;
    }
    else if (value == 'y' or value == 'Y') return 1;
    else return 0;
}
bool condicionVictoria(int navesIA) {
    //Si no hay mas naves de la IA, se cumple la condicion de victoria
    if (navesIA == 0)return true;
    return false;
}
bool condicionDerrota(int navesJugador) {
    //Si no hay mas naves del jugador, se cumple la condicion de derrota
    if (navesJugador == 0)return true;
    return false;
}

int strToCoord(string c, Input& input) {
    const int length = 10;
    string valor[length]{ "0","1","2" ,"3" ,"4" ,"5" ,"6" ,"7" ,"8" ,"9" };
    for (int i = 0; i < length; i++){
        if (c == valor[i]) { 
            input = Input::COORD;
            return i;
        }
    }
    input = Input::BAD;
    return -1;
}

char strToOrientacion(string c) {
    const int length = 10;
    if (c == "v" or c == "V") return 'v';
    if (c == "h" or c == "H") return 'h';
    else return '0';
}

char strToRespuesta(string c) {
    const int length = 10;
    if (c == "y" or c == "Y") return 'y';
    if (c == "n" or c == "N") return 'n';
    else return '0';
}

Input leerListaDeComandos(string c) {
    vector<string> comandos{ ":q", ":d"};
    for (int i = 0; i < comandos.size(); i++) {
        if (c == comandos[0]) return Input::QUITAR;
        if (c == comandos[1]) return Input::DEBUG;
    }
    return Input::NOCMD;
}

//Obtener cosas
int navesRestantes(Nave nave[], int cantidad) {
    int restantes = 0;
    for (int i = 0; i < cantidad; i++) {
        if (nave[i].getSalud() > 0) {
            restantes++;
        }
    }
    return restantes;
}
int modificarPuntuaje(int puntuaje, Estado mod, float mult) {
    return puntuaje + setMod(mod) * mult;
}
