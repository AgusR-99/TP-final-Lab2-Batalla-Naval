#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <string>

namespace consola {

    DWORD WINAPI CheckEscape(LPVOID lpParam) {
        while (GetAsyncKeyState(VK_ESCAPE) == 0) {
            Sleep(10);
        }
        exit(0);
    }

    void manejarConsola() {
        std::string valor;
        std::vector<std::string> lista;
        //Crear hilo para el handling de la tecla ESC
        CreateThread(NULL, 0, CheckEscape, NULL, 0, NULL);

        //Loop infinito
        while (true) {
            std::cin >> valor;
            lista.push_back(valor);
        }
    }
}
