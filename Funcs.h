#pragma once

//Funcion principal. Contiene a las demas funciones
void iniciarJuego();
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
//Se valida y muestra errores de colocacion de naves
void validacionesFlags(int& validacion, bool &flag0, bool& flag1, bool& flag2);
//Muestra una nave con los sprites
void mostrarNave(int id, int length);
//Muestra el resultado de un ataque
void mostrarResultadoAccion(int estado, int);
//Muestra ambos tableros
void mostrarTableros(Matriz, Matriz);
//Muestra la interfaz de ingreso de naves
void mostrarInterfazIngreso(int i, char r, int offsetX, int offsetY, bool bInstant);
//Muestra mensaje de comienzo rapido
void mostrarInterfazComienzoRapido(int offsetX, int offsetY);
//Muestra los turnos en la interfaz
void mostrarInterfazTurnos(int, int, int);
//Muestra las acciones en la interfaz
void mostrarInterfazAcciones(int estadoJugador, int estadoIA, int, int, int, int, int, int, int, int, int);
//Muestra en la interfaz las naves restantes
void mostrarInterfazNavesRestantes(int, int, int, int);
//Muestra el resultado de la partida en la interfaz
void mostrarInterfazCondicion(string condicion);
//Muestra un mensaje de error de respuesta invalida
void mostrarInterfazRespuestaInvalida(int offsetX, int offsetY);
//Muestra coordenadas ingresadas en el turno
void mostrarCoordenadas(int, int, int);
//Pide coordenadas X e Y, asi como una orientacion
void ingresarDatos(int&, int&, char&, int, int);
//Pide coordenadas X e Y
void ingresarDatos(int&, int&, int, int);
//Pide un char
void ingresarDatos(char&, int offsetX, int offsetY);
// Setear condicion
string setearCondicion(bool);
// Mostrar texto animado
void mostrarTextoAnimado(string texto, int sleepDuration);
//Mostrar texto animado con sonidos
void mostrarTextoAnimado(string texto, int beepFreq, int beepDuration);

void iniciarJuego() {
    int estadoJugador = -1, estadoIA = -1, comienzoRapido = -2;
    int turno = 0;
    int x, y, tempXJugador = -1, tempYJugador = -1, tempXIA = -1, tempYIA = -1;
    bool condicionV = false;
    bool condicionD = false;
    bool bInstant = false;
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
            mostrarInterfazAcciones(estadoJugador, estadoIA, restantesJugador, restantesIA, turno, 0, 12, tempXJugador, tempYJugador, tempXIA, tempYIA);
            ingresarDatos(x, y, 17, 11);
            atacarPosicion(tableroIA, restantesIA, estadoJugador, x, y, true);
        } while (estadoJugador == -2 || estadoJugador == -3); //Mientras se intente hacer un movimiento invalido, no pasara de turno
        //Se guardan las coordenadas validadas para ser mostradas al finalizar el turno
        tempXJugador = x;
        tempYJugador = y;
        do { //Turno IA
            cout << "\nIA Pensando...\n";
            generarCoordenadas(x, y);
            atacarPosicion(tableroJugador, restantesJugador, estadoIA, x, y, false);
        } while (estadoIA == -2); //Mientras se intente hacer un movimiento invalido, no pasara de turno
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
    mostrarInterfazAcciones(estadoJugador, estadoIA, restantesJugador, restantesIA, turno, 0, 12, tempXJugador, tempYJugador, tempXIA, tempYIA);
    mostrarInterfazCondicion(condicion);
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
int validarOrientacion(char r){
    if (r != 'v' and r != 'V' and r != 'h' and r != 'H'){
        return -3;
    }
    return 1;
}
int validarRespuesta(char value) {
    if (value != 'y' and value != 'Y' and value != 'n' and value != 'N') {
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
void validacionesFlags(int& validacion, bool& flag0, bool& flag1, bool& flag2) {
    if (validacion == 1) validacion = 0;
    if (flag0 == true) {
        locate(POSICION_MATRIX_X + 8, POSICION_MATRIX_Y + 21);
        setColor(RED);
        cout << "ERROR: ";
        resetColor();
        cout << "Colision de naves\n";
        flag0 = false;
    }
    else if (flag1 == true) {
        locate(POSICION_MATRIX_X - 1, POSICION_MATRIX_Y + 21);
        setColor(RED);
        cout << "ERROR: ";
        resetColor();
        cout << "Nave fuera de los limites del tablero\n";
        flag1 = false;
    }
    else if(flag2 == true) {
        locate(POSICION_MATRIX_X + 7, POSICION_MATRIX_Y + 21);
        setColor(RED);
        cout << "ERROR: ";
        resetColor();
        cout << "Orientacion invalida\n";
        flag2 = false;
    }
}
//Mostrar cosas
void mostrarTableros(Matriz tableroJugador, Matriz tableroIA) {
    locate(POSICION_MATRIX_X - 1, POSICION_MATRIX_Y);
    setColor(LIGHTCYAN);
    cout << "=======JUGADOR=======\n";
    tableroJugador.DibujarTabla(-1, 1);
    locate(POSICION_MATRIX_X + 22, POSICION_MATRIX_Y);
    setColor(LIGHTRED);
    cout << "=========IA==========\n";
    tableroIA.DibujarTabla(22, 1);
    locate(POSICION_MATRIX_X + 1, POSICION_MATRIX_Y + 14);
    resetColor();
}
void mostrarInterfazIngreso(int i, char r, int offsetX, int offsetY, bool bInstant) {
    int fastD = FAST;
    int normalD = NORMAL;
    int slowD = SLOW;
    if (bInstant == true) {
        fastD = INSTANT;
        normalD = INSTANT;
        slowD = INSTANT;
    }
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    mostrarTextoAnimado("EMBARCACION", normalD);
    locate(POSICION_MATRIX_X + 16 + offsetX, POSICION_MATRIX_Y + offsetY);
    mostrarTextoAnimado("SPRITE", normalD);
    locate(POSICION_MATRIX_X + 23 + offsetX, POSICION_MATRIX_Y + offsetY);
    mostrarTextoAnimado("TAMAÑO", normalD);
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 1 + offsetY);
    mostrarTextoAnimado("-----------------------------", fastD);
    //Se inicaliza una nave para poder mostrarlo en pantalla
    shipJugador[i].CrearNave(r, i);
    int length = shipJugador[i].getTamanio();
    //Se muestra que nave se va a ingresar
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 2 + offsetY);
    buffer << listaNaves[i];
    mostrarTextoAnimado(buffer.str(), normalD);
    //Limpieza de buffer
    buffer.str("");
    locate(POSICION_MATRIX_X + 12 + offsetX, POSICION_MATRIX_Y + 2 + offsetY);
    mostrarTextoAnimado(" >> ", normalD);
    mostrarNave(i, length);
    locate(POSICION_MATRIX_X + 22 + offsetX, POSICION_MATRIX_Y + 2 + offsetY);
    buffer << " [" << length << "]";
    mostrarTextoAnimado(buffer.str(), normalD);
    //Limpieza de buffer
    buffer.str("");
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 3 + offsetY);
    mostrarTextoAnimado("-----------------------------", fastD);
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 4 + offsetY);
    mostrarTextoAnimado("Coordenadas", normalD);
    locate(POSICION_MATRIX_X + offsetX + 16, POSICION_MATRIX_Y + 4 + offsetY);
    mostrarTextoAnimado("Orientacion", normalD);
    locate(POSICION_MATRIX_X + 4 + offsetX+ 4, POSICION_MATRIX_Y + 5 + offsetY);
    cout << "X";
    locate(POSICION_MATRIX_X + 4 + offsetX+ 6, POSICION_MATRIX_Y + 5 + offsetY);
    cout << "Y";
    locate(POSICION_MATRIX_X + offsetX+ 16, POSICION_MATRIX_Y + 5 + offsetY);
    mostrarTextoAnimado("v/h", normalD);
}
void mostrarInterfazAcciones(int estadoJugador, int estadoIA, int restantesJugador, int restantesIA, int turno, int offsetX, int offsetY, int xJugador, int yJugador, int xIA, int yIA) {
    mostrarInterfazNavesRestantes(restantesJugador, restantesIA, offsetX, offsetY);
    mostrarInterfazTurnos(turno, offsetX, offsetY + 1);
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 2 + offsetY);
    setColor(LIGHTCYAN);
    mostrarTextoAnimado("Jugador: ", NORMAL, HIGH);
    resetColor();
    mostrarCoordenadas(xJugador, yJugador, HIGH);
    mostrarResultadoAccion(estadoJugador, HIGH);
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 3 + offsetY);
    setColor(LIGHTRED);
    Sleep(500);
    mostrarTextoAnimado("IA: ", NORMAL, LOW);
    resetColor();
    mostrarCoordenadas(xIA, yIA, LOW);
    mostrarResultadoAccion(estadoIA, LOW);
    Sleep(500);
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 4 + offsetY);
    cout << "ATAQUE\n";
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 5 + offsetY);
    cout << "Coordenadas (X Y) >> ";
}
void mostrarInterfazTurnos(int turno, int offsetX, int offsetY) {
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    cout << "~~~~~~~~~~~~~~~~~TURNO " << turno << "~~~~~~~~~~~~~~~~~" ;
}
void mostrarInterfazComienzoRapido(int offsetX, int offsetY) {
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    setColor(YELLOW);
    mostrarTextoAnimado("¿Colocar naves aletoriamente (Y/N)? >>", NORMAL, MEDIUM);
    resetColor();
}
void mostrarResultadoAccion(int estado, int freq) {
    int color;
    if (estado == -1) { 
        color = WHITE;
        buffer << "A LA ESPERA"; 
    }
    else if (estado == 0) {
        color = YELLOW;
        buffer << "FALLO"; 
    }
    else if (estado == 1) {
        color = LIGHTRED;
        buffer << "GOLPE!";
    }
    else if (estado == 2) {
        color = LIGHTMAGENTA;
        buffer << "GOLPE! NAVE HUNDIDA!";
    }
    else if (estado == -2) {
        color = LIGHTRED;
        buffer << "ERROR:"; 
        buffer << " ATAQUE EN CELDA ATACADA";
    }
    else if (estado == -3) {
        color = LIGHTRED;
        buffer << "ERROR:";
        buffer << " ATAQUE FUERA DEL TABLERO";
    }
    setColor(color);
    mostrarTextoAnimado(buffer.str(), NORMAL, freq);
    resetColor();
    //Limpieza de buffer
    buffer.str("");
}
void mostrarInterfazNavesRestantes(int restantes0, int restantes1, int offsetX, int offsetY) {
    locate(POSICION_MATRIX_X + offsetX -1, POSICION_MATRIX_Y + offsetY);
    setColor(LIGHTCYAN);
    cout << "=========>"<< restantes0 <<"<=========";
    locate(POSICION_MATRIX_X + 22 + offsetX, POSICION_MATRIX_Y + offsetY);
    setColor(LIGHTRED);
    cout << "=========>" << restantes1 << "<=========";
    resetColor();
}
void mostrarInterfazCondicion(string condicion) {
    cout << condicion;
    system("pause");
}
void mostrarInterfazRespuestaInvalida(int offsetX, int offsetY) {
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    setColor(RED);
    cout << "ERROR: ";
    resetColor();
    cout << "Respuesta invalida";
}
void mostrarCoordenadas(int x, int y, int frequency) {
    if(x != -1 && y != -1) buffer << x << "-" << y << " -> ";
    mostrarTextoAnimado(buffer.str(), NORMAL, setFreq(frequency));
    buffer.str("");
}
void mostrarTextoAnimado(string texto, const int sleepDuration) {
    int x = 0;
    while (texto[x] != '\0') {
        cout << texto[x];
        Sleep(setDuration(sleepDuration));
        x++;
    };
}
void mostrarTextoAnimado(string texto, const int beepDuration, const int beepFreq) {
    int x = 0;
    while (texto[x] != '\0') {
        cout << texto[x];
        Beep(setFreq(beepFreq), setDuration(beepDuration));
        x++;
    };
}
void mostrarNave(int id, int length) {
    for (size_t i = 0; i < length; i++){
        buffer << spriteList[id + 4];
    }
    mostrarTextoAnimado(buffer.str(), NORMAL);
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
string setearCondicion(bool victoria) {
    string str;
    if (victoria == 1) {
        setColor(LIGHTGREEN);
        str = R"(
oooooo     oooo  o8o                .                       o8o            
 `888.     .8'   `"'              .o8                       `"'            
  `888.   .8'   oooo   .ooooo.  .o888oo  .ooooo.  oooo d8b oooo   .oooo.   
   `888. .8'    `888  d88' `"Y8   888   d88' `88b `888""8P `888  `P  )88b  
    `888.8'      888  888         888   888   888  888      888   .oP"888  
     `888'       888  888   .o8   888 . 888   888  888      888  d8(  888  
      `8'       o888o `Y8bod8P'   "888" `Y8bod8P' d888b    o888o `Y888""8o 
        )";
        resetColor();
    }
    else {
        setColor(LIGHTRED);
        str = R"(
            88888888ba,                                                                         
            88      `"8b                                                     ,d                 
            88        `8b                                                    88                 
            88         88   ,adPPYba,  8b,dPPYba,  8b,dPPYba,   ,adPPYba,  MM88MMM  ,adPPYYba,  
            88         88  a8P_____88  88P'   "Y8  88P'   "Y8  a8"     "8a   88     ""     `Y8  
            88         8P  8PP"""""""  88          88          8b       d8   88     ,adPPPPP88  
            88      .a8P   "8b,   ,aa  88          88          "8a,   ,a8"   88,    88,    ,88  
            88888888Y"'     `"Ybbd8"'  88          88           `"YbbdP"'    "Y888  `"8bbdP"Y8  
        )";
        resetColor();
    }
    return str;
}
//Ingresos
void ingresarDatos(int& x, int& y, char& r, int offsetX, int offsetY) {
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    cin >> x;
    locate(POSICION_MATRIX_X+ 2 + offsetX, POSICION_MATRIX_Y + offsetY);
    cin >> y;
    locate(POSICION_MATRIX_X + 8 + offsetX, POSICION_MATRIX_Y + offsetY);
    cin >> r;
}
void ingresarDatos(int& x, int& y, int offsetX, int offsetY) {
    locate(POSICION_MATRIX_X + 4 + offsetX, POSICION_MATRIX_Y + 6 + offsetY);
    cin >> x;
    locate(POSICION_MATRIX_X + 4 + 2 + offsetX, POSICION_MATRIX_Y + 6 + offsetY);
    cin >> y;
    locate(POSICION_MATRIX_X + 12 + offsetX, POSICION_MATRIX_Y + 6 + offsetY);
}
void ingresarDatos(char& value, int offsetX, int offsetY) {
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    cin >> value;
}