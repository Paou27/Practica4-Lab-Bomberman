#include "Juego.h"

using namespace Bomberman;

void main() {
	srand(static_cast<unsigned>(time(nullptr)));  // Semilla �nica
	Application::EnableVisualStyles();
	Application::Run(gcnew Juego());
}