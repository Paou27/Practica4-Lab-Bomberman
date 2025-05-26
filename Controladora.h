#pragma once
#include "Cancha.h"
#include "Jugador.h"
#include "ColeccionBomba.h"
#include "ColeccionHabilidad.h"
#include "ColeccionEnemigo.h"

class CControladora {
private:
	CCancha* cancha;
	CJugador* jugador;
	CColeccionBomba* bombas;
	CColeccionHabilidad* habilidades;
	CColeccionEnemigo* enemigos;
	int nivel;

public:
	CControladora();
	~CControladora() {};

	int getNivel();
	void inicializar();
	void Dibujar();
	void CControladora::dibujarCancha(Graphics^ g, Bitmap^ bmpPiso, Bitmap^ bmpIrrompible, Bitmap^ bmpRrompible, Bitmap^ bmpHabilidad);
	void dibujarJugador(Graphics^ g, Bitmap^ bmpJugador);
	void adicionarBomba();
	void moverJugador(Graphics^ g, Bitmap^ bmpJugador, Bitmap^ bmpBomba, Bitmap^ bmpExplosion, Bitmap^ bmpEnemigo);
	CJugador* getJugador();
	void crearHabilidades();
	void crearEnemigos();
	CColeccionHabilidad* getColeccionHabilidades();
	CColeccionEnemigo* getColeccionEnemigos();
};
