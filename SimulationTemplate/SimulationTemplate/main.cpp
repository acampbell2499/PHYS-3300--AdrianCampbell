
/*
Este es la plantilla que usaremos para todos los proyectos de simulaciones físicas.
Esta es una plantilla común para crear juegos simples en C++ usando SDL.
Este template actualizado tiene la lógica del poolEvent, teclado.
*/

/*
	PARA ASEGURARSE DE QUE EL TEMPLATE ESTÁ FUNCIONANDO, AL CORRER ESTO EN UN PROYECTO LE DEBE MOSTRAR UNA VENTANA
	CON EL ROBOT EN MEDIO Y EL FONDO ESPACIAL.
*/

#include "Simulation.h"

int main(int argc, char* args[])
{
	const float FPS = 60;
	const float frameDelay = 1000 / FPS;

	Uint32 frameStart;
	Uint32 frameEnd;
	float frameTime;

	Simulation* simulation = nullptr;
	simulation = new Simulation();

	// Puedes cambiar el título y las dimensiones de la pantalla.
	simulation->init("LostGaijin Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	/*
		Este es el ciclo donde todo ocurre. Esto es lo que llamamos un "frame".
	*/
	while (simulation->running()) {

		// Medimos los ticks (tiempo) al inicio del frame.
		frameStart = SDL_GetTicks();

		/*
			Leemos entradas por teclado, modificamos la posición de los objetos si es necesario
			y dibujamos cada objeto en su nueva posición.
		*/
		simulation->handleEvents();
		simulation->update();
		simulation->render();

		// Medios los ticks (tiempo) al finalizar la simulación. 
		frameEnd = SDL_GetTicks();

		/*
			Calculamos el tiempo que dura el frame haciendo Tiempo final - Tiempo inicial.
			Este tiempo lo usamos para hacer los cálculos en el engine.
		*/
		frameTime = frameEnd - frameStart;

		// Esto nos limita el FPS al número que hayamos definido anteriormente.
		if (frameTime < frameDelay)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	simulation->clean();

	return 0;
}