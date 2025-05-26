#pragma once
#include <ctime>
#include <stdlib.h>
#include "Items.h"
#include "Cancha.h"

using namespace System::Drawing;

enum EEstadoHabilidad {
    Oculta = 0,     // Habilidad oculta en bloque rompible
    Visible,        // Habilidad visible despu�s de romper bloque
    Desaparecida    // Habilidad que ya no debe mostrarse
};

class CHabilidad {
    int i;
    int j;
    int indiceX;
    int indiceY;
    bool posicionFinalizada; // Nueva variable para controlar si la posici�n ya est� fija
    int tipoHabilidad;
    bool ubicado;
    EEstadoHabilidad estado;

    // Control de tiempo para desaparici�n
    clock_t tiempoVisible;
    static const int DURACION_SEGUNDOS = 10;

public:
    CHabilidad();
    ~CHabilidad();

    void dibujar(Graphics^ g, Bitmap^ bmpHabilidad, const CanchaArray& cancha);
    void animar();

    void mostrarHabilidad(); // Hacer visible la habilidad
    bool debeDesaparecer();  // Verificar si debe desaparecer
    EEstadoHabilidad getEstado();
    int getFila() { return i; }
    int getColumna() { return j; }
    bool estaPosicionFinalizada() { return posicionFinalizada; }
    void finalizarPosicion() { posicionFinalizada = true; }
    // M�todo para verificar si la habilidad est� en una posici�n espec�fica
    bool estaEnPosicion(int fila, int columna) { return (i == fila && j == columna); }
};