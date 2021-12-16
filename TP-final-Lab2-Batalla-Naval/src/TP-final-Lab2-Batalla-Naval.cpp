#include <iostream>
#include <windows.h>
#include <time.h>
#include <cstdio>
#include <mmsystem.h>8
//#include <cwchar>
#include <sstream>

using namespace std;

#include "rlutil.h"
#include "Enums.h"
#include "UI.h"
#include "FuncsMulti.h"
void desplazarAbajo(int& x, int& y, int& menu_item);
void desplazarArriba(int& x, int& y, int& menu_item);
void desplazarTop(int& x, int& y, int& menu_item, int qItem);
void desplazarBottom(int& x, int& y, int& menu_item, int qItem, int bottom);
int main() {
    rlutil::setConsoleTitle("Batalla naval");
    setearColorDefault();
    bool sndMenu = true;
    int set[] = { 7,7,7,7 };
    srand((unsigned)time(0));
    setlocale(LC_ALL, "spanish");
    rlutil::setColor(rlutil::WHITE);
    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::saveDefaultColor();
    //Esto no andaba en la compu del profe, eliminar?
    //Probar si anda en maquina del profe
    /*CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0; // Ancho de cada caracter
    cfi.dwFontSize.Y = 24; // Altura
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Consolas"); // Elegir fuente
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);*/
    AjustarVentana(55, 20);
    PlaySound(TEXT("music/menu.wav"), NULL, SND_ASYNC | SND_LOOP);
    mostrarSplashScreen(0, 1);
    while (true) {
        if (sndMenu == false) {
            PlaySound(TEXT("music/menu.wav"), NULL, SND_ASYNC | SND_LOOP);
            sndMenu = true;
        }
        AjustarVentana(40, 20);
        system("cls");
        bool running = true;
        int menu_item = 0, x = 11, y = 2;
        int qItem = 2;
        int bottom = 5;
        int top = y;
        rlutil::hidecursor();
        rlutil::locate(9, 3);
        rlutil::resetColor();
        mostrarTextoAnimado("BIENVENIDO A BORDO CAPITAN", DuracionAnim::LENTO, FrecuenciaSnd::BAJA);
        while (running == true) {
            set[0] = 15;
            set[1] = 15;
            set[2] = 15;
            set[3] = 15;
            if (menu_item == 0) set[0] = 12;
            if (menu_item == 1) set[1] = 12;
            if (menu_item == 2) set[2] = 12;
            if (menu_item == 3) set[3] = 12;
            gotoxy(x + 8, 9);
            rlutil::color(set[0]);
            cout << "Jugar";
            gotoxy(x + 5, 10);
            rlutil::color(set[1]);
            cout << "Leaderboard";
            gotoxy(x + 8, 11);
            rlutil::color(set[2]);
            cout << "Lore";
            gotoxy(x + 2, 12);
            rlutil::color(set[3]);
            cout << "Salir del programa";

            rlutil::setColor(rlutil::LIGHTBLUE);
            rlutil::locate(x - 1, 18);
            cout << "[Enter]";
            rlutil::resetColor();
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
                    sndMenu = false;
                    running = false;
                    break;
                }

                case 1: {
                    mostrarInterfazLeaderboard();
                    running = false;
                    break;
                }

                case 2: {
                    mostrarLore();
                    running = false;
                    break;
                }

                case 3: {
                    rlutil::resetColor();
                    return 0;
                    break;
                }

                }
            }

        }
    }

}