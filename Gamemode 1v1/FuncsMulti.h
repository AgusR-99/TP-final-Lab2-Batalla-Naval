#pragma once

#include <assert.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
stringstream buffer;
enum {
    HIGH,
    MEDIUM,
    LOW
};

enum {
    INSTANT,
    FAST,
    NORMAL,
    SLOW
};

enum {
    //Workaround
    GOLPE = 4,
    FALLO = 5,
    HUNDIR,
};

enum {
    ESPERA,
    HUNDIDA,
    ATACADA,
    FUERA,
};

enum {
    ARRIBA,
    ABAJO,
    IZQUIERDA,
    DERECHA
};

int getEstado(const int value) {
    switch (value){
    case ESPERA: return -1;
    case FALLO: return 0;
    case GOLPE: return 1;
    case HUNDIDA: return 2;
    case ATACADA: return -2;
    case FUERA: return -3;
    }
}

const int ANCHO_VENTANA = 80;
const int ALTO_VENTANA = 20;
const int POSICION_MATRIX_X = 20;
const int POSICION_MATRIX_Y = 1;

#include "Clases.h"
#include "ComportamientoIA.h"
#include "UI.h"

//Funcion principal. Contiene a las demas funciones
void iniciarJuegoMulti();
//Inicializa una nave
void ingresarNave(Matriz, Matriz, int i, int& comienzoRapido, bool& bInstant);
//Desarrollo intermedio del juego
void atacarPosicion(Matriz tablero, int& res, int& estado, int, int, bool esJugador);
//Devuelve las naves restantes (Mas adelante debera tomar como parametro una lista de naves)
int navesRestantes(Nave nave[]);
//Si se destruyen las naves de la IA, se cumple la condicion
bool condicionVictoria(int);
//Si se destruyen las naves del jugador, se cumple la condicion
bool condicionDerrota(int);
//Evita un overflow en el buffer
bool validarAtaque(Matriz, int x, int y);
//Evita que se inicialicen naves con valores ilegales
int validarOrientacion(char r);
//Se valida si la respuesta esperada es la correcta "(Y/N)"
int validarRespuesta(char value);

// Setear condicion

//Modificar puntuaje (sumar o restar)
int modificarPuntuaje(int puntuaje, int mod, float mult);
void iniciarJuegoMulti() {
    AjustarVentana(ANCHO_VENTANA, ALTO_VENTANA);
    int estadoJugador = -1, estadoIA = -1, comienzoRapido = -2;
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
    Matriz tableroJugador(10, 10);
    Matriz tableroIA(10, 10);
    tableroJugador.IniciarTabla();
    tableroIA.IniciarTabla();
    for (int i = 0; i < cantidad; i++) {
        ingresarNave(tableroJugador, tableroIA, i, comienzoRapido, bInstant);
        colocarNaveIA(tableroIA, i);
    }
    system("cls");
    mostrarTableros(tableroJugador, tableroIA);
    locate(POSICION_MATRIX_X + 12, POSICION_MATRIX_Y + 13);
    setColor(YELLOW);
    mostrarTextoAnimado("Naves colocadas!", NORMAL, MEDIUM);
    int restantesJugador = navesRestantes(shipJugador);
    int restantesIA = navesRestantes(shipIA);
    locate(POSICION_MATRIX_X - 1, POSICION_MATRIX_Y + 14);
    mostrarTextoAnimado("Presione cualquier tecla para continuar. . . ", NORMAL, MEDIUM);
    getch();
    resetColor();
    //Comienzo del juego
    while (condicionV == false and condicionD == false) {
        turno++; //Avanza de turno una vez que ambas partes realicen la accion
        do { //Turno jugador
            system("cls");
            mostrarTableros(tableroJugador, tableroIA);
            mostrarInterfazAcciones(estadoJugador, estadoIA, restantesJugador, restantesIA, turno, 0, 12, tempXJugador, tempYJugador, tempXIA, tempYIA, puntuaje, puntuajeOld, multiplicador);
            puntuajeOld = puntuaje;
            ingresarDatos(x, y, 17, 11);
            atacarPosicion(tableroIA, restantesIA, estadoJugador, x, y, true);
            //Movimiento invalido
            if (estadoJugador == getEstado(ATACADA) or estadoJugador == getEstado(FUERA)) {
                estadoIA = getEstado(ESPERA);
                Beep(200, 250);
            }
        } while (estadoJugador == getEstado(ATACADA) || estadoJugador == getEstado(FUERA)); //Mientras se intente hacer un movimiento invalido, no pasara de turno
        if (estadoJugador == getEstado(FALLO)) { //FALLO
            //Multiplicador se revierte
            multiplicador = 1.0;
            //Puntuaje disminuye
            puntuaje = modificarPuntuaje(puntuaje, FALLO, multiplicador);
        }
        else if (estadoJugador == getEstado(GOLPE)) { //GOLPE
            //Puntuaje aumenta
            puntuaje = modificarPuntuaje(puntuaje, GOLPE, multiplicador);
            //Multiplicador aumenta
            if (multiplicador < 1.5) multiplicador = multiplicador + 0.1;
        }
        else if (estadoJugador == getEstado(ATACADA)) { //NAVE HUNDIDA
            //Puntuaje aumenta
            puntuaje = modificarPuntuaje(puntuaje, HUNDIR, multiplicador);
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
            if (estadoCaza == true) {
                cazarNave(lindanteX, lindanteY, direccion);
                x = lindanteX;
                y = lindanteY;
            }
            else generarCoordenadas(x, y);
            atacarPosicion(tableroJugador, restantesJugador, estadoIA, x, y, false);
            if (estadoCaza == true and estadoIA == getEstado(HUNDIDA)) {
                estadoCaza = false;
                direccion = ARRIBA;
            }
            else if (estadoCaza == true and
                    estadoIA == getEstado(FALLO) or 
                    estadoIA == getEstado(ATACADA) or
                    estadoIA == getEstado(FUERA)) {
                    //Cambiar de direccion de ataque
                    direccion++;
                    //Se retorna a las coordenadas originales
                    lindanteX = origenX;
                    lindanteY = origenY;
            }
            else if (estadoIA == getEstado(GOLPE) && estadoCaza == false) {
                estadoCaza = true;
                origenX = x;
                origenY = y;
                lindanteX = x;
                lindanteY = y;
            }
        } while (estadoIA == getEstado(ATACADA) or estadoIA == getEstado(FUERA)); //Mientras se intente hacer un movimiento invalido, no pasara de turno
        //Se guardan las coordenadas validadas para ser mostradas al finalizar el turno
        tempXIA = x;
        tempYIA = y;
        //Se analizan condiciones de victoria y derrota
        condicionV = condicionVictoria(restantesIA);
        condicionD = condicionDerrota(restantesJugador);
    }
    if (condicionV == true) condicion = setearCondicion(1);
    else condicion = setearCondicion(0);
    system("cls");
    mostrarTableros(tableroJugador, tableroIA);
    mostrarInterfazAcciones(estadoJugador, estadoIA, restantesJugador, restantesIA, turno, 0, 12, tempXJugador, tempYJugador, tempXIA, tempYIA, puntuaje, puntuajeOld, multiplicador);
    mostrarInterfazCondicion(condicion);
    mostrarInterfazPuntuaje(puntuaje, 0,0);
}

//Game stuff
void ingresarNave(Matriz tableroJugador, Matriz tableroIA, int i, int& comienzoRapido, bool& bInstant) {
    int x, y;
    char r = 'v';
    int validacion = 0;
    bool flag0 = false;
    bool flag1 = false;
    bool flag2 = false;
    while (validacion == 0 || validacion == -1 || validacion == -3) {
        system("cls");
        //Dependiendo lo que se haya validado, se mostrara o no un mensaje de error
        mostrarTableros(tableroJugador, tableroIA);
        if (comienzoRapido == -2) {
            mostrarInterfazComienzoRapido(1, 13);
            ingresarDatos(r, 40, 13);
            comienzoRapido = validarRespuesta(r);
        }
        while (comienzoRapido == -1) {
            system("cls");
            mostrarTableros(tableroJugador, tableroIA);
            mostrarInterfazComienzoRapido(1, 13);
            mostrarInterfazRespuestaInvalida(8, 15);
            ingresarDatos(r, 40, 13);
            comienzoRapido = validarRespuesta(r);
        }
        if (comienzoRapido == 0) {
            system("cls");
            validacionesFlags(validacion, flag0, flag1, flag2);
            mostrarTableros(tableroJugador, tableroIA);
            mostrarInterfazIngreso(i, r, 6, 13, bInstant);
            if (bInstant == false) bInstant = true;
            ingresarDatos(x, y, r, 14, 19);
            //Se valida si el input es el esperado
            validacion = validarOrientacion(r);
            //Se setea la orientacion de la nave una vez validada
            shipJugador[i].setOrientacion(r);
            //Se verifica si es posible colocar la nave en el tablero
            if (validacion != -3) validacion = tableroJugador.ColocarNave(shipJugador[i], tableroJugador, y, x);
            //Flags de validaciones
            if (validacion == 0) flag0 = true;
            else if (validacion == -1) flag1 = true;
            else flag2 = true;
            if (flag0 == true or flag1 == true or flag2 == true) Beep(200, 250);
        }
        else {
            generarCoordenadas(x, y);
            generarOrientacion(r);
            shipJugador[i].CrearNave(r, i);
            validacion = tableroJugador.ColocarNave(shipJugador[i], tableroJugador, y, x);
            //Si no se cumple la validacion, se crean nuevos valores
        }
    }
}
void atacarPosicion(Matriz tablero, int& res, int& estado, int x, int y, bool esJugador) {
    bool validacion;
    validacion = validarAtaque(tablero, x, y);
    if (validacion == false) {
        estado = getEstado(FUERA);
        return;
    }
    int ataque = tablero.Atacar(y, x, esJugador);
    //Si se produce un golpe
    if (ataque == 1) {
        estado = getEstado(GOLPE);
        int restantesNuevo;
        if (esJugador == true) restantesNuevo = navesRestantes(shipJugador);
        else restantesNuevo = navesRestantes(shipIA);
        //Si se hunde una nave
        if (restantesNuevo < res) {
            estado = getEstado(HUNDIDA);
            res = restantesNuevo;
        }
    }
    else if (ataque == 0) {
        //Si se ataca una celda vacia
        estado = getEstado(FALLO);
    }
    //Si se ataca una celda atacada
    else estado = getEstado(ATACADA);
}
//Validaciones
int validarOrientacion(char r) {
    if (r != 'v' and r != 'V' and r != 'h' and r != 'H') {
        return -3;
    }
    return 1;
}
int validarRespuesta(char value) {
    if (value != 'y' and value != 'Y' and value != 'n' and value != 'N') {
        Beep(200, 250);
        return -1;
    }
    else if (value == 'y' or value == 'Y') return 1;
    else return 0;
}
bool validarAtaque(Matriz tablero, int x, int y) {
    int limiteX = tablero.getColumnas();
    int limiteY = tablero.getFilas();
    if (x >= limiteX or y >= limiteY) {
        return false;
    }
    else return true;
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


//Obtener cosas
int navesRestantes(Nave nave[]) {
    int restantes = 0;
    for (int i = 0; i < cantidad; i++) {
        if (nave[i].getSalud() > 0) {
            restantes++;
        }
    }
    return restantes;
}
int modificarPuntuaje(int puntuaje, int mod, float mult) {
    return puntuaje + setMod(mod) * mult;
}
