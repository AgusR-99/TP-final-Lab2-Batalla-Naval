#pragma once
#include <Windows.h>
//Se valida si la respuesta esperada es la correcta "(Y/N)"
int validarRespuesta(char value);

void desplazarAbajo(int& x, int& y, int& menu_item);
void desplazarArriba(int& x, int& y, int& menu_item);
void desplazarTop(int& x, int& y, int& menu_item, int top);
void desplazarBottom(int& x, int& y, int& menu_item, int qItem, int bottom);