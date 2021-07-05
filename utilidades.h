#ifndef UTILIDADES_H_INCLUDED
#define UTILIDADES_H_INCLUDED

void recuadro(short iniX, short iniY, short ancho, short alto, short colorLinea=WHITE, short colorFondo=BLACK){
    setlocale(LC_ALL, "C");
    int i, j;
    for(i=iniX; i<=iniX+ancho; i++){
        for(j=iniY; j<=iniY+alto; j++){
            locate(i, j);
            setColor(colorLinea);
            setBackgroundColor(colorFondo);
            //Arriba izquierda
            if(i==iniX && j==iniY){
                cout << (char) 201;
            }
            //Arriba derecha
            else if(i==iniX+ancho && j==iniY){
                cout << (char) 187;
            }
            //Abajo izquierda
            else if(i==iniX && j==iniY+alto){
                cout << (char) 200;
            }
            //Abajo derecha
            else if(i==iniX+ancho && j==iniY+alto){
                cout << (char) 188;
            }
            //Lineas arriba y abajo
            else if(j==iniY || j==iniY+alto){
                cout << (char) 205;
            }
            //Lineas izquierda y derecha
            else if(i==iniX || i==iniX+ancho){
                cout << (char) 186;
            }
            //Dentro del recuadro
            else{
                cout << " ";
            }
        }
    }
    setlocale(LC_ALL, "spanish");
}

void separadorH(short iniX, short iniY, short ancho, short colorLinea=WHITE, short colorFondo=BLACK){
    setlocale(LC_ALL, "C");
    int i;
    locate(iniX,iniY);
    cout<<(char)204;
    for(i=1; i<ancho; i++){
        cout<<(char)205;
    }
    cout<<(char)185;
    setlocale(LC_ALL, "spanish");
}

void separadorV(short iniX, short iniY, short alto, short colorLinea=WHITE, short colorFondo=BLACK){
    setlocale(LC_ALL, "C");
    int i;
    locate(iniX,iniY);
    cout<<(char)203;
    for(i=1; i<alto; i++){
        locate(iniX,iniY+i);
        cout<<(char)186;
    }
    locate(iniX,iniY+alto);
    cout<<(char)202;
    setlocale(LC_ALL, "spanish");
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

#endif // UTILIDADES_H_INCLUDED
