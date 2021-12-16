#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <string>

namespace consola {
    Input manejarConsola(TipoCheat& cmdCheat, std::string& foo) {
        std::string str;
        rlutil::locate(1, 24);
        std::cin >> str;
        foo = str;
        return leerListaDeComandos(str, cmdCheat);
    }
}
