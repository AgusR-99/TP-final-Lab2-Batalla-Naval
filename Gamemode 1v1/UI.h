#pragma once



int setFreq(Frecuencia value);
int setDuration(Duracion value);
int setMod(Estado value);
bool AjustarVentana(int Ancho, int Alto);

int setFreq(Frecuencia value) {
    switch (value) {
    case Frecuencia:: ALTA: return 2000;
    case Frecuencia::MEDIA: return 750;
    case Frecuencia:: BAJA: return 500;
    }
}
int setDuration(Duracion value) {
    switch (value) {
    case Duracion::INSTANTANEO: return 0;
    case Duracion::     RAPIDO: return 5;
    case Duracion::     NORMAL: return 15;
    case Duracion::      LENTO: return 30;
    }
}
int setMod(Estado estado) {
    switch (estado) {
    case Estado::  GOLPE: return 50;
    case Estado::  FALLO: return -5;
    case Estado::HUNDIDA: return 250;
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

//Muestra la interfaz de ingreso de naves
void mostrarInterfazIngreso(int i, char r, int offsetX, int offsetY, bool bInstant);
//Muestra mensaje de comienzo rapido
void mostrarInterfazComienzoRapido(int offsetX, int offsetY);
//Muestra los turnos en la interfaz
void mostrarInterfazTurnos(int, int, int);
//Muestra las acciones en la interfaz
void mostrarInterfazAcciones(Estado est0, Estado est1, int res0, int res1, int turn, int x, int y, int xJug, int yJug, int xIA, int yIA, int score, int oldScore, float mult);
//Muestra en la interfaz las naves restantes
void mostrarInterfazNavesRestantes(int, int, int, int);
//Muestra el resultado de la partida en la interfaz
void mostrarInterfazCondicion(string condicion);
//Muestra un mensaje de error de respuesta invalida
void mostrarInterfazRespuestaInvalida(int offsetX, int offsetY);
//Mostrar interfaz de leaderboard
void mostrarInterfazLeaderboard();
//Intercambiar elementos de un vector
void intercambiar(Jugador*, Jugador*);

//Se valida y muestra errores de colocacion de naves
void validacionesFlags(int& validacion, bool& flag0, bool& flag1, bool& flag2);

//Muestra el resultado de un ataque
void mostrarResultadoAccion(Estado estado, Frecuencia freq);
//Muestra ambos tableros
void mostrarTableros(Matriz, Matriz);

//Muestra coordenadas ingresadas en el turno
void mostrarCoordenadas(int, int, Frecuencia);
//Muestra una nave con los sprites
void mostrarNave(int id, int length, Elemento);

bool esDigitos(const std::string& str);
char strToOrientacion(string c);
char strToRespuesta(string input);
Input leerListaDeComandos(string input);
//Pide coordenadas X e Y, asi como una orientacion
Input ingresarDatos(int&, int&, char&, int, int);
//Pide coordenadas X e Y
Input ingresarDatos(int&, int&, int, int);
//Pide un char
Input ingresarDatos(char&, int offsetX, int offsetY);
// Mostrar texto animado
void mostrarTextoAnimado(string texto, Duracion sleepDuration);
//Mostrar texto animado con sonidos
void mostrarTextoAnimado(string texto, Duracion beepDuration, Frecuencia beepFreq);
//Muestra el cambio en puntuaje mediante una animacion
void rollearPuntuaje(int inicio, int objetivo, int offsetX, int offsetY);
string setearCondicion(Resultados);

void mostrarInterfazIngreso(int id, char r, int offsetX, int offsetY, bool bInstant) {
    Nave nave;
    Elemento elemento;
    Duracion fastD   = Duracion::RAPIDO;
    Duracion normalD = Duracion::NORMAL;
    Duracion slowD   = Duracion::LENTO;
    if (bInstant == true) {
        fastD   = Duracion::INSTANTANEO;
        normalD = Duracion::INSTANTANEO;
        slowD   = Duracion::INSTANTANEO;
    }
    locate(POSICION_MATRIX_X + offsetX - 15, POSICION_MATRIX_Y + 7 + offsetY);
    cout << ":q";
    setColor(LIGHTBLUE);
    cout << "<Enter>";
    resetColor();
    cout << " para salir - :d";
    setColor(LIGHTBLUE);
    cout << "<Enter>";
    resetColor();
    cout << " para togglear debug mode";
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    mostrarTextoAnimado("EMBARCACION", normalD);
    locate(POSICION_MATRIX_X + 16 + offsetX, POSICION_MATRIX_Y + offsetY);
    mostrarTextoAnimado("SPRITE", normalD);
    locate(POSICION_MATRIX_X + 23 + offsetX, POSICION_MATRIX_Y + offsetY);
    mostrarTextoAnimado("TAMAÑO", normalD);
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 1 + offsetY);
    mostrarTextoAnimado("-----------------------------", fastD);
    //Se crea una nave temporalmente para poder mostrarla
    nave.CrearNave(id);
    elemento.setSpriteNave(id);
    int length = nave.getTamanio();
    //Se muestra que nave se va a ingresar
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 2 + offsetY);
    //Nombre de la nave
    buffer << nave.getNombre();
    mostrarTextoAnimado(buffer.str(), normalD);
    //Limpieza de buffer
    buffer.str("");
    locate(POSICION_MATRIX_X + 12 + offsetX, POSICION_MATRIX_Y + 2 + offsetY);
    mostrarTextoAnimado(" >> ", normalD);
    //Mostrar sprite de nave
    mostrarNave(id, length, elemento);
    locate(POSICION_MATRIX_X + 22 + offsetX, POSICION_MATRIX_Y + 2 + offsetY);
    //Limpieza de buffer
    buffer.str("");
    //Mostar tamanio de nave
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
    resetColor();
    locate(POSICION_MATRIX_X + offsetX - 10, POSICION_MATRIX_Y + 7 + offsetY);
    cout << ":q";
    setColor(LIGHTBLUE);
    cout << "<Enter>";
    resetColor();
    cout << " para salir - :d";
    setColor(LIGHTBLUE);
    cout << "<Enter>";
    resetColor();
    cout << " para togglear debug mode";
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    setColor(YELLOW);
    mostrarTextoAnimado("¿Colocar naves aletoriamente (Y/N)? >>", Duracion::NORMAL, Frecuencia::MEDIA);
}
void mostrarInterfazTurnos(int turno, int offsetX, int offsetY) {
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    cout << "~~~~~~~~~~~~~~~~~TURNO " << turno << "~~~~~~~~~~~~~~~~~";
}
void mostrarInterfazAcciones(Estado estadoJugador, Estado estadoIA, int restantesJugador, int restantesIA, int turno, int offsetX, int offsetY, int xJugador, int yJugador, int xIA, int yIA, int puntuaje, int puntuajeOld, float mult) {
    locate(POSICION_MATRIX_X + offsetX - 5, POSICION_MATRIX_Y + 8 + offsetY);
    cout << ":q";
    setColor(LIGHTBLUE);
    cout << "<Enter>";
    resetColor();
    cout << " para salir - :d";
    setColor(LIGHTBLUE);
    cout << "<Enter>";
    resetColor();
    cout << " para togglear debug mode";
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    mostrarInterfazNavesRestantes(restantesJugador, restantesIA, offsetX, offsetY);
    mostrarInterfazTurnos(turno, offsetX, offsetY + 1);
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 2 + offsetY);
    setColor(LIGHTCYAN);
    mostrarTextoAnimado("Jugador: ", Duracion::NORMAL, Frecuencia::ALTA);
    resetColor();
    mostrarCoordenadas(xJugador, yJugador, Frecuencia::ALTA);
    mostrarResultadoAccion(estadoJugador, Frecuencia::ALTA);
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 3 + offsetY);
    setColor(LIGHTRED);
    Sleep(500);
    mostrarTextoAnimado("IA: ", Duracion::NORMAL, Frecuencia::BAJA);
    resetColor();
    mostrarCoordenadas(xIA, yIA, Frecuencia::BAJA);
    mostrarResultadoAccion(estadoIA, Frecuencia::BAJA);
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
    cout << "      ";
    cout << condicion;
    locate(20, 22);
    cout << "Presione cualquier tecla para continuar...";
    system("pause>nul");
}
void mostrarInterfazRespuestaInvalida(int offsetX, int offsetY) {
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    setColor(RED);
    cout << "ERROR: ";
    resetColor();
    cout << "Respuesta invalida";
}
void mostrarInterfazPuntuaje(int puntuaje, char* resultado, int offsetX, int offsetY) {
    system("cls");
    int max = 15;
    char nombre[15];
    locate(POSICION_MATRIX_X + offsetX + 13, POSICION_MATRIX_Y + offsetY);
    setColor(LIGHTCYAN);
    cout << "Su puntuaje: " << setw(4) << setfill('0') << puntuaje;
    resetColor();
    locate(POSICION_MATRIX_X + offsetX + 3, POSICION_MATRIX_Y + 2 + offsetY);
    cout << "Ingrese su nombre ";
    cout << "[MAX " << max << " caracteres]";
    locate(POSICION_MATRIX_X + offsetX + 14, POSICION_MATRIX_Y + 4 + offsetY);
    cin >> nombre;
    size_t Size = strlen(nombre);
    while ( Size  > max) {
        showcursor();
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
    jugador.setResultado(resultado);
    if (jugador.Grabar() == true) {
        locate(POSICION_MATRIX_X + offsetX + 5, POSICION_MATRIX_Y + 6 + offsetY);
        setColor(LIGHTGREEN);
        cout << "Has sido agregado al leaderboard!";
        resetColor();
    }
    hidecursor();
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

void intercambiar(Jugador* xp, Jugador* yp) {
    Jugador temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void mostrarInterfazLeaderboard() {
    Jugador reg;
    vector<Jugador> vec;
    int pos = 0;
    system("cls");
    while (true) {
        locate(7, 1);
        setColor(LIGHTBLUE);
        cout << "[Esc]";
        resetColor();
        cout << " - Volver al menu";
        locate(7, 2);
        setColor(LIGHTBLUE);
        cout << "[Supr]";
        resetColor();
        cout << " - Borrar Leaderboard";
        locate(POSICION_MATRIX_X - 15, POSICION_MATRIX_Y + 3);
        cout << "Jugador";
        locate(POSICION_MATRIX_X + 1, POSICION_MATRIX_Y + 3);
        cout << "Puntuaje";
        locate(POSICION_MATRIX_X + 10, POSICION_MATRIX_Y + 3);
        cout << "Resultado";
        while (reg.Leer(pos++)) {
            vec.push_back(reg);
        }

        char maxN[15];
        Resultados maxR;
        int i;
        for (i = 0; i < vec.size(); i++) {
            int max_idx = i;
            for (int j = i + 1; j < vec.size(); j++) {
                if (vec[j].getPuntuaje() > vec[i].getPuntuaje()) {
                    max_idx = j;
                }
            }
            intercambiar(&vec[max_idx], &vec[i]);
            locate(1, i + 4);
            cout << i + 1;
            vec[i].Mostrar(-15, i + 4);
        }
        if (i == 0) { 
            locate(7, POSICION_MATRIX_Y + 5);
            setColor(YELLOW);
            cout << "No existen datos de jugadores";
            resetColor();
        }
        
        if (GetAsyncKeyState(VK_ESCAPE)) {
            Beep(1000, 50);
            return;
        }
        if (GetAsyncKeyState(VK_DELETE)) {
            Beep(1000, 50);
            system("cls");
            locate(4, 5);
            cout << "¿Borrar datos de leaderboard?(Y/N)";
            char rta;
            showcursor();
            cin >> rta;
            hidecursor();
            int validacion = validarRespuesta(rta);
            while (validacion == -1) {
                system("cls");
                locate(4, 5);
                cout << "¿Borrar datos de leaderboard?";
                locate(33, 5);
                setColor(LIGHTRED);
                cout << "(Y/N)";
                resetColor();
                showcursor();
                cin >> rta;
                hidecursor();
                validacion = validarRespuesta(rta);
            }
            Beep(1000, 50);
            if (validacion == 1) { 
                reg.VaciarArchivo();
                locate(15, 9);
                setColor(LIGHTRED);
                mostrarTextoAnimado("Datos borrados", Duracion::NORMAL, Frecuencia::MEDIA);
                resetColor();
                locate(1, 13);
                mostrarTextoAnimado("Presione cualquier tecla para continuar", Duracion::NORMAL, Frecuencia::MEDIA);
                system("pause>nul");
            }
            return;
        }
    }
}

void validacionesFlags(Error& validacion, bool& flag0, bool& flag1, bool& flag2, Input cmd) {
    if (validacion == Error::OK) validacion = Error::FUERA;
    if (cmd == Input::BAD) {
        locate(POSICION_MATRIX_X + 8, POSICION_MATRIX_Y + 21);
        setColor(RED);
        cout << "ERROR: ";
        resetColor();
        cout << "Comando invalido\n";
    }
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
void mostrarResultadoAccion(Estado estado, Frecuencia freq) {
    int color = WHITE;
    switch (estado) {
    case Estado::ESPERA:
        buffer << "A LA ESPERA";
        break;
    case Estado::HUNDIDA:
        color = LIGHTMAGENTA;
        buffer << "GOLPE! NAVE HUNDIDA!";
        break;
    case Estado::REPETIDO:
        color = LIGHTRED;
        buffer << "ERROR:";
        buffer << " ATAQUE EN CELDA ATACADA";
        break;
    case Estado::FUERA:
        color = LIGHTRED;
        buffer << "ERROR:";
        buffer << " ATAQUE FUERA DEL TABLERO";
        break;
    case Estado::FALLO:
        color = YELLOW;
        buffer << "FALLO";
        break;
    case Estado::GOLPE:
        color = LIGHTRED;
        buffer << "GOLPE!";
        break;
    case Estado::INVALIDO:
        color = LIGHTRED;
        buffer << "COMANDO INVALIDO";
        break;
    case Estado::DEBUG:
        color = LIGHTGREEN;
        buffer << "MODO DEBUG ACTIVADO";
        break;
    case Estado::DEBUGOFF:
        color = YELLOW;
        buffer << "MODO DEBUG DESACTIVADO";
        break;
    default:
        color = LIGHTRED;
        buffer << "ERROR DESCONOCIDO";
        break;
    }
    
    setColor(color);
    mostrarTextoAnimado(buffer.str(), Duracion::NORMAL, freq);
    resetColor();
    //Limpieza de buffer
    buffer.str("");
}

void mostrarCoordenadas(int x, int y, Frecuencia frequency) {
    if (x != -1 && y != -1) buffer << x << "-" << y << " -> ";
    mostrarTextoAnimado(buffer.str(), Duracion::NORMAL, frequency);
    buffer.str("");
}
void mostrarNave(int id, int length, Elemento elemento) {
    for (size_t i = 0; i < length; i++) {
        buffer << elemento.getSprite();
    }
    mostrarTextoAnimado(buffer.str(), Duracion::NORMAL);
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
void mostrarTextoAnimado(string texto, Duracion sleepDuration) {
    int x = 0;
    while (texto[x] != '\0') {
        cout << texto[x];
        Sleep(setDuration(sleepDuration));
        x++;
    };
}
void mostrarTextoAnimado(string texto, Duracion beepDuration, Frecuencia beepFreq) {
    int x = 0;
    while (texto[x] != '\0') {
        cout << texto[x];
        Beep(setFreq(beepFreq), setDuration(beepDuration));
        x++;
    };
}

bool esDigitos(const string& str) {
    return str.find_first_not_of("0123456789") == string::npos;
}


Input ingresarDatos(int& x, int& y, char& r, int offsetX, int offsetY) {
    string input;
    Input inputTipo;
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    cin >> input;
    inputTipo = leerListaDeComandos(input);
    if (inputTipo == Input::QUITAR) return Input::QUITAR;
    if (inputTipo == Input::DEBUG) return Input::DEBUG;
    if (esDigitos(input) == true) {
        x = stoi(input);
    }
    else return Input::BAD;
    locate(POSICION_MATRIX_X + 2 + offsetX, POSICION_MATRIX_Y + offsetY);
    cin >> input;
    inputTipo = leerListaDeComandos(input);
    if (inputTipo == Input::QUITAR) return Input::QUITAR;
    if (inputTipo == Input::DEBUG) return Input::DEBUG;
    if (esDigitos(input) == true) {
        y = stoi(input);
    }
    else return Input::BAD;
    locate(POSICION_MATRIX_X + 8 + offsetX, POSICION_MATRIX_Y + offsetY);
    cin >> input;
    inputTipo = leerListaDeComandos(input);
    if (inputTipo == Input::QUITAR) return Input::QUITAR;
    if (inputTipo == Input::DEBUG) return Input::DEBUG;
    r = strToOrientacion(input);
    if (r == '0') return Input::BAD;
    return Input::OK;
}
Input ingresarDatos(int& x, int& y, int offsetX, int offsetY) {
    string input;
    Input inputTipo;
    locate(POSICION_MATRIX_X + 4 + offsetX, POSICION_MATRIX_Y + 6 + offsetY);
    cin >> input;
    inputTipo = leerListaDeComandos(input);
    if (inputTipo == Input::QUITAR) return Input::QUITAR;
    if (inputTipo == Input::DEBUG) return Input::DEBUG;
    if (esDigitos(input) == true) {
        x = stoi(input);
    }
    else return Input::BAD;
    locate(POSICION_MATRIX_X + 4 + 2 + offsetX, POSICION_MATRIX_Y + 6 + offsetY);
    cin >> input;
    inputTipo = leerListaDeComandos(input);
    if (inputTipo == Input::QUITAR) return Input::QUITAR;
    if (inputTipo == Input::DEBUG) return Input::DEBUG;
    if (esDigitos(input) == true) {
        y = stoi(input);
    }
    else return Input::BAD;
    return Input::OK;
}
Input ingresarDatos(char& value, int offsetX, int offsetY) {
    string input;
    Input inputTipo;
    locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    cin >> input;
    inputTipo = leerListaDeComandos(input);
    if (inputTipo == Input::QUITAR) return Input::QUITAR;
    if (inputTipo == Input::DEBUG) return Input::DEBUG;
    value = strToRespuesta(input);
    if (value == '0') return Input::BAD;
    return Input::OK;
}

string setearCondicion(Resultados condicion) {
    string str;
    if (condicion == Resultados::VICTORIA) {
        str = R"(
                ____   ____.__        __               .__        
                \   \ /   /|__| _____/  |_  ___________|__|____   
                 \   Y   / |  |/ ___\   __\/  _ \_  __ \  \__  \  
                  \     /  |  \  \___|  | (  <_> )  | \/  |/ __ \_
                   \___/   |__|\___  >__|  \____/|__|  |__(____  /
                                   \/                          \/ )";
    }
    else if (condicion == Resultados::DERROTA) {
        str = R"(
                ________                              __          
                \______ \   __________________  _____/  |______   
                 |    |  \_/ __ \_  __ \_  __ \/  _ \   __\__  \  
                 |    `   \  ___/|  | \/|  | \(  <_> )  |  / __ \_
                /_______  /\___  >__|   |__|   \____/|__| (____  /
                        \/     \/                              \/ 
)";
    }
    else if (condicion == Resultados::TRAMPOSO) {
        str = R"(
                 _____                                         
                |_   _|                                        
                  | |_ __ __ _ _ __ ___  _ __   ___  ___  ___  
                  | | '__/ _` | '_ ` _ \| '_ \ / _ \/ __|/ _ \ 
                  | | | | (_| | | | | | | |_) | (_) \__ \ (_) |
                  \_/_|  \__,_|_| |_| |_| .__/ \___/|___/\___/ 
                                        | |                    
                                        |_|                      
        )";
    }
    return str;
}
