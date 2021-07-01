#pragma once

//Funcion principal. Contiene a las demas funciones
void iniciarJuego();
//Inicializa una nave
void ingresarNave(Matriz, int i);
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
void validarOrientacion(char r);
//Muestra una nave con los sprites
void mostrarNave(int id, int length);
//Muestra el resultado de un ataque
void mostrarResultadoAccion(int estado);
//Muestra la interfaz del juego
void mostrarInterfaz(int turno, Matriz, Matriz, int estadoJugador, int estadoIA, int, int);

void iniciarJuego() {
    int estadoJugador = -1, estadoIA = -1;
    int turno = 0;
    int x, y;
    bool condicionV = false;
    bool condicionD = false;
    Matriz tableroJugador(10, 10);
    Matriz tableroIA(10, 10);
    tableroJugador.IniciarTabla();
    tableroIA.IniciarTabla();
    for (int i = 0; i < cantidad; i++) {
        ingresarNave(tableroJugador, i);
        colocarNaveIA(tableroIA, i);
    }
    system("cls");
    cout << "=======JUGADOR=======\n";
    tableroJugador.DibujarTabla();
    cout << "=========IA==========\n";
    tableroIA.DibujarTabla();
    cout << "Naves colocadas!\n";
    int restantesJugador = navesRestantes(shipJugador);
    int restantesIA = navesRestantes(shipIA);
    system("pause");
    //Comienzo del juego
    while (condicionV == false and condicionD == false) {
        turno++; //Avanza de turno una vez que ambas partes realicen la accion
        do { //Turno jugador
            system("cls");
            mostrarInterfaz(turno, tableroJugador, tableroIA, estadoJugador, estadoIA, restantesJugador, restantesIA);
            cin >> x;
            cin >> y;
            atacarPosicion(tableroIA, restantesIA, estadoJugador, x, y, true);
        } while (estadoJugador == -2 || estadoJugador == -3); //Mientras se intente hacer un movimiento invalido, no pasara de turno
        do { //Turno IA
            cout << "\nIA Pensando...\n";
            generarCoordenadas(x, y);
            atacarPosicion(tableroJugador, restantesJugador, estadoIA, x, y, false);
        } while (estadoIA == -2); //Mientras se intente hacer un movimiento invalido, no pasara de turno
        condicionV = condicionVictoria(restantesIA);
        condicionD = condicionDerrota(restantesJugador);
    }
    string condicion;
    if (condicionVictoria(restantesIA) == true) condicion = "VICTORIA";
    else condicion = "DERROTA";
    system("cls");
    mostrarInterfaz(turno, tableroJugador, tableroIA, estadoJugador, estadoIA, restantesJugador, restantesIA);
    cout << "\n-------------------------\n";
    cout << "---------" << condicion << "---------\n";
    cout << "-------------------------\n";
}

//Game stuff
void ingresarNave(Matriz tablero, int i) {
    int x, y;
    char r = 'v';
    int validacion = 0;
    bool flag0 = false;
    bool flag1 = false;
    while (validacion == 0 || validacion == -1) {
        system("cls");
        if (validacion == 1)validacion = false;
        tablero.DibujarTabla();
        if (flag0 == true) {
            cout << "ERROR: Colision de naves\n";
            flag0 = false;
        }
        else if (flag1 == true) cout << "ERROR: Nave fuera de los limites del tablero\n";
        cout << "POSICION DE LA NAVE\n";
        cout << "---------";
        //Se inicaliza una nave para poder mostrarlo en pantalla
        shipJugador[i].CrearNave(r, i);
        int length = shipJugador[i].getTamanio();
        //Se muestra que nave se va a ingresar
        cout << endl << listaNaves[i] << " >> ";
        mostrarNave(i, length);
        cout << " [" << length << "]" << endl;
        cout << "---------\n";
        cout << "Coordenadas|Orientacion\n        X Y v/h \n";
        cout << "        ";
        cin >> x;
        cin >> y;
        cout << "Orientacion (v/h) >> ";
        cin >> r;
        //Se valida si el input es el esperado
        validarOrientacion(r);
        shipJugador[i].setOrientacion(r);
        validacion = tablero.ColocarNave(shipJugador[i], tablero, y, x);
        //Flags de validaciones
        if (validacion == 0) flag0 = true;
        else if (validacion == -1) flag1 = true;
    }
}
void atacarPosicion(Matriz tablero, int& res, int& estado, int x, int y, bool esJugador) {
    bool validacion;
    validacion = validarAtaque(tablero, x, y);
    if (validacion == false) {
        estado = -3;
        return;
    }
    int ataque = tablero.Atacar(y, x, esJugador);
    //Si se produce un golpe
    if (ataque == 1) {
        estado = 1;
        int restantesNuevo;
        if(esJugador == true) restantesNuevo = navesRestantes(shipJugador);
        else restantesNuevo = navesRestantes(shipIA);
        //Si se hunde una nave
        if (restantesNuevo < res) {
            estado = 2;
            res = restantesNuevo;
        }
    }
    else if (ataque == 0) {
        //Si se ataca una celda vacia
        estado = 0;
    }
    //Si se ataca una celda atacada
    else estado = -2;
}
//Validaciones
//Deberia cambiar esta funcion para que sea consistente con el resto
void validarOrientacion(char r){
    while (r != 'v' and r != 'V' and r != 'h' and r != 'H'){
        cout << "ERROR: ingrese una orientacion valida >> ";
        cin >> r;
    }
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
//Mostrar cosas
void mostrarNave(int id, int length) {
    for (size_t i = 0; i < length; i++){
        cout << spriteList[id + 4];
    }
}
void mostrarResultadoAccion(int estado) {
    if (estado == -1) cout << "A LA ESPERA";
    else if (estado == 0) cout << "FALLO";
    else if (estado == 1) cout << "GOLPE!";
    else if (estado == 2) cout << "GOLPE!\n                NAVE HUNDIDA!";
    else if (estado == -2) cout << "ATAQUE EN CELDA ATACADA\n                INTENTE NUEVAMENTE";
    else if (estado == -3) cout << "ATAQUE FUERA DEL TABLERO\n                INTENTE NUEVAMENTE";
}
void mostrarInterfaz(int turno, Matriz tableroJugador, Matriz tableroIA, int estadoJugador, int estadoIA, int restantesJugador, int restantesIA) {
    cout << "----------------\n";
    cout << "|  TURNO >> " << turno << "  |" << endl;
    cout << "----------------\n";
    cout << "=======JUGADOR=======\n Naves restantes >> " << restantesJugador << endl;
    tableroJugador.DibujarTabla();
    cout << "=========IA==========\n Naves restantes >> " << restantesIA << endl;
    tableroIA.DibujarTabla();
    cout << "-----------------\n";
    cout << "Mi resultado >> ";
    mostrarResultadoAccion(estadoJugador);
    cout << "\nResultado IA >> ";
    mostrarResultadoAccion(estadoIA);
    cout << endl << "-----------------\n";
    cout << "ATAQUE\n";
    cout << "Coordenadas (X Y) >> ";
}
//Get stuff
int navesRestantes(Nave nave[]) {
    int restantes = 0;
    for (int i = 0; i < cantidad; i++) {
        if (nave[i].getSalud() > 0) {
            restantes++;
        }
    }
    return restantes;
}