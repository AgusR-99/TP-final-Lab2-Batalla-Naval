#include "SharedFuncs.h"

int validarRespuesta(char value) {
    if (value != 'y' and value != 'Y' and value != 'n' and value != 'N') {
        Beep(200, 250);
        return -1;
    }
    else if (value == 'y' or value == 'Y') return 1;
    else return 0;
}