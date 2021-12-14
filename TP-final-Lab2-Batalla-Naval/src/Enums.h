#pragma once

enum {
	ARRIBA,
	ABAJO,
	IZQUIERDA,
	DERECHA
};

enum class Error {
	ORIENTACION,
	FUERA,
	COLISION,
	OK,
};

enum class Estado {
	ESPERA,
	HUNDIDA,
	REPETIDO,
	FUERA,
	FALLO,
	GOLPE,
	DEBUG,
	DEBUGOFF,
	INVALIDO
};

enum class EstadoAtaque {
	FUERA,
	REPETIDO,
	GOLPE,
	FALLO,
	HUNDIDO,
	OK
};

enum class TipoCheat {
	GANAR,
	PERDER,
	REVELAR,
	NONE
};

enum class Input {
	NOCMD,
	CHEAT,
	QUITAR,
	COORD,
	BAD,
	OK
};

enum class Frecuencia {
	ALTA,
	MEDIA,
	BAJA
};

enum class Duracion {
	INSTANTANEO,
	RAPIDO,
	NORMAL,
	LENTO
};

enum class Resultados {
	VICTORIA, DERROTA, SIN_TERMINAR, TRAMPOSO
};