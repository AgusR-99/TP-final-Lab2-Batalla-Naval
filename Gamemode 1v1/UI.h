#pragma once

int setFreq(const int value);
int setDuration(const int value);
int setMod(const int value);
bool AjustarVentana(int Ancho, int Alto);


int setFreq(const int value) {
    switch (value) {
    case HIGH: return 2000;
    case MEDIUM: return 750;
    case LOW: return 500;
    }
}
int setDuration(const int value) {
    switch (value) {
    case INSTANT: return 0;
    case FAST: return 5;
    case NORMAL: return 15;
    case SLOW: return 30;
    }
}
int setMod(const int value) {
    switch (value) {
    case GOLPE: return 50;
    case FALLO: return -5;
    case HUNDIR: return 250;
    }
}
bool AjustarVentana(int Ancho, int Alto) {
    _COORD Coordenada;
    Coordenada.X = Ancho;
    Coordenada.Y = Alto;

    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Right = Ancho - 1;
    Rect.Bottom = Alto - 1;

    // Obtener el handle de la consola
    HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);

    // Ajustar el buffer al nuevo tamaño
    SetConsoleScreenBufferSize(hConsola, Coordenada);

    // Cambiar tamaño de consola a lo especificado en el buffer
    SetConsoleWindowInfo(hConsola, TRUE, &Rect);
    return TRUE;
}

void mostrarInterfazInicio(int offsetX, int offsetY);
//Muestra la interfaz de ingreso de naves
void mostrarInterfazIngreso(int i, char r, int offsetX, int offsetY, bool bInstant);
//Muestra mensaje de comienzo rapido
void mostrarInterfazComienzoRapido(int offsetX, int offsetY);
//Muestra los turnos en la interfaz
void mostrarInterfazTurnos(int, int, int);
//Muestra las acciones en la interfaz
void mostrarInterfazAcciones(int est0, int est1, int res0, int res1, int turn, int x, int y, int xJug, int yJug, int xIA, int yIA, int score, int oldScore, float mult);
//Muestra en la interfaz las naves restantes
void mostrarInterfazNavesRestantes(int, int, int, int);
//Muestra el resultado de la partida en la interfaz
void mostrarInterfazCondicion(string condicion);
//Muestra un mensaje de error de respuesta invalida
void mostrarInterfazRespuestaInvalida(int offsetX, int offsetY);


//Se valida y muestra errores de colocacion de naves
void validacionesFlags(int& validacion, bool& flag0, bool& flag1, bool& flag2);

//Muestra el resultado de un ataque
void mostrarResultadoAccion(int estado, int);
//Muestra ambos tableros
void mostrarTableros(Matriz, Matriz);

//Muestra coordenadas ingresadas en el turno
void mostrarCoordenadas(int, int, int);
//Muestra una nave con los sprites
void mostrarNave(int id, int length);

//Pide coordenadas X e Y, asi como una orientacion
void ingresarDatos(int&, int&, char&, int, int);
//Pide coordenadas X e Y
void ingresarDatos(int&, int&, int, int);
//Pide un char
void ingresarDatos(char&, int offsetX, int offsetY);
// Mostrar texto animado
void mostrarTextoAnimado(string texto, int sleepDuration);
//Mostrar texto animado con sonidos
void mostrarTextoAnimado(string texto, int beepFreq, int beepDuration);
//Muestra el cambio en puntuaje mediante una animacion
void rollearPuntuaje(int inicio, int objetivo, int offsetX, int offsetY);
string setearCondicion(bool);

void mostrarInterfazInicio(int offsetX, int offsetY) {

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
    locate(POSICION_MATRIX_X + 4 + offsetX + 4, POSICION_MATRIX_Y + 5 + offsetY);
    cout << "X";
    locate(POSICION_MATRIX_X + 4 + offsetX + 6, POSICION_MATRIX_Y + 5 + offsetY);
    cout << "Y";
    locate(POSICION_MATRIX_X + offsetX + 16, POSICION_MATRIX_Y + 5 + offsetY);
    mostrarTextoAnimado("v/h", normalD);
}
void mostrarInterfazComienzoRapido(int offsetX, int offsetY) {
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    setColor(YELLOW);
    mostrarTextoAnimado("¿Colocar naves aletoriamente (Y/N)? >>", NORMAL, MEDIUM);
    resetColor();
}
void mostrarInterfazTurnos(int turno, int offsetX, int offsetY) {
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    cout << "~~~~~~~~~~~~~~~~~TURNO " << turno << "~~~~~~~~~~~~~~~~~";
}
void mostrarInterfazAcciones(int estadoJugador, int estadoIA, int restantesJugador, int restantesIA, int turno, int offsetX, int offsetY, int xJugador, int yJugador, int xIA, int yIA, int puntuaje, int puntuajeOld, float mult) {
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
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 6 + offsetY);
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 7 + offsetY);
    cout << "Score:";
    locate(POSICION_MATRIX_X + offsetX + 12, POSICION_MATRIX_Y + 7 + offsetY);
    cout << "Mult:" << mult;
    rollearPuntuaje(puntuajeOld, puntuaje, POSICION_MATRIX_X + 7 + +offsetX, POSICION_MATRIX_Y + 7 + offsetY);
}
void mostrarInterfazNavesRestantes(int restantes0, int restantes1, int offsetX, int offsetY) {
    locate(POSICION_MATRIX_X + offsetX - 1, POSICION_MATRIX_Y + offsetY);
    setColor(LIGHTCYAN);
    cout << "=========>" << restantes0 << "<=========";
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
void mostrarInterfazPuntuaje(int puntuaje, int offsetX, int offsetY) {
    system("cls");
    int max = 15;
    string nombre;
    locate(POSICION_MATRIX_X + offsetX + 13, POSICION_MATRIX_Y + offsetY);
    setColor(LIGHTCYAN);
    cout << "Su puntuaje: " << setw(4) << setfill('0') << puntuaje;
    resetColor();
    locate(POSICION_MATRIX_X + offsetX + 3, POSICION_MATRIX_Y + 2 + offsetY);
    cout << "Ingrese su nombre ";
    cout << "[MAX " << max << " caracteres]";
    locate(POSICION_MATRIX_X + offsetX + 14, POSICION_MATRIX_Y + 4 + offsetY);
    cin >> nombre;
    while (nombre.size() > max) {
        locate(POSICION_MATRIX_X + offsetX + 3, POSICION_MATRIX_Y + 2 + offsetY);
        cout << "Ingrese su nombre ";
        setColor(LIGHTRED);
        cout << "[MAX " << max << " caracteres]";
        resetColor();
        locate(POSICION_MATRIX_X + offsetX + 14, POSICION_MATRIX_Y + 4 + offsetY);
        //Limpiar campo
        printf("%c[2K", 27);
        cin >> nombre;
    }
    hidecursor();
    Jugador jugador;
    jugador.setNombre(nombre);
    jugador.setPuntuaje(puntuaje);
    if (jugador.Grabar() == true) {
        locate(POSICION_MATRIX_X + offsetX + 5, POSICION_MATRIX_Y + 6 + offsetY);
        setColor(LIGHTGREEN);
        cout << "Has sido agregado al leaderboard!";
        resetColor();
    }
    locate(POSICION_MATRIX_X + offsetX + 3, POSICION_MATRIX_Y + 2 + offsetY);
    cout << "Ingrese su nombre ";
    setColor(LIGHTGREEN);
    cout << "[MAX " << max << " caracteres]";
    resetColor();
    locate(POSICION_MATRIX_X + offsetX + 10, POSICION_MATRIX_Y + 8 + offsetY);
    cout << "Retornando al menu...";
    for (size_t i = 3; i > 0; i--){
        locate(POSICION_MATRIX_X + offsetX + 31, POSICION_MATRIX_Y + 8 + offsetY);
        cout << i;
        Sleep(1000);
    }
    showcursor();
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
    else if (flag2 == true) {
        locate(POSICION_MATRIX_X + 7, POSICION_MATRIX_Y + 21);
        setColor(RED);
        cout << "ERROR: ";
        resetColor();
        cout << "Orientacion invalida\n";
        flag2 = false;
    }
}

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
void mostrarResultadoAccion(int estado, int freq) {
    int color = WHITE;
    if (estado == -1) {
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

void mostrarCoordenadas(int x, int y, int frequency) {
    if (x != -1 && y != -1) buffer << x << "-" << y << " -> ";
    mostrarTextoAnimado(buffer.str(), NORMAL, setFreq(frequency));
    buffer.str("");
}
void mostrarNave(int id, int length) {
    for (size_t i = 0; i < length; i++) {
        buffer << spriteList[id + 4];
    }
    mostrarTextoAnimado(buffer.str(), NORMAL);
}

void rollearPuntuaje(int inicio, int objetivo, int x, int y) {
    //Si la diferenca es mayor a 100, la animacion sera mas rapida
    int velocidad = 1;
    int dif = objetivo - inicio;
    if (dif > 100) velocidad = 4;
    hidecursor();
    if (inicio < objetivo) {
        for (int i = inicio; i < objetivo; i = i + velocidad) {
            locate(x, y);
            cout << setw(4) << setfill('0') << i;
            Sleep(1);
        }
    }
    else if (inicio > objetivo) {
        int dif = inicio - objetivo;
        for (int i = inicio; i > objetivo; i = i - velocidad) {
            locate(x, y);
            cout << setw(4) << setfill('0') << i;
            Sleep(1);
        }
    }
    locate(x, y);
    cout << setw(4) << setfill('0') << objetivo;
    showcursor();
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

void ingresarDatos(int& x, int& y, char& r, int offsetX, int offsetY) {
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    cin >> x;
    locate(POSICION_MATRIX_X + 2 + offsetX, POSICION_MATRIX_Y + offsetY);
    cin >> y;
    locate(POSICION_MATRIX_X + 8 + offsetX, POSICION_MATRIX_Y + offsetY);
    cin >> r;
}
void ingresarDatos(int& x, int& y, int offsetX, int offsetY) {
    locate(POSICION_MATRIX_X + 4 + offsetX, POSICION_MATRIX_Y + 6 + offsetY);
    cin >> x;
    locate(POSICION_MATRIX_X + 4 + 2 + offsetX, POSICION_MATRIX_Y + 6 + offsetY);
    cin >> y;
}
void ingresarDatos(char& value, int offsetX, int offsetY) {
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    cin >> value;
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
