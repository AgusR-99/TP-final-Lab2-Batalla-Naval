#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <Windows.h>
std::stringstream buffer;
#include "UI.h"
int setFreq(Frecuencia value) {
    switch (value) {
    case Frecuencia::ALTA: return 2000;
    case Frecuencia::MEDIA: return 750;
    case Frecuencia::BAJA: return 500;
    }
}
int setDuration(Duracion value) {
    switch (value) {
    case Duracion::INSTANTANEO: return 0;
    case Duracion::RAPIDO: return 5;
    case Duracion::NORMAL: return 15;
    case Duracion::LENTO: return 30;
    }
}
int setMod(Estado estado) {
    switch (estado) {
    case Estado::GOLPE: return 50;
    case Estado::FALLO: return -5;
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

void setearColorDefault(){
    rlutil::setColor(rlutil::WHITE);
    rlutil::saveDefaultColor();
}

void mostrarInterfazIngreso(int id, char r, int offsetX, int offsetY, bool bInstant) {
    Nave nave;
    Elemento elemento;
    Duracion fastD = Duracion::RAPIDO;
    Duracion normalD = Duracion::NORMAL;
    Duracion slowD = Duracion::LENTO;
    if (bInstant == true) {
        fastD = Duracion::INSTANTANEO;
        normalD = Duracion::INSTANTANEO;
        slowD = Duracion::INSTANTANEO;
    }
    rlutil::locate(POSICION_MATRIX_X + offsetX - 15, POSICION_MATRIX_Y + 7 + offsetY);
    std::cout << ":q";
    rlutil::setColor(rlutil::LIGHTBLUE);
    std::cout << "<Enter>";
    rlutil::resetColor();
    std::cout << " para salir - :d";
    rlutil::setColor(rlutil::LIGHTBLUE);
    std::cout << "<Enter>";
    rlutil::resetColor();
    std::cout << " para togglear debug mode";
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    mostrarTextoAnimado("EMBARCACION", normalD);
    rlutil::locate(POSICION_MATRIX_X + 16 + offsetX, POSICION_MATRIX_Y + offsetY);
    mostrarTextoAnimado("SPRITE", normalD);
    rlutil::locate(POSICION_MATRIX_X + 23 + offsetX, POSICION_MATRIX_Y + offsetY);
    mostrarTextoAnimado("TAMAÑO", normalD);
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 1 + offsetY);
    mostrarTextoAnimado("-----------------------------", fastD);
    //Se crea una nave temporalmente para poder mostrarla
    nave.CrearNave(id);
    elemento.setSpriteNave(id);
    int length = nave.getTamanio();
    //Se muestra que nave se va a ingresar
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 2 + offsetY);
    //Nombre de la nave
    buffer << nave.getNombre();
    mostrarTextoAnimado(buffer.str(), normalD);
    //Limpieza de buffer
    buffer.str("");
    rlutil::locate(POSICION_MATRIX_X + 12 + offsetX, POSICION_MATRIX_Y + 2 + offsetY);
    mostrarTextoAnimado(" >> ", normalD);
    //Mostrar sprite de nave
    mostrarNave(id, length, elemento);
    rlutil::locate(POSICION_MATRIX_X + 22 + offsetX, POSICION_MATRIX_Y + 2 + offsetY);
    //Limpieza de buffer
    buffer.str("");
    //Mostar tamanio de nave
    buffer << " [" << length << "]";
    mostrarTextoAnimado(buffer.str(), normalD);
    //Limpieza de buffer
    buffer.str("");
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 3 + offsetY);
    mostrarTextoAnimado("-----------------------------", fastD);
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 4 + offsetY);
    mostrarTextoAnimado("Coordenadas", normalD);
    rlutil::locate(POSICION_MATRIX_X + offsetX + 16, POSICION_MATRIX_Y + 4 + offsetY);
    mostrarTextoAnimado("Orientacion", normalD);
    rlutil::locate(POSICION_MATRIX_X + 4 + offsetX + 4, POSICION_MATRIX_Y + 5 + offsetY);
    std::cout << "X";
    rlutil::locate(POSICION_MATRIX_X + 4 + offsetX + 6, POSICION_MATRIX_Y + 5 + offsetY);
    std::cout << "Y";
    rlutil::locate(POSICION_MATRIX_X + offsetX + 16, POSICION_MATRIX_Y + 5 + offsetY);
    mostrarTextoAnimado("v/h", normalD);
}
void mostrarInterfazComienzoRapido(int offsetX, int offsetY) {
    rlutil::resetColor();
    rlutil::locate(POSICION_MATRIX_X + offsetX - 10, POSICION_MATRIX_Y + 7 + offsetY);
    std::cout << ":q";
    rlutil::setColor(rlutil::LIGHTBLUE);
    std::cout << "<Enter>";
    rlutil::resetColor();
    std::cout << " para salir - :d";
    rlutil::setColor(rlutil::LIGHTBLUE);
    std::cout << "<Enter>";
    rlutil::resetColor();
    std::cout << " para togglear debug mode";
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    rlutil::setColor(rlutil::YELLOW);
    mostrarTextoAnimado("¿Colocar naves aletoriamente (Y/N)? >>", Duracion::NORMAL, Frecuencia::MEDIA);
}
void mostrarInterfazTurnos(int turno, int offsetX, int offsetY) {
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    std::cout << "~~~~~~~~~~~~~~~~~TURNO " << turno << "~~~~~~~~~~~~~~~~~";
}
void mostrarInterfazAcciones(Estado estadoJugador, Estado estadoIA, int restantesJugador, int restantesIA, int turno, int offsetX, int offsetY, int xJugador, int yJugador, int xIA, int yIA, int puntuaje, int puntuajeOld, float mult, bool* flagVictoria, bool* flagDerrota) {
    rlutil::locate(POSICION_MATRIX_X + offsetX - 5, POSICION_MATRIX_Y + 8 + offsetY);
    std::cout << ":q";
    rlutil::setColor(rlutil::LIGHTBLUE);
    std::cout << "<Enter>";
    rlutil::resetColor();
    std::cout << " para salir - :d";
    rlutil::setColor(rlutil::LIGHTBLUE);
    std::cout << "<Enter>";
    rlutil::resetColor();
    std::cout << " para togglear debug mode";
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    mostrarInterfazNavesRestantes(restantesJugador, restantesIA, offsetX, offsetY);
    mostrarInterfazTurnos(turno, offsetX, offsetY + 1);
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 2 + offsetY);
    rlutil::setColor(rlutil::LIGHTCYAN);
    mostrarTextoAnimado("Jugador: ", Duracion::NORMAL, Frecuencia::ALTA);
    rlutil::resetColor();
    mostrarCoordenadas(xJugador, yJugador, Frecuencia::ALTA);
    mostrarResultadoAccion(estadoJugador, Frecuencia::ALTA);
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 3 + offsetY);
    rlutil::setColor(rlutil::LIGHTRED);
    Sleep(500);
    mostrarTextoAnimado("IA: ", Duracion::NORMAL, Frecuencia::BAJA);
    rlutil::resetColor();
    mostrarCoordenadas(xIA, yIA, Frecuencia::BAJA);
    mostrarResultadoAccion(estadoIA, Frecuencia::BAJA);
    Sleep(500);
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 4 + offsetY);
    std::cout << "ATAQUE\n";
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 5 + offsetY);
    std::cout << "Coordenadas (X Y) >> ";
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 6 + offsetY);
    if (restantesIA == 2 and *flagVictoria == false) { 
        *flagVictoria = true;
        rlutil::setColor(rlutil::LIGHTCYAN);
        mostrarTextoAnimado("Victoria inminente!", Duracion::RAPIDO);
        rlutil::resetColor();
    }
    else if (restantesJugador == 2 and *flagDerrota == false) { 
        *flagDerrota = true;
        rlutil::setColor(rlutil::LIGHTRED);
        mostrarTextoAnimado("Derrota inminente!", Duracion::RAPIDO);
        rlutil::resetColor();
    }
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 7 + offsetY);
    std::cout << "Score:";
    rlutil::locate(POSICION_MATRIX_X + offsetX + 12, POSICION_MATRIX_Y + 7 + offsetY);
    std::cout << "Mult:" << mult;
    rollearPuntuaje(puntuajeOld, puntuaje, POSICION_MATRIX_X + 7 + +offsetX, POSICION_MATRIX_Y + 7 + offsetY);
}
void mostrarInterfazNavesRestantes(int restantes0, int restantes1, int offsetX, int offsetY) {
    rlutil::locate(POSICION_MATRIX_X + offsetX - 1, POSICION_MATRIX_Y + offsetY);
    rlutil::setColor(rlutil::LIGHTCYAN);
    std::cout << "=========>" << restantes0 << "<=========";
    rlutil::locate(POSICION_MATRIX_X + 22 + offsetX, POSICION_MATRIX_Y + offsetY);
    rlutil::setColor(rlutil::LIGHTRED);
    std::cout << "=========>" << restantes1 << "<=========";
    rlutil::resetColor();
}
void mostrarInterfazCondicion(std::string condicion) {
    std::cout << "      ";
    std::cout << condicion;
    rlutil::locate(20, 22);
    std::cout << "Presione cualquier tecla para continuar...";
    system("pause>nul");
}
void mostrarInterfazRespuestaInvalida(int offsetX, int offsetY) {
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    rlutil::setColor(rlutil::RED);
    std::cout << "ERROR: ";
    rlutil::resetColor();
    std::cout << "Respuesta invalida";
}
void mostrarInterfazPuntuaje(int puntuaje, char* resultado, int offsetX, int offsetY) {
    system("cls");
    int max = 15;
    char nombre[15];
    std::string str;
    rlutil::locate(POSICION_MATRIX_X + offsetX + 13, POSICION_MATRIX_Y + offsetY);
    rlutil::setColor(rlutil::LIGHTCYAN);
    std::cout << "Su puntuaje: " << std::setw(4) << std::setfill('0') << puntuaje;
    rlutil::resetColor();
    rlutil::locate(POSICION_MATRIX_X + offsetX + 3, POSICION_MATRIX_Y + 2 + offsetY);
    std::cout << "Ingrese su nombre ";
    std::cout << "[MAX " << max << " caracteres]";
    rlutil::locate(POSICION_MATRIX_X + offsetX + 14, POSICION_MATRIX_Y + 4 + offsetY);
    std::cin >> str;
    size_t Size = str.size();
    while (Size > max) {
        rlutil::showcursor();
        rlutil::locate(POSICION_MATRIX_X + offsetX + 3, POSICION_MATRIX_Y + 2 + offsetY);
        std::cout << "Ingrese su nombre ";
        rlutil::setColor(rlutil::LIGHTRED);
        std::cout << "[MAX " << max << " caracteres]";
        rlutil::resetColor();
        rlutil::locate(POSICION_MATRIX_X + offsetX + 14, POSICION_MATRIX_Y + 4 + offsetY);
        //Limpiar campo
        printf("%c[2K", 27);
        std::cin >> str;
        Size = str.size();
    }
    strcpy(nombre, str.c_str());
    rlutil::hidecursor();
    Jugador jugador;
    jugador.setNombre(nombre);
    jugador.setPuntuaje(puntuaje);
    jugador.setResultado(resultado);
    if (jugador.Grabar() == true) {
        rlutil::locate(POSICION_MATRIX_X + offsetX + 5, POSICION_MATRIX_Y + 6 + offsetY);
        rlutil::setColor(rlutil::LIGHTGREEN);
        std::cout << "Has sido agregado al leaderboard!";
        rlutil::resetColor();
    }
    rlutil::hidecursor();
    rlutil::locate(POSICION_MATRIX_X + offsetX + 3, POSICION_MATRIX_Y + 2 + offsetY);
    std::cout << "Ingrese su nombre ";
    rlutil::setColor(rlutil::LIGHTGREEN);
    std::cout << "[MAX " << max << " caracteres]";
    rlutil::resetColor();
    rlutil::locate(POSICION_MATRIX_X + offsetX + 10, POSICION_MATRIX_Y + 8 + offsetY);
    std::cout << "Retornando al menu...";
    for (size_t i = 3; i > 0; i--) {
        rlutil::locate(POSICION_MATRIX_X + offsetX + 31, POSICION_MATRIX_Y + 8 + offsetY);
        std::cout << i;
        Sleep(1000);
    }
    rlutil::showcursor();
}

void intercambiar(Jugador* xp, Jugador* yp) {
    Jugador temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void mostrarInterfazLeaderboard() {
    Jugador reg;
    std::vector<Jugador> vec;
    int pos = 0;
    system("cls");
    while (true) {
        rlutil::locate(7, 1);
        rlutil::setColor(rlutil::LIGHTBLUE);
        std::cout << "[Esc]";
        rlutil::resetColor();
        std::cout << " - Volver al menu";
        rlutil::locate(7, 2);
        rlutil::setColor(rlutil::LIGHTBLUE);
        std::cout << "[Supr]";
        rlutil::resetColor();
        std::cout << " - Borrar Leaderboard";
        rlutil::locate(POSICION_MATRIX_X - 15, POSICION_MATRIX_Y + 3);
        std::cout << "Jugador";
        rlutil::locate(POSICION_MATRIX_X + 1, POSICION_MATRIX_Y + 3);
        std::cout << "Puntuaje";
        rlutil::locate(POSICION_MATRIX_X + 10, POSICION_MATRIX_Y + 3);
        std::cout << "Resultado";
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
            rlutil::locate(1, i + 5);
            std::cout << i + 1;
            vec[i].Mostrar(-15, i + 4);
        }
        if (i == 0) {
            rlutil::locate(7, POSICION_MATRIX_Y + 5);
            rlutil::setColor(rlutil::YELLOW);
            std::cout << "No existen datos de jugadores";
            rlutil::resetColor();
        }

        if (GetAsyncKeyState(VK_ESCAPE)) {
            Beep(1000, 50);
            return;
        }
        if (GetAsyncKeyState(VK_DELETE)) {
            Beep(1000, 50);
            system("cls");
            rlutil::locate(4, 5);
            std::cout << "¿Borrar datos de leaderboard?(Y/N)";
            char rta;
            rlutil::showcursor();
            std::cin >> rta;
            rlutil::hidecursor();
            int validacion = validarRespuesta(rta);
            while (validacion == -1) {
                system("cls");
                rlutil::locate(4, 5);
                std::cout << "¿Borrar datos de leaderboard?";
                rlutil::locate(33, 5);
                rlutil::setColor(rlutil::LIGHTRED);
                std::cout << "(Y/N)";
                rlutil::resetColor();
                rlutil::showcursor();
                std::cin >> rta;
                rlutil::hidecursor();
                validacion = validarRespuesta(rta);
            }
            Beep(1000, 50);
            if (validacion == 1) {
                reg.VaciarArchivo();
                rlutil::locate(15, 9);
                rlutil::setColor(rlutil::LIGHTRED);
                mostrarTextoAnimado("Datos borrados", Duracion::NORMAL, Frecuencia::MEDIA);
                rlutil::resetColor();
                rlutil::locate(1, 13);
                mostrarTextoAnimado("Presione cualquier tecla para continuar", Duracion::NORMAL, Frecuencia::MEDIA);
                system("pause>nul");
            }
            return;
        }
    }
}

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_ENTER 10

bool navegarEnTablero(int x, int y, Matriz tablero){
    int c;
    while (true) {
        //Mostrar coordenadas actuales
        rlutil::resetColor();
        gotoxy(20, 20);
        std::cout << x << "-" << y;

        //Colocar cursor sobre el elemento actual
        gotoxy(x * 2, y);

        //Presionar alguna flecha
        c = _getch();

        //Si se presiona la tecla ESC, se devuelve valor para ir a menu de pausa
        if (c == KEY_ESC) return false;
        //Si se presiona la tecla ENTER, se devuelve valor que confirma las coordenadas
        else if (c == KEY_ENTER) return true;

        //Si se presionan las flechas y no hay overflow, se acciona sobre coords
        if ((c == KEY_UP or c == KEY_DOWN or c == KEY_LEFT or c == KEY_RIGHT)
            and (x < 10 and x >= 0) and (y < 10 and y >= 0)) {

            //Desmarcar elemento actual
            rlutil::resetColor();
            tablero.getElemento();

            //Cambio de coordenadas
            switch (c) {
            case KEY_UP:
                y--;
                break;
            case KEY_DOWN:
                y++;
                break;
            case KEY_LEFT:
                x--;
                break;
            case KEY_RIGHT:
                x++;
                break;
            }

            //Evitar overflow
            if (x > 9) x = 9;
            else if (x < 0) x = 0;
            if (y > 9) y = 9;
            else if (y < 0)y = 0;

            //Bypass del retorno de la funcion getch()
            if (c != 224) {
                rlutil::setColor(rlutil::LIGHTGREEN);
                gotoxy(x * 2, y);
                tablero.getElemento();
            }
        }
    }
}

void validacionesFlags(Error& validacion, bool& flag0, bool& flag1, bool& flag2, Input cmd) {
    if (validacion == Error::OK) validacion = Error::FUERA;
    if (cmd == Input::BAD) {
        rlutil::locate(POSICION_MATRIX_X + 8, POSICION_MATRIX_Y + 21);
        rlutil::setColor(rlutil::RED);
        std::cout << "ERROR: ";
        rlutil::resetColor();
        std::cout << "Comando invalido\n";
    }
    if (flag0 == true) {
        rlutil::locate(POSICION_MATRIX_X + 8, POSICION_MATRIX_Y + 21);
        rlutil::setColor(rlutil::RED);
        std::cout << "ERROR: ";
        rlutil::resetColor();
        std::cout << "Colision de naves\n";
        flag0 = false;
    }
    else if (flag1 == true) {
        rlutil::locate(POSICION_MATRIX_X - 1, POSICION_MATRIX_Y + 21);
        rlutil::setColor(rlutil::RED);
        std::cout << "ERROR: ";
        rlutil::resetColor();
        std::cout << "Nave fuera de los limites del tablero\n";
        flag1 = false;
    }
    else if (flag2 == true) {
        rlutil::locate(POSICION_MATRIX_X + 7, POSICION_MATRIX_Y + 21);
        rlutil::setColor(rlutil::RED);
        std::cout << "ERROR: ";
        rlutil::resetColor();
        std::cout << "Orientacion invalida\n";
        flag2 = false;
    }
}

void mostrarTableros(Matriz tableroJugador, Matriz tableroIA) {
    rlutil::locate(POSICION_MATRIX_X - 1, POSICION_MATRIX_Y);
    rlutil::setColor(rlutil::LIGHTCYAN);
    std::cout << "=======JUGADOR=======\n";
    tableroJugador.DibujarTabla(-1, 1);
    rlutil::locate(POSICION_MATRIX_X + 22, POSICION_MATRIX_Y);
    rlutil::setColor(rlutil::LIGHTRED);
    std::cout << "=========IA==========\n";
    tableroIA.DibujarTabla(22, 1);
    rlutil::locate(POSICION_MATRIX_X + 1, POSICION_MATRIX_Y + 14);
    rlutil::resetColor();
}
void mostrarResultadoAccion(Estado estado, Frecuencia freq) {
    int color = rlutil::WHITE;
    switch (estado) {
    case Estado::ESPERA:
        buffer << "A LA ESPERA";
        break;
    case Estado::HUNDIDA:
        color = rlutil::LIGHTMAGENTA;
        buffer << "GOLPE! NAVE HUNDIDA!";
        break;
    case Estado::REPETIDO:
        color = rlutil::LIGHTRED;
        buffer << "ERROR:";
        buffer << " ATAQUE EN CELDA ATACADA";
        break;
    case Estado::FUERA:
        color = rlutil::LIGHTRED;
        buffer << "ERROR:";
        buffer << " ATAQUE FUERA DEL TABLERO";
        break;
    case Estado::FALLO:
        color = rlutil::YELLOW;
        buffer << "FALLO";
        break;
    case Estado::GOLPE:
        color = rlutil::LIGHTRED;
        buffer << "GOLPE!";
        break;
    case Estado::INVALIDO:
        color = rlutil::LIGHTRED;
        buffer << "COMANDO INVALIDO";
        break;
    case Estado::DEBUG:
        color = rlutil::LIGHTGREEN;
        buffer << "MODO DEBUG ACTIVADO";
        break;
    case Estado::DEBUGOFF:
        color = rlutil::YELLOW;
        buffer << "MODO DEBUG DESACTIVADO";
        break;
    default:
        color = rlutil::LIGHTRED;
        buffer << "ERROR DESCONOCIDO";
        break;
    }

    rlutil::setColor(color);
    mostrarTextoAnimado(buffer.str(), Duracion::NORMAL, freq);
    rlutil::resetColor();
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
    rlutil::hidecursor();
    if (inicio < objetivo) {
        for (int i = inicio; i < objetivo; i = i + velocidad) {
            rlutil::locate(x, y);
            std::cout << std::setw(4) << std::setfill('0') << i;
            Sleep(1);
        }
    }
    else if (inicio > objetivo) {
        int dif = inicio - objetivo;
        for (int i = inicio; i > objetivo; i = i - velocidad) {
            rlutil::locate(x, y);
            std::cout << std::setw(4) << std::setfill('0') << i;
            Sleep(1);
        }
    }
    rlutil::locate(x, y);
    std::cout << std::setw(4) << std::setfill('0') << objetivo;
    rlutil::showcursor();
}
void mostrarTextoAnimado(std::string texto, Duracion sleepDuration) {
    int x = 0;
    while (texto[x] != '\0') {
        std::cout << texto[x];
        Sleep(setDuration(sleepDuration));
        x++;
    };
}
void mostrarTextoAnimado(std::string texto, Duracion beepDuration, Frecuencia beepFreq) {
    int x = 0;
    while (texto[x] != '\0') {
        std::cout << texto[x];
        Beep(setFreq(beepFreq), setDuration(beepDuration));
        x++;
    };
}

bool esDigitos(const std::string& str) {
    return str.find_first_not_of("0123456789") == std::string::npos;
}

void desplazarCursor(int& x, int& y) {

}

Input ingresarDatos(int& x, int& y, char& r, int offsetX, int offsetY, TipoCheat* cmdCheat) {
    std::string input;
    Input inputTipo;
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    std::cin >> input;
    inputTipo = leerListaDeComandos(input, cmdCheat);
    if (inputTipo == Input::QUITAR) return Input::QUITAR;
    if (inputTipo == Input::CHEAT) return Input::CHEAT;
    if (esDigitos(input) == true) {
        x = stoi(input);
    }
    else return Input::BAD;
    rlutil::locate(POSICION_MATRIX_X + 2 + offsetX, POSICION_MATRIX_Y + offsetY);
    std::cin >> input;
    inputTipo = leerListaDeComandos(input, cmdCheat);
    if (inputTipo == Input::QUITAR) return Input::QUITAR;
    if (inputTipo == Input::CHEAT) return Input::CHEAT;
    if (esDigitos(input) == true) {
        y = stoi(input);
    }
    else return Input::BAD;
    rlutil::locate(POSICION_MATRIX_X + 8 + offsetX, POSICION_MATRIX_Y + offsetY);
    std::cin >> input;
    inputTipo = leerListaDeComandos(input, cmdCheat);
    if (inputTipo == Input::QUITAR) return Input::QUITAR;
    if (inputTipo == Input::CHEAT) return Input::CHEAT;
    r = strToOrientacion(input);
    if (r == '0') return Input::BAD;
    return Input::OK;
}
Input ingresarDatos(int& x, int& y, int offsetX, int offsetY, TipoCheat* cmdCheat) {
    std::string input;
    Input inputTipo;
    rlutil::locate(POSICION_MATRIX_X + 4 + offsetX, POSICION_MATRIX_Y + 6 + offsetY);
    std::cin >> input;
    inputTipo = leerListaDeComandos(input, cmdCheat);
    if (inputTipo == Input::QUITAR) return Input::QUITAR;
    if (inputTipo == Input::CHEAT) return Input::CHEAT;
    if (esDigitos(input) == true) {
        x = stoi(input);
    }
    else return Input::BAD;
    rlutil::locate(POSICION_MATRIX_X + 4 + 2 + offsetX, POSICION_MATRIX_Y + 6 + offsetY);
    std::cin >> input;
    inputTipo = leerListaDeComandos(input, cmdCheat);
    if (inputTipo == Input::QUITAR) return Input::QUITAR;
    if (inputTipo == Input::CHEAT) return Input::CHEAT;
    if (esDigitos(input) == true) {
        y = stoi(input);
    }
    else return Input::BAD;
    return Input::OK;
}

Input ingresarDatos(char& value, int offsetX, int offsetY, TipoCheat* cmdCheat) {
    std::string input;
    Input inputTipo;
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    std::cin >> input;
    inputTipo = leerListaDeComandos(input, cmdCheat);
    if (inputTipo == Input::QUITAR) return Input::QUITAR;
    if (inputTipo == Input::CHEAT) return Input::CHEAT;
    value = strToRespuesta(input);
    if (value == '0') return Input::BAD;
    return Input::OK;
}

std::string setearCondicion(Resultados condicion) {
    std::string str;
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

void mostrarSplashScreen(int offsetX, int offsetY) {
    std::string str;
    str = R"(
 ___         _   _   _              _                  
(  _ \      ( )_( )_(_ )           ( )    _            
| (_) )  _ _|  _)  _)| |   __   ___| |__ (_)_ _    ___ 
|  _ ( / _  ) | | |  | | / __ \  __)  _  \ |  _ \/  __)
| (_) ) (_| | |_| |_ | |(  ___/__  \ | | | | (_) )__  \
(____/ \__ _)\__)\__)___)\____)____/_) (_)_)  __/(____/
                                           | |         
                                           (_)         

                
        )";
    system("cls");
    rlutil::locate(POSICION_MATRIX_X + offsetX - 18, POSICION_MATRIX_Y + offsetY + 8);
    mostrarTextoAnimado("Un proyecto para Laboratorio 2 - Rodriguez Ivan (2021)", Duracion::LENTO);
    Sleep(1100);
    system("cls");
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    std::cout << str;
    std::cout << "Presione cualquier tecla para continuar...";
    system("pause>nul");
}
