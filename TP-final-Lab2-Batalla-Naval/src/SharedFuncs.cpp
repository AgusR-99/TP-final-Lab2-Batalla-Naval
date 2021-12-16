#include "SharedFuncs.h"

int validarRespuesta(char value) {
    if (value != 'y' and value != 'Y' and value != 'n' and value != 'N') {
        Beep(200, 250);
        return -1;
    }
    else if (value == 'y' or value == 'Y') return 1;
    else return 0;
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

void desplazarBottom(int& x, int& y, int& menu_item, int qItem, int bottom) {
    y = bottom;
    Beep(1000, 50);
    menu_item = qItem;
}