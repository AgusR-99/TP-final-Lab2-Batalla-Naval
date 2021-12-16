#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <Windows.h>
std::stringstream buffer;
#include "UI.h"
int setFreq(FrecuenciaSnd value) {
    switch (value) {
    case FrecuenciaSnd::ALTA: return 2000;
    case FrecuenciaSnd::MEDIA: return 750;
    case FrecuenciaSnd::BAJA: return 500;
    }
}
int setDuration(DuracionAnim value) {
    switch (value) {
    case DuracionAnim::INSTANTANEO: return 0;
    case DuracionAnim::RAPIDO: return 5;
    case DuracionAnim::NORMAL: return 15;
    case DuracionAnim::LENTO: return 30;
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

OpcionMenuPausa mostrarInterfazPausa(int offsetX, int offsetY, TipoCheat& cmdCheat) {
    int set[] = { 7,7,7 };
    int menu_item = 0, x = 11, y = 2;
    int qItem = 2;
    int bottom = 4;
    int top = y;

    //Crear background del menu
    gotoxy(offsetX, offsetY);
    rlutil::squareBorders(19, 7, offsetX, offsetY, 240);

    rlutil::hidecursor();
    gotoxy(offsetX + 7, offsetY + 1);
    rlutil::color(240);
    std::cout << "PAUSA";
    while (true) {
        set[0] = 15;
        set[1] = 15;
        set[2] = 15;
        if (menu_item == 0) set[0] = 12;
        if (menu_item == 1) set[1] = 12;
        if (menu_item == 2) set[2] = 12;
        gotoxy(offsetX + 2, offsetY + 3);
        rlutil::color(set[0]);
        std::cout << "Reanudar batalla";
        gotoxy(offsetX + 4, offsetY + 4);
        rlutil::color(set[1]);
        std::cout << "Abrir consola";
        gotoxy(offsetX + 6, offsetY + 5);
        rlutil::color(set[2]);
        std::cout << "Rendirse";

        system("pause>nul");
        if (GetAsyncKeyState(VK_DOWN) && y != bottom) {
            desplazarAbajo(x, y, menu_item);
            continue;
        }
        else if (GetAsyncKeyState(VK_DOWN) && y == bottom) {
            desplazarTop(x, y, menu_item, top);
            continue;
        }

        if (GetAsyncKeyState(VK_UP) && y != top) {
            desplazarArriba(x, y, menu_item);
            continue;
        }
        else if (GetAsyncKeyState(VK_UP) && y == top) {
            desplazarBottom(x, y, menu_item, qItem, bottom);
            continue;
        }
        if (GetAsyncKeyState(VK_ESCAPE)) return OpcionMenuPausa::VOLVER;
        if (GetAsyncKeyState(VK_RETURN)) {
            Beep(2000, 50);
            switch (menu_item) {

            case 0: {
                return OpcionMenuPausa::VOLVER;
                break;
            }

            case 1: {
                mostrarConsola(cmdCheat);
                return OpcionMenuPausa::CONSOLA;
                break;
            }

            case 2: {
                return OpcionMenuPausa::SALIR;
                break;
            }

            }
        }

    }
}

#include "Consola.h"

void mostrarConsola(TipoCheat& cmdCheat) {
    //Background de consola
    Input input = Input::NOCMD;
    std::string str;
    rlutil::locate(1, 23);
    std::cout << ":q";
    rlutil::setColor(rlutil::LIGHTBLUE);
    std::cout << "<Enter>";
    rlutil::resetColor();
    std::cout << " para salir";
    while(true) {
        if (input == Input::BAD) {
        Beep(250, 200);
        rlutil::locate(1, 25);
        rlutil::color(79);
        printf("\33[2K\r");
        std::cout << "'" << str << "' no es reconocido como un comando valido";
        rlutil::resetColor();
        }
        else if(input == Input::CHEAT) {
            Beep(1000, 200);
            rlutil::locate(1, 25);
            rlutil::color(47);
            printf("\33[2K\r");
            std::cout << "TRUCO ACTIVADO";
            rlutil::resetColor();
        }
        rlutil::locate(1, 24);
        rlutil::color(31);
        for (size_t i = 0; i < 80; i++) {
            std::cout << " ";
        }
        
        input = consola::manejarConsola(cmdCheat, str);
        rlutil::resetColor();
        if (input == Input::QUITAR) return;
    }
}

void setearColorDefault(){
    rlutil::setColor(rlutil::WHITE);
    rlutil::saveDefaultColor();
}

void mostrarInterfazIngreso(int id, char r, int offsetX, int offsetY, bool bInstant) {
    Nave nave;
    Elemento elemento;
    DuracionAnim fastD = DuracionAnim::RAPIDO;
    DuracionAnim normalD = DuracionAnim::NORMAL;
    DuracionAnim slowD = DuracionAnim::LENTO;
    if (bInstant == true) {
        fastD = DuracionAnim::INSTANTANEO;
        normalD = DuracionAnim::INSTANTANEO;
        slowD = DuracionAnim::INSTANTANEO;
    }
    rlutil::locate(POSICION_MATRIX_X + offsetX + 5, POSICION_MATRIX_Y + 7 + offsetY);
    std::cout << ":q";
    rlutil::setColor(rlutil::LIGHTBLUE);
    std::cout << "<Enter>";
    rlutil::resetColor();
    std::cout << " para salir";
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
OpcionMenuComienzo mostrarInterfazComienzoRapido(int offsetX, int offsetY) {
    int set[] = { 7,7,7 };
    int menu_item = 0, x = 11, y = 2;
    int qItem = 2;
    int bottom = 4;
    int top = y;
    gotoxy(offsetX + 2, offsetY);
    mostrarTextoAnimado("¿Colocar naves aleatoriamente?", DuracionAnim::NORMAL, FrecuenciaSnd::MEDIA);
    //Crear background del menu
    rlutil::squareBorders(27, 7, offsetX + 3, offsetY, 240);

    rlutil::hidecursor();
    gotoxy(offsetX + 9, offsetY + 1);
    rlutil::color(240);
    std::cout << "ELIJA UNA OPCION";
    while (true) {
        set[0] = 15;
        set[1] = 15;
        set[2] = 15;
        if (menu_item == 0) set[0] = 12;
        if (menu_item == 1) set[1] = 12;
        if (menu_item == 2) set[2] = 12;
        gotoxy(offsetX + 14, offsetY + 3);
        rlutil::color(set[0]);
        std::cout << "Si";
        gotoxy(offsetX + 14, offsetY + 4);
        rlutil::color(set[1]);
        std::cout << "No";
        gotoxy(offsetX + 4,  offsetY + 5);
        rlutil::color(set[2]);
        std::cout << "Volver al menu principal";

        system("pause>nul");
        if (GetAsyncKeyState(VK_DOWN) && y != bottom) {
            desplazarAbajo(x, y, menu_item);
            continue;
        }
        else if (GetAsyncKeyState(VK_DOWN) && y == bottom) {
            desplazarTop(x, y, menu_item, top);
            continue;
        }

        if (GetAsyncKeyState(VK_UP) && y != top) {
            desplazarArriba(x, y, menu_item);
            continue;
        }
        else if (GetAsyncKeyState(VK_UP) && y == top) {
            desplazarBottom(x, y, menu_item, qItem, bottom);
            continue;
        }
        if (GetAsyncKeyState(VK_ESCAPE)) return OpcionMenuComienzo::SALIR;
        if (GetAsyncKeyState(VK_RETURN)) {
            Beep(2000, 50);
            switch (menu_item) {

            case 0: {
                return OpcionMenuComienzo::SI;
                break;
            }

            case 1: {
                return OpcionMenuComienzo::NO;
                break;
            }

            case 2: {
                return OpcionMenuComienzo::SALIR;
                break;
            }

            }
        }

    }
}
void mostrarLore() {
    system("cls");
    mostrarTextoAnimado(
        "El 18 de noviembre de 1944, después\n"
        "de una preparación artillera que\n"
        "había durado horas, los soviéticos\n"
        "se lanzaron al asalto de la península\n"
        "de Sworbe, que avanzaba en el mar en la\n"
        "extremidad meridional de Oesel. Las\n"
        "tropas alemanas estaban cercadas y era\n"
        "imposible enviar refuerzos. La\n"
        "península estaba condenada, pero era\n"
        "deseable, por lo menos, sacar de allí\n"
        "las tropas y su material más valioso.\n"
        "Para ello era preciso contener el\n"
        "asalto soviético\n"
        "Tras la llegada, su artillería actuó\n"
        "con precisión. Los buques agotaron las\n"
        "municiones luego de 36 h. Ante la\n"
        "cuantía de los daños, los soviéticos\n"
        "deciden destruir los buques alemanes.\n", DuracionAnim::RAPIDO);
    rlutil::showcursor();
    system("pause>nul");
}
void mostrarInterfazTurnos(int turno, int offsetX, int offsetY) {
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    std::cout << "~~~~~~~~~~~~~~~~~TURNO " << turno << "~~~~~~~~~~~~~~~~~";
}
void mostrarInterfazAcciones(Estado estadoJugador, Estado estadoIA, int restantesJugador, int restantesIA, int turno, int offsetX, int offsetY, int xJugador, int yJugador, int xIA, int yIA, int puntuaje, int puntuajeOld, float mult, bool* flagVictoria, bool* flagDerrota) {
    rlutil::locate(POSICION_MATRIX_X + offsetX + 13, POSICION_MATRIX_Y + 8 + offsetY);
    rlutil::setColor(rlutil::LIGHTBLUE);
    std::cout << "<ESC>";
    rlutil::resetColor();
    std::cout << " para pausar";
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    mostrarInterfazNavesRestantes(restantesJugador, restantesIA, offsetX, offsetY);
    mostrarInterfazTurnos(turno, offsetX, offsetY + 1);
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 2 + offsetY);
    rlutil::setColor(rlutil::LIGHTCYAN);
    mostrarTextoAnimado("Jugador: ", DuracionAnim::NORMAL, FrecuenciaSnd::ALTA);
    rlutil::resetColor();
    rlutil::locate(POSICION_MATRIX_X + 9 + offsetX, POSICION_MATRIX_Y + 2 + offsetY);
    mostrarCoordenadas(xJugador, yJugador, FrecuenciaSnd::ALTA);
    mostrarResultadoAccion(estadoJugador, FrecuenciaSnd::ALTA);
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 3 + offsetY);
    rlutil::setColor(rlutil::LIGHTRED);
    Sleep(500);
    mostrarTextoAnimado("IA: ", DuracionAnim::NORMAL, FrecuenciaSnd::BAJA);
    rlutil::resetColor();
    mostrarCoordenadas(xIA, yIA, FrecuenciaSnd::BAJA);
    mostrarResultadoAccion(estadoIA, FrecuenciaSnd::BAJA);
    Sleep(500);
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 4 + offsetY);
    std::cout << "ATAQUE\n";
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 5 + offsetY);
    std::cout << "Coordenadas (X Y) >> ";
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + 6 + offsetY);
    if (restantesIA == 2 and *flagVictoria == false) { 
        *flagVictoria = true;
        rlutil::setColor(rlutil::LIGHTCYAN);
        mostrarTextoAnimado("Victoria inminente!", DuracionAnim::RAPIDO);
        rlutil::resetColor();
    }
    else if (restantesJugador == 2 and *flagDerrota == false) { 
        *flagDerrota = true;
        rlutil::setColor(rlutil::LIGHTRED);
        mostrarTextoAnimado("Derrota inminente!", DuracionAnim::RAPIDO);
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
        std::cout << "Capitan";
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
                mostrarTextoAnimado("Datos borrados", DuracionAnim::NORMAL, FrecuenciaSnd::MEDIA);
                rlutil::resetColor();
                rlutil::locate(1, 13);
                mostrarTextoAnimado("Presione cualquier tecla para continuar", DuracionAnim::NORMAL, FrecuenciaSnd::MEDIA);
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
#define KEY_ENTER 13

OpcionNavegacion navegarEnTablero(int& x, int& y, Matriz tablero, int offsetX, int offsetY){
    int c;
    Elemento** elemento = tablero.getElemento();
    while (true) {
        //Mostrar coordenadas actuales
        rlutil::resetColor();
        gotoxy(29, 15);
        std::cout << x << "-" << y;

        //Colocar cursor sobre el elemento actual
        gotoxy(x * 2 + offsetX, y + offsetY);
        rlutil::setColor(rlutil::YELLOW);
        std::cout << elemento[y][x].getSprite();
        //Reposicionar cursor
        gotoxy(x * 2 + offsetX, y + offsetY);
        //Presionar alguna flecha
        c = _getch();

        //Si se presiona la tecla ESC, se devuelve valor para ir a menu de pausa
        if (c == KEY_ESC) return OpcionNavegacion::MENU;
        //Si se presiona la tecla ENTER, se devuelve valor que confirma las coordenadas
        else if (c == KEY_ENTER) return OpcionNavegacion::CONTINUAR;

        //Si se presionan las flechas y no hay overflow, se acciona sobre coords
        if ((c == KEY_UP or c == KEY_DOWN or c == KEY_LEFT or c == KEY_RIGHT)
            and (x < 10 and x >= 0) and (y < 10 and y >= 0)) {

            //Desmarcar elemento actual
            rlutil::setColor(rlutil::LIGHTRED);
            std::cout << elemento[y][x].getSprite();
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
            if (x > 9) x = 0;
            else if (x < 0) x = 9;
            if (y > 9) y = 0;
            else if (y < 0)y = 9;
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
void mostrarResultadoAccion(Estado estado, FrecuenciaSnd freq) {
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
    mostrarTextoAnimado(buffer.str(), DuracionAnim::NORMAL, freq);
    rlutil::resetColor();
    //Limpieza de buffer
    buffer.str("");
}

void mostrarCoordenadas(int x, int y, FrecuenciaSnd frequency) {
    if (x != -1 && y != -1) buffer << x << "-" << y << " -> ";
    mostrarTextoAnimado(buffer.str(), DuracionAnim::NORMAL, frequency);
    buffer.str("");
}
void mostrarNave(int id, int length, Elemento elemento) {
    for (size_t i = 0; i < length; i++) {
        buffer << elemento.getSprite();
    }
    mostrarTextoAnimado(buffer.str(), DuracionAnim::NORMAL);
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
void mostrarTextoAnimado(std::string texto, DuracionAnim sleepDuration) {
    int x = 0;
    while (texto[x] != '\0') {
        std::cout << texto[x];
        Sleep(setDuration(sleepDuration));
        x++;
    };
}
void mostrarTextoAnimado(std::string texto, DuracionAnim beepDuration, FrecuenciaSnd beepFreq) {
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

Input ingresarDatos(int& x, int& y, char& r, int offsetX, int offsetY, TipoCheat& cmdCheat) {
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
Input ingresarDatos(int& x, int& y, int offsetX, int offsetY, TipoCheat& cmdCheat) {
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

Input ingresarDatos(char& value, int offsetX, int offsetY) {
    std::string input;
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    std::cin >> input;
    if (input == ":q") return Input::QUITAR;
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
    mostrarTextoAnimado("Un proyecto para Laboratorio 2 - Rodriguez Ivan (2021)", DuracionAnim::LENTO);
    Sleep(1100);
    system("cls");
    rlutil::locate(POSICION_MATRIX_X + offsetX, POSICION_MATRIX_Y + offsetY);
    std::cout << str;
    std::cout << "Presione cualquier tecla para continuar...";
    system("pause>nul");
}
