#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <cwchar>
using namespace std;
#include "Gamemode 1v1/rlutil.h"
using namespace rlutil;
#include "Gamemode 1v1/FuncsMulti.h"

void desplazarAbajo(int& x, int& y, int& menu_item);
void desplazarArriba(int& x, int& y, int& menu_item);
void desplazarTop(int& x, int& y, int& menu_item, int qItem);
void desplazarBottom(int& x, int& y, int& menu_item, int qItem, int bottom);
void color(int);
int main() {
    setConsoleTitle("Batalla naval");
    bool musica = false;
    int set[] = { 7,7,7 };
    srand((unsigned)time(0));
    setlocale(LC_ALL, "spanish");
    setColor(WHITE);
    setBackgroundColor(BLACK);
    saveDefaultColor();
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0; // Ancho de cada caracter
    cfi.dwFontSize.Y = 24; // Altura
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Consolas"); // Elegir fuente
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    while (true) {
        if (musica == false) {
            PlaySound(TEXT("music/menu.wav"), NULL, SND_ASYNC | SND_LOOP);
            musica = true;
        }
        AjustarVentana(40,20);
        resetColor();
        system("cls");
        bool running = true;
        int menu_item = 0, x = 11, y = 2;
        int qItem = 2;
        int bottom = 4;
        int top = y;
        hidecursor();
        locate(8, 3);
        mostrarTextoAnimado("BIENVENIDO A LA BATALLA NAVAL", Duracion::LENTO, Frecuencia::BAJA);
        while (running == true) {
            set[0] = 15;
            set[1] = 15;
            set[2] = 15;
            if (menu_item == 0) set[0] = 12;
            if (menu_item == 1) set[1] = 12;
            if (menu_item == 2) set[2] = 12;
            gotoxy(x + 8, 9);
            color(set[0]);
            cout << "Jugar";
            gotoxy(x + 5, 10);
            color(set[1]);
            cout << "Leaderboard";
            gotoxy(x + 2, 11);
            color(set[2]);
            cout << "Salir del programa";

            setColor(LIGHTBLUE);
            locate(x - 1, 18);
            cout << "[Enter]";
            resetColor();
            cout << " - Elegir opcion";

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
            if (GetAsyncKeyState(VK_ESCAPE)) return 0;
            if (GetAsyncKeyState(VK_RETURN)) {
                Beep(2000, 50);
                switch (menu_item) {

                case 0: {
                    iniciarJuegoMulti();
                    musica = false;
                    running = false;
                    break;
                }

                case 1: {
                    mostrarInterfazLeaderboard();
                    running = false;
                    break;
                }

                case 2: {
                    resetColor();
                    return 0;
                    break;
                }

                }
            }

        }
    }
   
}


void color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void desplazarAbajo(int& x, int& y, int& menu_item) {
    y++;
    Beep(1000, 50);
    menu_item++;
}

void desplazarArriba(int& x, int& y, int& menu_item) {
    y--;
    Beep(1000, 50);
    menu_item--;
}

void desplazarTop(int& x, int& y, int& menu_item, int top) {
    y = top;
    Beep(1000, 50);
    menu_item = 0;
}

void desplazarBottom(int& x, int& y, int& menu_item, int qItem, int bottom){
    y = bottom;
    Beep(1000, 50);
    menu_item = qItem;
}
