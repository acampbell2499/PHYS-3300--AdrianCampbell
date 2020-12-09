
#include "Simulation.h"
#include "TextureManager.h"
#include "GameObject.h"

GameObject* background;
GameObject* robot;
SDL_Event Simulation::event;

Simulation::Simulation()
{}

Simulation::~Simulation()
{}

void Simulation::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL Initialized!" << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)
		{
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}
	else {
		std::cout << "Couldn't initiate SDL..." << std::endl;
		isRunning = false;
	}

	background = new GameObject("assets/blue.png", renderer);
	robot = new GameObject("assets/chibi-robot.png", renderer);
}

void Simulation::handleEvents()
{
	/*
		Debemos agregar cosas como cambios de velocidad o aplicación de fuerzas en esta parte.
	*/
	SDL_PollEvent(&event);

	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_w:
			keyDown[0] = true;
			break;

		case SDLK_a:
			keyDown[1] = true;
			break;

		case SDLK_s:
			keyDown[2] = true;
			break;

		case SDLK_d:
			keyDown[3] = true;
			break;
		}
	}
	else if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case SDLK_w:
			keyDown[0] = false;
			break;

		case SDLK_a:
			keyDown[1] = false;
			break;

		case SDLK_s:
			keyDown[2] = false;
			break;

		case SDLK_d:
			keyDown[3] = false;
			break;
		}
	}

	keyCounter = 0;

	while (keyCounter <= 3) {
		if (keyDown[keyCounter] && !keyAppliedDown[keyCounter]) {
			keyAppliedDown[keyCounter] = true;
			keyAppliedUp[keyCounter] = false;
		}
		else if (!keyDown[keyCounter] && !keyAppliedUp[keyCounter]) {
			keyAppliedUp[keyCounter] = true;
			keyAppliedDown[keyCounter] = false;
		}
		keyCounter++;
	}

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Simulation::update()
{
	/*
		Los dos primeros argumentos son la posición (x,y) del objeto. En el template está fijo como 400 y 300, pero
		cuando se trabaje con el engine, se debe usar las posiciones calculadas para el body del robot.
		Los dos últimos argumentos son las dimensiones del destination rectangle. El robot se dibujará con dimensiones
		64px x 64px. Debes cambiar esto a tu gusto.
	*/
	robot->update(400, 300, 64, 64);
}

void Simulation::render()
{
	SDL_RenderClear(renderer);
	/*
		Es importante hacer el render de los fondos en orden. Si son assets que ocupan toda la pantalla, se debe
		pasar el argumento true. De otra forma se puede dejar vacío.
	*/
	background->render(true);
	robot->render();

	/*
		Recordamos limpiar la ventana para que no suceda el efecto "victoria en solitario".
	*/
	SDL_RenderPresent(renderer);
}

void Simulation::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Simulation cleaned..." << std::endl;
}
