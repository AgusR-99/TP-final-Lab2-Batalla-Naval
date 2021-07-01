# TP-final-Lab2-Batalla-Naval
![image](https://user-images.githubusercontent.com/76019584/122438385-0b228d80-cf71-11eb-8807-99e632f2cb08.png)

Juego de batalla naval, hecho en C++, para la materia Laboratorio 2.

![image](https://user-images.githubusercontent.com/76019584/122438715-618fcc00-cf71-11eb-92dd-a9d271bcc89a.png)

Trello: https://trello.com/b/aSWu0TsL/batalla-naval-lab2

### Integrantes de la cátedra
- Kloster, Daniel - Profesor
- Wener, Maximiliano - Ayudante

### Integrantes del grupo
- María Julia Archieri
- Rodriguez Ivan Agustin
- Manuel Granada

### Descripcion
1er modo de juego en contra de la computadora: tanto el jugador como el BOT colocan naves en un tablero 10x10. El objetivo es destruir las naves del tablero enemigo utilizando coordenadas (X,Y).
2do modo de juego (WIP): En una matriz que tiene escondidas varias flotas, hay que deducir donde están de acuerdo a ciertas pistas. Se recorre la matriz con el cursor y vamos completando los elementos con lo que creemos que va en ese lugar.

### Clases a desarrollar
- **Clase Nave:** Esta clase corresponde a las propiedades de una nave (Salud, tamaño, orientacion y id).
- **Clase Elemento:** Esta clase corresponde a una unidad del gráfico correspondiente a la matriz con sus flotas. Tendrá propiedades como x.y de posición, tipo de elemento (agua, submarino, cuerpo de flota, cola de flota, etc.) para seleccionarlo cuando resolvemos el elemento en de esa posición.
- **Clase Matriz:**	Es la matriz de elementos que se usará para la resolución del juego. Tendrá propiedades como el ancho y el alto de la matriz, el dibujo de la misma. Métodos de generación de juegos nuevos, supervisión del desarrollo y comprobación del éxito de la resolución.
- **Clase Jugador:** Esta clase guardará el nombre del jugador, fecha y puntaje obtenido deducido por el tiempo de resolución.

### Una representación aproximada a lo que se quiere llegar:
![image](https://user-images.githubusercontent.com/76019584/122438123-c5fe5b80-cf70-11eb-9628-55e37d22a06d.png)  
![image](https://user-images.githubusercontent.com/76019584/122438137-c991e280-cf70-11eb-88d2-cbb312b8cfe2.png)
![image](https://user-images.githubusercontent.com/76019584/122438144-cb5ba600-cf70-11eb-8c9b-feea066d7657.png)
