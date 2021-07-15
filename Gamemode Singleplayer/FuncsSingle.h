#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

const char* rutaSingle = "Gamemode Singleplayer/juegos.dat";

#define CHARPUNTO "*"
#define CHARCUADROVERTICAL "|"
#define CHARCUADROHORIZONTAL "-"

#define ESCAPE 27
#define ABAJO 80
#define ARRIBA 72
#define DERECHA 77
#define IZQUIERDA 75
#define ENTER 13

#define ALTOMATRIZ 10
#define ANCHOMATRIZ 10
#define ESPACIOCOLUMNAS 2

#define TITULOTABLEROCOLUMNAS "ABCDEFGHIJ"
#define TITULOTABLEROFILAS "ABCDEFGHIJ"

#define xMinTablero 4 //Posicion x0 mínima para el tablero
#define yMinTablero 3 //Posicion x0 mínima para el tablero

#define xTableroJ 6 //Posicion x0,y0 del tablero Jugadas
#define yTableroJ 5
#define xTableroO 52  //Posicion x0,y0 del tablero Objetivo
#define yTableroO 5
#define xTotFlotas 31  //Posicion x0,y0 del tablero Objetivo
#define yTotFlotas 5
#define xMenu 3  //Posicion x0,y0 del tablero Objetivo
#define yMenu 3
#define xAyuda 2  //Posicion x0,y0 del tablero Objetivo
#define yAyuda 3

struct coordPto {
    int x;   // x coordinate
    int y;   // y coordinate
};

int anchoMonitor() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;  // Ancho del monitor
}


int altoMonitor() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;    // Alto del monitor
}

class TJuego {
private:
    int acorazados = 0;
    int cruceros = 0;
    int destructores = 0;
    int submarinos = 0;
public:
    // Matriz Objetivo con las jugadas a donde se quiere llegar
    char MO[10][10];
    // Matriz Jugadas donde se guardan las jugadas del jugador (inicialmente tiene algunas pistas)
    char MJ[10][10];
    int getCruceros() { return cruceros; }
    void setCruceros(const int n) { cruceros = n; }
    int getAcorazados() { return acorazados; }
    void setAcorazados(const int n) { acorazados = n; }

    int getDestructores() { return destructores; }
    void setDestructores(const int n) { destructores = n; }
    int getSubmarinos() { return submarinos; }
    void setSubmarinos(const int n) { submarinos = n; }
    //void setTotFilas(const char *t){strcpy(totFilas, t);}
    void setMO(char M[10][10]) {
        int x, y;
        for (y = 0; y < ALTOMATRIZ; y++)
            for (x = 0; x < ANCHOMATRIZ; x++) {
                MO[x][y] = M[x][y];
            }
    }
    void setMJ(char M[10][10]) {
        int x, y;
        for (y = 0; y < ALTOMATRIZ; y++)
            for (x = 0; x < ANCHOMATRIZ; x++) {
                MJ[x][y] = M[x][y];
            }
    }
    bool grabarEnDisco() {
        FILE* p;
        p = fopen(rutaSingle, "ab");
        //p=fopen(ARCHIVO_AVISTAJES,"ab");
        if (p == NULL) return false;
        bool escribio = fwrite(this, sizeof * this, 1, p);
        fclose(p);
        return escribio;
    }
    bool modificarEnDisco(int pos) {
        FILE* p;
        p = fopen(rutaSingle, "rb+");
        //          p=fopen(rutaSingle,"wb");
        if (p == NULL) return false;
        fseek(p, (sizeof * this) * pos, 0);
        bool escribio = fwrite(this, sizeof * this, 1, p);
        fclose(p);
        return escribio;
    }
    bool leerDeDisco(int pos) {
        FILE* p;
        p = fopen(rutaSingle, "rb");
        if (p == NULL) return false;
        fseek(p, pos * sizeof * this, 0);
        bool leyo = fread(this, sizeof * this, 1, p);
        fclose(p);
        return leyo;
    }
    int getTotJuegos() {
        long file_size;
        int n = 0;
        FILE* p;
        p = fopen(rutaSingle, "rb");
        if (p == NULL) return -1;

        // Me posiciono al final del archivo para obtener la longitud del archivo con ftell
        fseek(p, 0, SEEK_END);
        file_size = ftell(p);
        if (file_size == -1) {
            return -2;
        }
        // Divido la longitud del archivo por el tamaño del registro y así obtengo la cantidad de registros
        n = file_size / (sizeof * this);
        fclose(p);
        return n;
    }
    TJuego() {
    }
};

class TJugadas {
private:
    int aciertos = 0;
    char totFilas[ALTOMATRIZ + 1] = "0000000000";
    char totColumnas[ANCHOMATRIZ + 1] = "0000000000";
public:
    char M[ALTOMATRIZ][ANCHOMATRIZ];
    const char* getTotFilas() { return totFilas; }
    const char* getTotColumnas() { return totColumnas; }
    void setTotFilas(const char* t) { strcpy(totFilas, t); }
    void setTotColumnas(const char* t) { strcpy(totColumnas, t); }

    int getAciertos() { return aciertos; }
    void inicializar() {
        int i, j;
        // inicializo matriz
        for (i = 0; i < ALTOMATRIZ; i++) for (j = 0; j < ANCHOMATRIZ; j++) M[i][j] = ' ';
    }
    // Calculo los totales del tablero o matriz Objetivo
    void calculoTotalesTableroObjetivo(TJuego J) {
        int i, j;
        // calculo totales filas del tablero Objetivo
        for (i = 0; i < ALTOMATRIZ; i++)
            for (j = 0; j < ANCHOMATRIZ; j++) {
                // si no es agua incremento
                if (J.MO[i][j] != '~') totColumnas[j]++;
            }
        // calculo totales columnas del tablero Objetivo
        for (i = 0; i < ANCHOMATRIZ; i++)
            for (j = 0; j < ALTOMATRIZ; j++) {
                // si no es agua incremento
                if (J.MO[i][j] != '~') totFilas[i]++;
            }
    }
    void cargar(TJuego J, char MZ[10][10]) {
        int x, y;
        for (y = 0; y < ALTOMATRIZ; y++)
            for (x = 0; x < ANCHOMATRIZ; x++) {
                M[x][y] = MZ[x][y];
            }
        calculoTotalesTableroObjetivo(J);
    }
    void guardar(char val, int x, int y) {
        M[x][y] = val;
    }
    char leer(int x, int y) {
        char val = M[x][y];
        return val;
    }
    bool jugadaValida(char val) {
        if (val == ' ') return true;
        if (val == 'O') return true; // cuerpo de flota
        if (val == '~') return true; // agua
        if (val == '^') return true; // cola de flota sup
        if (val == 'v') return true; // cola de flota inf
        if (val == '<') return true; // cola de flota izq
        if (val == '>') return true; // cola de flota er
        if (val == '@') return true; // submarino
        if (val == '*') return true; // submarino
        return false;
    }
    bool operator==(TJugadas T) {
        int x, y;
        aciertos = 0;
        for (y = 0; y < ALTOMATRIZ; y++)
            for (x = 0; x < ANCHOMATRIZ; x++) {
                if (M[x][y] == T.M[x][y]) aciertos++;
            }
        if (aciertos == 100) return true;
        else return false;
    }
    void inicializarConAgua() {
        int i, j;
        // inicializo matriz
        for (i = 0; i < ALTOMATRIZ; i++) for (j = 0; j < ANCHOMATRIZ; j++) M[i][j] = '~';
    }
    // Constructori
    TJugadas() {
        inicializar(); //matriz M
    }
};

class TCursor {
private:
    // Donde se encuentra ubicado el CampoJuego
    // (x0,y0) es la posición del primer elemento de la matriz, es decir matriz[0,0]
    int x0;
    int y0;
    // Posición del cursor (relativo dentro de la matriz)
    int xCur;
    int yCur;

    char tecla;
public:
    // Ubicación del origen del cursor, luego las posiciones son relativas a esta
    void setOrigenXY(int x, int y) { x0 = x; y0 = y; }
    void setx0(const int x) { x0 = x; }
    void sety0(const int y) { y0 = y; }
    int getxCur() { return xCur; }
    int getyCur() { return yCur; }
    void setxCur(const int x) {
        if (x >= 0 && x < ANCHOMATRIZ) xCur = x;
    }
    void setyCur(const int y) {
        if (y >= 0 && y < ALTOMATRIZ) yCur = y;
    }
    char getTecla() { return tecla; }
    void incxCur(int n) { setxCur(xCur + n); }
    void incyCur(int n) { setyCur(yCur + n); }
    // Pone el cursor en las posición establecida xPos,yPos dentro de la matriz
    void ponerCursor() {
        gotoxytablero(xCur, yCur);
    }
    // Mover cursor x posiciones vertical, y posiciones horizontal
    void moverCursor(int x, int y) {
        incxCur(x);
        incyCur(y);
    }
    // Posiciona dentro de la matriz
    // parametros de posición son relativos dentro de la matriz
    void gotoxytablero(int x, int y) {
        gotoxy(x0 + (x * ESPACIOCOLUMNAS), y0 + y);
    }
    void leerTecla() {
        tecla = _getch();
        if (toupper(tecla) == 'W') tecla = '~';  // agua o water
        if (toupper(tecla) == 'S') tecla = '@';  // submarino
        if (toupper(tecla) == 'O') tecla = 'O';  // agua o water
        // flota con teclado numerico
        if (tecla == '9') tecla = '@';
        if (tecla == '8') tecla = '^';
        if (tecla == '4') tecla = '<';
        if (tecla == '5') tecla = 'O';
        if (tecla == '6') tecla = '>';
        if (tecla == '2') tecla = 'v';
        if (tecla == '0') tecla = '~';
    }
    // Constructor
    TCursor(int x = 1, int y = 1) {
        x0 = x;
        y0 = y;
        xCur = 0;
        yCur = 0;
    }
};

class TTablero {
private:
    // Donde se encuentra ubicado el CampoJuego
    // (x0,y0) es la posición del primer elemento de la matriz, es decir matriz[0,0]
    int x0;
    int y0;
public:
    TCursor cursor;      // cursor del tablero
    TJugadas jugadas;      // matriz jugadas
    int getx0() { return x0; }
    void setx0(const int x) { x0 = x; cursor.setx0(x0); }
    int gety0() { return y0; }
    void sety0(const int y) { y0 = y; cursor.sety0(y0); }
    void mostrarJugadas() {
        int x, y;
        for (y = 0; y < ALTOMATRIZ; y++)
            for (x = 0; x < ANCHOMATRIZ; x++) {
                cursor.gotoxytablero(x, y);
                cout << jugadas.leer(x, y);
            }
    }
    void guardarMostrarJugada(char val) {
        jugadas.guardar(val, cursor.getxCur(), cursor.getyCur());
        cout << jugadas.leer(cursor.getxCur(), cursor.getyCur());
    }
    // Constructor
    TTablero(int x, int y) {
        setx0(x); sety0(y);
        jugadas.inicializar();
    }
    TTablero() {
        setx0(xMinTablero); sety0(yMinTablero);
        jugadas.inicializar();
    }
    // compara las matrices de las jugadas con el objetivo
    // y calcula número de aciertos
    bool operator==(TTablero T) {
        return (jugadas == T.jugadas);
    }
    // cambiar por tomarJugada
    bool leerJugada() {
        cursor.ponerCursor(); cursor.leerTecla();

        // Veo si es tecla de Valor
        if (jugadas.jugadaValida(cursor.getTecla()) == true) {
            guardarMostrarJugada(cursor.getTecla());
            //          moverCursor(1,0); //Avanzo una posición
        }

        switch (toupper(cursor.getTecla())) {
        case DERECHA:
        case 'R':
            cursor.moverCursor(1, 0);
            break;
        case IZQUIERDA:
        case 'L':
            cursor.moverCursor(-1, 0);
            break;
        case ARRIBA:
        case 'U':
            cursor.moverCursor(0, -1);
            break;
        case ABAJO:
        case 'D':
            cursor.moverCursor(0, 1);
            break;
        case ESCAPE:
        case 'E':
            return false;
            break;
        }
        return true;
    }
};

class TVisual {
private:

public:
    void gotoxyTablero(int x0, int y0, int dx, int dy) {
        gotoxy(x0 + (dx * ESPACIOCOLUMNAS), y0 + dy);
    }

    void mostrarJugadas(TTablero T) {
        int x, y;
        for (y = 0; y < ALTOMATRIZ; y++)
            for (x = 0; x < ANCHOMATRIZ; x++) {
                gotoxyTablero(T.getx0(), T.gety0(), x, y);
                cout << T.jugadas.M[x][y];
            }
    }

    void dibujarRecuadro(TTablero T) {
        int x, y;
        for (x = 0; x < ANCHOMATRIZ; x++) { gotoxyTablero(T.getx0(), T.gety0(), x, -1); printf(CHARCUADROHORIZONTAL); } //Linea Horizontal Superior
        for (x = 0; x < ANCHOMATRIZ; x++) { gotoxyTablero(T.getx0(), T.gety0(), x, ALTOMATRIZ); printf(CHARCUADROHORIZONTAL); } //Linea Horizontal Inferior
        for (y = 0; y < ALTOMATRIZ; y++) { gotoxyTablero(T.getx0(), T.gety0(), -1, y); printf(CHARCUADROVERTICAL); } //Linea Vertical Izquierda
        for (y = 0; y < ALTOMATRIZ; y++) { gotoxyTablero(T.getx0(), T.gety0(), ANCHOMATRIZ, y); printf(CHARCUADROVERTICAL); } //Linea Vertical Derecha
    }

    void mostrarTitulos(TTablero T, const char* titCol = TITULOTABLEROCOLUMNAS, const char* titFil = TITULOTABLEROFILAS) {
        int x, y;
        for (x = 0; x < ANCHOMATRIZ; x++) { gotoxyTablero(T.getx0(), T.gety0(), x, -2); cout << titFil[x]; } //Linea Horizontal Superior
        for (y = 0; y < ALTOMATRIZ; y++) { gotoxyTablero(T.getx0(), T.gety0(), -2, y); cout << titCol[y]; } //Linea Vertical Izquierda
    }

    void mostrarTitulosTotales(TTablero T) {
        int x, y;
        const char* totCol = T.jugadas.getTotColumnas();
        const char* totFil = T.jugadas.getTotFilas();
        for (x = 0; x <= ANCHOMATRIZ; x++) { gotoxyTablero(T.getx0(), T.gety0(), x, ALTOMATRIZ + 1); cout << totFil[x]; } //Linea Horizontal Inferior
        for (y = 0; y <= ALTOMATRIZ; y++) { gotoxyTablero(T.getx0(), T.gety0(), ANCHOMATRIZ + 1, y); cout << totCol[y]; } //Linea Vertical Derecha
    }

    void mostrarTablero(TTablero T, bool tot = 1) {
        setBackgroundColor(BLACK);
        setColor(YELLOW);
        dibujarRecuadro(T);
        setColor(GREEN);
        mostrarTitulos(T);
        setColor(LIGHTCYAN);
        if (tot == 1) mostrarTitulosTotales(T);
        mostrarJugadas(T);
    }

    void mostrarCantidadFlotas(int x, int y, TJuego j) {
        setColor(LIGHTBLUE);
        gotoxy(x, y + 0); cout << "   <OO>    ";
        gotoxy(x, y + 1); cout << "Acorazados=" << j.getAcorazados();
        gotoxy(x, y + 3); cout << "   <O>    ";
        gotoxy(x, y + 4); cout << "Cruceros=" << j.getCruceros();
        gotoxy(x, y + 6); cout << "   <>    ";
        gotoxy(x, y + 7); cout << "Destructores=" << j.getDestructores();
        gotoxy(x, y + 9); cout << "   @    ";
        gotoxy(x, y + 10); cout << "Submarinos=" << j.getSubmarinos();
    }

    void cargarCantidadFlotas(int x, int y, TJuego& j) {
        int n;
        gotoxy(x, y + 0); cout << "   <OO>    ";
        gotoxy(x, y + 1); cout << "Acorazados="; cin >> n; j.setAcorazados(n);
        gotoxy(x, y + 3); cout << "   <O>    ";
        gotoxy(x, y + 4); cout << "Cruceros="; cin >> n; j.setCruceros(n);
        gotoxy(x, y + 6); cout << "   <>    ";
        gotoxy(x, y + 7); cout << "Destructores="; cin >> n; j.setDestructores(n);
        gotoxy(x, y + 9); cout << "   @    ";
        gotoxy(x, y + 10); cout << "Submarinos="; cin >> n; j.setSubmarinos(n);
    }

    void mostrarAyuda() {
        iniPantalla();
        int x = xAyuda, y = yAyuda;
        setColor(LIGHTCYAN);
        gotoxy(x, y++); cout << "-------------------------------AYUDA------------------------------------------" << endl;
        gotoxy(x, y++); cout << "TECLAS: ~ (Agua) @ (Submarino) O (cuerpo flota) ^ v < > (Cola flota) * (marca) " << endl;
        gotoxy(x, y++); cout << "TECLAS DE NAVEGACION: Up, Down, Left, Right   -    PARA SALIR: e o Tecla Esc" << endl;
        gotoxy(x, y++); cout << "EQUIVALENTES: w -> ~   s -> @   u ->  Up  d -> Down   l -> Left   r -> Right " << endl;
        gotoxy(x, y++); cout << "NUMERICAS: 9 -> @   8 -> ^   4 -> <   5 -> O   6 -> >   2 -> v   0 -> ~ " << endl;
        gotoxy(x, y++); cout << "------------------------------------------------------------------------------" << endl;
        y++;
        setColor(LIGHTMAGENTA);
        gotoxy(x, y++); cout << "La tabla representa una sección del océano en la que se oculta una flota." << endl;
        gotoxy(x, y++); cout << "En cada caso se indica que barcos componen la flota: " << endl << endl;
        y++;
        gotoxy(x, y++); cout << "       <OO> Crucero	<O> Acorazado   <> Destructor   @ submarino." << endl;
        y++;
        gotoxy(x, y++); cout << "Lo dígitos de la parte derecha inferior de la tabla muestran cuántas" << endl;
        gotoxy(x, y++); cout << "casillas ocupan los barcos en una fila o columna. Para empezar, tienes" << endl;
        gotoxy(x, y++); cout << "situado parte de algunos barcos; utiliza esta información para averiguar" << endl;
        gotoxy(x, y++); cout << "dónde están. Todos los barcos están situados en horizontal o en vertical" << endl;
        gotoxy(x, y++); cout << "y no ocupan casillas adyacentes (ni siquiera en diagonal). " << endl;
        gotoxy(x, y++); cout << "Puede usar la marca temporal * cuando se desconoce el elemento de la casilla. " << endl;
        pausa();
    }

    void mostrarResultado(int aciertos, float tiempo, bool exito) {
        char str[50];
        if (exito == 1) sprintf(str, "Ganaste! Aciertos 100% - Tiempo de resolucion: %f segundos", tiempo);
        else sprintf(str, "Aciertos: %d - Tiempo de resolucion: %f segundos", aciertos, tiempo);
        mostrarMensaje(str);
    }

    void mostrarMensaje(const char* mensaje) {
        setColor(LIGHTMAGENTA);
        gotoxy(1, altoMonitor() - 2);
        cout << mensaje << endl;
        pausa();
    }

    void iniPantalla() {
        const char* titulo = " BATALLA NAVAL ENIGMA ";
        system("cls");
        setColor(LIGHTMAGENTA);
        setBackgroundColor(BLACK);
        int c, f;
        // inicializo matriz
        //gotoxy(0,1); for(c=0;c<anchoMonitor();c++) cout<<'#';
        gotoxy((anchoMonitor() - strlen(titulo) + 6) / 2, 2); cout << "** " << titulo << " **" << endl;
        //gotoxy(0,altoMonitor()-2); for(c=0;c<anchoMonitor();c++) cout<<'#';
    }

    void pausa() {
        gotoxy(0, altoMonitor() - 3); system("pause");
    }

    int solicitarNumJuego(int totJuegos) {
        iniPantalla();
        int numJuego = 0;
        if (totJuegos > 0) {
            char str[50]; sprintf(str, "Ingrese Nro de Juego (1-%d): ", totJuegos);
            gotoxy(xMenu, yMenu); cout << str; cin >> numJuego;
        }
        return numJuego;
    }

    int menu() {
        /*iniPantalla();*/
        /*setColor(YELLOW);
        setBackgroundColor(BLACK);*/

        /*int x = xMenu, y = yMenu;*/
        /*int opc = 1;*/
        /*gotoxy(x, y++); cout << "1.Jugar" << endl;
        gotoxy(x, y++); cout << "2.Jugar (Modo Debug)" << endl;
        gotoxy(x, y++); cout << "3.Ayuda" << endl;
        gotoxy(x, y++); cout << "4.Configuracion" << endl;
        gotoxy(x, y++); cout << "0.Salir" << endl;
        gotoxy(x, y++); cout << "Opcion:"; cin >> opc;*/
        while (true) {
            iniPantalla();
            setColor(YELLOW);
            setBackgroundColor(BLACK);
            bool running = true;
            int menu_item = 1, x = 6, y = 2;
            int bottom = x;
            int top = y;
            int qItem = 5;
            hidecursor();
            gotoxy(x - 2, 2);
            cout << "->";
            while (running == true) {

                gotoxy(x, 2);
                cout << "Jugar";
                gotoxy(x, 3);
                cout << "Jugar (Modo Debug)";
                gotoxy(x, 4);
                cout << "Ayuda";
                gotoxy(x, 5);
                cout << "Configuracion";
                gotoxy(x, 6);
                cout << "Ir al menu principal";

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
                    menu_item = 1;
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
                    showcursor();
                    return menu_item;
                }
            }
        }
        /*return opc;*/
    }

    int menuConfig() {
        iniPantalla();
        setColor(YELLOW);
        setBackgroundColor(BLACK);
        int x = xMenu, y = yMenu;
        int opc = 1;
        gotoxy(x, y++); cout << "1.Alta Juego" << endl;
        gotoxy(x, y++); cout << "2.Modificar Juego" << endl;
        gotoxy(x, y++); cout << "3.Listar Juegos" << endl;
        gotoxy(x, y++); cout << "0.Volver al menu anterior" << endl;
        gotoxy(x, y++); cout << "Opcion:"; cin >> opc;
        return opc;
    }
    // Constructor
    TVisual(int x = 1, int y = 1) {

    }
};

int buscarJuego(TJuego& J) {
    TVisual visual;

    int numJuego = visual.solicitarNumJuego(J.getTotJuegos());

    if (numJuego > 0 and numJuego <= J.getTotJuegos()) {
        // Se busca numJuego-1 porque se los juegos estan contabilizados desde 0
        if (J.leerDeDisco(numJuego - 1) != 1) {
            visual.mostrarMensaje("Error: No se pudo cargar juego o no hay juegos cargados");
            return 0;
        };
        return numJuego;
    }
    else {
        visual.mostrarMensaje("Error: No se pudo cargar juego o no hay juegos cargados");
        return 0;
    }
}

void jugarBN(bool debug = 0) {
    TVisual visual;

    TJuego juego; //Biblioteca de juegos

    // Si no hay juego, salgo
    int numJuego = buscarJuego(juego);
    if (numJuego <= 0) { return; }

    visual.iniPantalla();

    // Tablero objetivo
    TTablero tableroO;
    tableroO.jugadas.cargar(juego, juego.MO);
    // Posición del tablero
    tableroO.setx0(xTableroO);
    tableroO.sety0(yTableroO);
    if (debug == 1) visual.mostrarTablero(tableroO); // se puede mostar en modo debug

    // Creo el Tablero Jugadas y le cargo la matriz/jugadas MJ del objeto juegos
    // Esta matriz inicialmente esta vacia, solo tiene algunas jugadas para empezar
    TTablero tableroJ;
    tableroJ.jugadas.cargar(juego, juego.MJ);
    // Posición del tablero
    tableroJ.setx0(xTableroJ);
    tableroJ.sety0(yTableroJ);
    visual.mostrarTablero(tableroJ);

    visual.mostrarCantidadFlotas(xTotFlotas, yTotFlotas, juego);

    // Guardo tiempo de inicio
    const clock_t iniTime = clock();

    int loop = 1;
    while (loop) {
        loop = tableroJ.leerJugada();
    }

    float tiempoJugada = float(clock() - iniTime) / CLOCKS_PER_SEC;

    // Muestro resultado
    if (tableroJ == tableroO) visual.mostrarResultado(tableroJ.jugadas.getAciertos(), tiempoJugada, 1);
    else visual.mostrarResultado(tableroJ.jugadas.getAciertos(), tiempoJugada, 0);
}

void listarJuegosBN() {
    TVisual visual;

    TJuego juego; //Biblioteca de juegos

    int numJuego = 0, totJuegos = 0;

    totJuegos = juego.getTotJuegos();

    if (totJuegos < 0) {
        visual.mostrarMensaje("Error al leer el archivo de juegos o no hay juegos cargados");
        return;
    }

    for (numJuego = 1; numJuego <= totJuegos; numJuego++) {
        visual.iniPantalla();
        // Muestro tablero

        // Se busca numJuego-1 porque se los juegos estan contabilizados desde 0
        if (juego.leerDeDisco(numJuego - 1) != 1) {
            visual.mostrarMensaje("Error: No se pudo cargar juego");
            return;
        };

        // Tablero objetivo
        TTablero tableroO;
        tableroO.jugadas.cargar(juego, juego.MO);
        // Posición del tablero
        tableroO.setx0(xTableroO);
        tableroO.sety0(yTableroO);
        visual.mostrarTablero(tableroO); // se puede mostar en modo debug

        // Creo el Tablero Jugadas y le cargo la matriz/jugadas MJ del objeto juegos
        // Esta matriz inicialmente esta vacia, solo tiene algunas jugadas para empezar
        TTablero tableroJ;
        tableroJ.jugadas.cargar(juego, juego.MJ);
        // Posición del tablero
        tableroJ.setx0(xTableroJ);
        tableroJ.sety0(yTableroJ);
        visual.mostrarTablero(tableroJ);

        visual.mostrarCantidadFlotas(xTotFlotas, yTotFlotas, juego);

        char str[50]; sprintf(str, "Juego %d de %d", numJuego, totJuegos);
        visual.mostrarMensaje(str);
    };
}

void altaJuegoBN() {
    TVisual visual;

    visual.iniPantalla();

    // Tablero objetivo
    TTablero tableroO;
    // Posición del tablero
    tableroO.setx0(xTableroO);
    tableroO.sety0(yTableroO);
    tableroO.jugadas.inicializarConAgua();
    visual.mostrarTablero(tableroO); // se puede mostar en modo debug

    // Creo el Tablero Jugadas y le cargo la matriz/jugadas MJ del objeto juegos
    // Esta matriz inicialmente esta vacia, solo tiene algunas jugadas para empezar
    TTablero tableroJ;
    // Posición del tablero
    tableroJ.setx0(xTableroJ);
    tableroJ.sety0(yTableroJ);
    visual.mostrarTablero(tableroJ);

    // carga del tablero objetivo
    int loop = 1;
    while (loop) {
        loop = tableroO.leerJugada();
    }

    // cargo tablero con alguna jugada como pistas
    loop = 1;
    while (loop) {
        loop = tableroJ.leerJugada();
    }

    // guardar Juego
    TJuego juego; //Biblioteca de juegos
    // copio los contenidos de los tableros en el objeto juego
    juego.setMO(tableroO.jugadas.M);
    juego.setMJ(tableroJ.jugadas.M);

    // carga cantidades de flotas
    visual.cargarCantidadFlotas(xTotFlotas, yTotFlotas, juego);

    // guardo en disco
    if (juego.grabarEnDisco() == 1) visual.mostrarMensaje("Juego guardado");
    else  visual.mostrarMensaje("Juego descartado");
}

void modifJuegoBN() {
    TVisual visual;

    TJuego juego; //Biblioteca de juegos

    // Si no hay juego, salgo
    int numJuego = buscarJuego(juego);
    if (numJuego == 0) { return; }

    visual.iniPantalla();

    // Tablero objetivo
    TTablero tableroO;
    tableroO.jugadas.cargar(juego, juego.MO);
    // Posición del tablero
    tableroO.setx0(xTableroO);
    tableroO.sety0(yTableroO);
    visual.mostrarTablero(tableroO); // se puede mostar en modo debug

    // Creo el Tablero Jugadas y le cargo la matriz/jugadas MJ del objeto juegos
    // Esta matriz inicialmente esta vacia, solo tiene algunas jugadas para empezar
    TTablero tableroJ;
    tableroJ.jugadas.cargar(juego, juego.MJ);
    // Posición del tablero
    tableroJ.setx0(xTableroJ);
    tableroJ.sety0(yTableroJ);
    visual.mostrarTablero(tableroJ);

    // Modifico tablero Objetivo
    int loop = 1;
    while (loop) {
        loop = tableroO.leerJugada();
    }

    // Modifico tablero Jugada
    loop = 1;
    while (loop) {
        loop = tableroJ.leerJugada();
    }

    // modificacion cantidades de flotas
    visual.cargarCantidadFlotas(xTotFlotas, yTotFlotas, juego);

    // copio los contenidos de los tableros en el objeto juego
    juego.setMO(tableroO.jugadas.M);
    juego.setMJ(tableroJ.jugadas.M);

    // Se usa numJuego-1 porque se los juegos estan contabilizados desde 0
    if (juego.modificarEnDisco(numJuego - 1) != 1) {
        visual.mostrarMensaje("Error: No se pudo modificar juego");
        return;
    };
    visual.mostrarMensaje("Juego modificado");
}

void pantallaAyuda() {
    TVisual visual;
    visual.mostrarAyuda();
}

int menuConfiguracion()
{
    TVisual visual;
    int opc = visual.menuConfig();
    while (opc != 0) {
        switch (opc) {
        case 1: altaJuegoBN(); break;
        case 2: modifJuegoBN(); break;
        case 3: listarJuegosBN(); break;
        }
        opc = visual.menuConfig();
    };
    return 0;
}
const int w = 85;
const int h = 20;

void iniciarJuegoSingle() {
    AjustarVentana(w, h);
    TVisual visual;
    visual.iniPantalla();
    int opc = visual.menu();
    while (opc != 0) {
        switch (opc) {
        case 1: jugarBN(); break;
        case 2: jugarBN(1); break;
        case 3: pantallaAyuda(); break;
        case 4: menuConfiguracion(); break;
        case 5: return; //Workaround de agus
        }
        opc = visual.menu();
    };
    return;
}
