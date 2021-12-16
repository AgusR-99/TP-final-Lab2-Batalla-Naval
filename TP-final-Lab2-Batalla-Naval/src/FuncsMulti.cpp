#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <Windows.h>
#include <mmsystem.h>
#include "Nave.h"
#include "Matriz.h"
#include "UI.h"
#include "Enums.h"
#include "Constantes.h"
#include "ComportamientoIA.h"
#include "FuncsMulti.h"

void iniciarJuegoMulti() {
    PlaySound(TEXT("music/placement.wav"), NULL, SND_ASYNC | SND_LOOP);
    AjustarVentana(ANCHO_VENTANA, ALTO_VENTANA);
    const int cantidad = 5;
    Nave naveJugador[cantidad];
    Nave naveIA[cantidad];
    OpcionMenuComienzo comienzoRapido = OpcionMenuComienzo::NONE;
    Estado estadoJugador = Estado::ESPERA;
    Estado estadoIA = Estado::ESPERA;
    int estadoCaza = false;
    int origenX, origenY, lindanteX, lindanteY;
    int direccion = ARRIBA;
    int turno = 0;
    int x = 0, y = 0, /*<---Variables deprecadas*/ tempXJugador = 0, tempYJugador = 0, tempXIA = -1, tempYIA = -1;
    bool condicionV = false;
    bool condicionD = false;
    bool bInstant = false;
    int puntuaje = 0, puntuajeOld = 0;
    float multiplicador = 1.0;
    std::string condicion;
    Matriz tableroJugador;
    Matriz tableroIA;
    OpcionMenuPausa comando;
    Input input; //No deberia usarse. No permite que la UI sea uniforme
    bool toggleDebug = false, tramposo = false;
    bool sndClimax = false, sndTransicion = false;
    bool flagVictoria = false, flagDerrota = false;
    TipoCheat cmdCheat = TipoCheat::NONE;
    for (int i = 0; i < cantidad; i++) {
        ingresarNave(naveJugador, tableroJugador, tableroIA, i, comienzoRapido, bInstant, input, cmdCheat);
        if (comienzoRapido == OpcionMenuComienzo::SALIR or
            input == Input::QUITAR) return;
        colocarNaveIA(tableroIA, i, naveIA);
        if (toggleDebug == false) tableroIA.OcultarTablero();
        else tableroIA.RevelarTablero();
    }
    rlutil::hidecursor();
    system("cls");
    mostrarTableros(tableroJugador, tableroIA);
    rlutil::locate(POSICION_MATRIX_X + 12, POSICION_MATRIX_Y + 13);
    rlutil::setColor(rlutil::YELLOW);
    mostrarTextoAnimado("Naves colocadas!", DuracionAnim::NORMAL, FrecuenciaSnd::MEDIA);
    int restantesJugador = navesRestantes(naveJugador, cantidad);
    int restantesIA = navesRestantes(naveIA, cantidad);
    rlutil::locate(POSICION_MATRIX_X - 1, POSICION_MATRIX_Y + 14);
    mostrarTextoAnimado("Presione cualquier tecla para continuar. . . ", DuracionAnim::NORMAL, FrecuenciaSnd::MEDIA);
    getch();
    rlutil::resetColor();
    EstadoAtaque validacion;
    //Comienzo del juego
    PlaySound(TEXT("music/battle.wav"), NULL, SND_ASYNC | SND_LOOP);
    while (condicionV == false and condicionD == false) {
        turno++; //Avanza de turno una vez que ambas partes realicen la accion
        rlutil::showcursor();

        OpcionNavegacion opcion;
        do { //Turno jugador
            if ((restantesIA <= 2 or restantesJugador <= 2) && sndTransicion == false) {
                PlaySound(TEXT("music/transition.wav"), NULL, SND_ASYNC); //El sonido se reproducira al mismo tiempo que se ejecutan las instrucciones de abajo
                sndTransicion = true;
                sndClimax = true;
            }
            do {
                system("cls");
                mostrarTableros(tableroJugador, tableroIA);
                mostrarInterfazAcciones(estadoJugador, estadoIA, restantesJugador, restantesIA,
                    turno, 0, 12, tempXJugador, tempYJugador, tempXIA, tempYIA, puntuaje, puntuajeOld, multiplicador, &flagVictoria, &flagDerrota);
                if (sndClimax == true) { 
                    PlaySound(TEXT("music/climax.wav"), NULL, SND_ASYNC | SND_LOOP);
                    sndClimax = false;

                }
                puntuajeOld = puntuaje;

                //Setear coordenadas en la ultima posicion
                x = tempXJugador, y = tempYJugador;

                //Navegacion en tablero
                //Se muestra el menu de pausa al presionar ESC
                opcion = navegarEnTablero(x, y, tableroIA, POSICION_MATRIX_X + 24, POSICION_MATRIX_Y + 2);

                //Actualizar variables temporales
                tempXJugador = x;
                tempYJugador = y;
                if (opcion == OpcionNavegacion::MENU) {
                    comando = mostrarInterfazPausa(POSICION_MATRIX_X + 10, POSICION_MATRIX_Y + 7, cmdCheat);
                    if (comando == OpcionMenuPausa::SALIR) return;
                }
                //Detecta si el usuario hizo trampa
                if (cmdCheat != TipoCheat::NONE) {
                    tramposo = true;
                    if (cmdCheat == TipoCheat::GANAR)   condicionV = true;
                    else if (cmdCheat == TipoCheat::PERDER)  condicionD = true;
                    else if (cmdCheat == TipoCheat::REVELAR) tableroIA.RevelarTablero();
                }
              //Sigue loopeando mientras no se confirmen coordenadas
            } while (opcion == OpcionNavegacion::MENU);
            validacion = tableroIA.ValidarAtaque(x, y);
            if (validacion == EstadoAtaque::FUERA) estadoJugador = Estado::FUERA;
            else if (validacion == EstadoAtaque::REPETIDO) estadoJugador = Estado::REPETIDO;
            else estadoJugador = atacarPosicion(tableroIA, restantesIA, x, y, naveIA, cantidad);
            //Movimiento invalido
            if (estadoJugador == Estado::REPETIDO or estadoJugador == Estado::FUERA or estadoJugador == Estado::INVALIDO) {
                estadoIA = Estado::ESPERA;
                Beep(200, 250);
            }

            //Mientras se intente hacer un movimiento invalido, no pasara de turno
        } while (estadoJugador == Estado::REPETIDO or estadoJugador == Estado::FUERA);
        rlutil::hidecursor();
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
        condicionV = condicionVictoria(restantesIA, &cmdCheat);
        condicionD = condicionDerrota(restantesJugador, &cmdCheat);
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

void ingresarNave(Nave naveJugador[],
 Matriz tableroJugador, Matriz tableroIA,int id, OpcionMenuComienzo& comienzoRapido,
 bool& bInstant, Input& comando, TipoCheat& cmdCheat) {

    int x, y;
    char r = 'v';
    Error validacion = Error::FUERA;
    bool flag0 = false;
    bool flag1 = false;
    bool flag2 = false;
    naveJugador[id].CrearNave(id);
    system("cls");
    mostrarTableros(tableroJugador, tableroIA);
    if (comienzoRapido == OpcionMenuComienzo::NONE)
        comienzoRapido = mostrarInterfazComienzoRapido(23, 13);
    if (comienzoRapido == OpcionMenuComienzo::SALIR) return;
    while (validacion == Error::ORIENTACION or
        validacion == Error::FUERA or
        validacion == Error::COLISION) {
        rlutil::hidecursor;
        if (comienzoRapido == OpcionMenuComienzo::NO) {
            do {
                rlutil::hidecursor();
                system("cls");
                validacionesFlags(validacion, flag0, flag1, flag2, comando);
                mostrarTableros(tableroJugador, tableroIA);
                mostrarInterfazIngreso(id, r, 6, 13, bInstant);
                if (bInstant == false) bInstant = true;
                rlutil::showcursor();
                comando = ingresarDatos(x, y, r, 14, 19, cmdCheat);
                rlutil::hidecursor();
                if (comando == Input::QUITAR) return;
                if (comando == Input::CHEAT) return;
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
    std::string foo;
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

bool condicionVictoria(int navesIA, TipoCheat* cmdCheat) {
    //Si no hay mas naves de la IA, se cumple la condicion de victoria
    if (navesIA == 0 or *cmdCheat == TipoCheat::GANAR)return true;
    return false;
}

bool condicionDerrota(int navesJugador, TipoCheat* cmdCheat) {
    //Si no hay mas naves del jugador, se cumple la condicion de derrota
    if (navesJugador == 0 or *cmdCheat == TipoCheat::PERDER)return true;
    return false;
}

char strToOrientacion(std::string c) {
    const int length = 10;
    if (c == "v" or c == "V") return 'v';
    if (c == "h" or c == "H") return 'h';
    else return '0';
}

char strToRespuesta(std::string c) {
    const int length = 10;
    if (c == "y" or c == "Y") return 'y';
    if (c == "n" or c == "N") return 'n';
    else return '0';
}

#include "Cheat.h"

Input leerListaDeComandos(std::string c, TipoCheat& cmdCheat) {
    for (int i = 0; i < listaCheats_size; i++) {
        if (c == listaCheats[i].getNombre()) {
            cmdCheat = listaCheats[i].getTipo(); return Input::CHEAT;
        }
    }
    if (c == ":q") return Input::QUITAR;
    return Input::BAD;
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
