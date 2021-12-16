#pragma once

enum {
	ARRIBA,
	ABAJO,
	IZQUIERDA,
	DERECHA
};

enum class OpcionNavegacion {
	CONTINUAR,
	MENU
};

enum class OpcionMenuPausa {
	VOLVER,
	CONSOLA,
	SALIR
};

enum class OpcionMenuComienzo {
	NONE,
	SI,
	NO,
	SALIR
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

//Varios de los enums estan deprecados
enum class Input {
	NOCMD, 
	CHEAT,
	BAD,
	OK,
	QUITAR
};

enum class FrecuenciaSnd {
	ALTA,
	MEDIA,
	BAJA
};

enum class DuracionAnim {
	INSTANTANEO,
	RAPIDO,
	NORMAL,
	LENTO
};

enum class Resultados {
	VICTORIA, DERROTA, SIN_TERMINAR, TRAMPOSO
};