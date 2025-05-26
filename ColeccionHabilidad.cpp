#include "ColeccionHabilidad.h"
#include <thread>
#include <chrono>
#include <algorithm>
#include <iostream>

using namespace std;

vector<CHabilidad*> CColeccionHabilidad::getHabilidades() {
    return habilidades;
}

void CColeccionHabilidad::crearHabilidad() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Reducido para mejor rendimiento
    CHabilidad* habilidad = new CHabilidad();
    cout << "Habilidad creada en la posici�n: (" << habilidad->getFila() << ", " << habilidad->getColumna() << ")" << endl;
    habilidades.push_back(habilidad);
}

void CColeccionHabilidad::revelarHabilidadEnPosicion(int fila, int columna) {
    cout << "Intentando revelar habilidad en posici�n: (" << fila << ", " << columna << ")" << endl;

    bool habilidadEncontrada = false;
    for (auto habilidad : habilidades) {
        // Usar el m�todo estaEnPosicion para verificar la coincidencia exacta
        if (habilidad->estaEnPosicion(fila, columna)) {
            cout << "Habilidad encontrada y revelada en posici�n: (" << fila << ", " << columna << ")" << endl;
            habilidad->mostrarHabilidad();
            habilidadEncontrada = true;
            break; // Solo revelar una habilidad por posici�n
        }
    }

    if (!habilidadEncontrada) {
        cout << "No se encontr� habilidad en la posici�n: (" << fila << ", " << columna << ")" << endl;
    }
}

void CColeccionHabilidad::limpiarHabilidadesExpiradas() {
    auto it = std::remove_if(habilidades.begin(), habilidades.end(),
        [](CHabilidad* habilidad) {
            if (habilidad->debeDesaparecer()) {
                delete habilidad;
                return true;
            }
            return false;
        });

    habilidades.erase(it, habilidades.end());
}

void CColeccionHabilidad::dibujar(Graphics^ g, Bitmap^ bmpHabilidad, const CanchaArray& cancha) {
    // Limpiar habilidades expiradas antes de dibujar
    limpiarHabilidadesExpiradas();

    for (int i = 0; i < habilidades.size(); i++) {
        habilidades.at(i)->dibujar(g, bmpHabilidad, cancha);
        habilidades.at(i)->animar();
    }
}