#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class Simulation
{
public:
	Simulation();
	~Simulation();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

	/*
		Definimos los arreglos para el control del pool event, teclado.
	*/
	static SDL_Event event;

	int keyCounter = 0;

	bool keyDown[4] = { false, false, false, false }; /* 0W 1A 2S 3D */
	bool keyAppliedDown[4] = { false,false,false,false }; /* 0W 1A 2S 3D */
	bool keyAppliedUp[4] = { true,true,true,true }; /* 0W 1A 2S 3D */

private:
	bool isRunning;
	int count = 0;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif /* SIMULATION_H */