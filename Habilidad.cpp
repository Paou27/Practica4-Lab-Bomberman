#include "Habilidad.h"

CHabilidad::CHabilidad() {
    ubicado = false;
    estado = EEstadoHabilidad::Oculta;
    tiempoVisible = 0;

    // Buscar una posici�n aleatoria v�lida desde el constructor
    do {
        i = rand() % (FILAS - 2) + 1;
        j = rand() % (COLUMNAS - 2) + 1;
    } while (false); // Se validar� en el momento de ubicar

    indiceX = 0;
    indiceY = 0;
    tipoHabilidad = (rand() % 5) + 1;
}

CHabilidad::~CHabilidad() {}

void CHabilidad::mostrarHabilidad() {
    if (estado == EEstadoHabilidad::Oculta) {
        estado = EEstadoHabilidad::Visible;
        tiempoVisible = clock(); // Iniciar contador de tiempo
    }
}

bool CHabilidad::debeDesaparecer() {
    if (estado == EEstadoHabilidad::Visible) {
        double tiempoTranscurrido = double(clock() - tiempoVisible) / CLOCKS_PER_SEC;
        if (tiempoTranscurrido >= DURACION_SEGUNDOS) {
            estado = EEstadoHabilidad::Desaparecida;
            return true;
        }
    }
    return estado == EEstadoHabilidad::Desaparecida;
}

EEstadoHabilidad CHabilidad::getEstado() {
    return estado;
}

void CHabilidad::dibujar(Graphics^ g, Bitmap^ bmpHabilidad, const CanchaArray& cancha) {
    // Solo dibujar si la habilidad est� visible
    if (estado != EEstadoHabilidad::Visible) {
        return;
    }

    // Verificar si debe desaparecer
    if (debeDesaparecer()) {
        return;
    }

    Rectangle rectangulo = Rectangle(indiceX * ANCHOIMAGEN, indiceY * ALTOIMAGEN, ANCHOIMAGEN, ALTOIMAGEN);

    // Ubicar la habilidad en un bloque rompible si a�n no est� ubicada
    // IMPORTANTE: Una vez ubicada, no cambiar m�s las coordenadas
    if (!ubicado) {
        int intentos = 0;
        int tempI = i, tempJ = j;

        // Buscar una posici�n v�lida sin modificar las coordenadas originales hasta encontrar una v�lida
        while (intentos < (FILAS * COLUMNAS) && !ubicado) {
            if (cancha[tempI][tempJ]->getTipo() == EElementos::rrompible) {
                // Encontramos una posici�n v�lida, actualizar las coordenadas definitivas
                i = tempI;
                j = tempJ;
                ubicado = true;
            }
            else {
                tempJ++;
                if (tempJ >= COLUMNAS - 1) {
                    tempJ = 1;
                    tempI++;
                    if (tempI >= FILAS - 1) {
                        tempI = 1;
                    }
                }
                intentos++;
            }
        }

        // Si no se encontr� posici�n v�lida, marcar como ubicado para evitar bucle infinito
        if (!ubicado) {
            ubicado = true;
        }
    }

    // Solo dibujar si est� ubicado y en una posici�n v�lida
    if (ubicado && i >= 0 && i < FILAS && j >= 0 && j < COLUMNAS) {
        Rectangle zoom = Rectangle(j * ANCHOIMAGEN, i * ALTOIMAGEN, ANCHOIMAGEN, ALTOIMAGEN);
        g->DrawImage(bmpHabilidad, zoom, rectangulo, GraphicsUnit::Pixel);
    }
}

void CHabilidad::animar() {
    // Solo animar si est� visible
    if (estado != EEstadoHabilidad::Visible) {
        return;
    }

    switch (tipoHabilidad) {
    case 1: // Bomba Adicional
        indiceX = 0;
        if ((indiceY >= 0) && (indiceY < 1)) {
            indiceY++;
        }
        else {
            indiceY = 0;
        }
        break;
    case 2: // Mover Bomba
        indiceX = 4;
        if ((indiceY >= 0) && (indiceY < 1)) {
            indiceY++;
        }
        else {
            indiceY = 0;
        }
        break;
    case 3: // Calavera
        indiceX = 5;
        if ((indiceY >= 0) && (indiceY < 1)) {
            indiceY++;
        }
        else {
            indiceY = 0;
        }
        break;
    case 4: // Patines
        indiceX = 8;
        if ((indiceY >= 0) && (indiceY < 1)) {
            indiceY++;
        }
        else {
            indiceY = 0;
        }
        break;
    case 5: // Adicionar Vida
        indiceX = 9;
        if ((indiceY >= 0) && (indiceY < 1)) {
            indiceY++;
        }
        else {
            indiceY = 0;
        }
        break;
    }
}