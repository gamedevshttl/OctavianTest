#pragma once

#include <SDL.h>
#include <memory>

class GamblingMachine;

class Application
{
public:
	bool init();
	void run();
	void stop();
private:
	SDL_Window* gWindow = nullptr;
	SDL_Renderer * gRenderer = nullptr;

	std::shared_ptr<GamblingMachine> gamblingMachine;
};

