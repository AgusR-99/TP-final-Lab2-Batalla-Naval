#include <iostream>
#include <windows.h>
using namespace std;
#include "rlutil.h"
using namespace rlutil;
#include "Gamemode 1v1/FuncsMulti.h"
#include "Gamemode Singleplayer/FuncsSingle.h"


int main() {
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
        AjustarVentana(40,20);
        resetColor();
        system("cls");
        bool running = true;
        int menu_item = 0, x = 4, y = 2;
        int bottom = x;
        int top = y;
        int qItem = 2;
        hidecursor();
        gotoxy(x, 0);
        mostrarTextoAnimado("BIENVENIDO A LA BATALLA NAVAL", 50, 400);
        gotoxy(x - 2, 2);
        cout << "->";
        while (running == true) {

            gotoxy(x, 2);
            cout << "Jugar vs IA";
            gotoxy(x, 3);
            cout << "Jugar vs Enigma";
            gotoxy(x, 4);
            cout << "Salir del programa";

            system("pause>nul");
            if (GetAsyncKeyState(VK_DOWN) && y != bottom) {
                gotoxy(x - 2, y);
                cout << "  ";
                y++;
                gotoxy(x - 2, y);
                cout << "->";
                Beep(1000, 50);
                menu_item++;
                continue;
            }
            else if (GetAsyncKeyState(VK_DOWN) && y == bottom) {
                gotoxy(x - 2, y);
                cout << "  ";
                y = top;
                gotoxy(x - 2, y);
                cout << "->";
                Beep(1000, 50);
                menu_item = 0;
                continue;
            }

            if (GetAsyncKeyState(VK_UP) && y != top) {
                gotoxy(x - 2, y);
                cout << "  ";
                y--;
                gotoxy(x - 2, y);
                cout << "->";
                Beep(1000, 50);
                menu_item--;
                continue;
            }
            else if (GetAsyncKeyState(VK_UP) && y == top) {
                gotoxy(x - 2, y);
                cout << "  ";
                y = bottom;
                gotoxy(x - 2, y);
                cout << "->";
                Beep(1000, 50);
                menu_item = qItem;
                continue;
            }
            if (GetAsyncKeyState(VK_ESCAPE)) return 0;
            if (GetAsyncKeyState(VK_RETURN)) {
                Beep(2000, 50);
                switch (menu_item) {

                case 0: {
                    iniciarJuegoMulti();
                    running = false;
                    break;
                }

                case 1: {
                    iniciarJuegoSingle();
                    running = false;
                    break;
                }

                case 2: {
                    return 0;
                    break;
                }

                }
            }

        }
    }
}
